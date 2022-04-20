#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

enum MODBUS_STATES
{
  MODBUS_STATE_RESET                                = 0, //Ждем стартовый байт.
  MODBUS_STATE_RECEIVING_MESSAGE                    = 1, //Принимаем ASCII сообщение.
  MODBUS_STATE_MESSAGE_RECEIVED                     = 2, //ASCII сообщение принято.
  MODBUS_STATE_MESSAGE_VERIFIED                     = 3, //Принятое сообщение проверенно на корректность.
  MODBUS_STATE_CONVERT_ASII_TO_HEX                  = 4, //Принятое сообщение преобразованно из формата ASCII в HEX.
  MODBUS_STATE_LCR_VERIFIED                         = 5, //Контрольная сумма в принятом сообщении корректная.
  MODBUS_STATE_ADR_VERIFIED                         = 6, //Сообщение имеет необходимый MODBUS адрес.
  MODBUS_STATE_READ_PDU                             = 7, //PDU часть сообщения прочитана.
  MODBUS_STATE_FUN_ERROR                            = 8, //MODBUS функция не поддерживается.
  MODBUS_STATE_FUN_READ_HOLDING_REGISTERS           = 9, //MODBUS функция чтение регистров.
  MODBUS_STATE_FUN_WRITE_MULTIPLE_HOLDING_REGISTERS = 10, //MODBUS функция записи регистров.
  MODBUS_STATE_PDU_PROCESSING_OK                    = 11, //PDU сооющение обработанно корректно.
  MODBUS_STATE_PDU_ADD_ADR                          = 12, //Добавили к PDU адресс MODBUS.
  MODBUS_STATE_PDU_ADD_LCR                          = 13, //Добавили к PDU контрольную сумму LCR.
  MODBUS_STATE_PDU_ADD_START_STOP_BYTES             = 14, //Добавили к буферу 1 старт и стоп байты.
  MODBUS_STATE_TX_START                             = 15, //Начать передачу ответного сообщения.
  MODBUS_STATE_TX_STOP                              = 16  //Последний символ ответного пакета передан.
};

struct Modbus
{
  //Структура спроектированна так чтоб можно было обслуживать сразу несколько UART и быть двойным подчиненным.
  uint8_t  SlaveAddress; //Адресс устройства в сети MODBUS ASCII.
  uint16_t Counter1    ; //Адресс последнего элемнта для Buffer1[].
  uint16_t Counter2    ; //Адресс последнего элемнта для Buffer2[].
  uint16_t Counter3    ; //Адресс последнего элемнта для Buffer3[].
  uint16_t Counter4    ; //Счетчик переданных байт для Buffer1[].
  uint8_t  State       ; //Граф состояний.
  uint8_t  UDR         ; //Байт для UART.
  uint8_t  Buffer1[32] ; //Патек в формате ASCII. //rx ascii
  uint8_t  Buffer2[32] ; //Патек в формате HEX. //rx bytes ADU?
  uint8_t  Buffer3[32] ; //Пакет PDU. //rx tx PDU <> MW[]
  uint16_t ErrorCounter; //Счетчик ошибок.
};

void FbModbusRxPacketASCII(struct Modbus *p); //Принимаем ASCII сообщение.
void FbModbusConvertASCIItoPDU(struct Modbus *p);
void FbModbusProcessingPDU(struct Modbus *p, struct GlobalVar *ptr);
void FbModbusConvertPDUtoASCII(struct Modbus *p);
void FbModbusTxPacketASCII(struct Modbus *p);

//MODBUS протокол подразумевает 16 битные целоцисленные регистры для обмена данными.
//Вероятно потому что 16 бит достаточная точность ЦАП / АЦП в промышленности.
//Чтобы передать другие типы данных через целоцисленные регистры MODBUS
//Используйте следующие функции:
int16_t  uint16_to_int16(uint16_t In)                                       ; //MODBUS поддержка int16
uint16_t int16_to_uint16(int16_t  In)                                       ; //MODBUS поддержка int16
float    two_uint16_to_float32(uint16_t InRegisterLo, uint16_t InRegisterHi); //MODBUS поддержка float32
uint16_t float32_to_uint16_register_lo(float In)                            ; //MODBUS поддержка float32
uint16_t float32_to_uint16_register_hi(float In)                            ; //MODBUS поддержка float32
uint32_t two_uint16_to_uint32(uint16_t InRegisterLo, uint16_t InRegisterHi) ; //MODBUS поддержка uint32
uint16_t uint32_to_uint16_register_lo(uint32_t In)                          ; //MODBUS поддержка uint32
uint16_t uint32_to_uint16_register_hi(uint32_t In)                          ; //MODBUS поддержка uint32
int32_t  two_uint16_to_int32(uint16_t InRegisterLo, uint16_t InRegisterHi)  ; //MODBUS поддержка int32
uint16_t int32_to_uint16_register_lo(int32_t In)                            ; //MODBUS поддержка int32
uint16_t int32_to_uint16_register_hi(int32_t In)                            ; //MODBUS поддержка int32

#ifdef __cplusplus
}
#endif
