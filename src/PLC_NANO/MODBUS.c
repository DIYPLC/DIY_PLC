//MODBUS ASCII Slave adr1.
//RS485 9600 8N1
//Младшим битом вперед.
//Младшим ASCII байтом вперед.
//MODBUS Class 0 поддерживает минимальный набор функций 3,16.
//read multiple registers FC 3
//write multiple registers FC 16 (0x10)
//Протестированно программой insat.ru MasterOPC Universal Modbus Server

#include <stdint.h>
#include <stdbool.h>
#include <iso646.h>
#include "GlobalVar.h" //Глобальные переменные ПЛК.
#include "MODBUS.h"

#define SlaveAddress p->SlaveAddress
#define Counter1     p->Counter1
#define Counter2     p->Counter2
#define Counter3     p->Counter3
#define Counter4     p->Counter4
#define State        p->State
#define UDR          p->UDR
#define Buffer1      p->Buffer1
#define Buffer2      p->Buffer2
#define Buffer3      p->Buffer3
#define ErrorCounter p->ErrorCounter

#define SIZE_BUFFER_1 sizeof(Buffer1)
#define SIZE_BUFFER_2 sizeof(Buffer2)
#define SIZE_BUFFER_3 sizeof(Buffer3)

//MODBUS_FUNCTION_CODES
#define FUN_READ_HOLDING_REGISTERS           0x03 //3
#define FUN_WRITE_MULTIPLE_HOLDING_REGISTERS 0x10 //16
//#define FUN_WRITE_SINGLE_REGISTER            0x06 //6 //в разработке
//MODBUS_ERROR_CODES
#define ERROR_ILLEGAL_FUNCTION     0x01
#define ERROR_ILLEGAL_DATA_ADDRESS 0x02
//ASCII TABLE
#define START_BYTE 0x3A //ASCII ":"
#define STOP1_BYTE 0x0D //ASCII "CR"
#define STOP2_BYTE 0x0A //ASCII "LF"

uint16_t TwoByteToWord(uint8_t ByteLo, uint8_t ByteHi);
uint8_t  WordToByteLo(uint16_t InputWord);
uint8_t  WordToByteHi(uint16_t InputWord);
uint8_t  Lo4BitInByteToASCII(uint8_t InputByte);
uint8_t  Hi4BitInByteToASCII(uint8_t InputByte);
uint8_t  TwoASCIItoByte(uint8_t LoASCII, uint8_t HiASCII);
//uint16_t Limit(uint16_t In, uint16_t Max, uint16_t Min);

/****************************************************************************************/

void FbModbusRxPacketASCII(struct Modbus *p) //Принимаем ASCII сообщение.
{
  //Прием пакета MODBUS ASCII.
  switch (State)
  {
    case MODBUS_STATE_RESET: //Ждем стартовый байт.
      {
        //Ожидание байта начала пакета.
        if (UDR == START_BYTE)
        {
          Buffer1[0] = UDR;
          State = MODBUS_STATE_RECEIVING_MESSAGE;
          Counter1 = 1;
        }
        break;
      }
    case MODBUS_STATE_RECEIVING_MESSAGE: //Принимаем ASCII сообщение.
      {
        //Если во время приема сообщения пришел стартовый байт значит что то пошло не так.
        //Если во время приема сообщения произошло переполнение буфера.
        if ((UDR == START_BYTE) or (Counter1 >= (SIZE_BUFFER_1 - 1)))
        {
          State = MODBUS_STATE_RESET;
          ErrorCounter++;
          //Если во время приема сообщения принят стартовый байт то данная несштатная ситуация отработается правильно.
          if ((UDR == START_BYTE))
          {
            Buffer1[0] = UDR;
            State = MODBUS_STATE_RECEIVING_MESSAGE;
            Counter1 = 1;
          }
        }
        else
        {
          //Если последний принятый байт LF предпоследний CR то сообщение принято.
          Buffer1[Counter1] = UDR;
          Counter1 = Counter1 + 1; //Количество байт в принятом сообщении.
          if ((Buffer1[Counter1] == STOP2_BYTE) and (Buffer1[Counter1 - 1] == STOP1_BYTE))
          {
            State = MODBUS_STATE_MESSAGE_RECEIVED; //Пакет принят.
          }
        }
        break;
      }
  }
}

/****************************************************************************************/

void FbModbusConvertASCIItoPDU(struct Modbus *p)
{

  //Проверка корректности принятого сообщения.
  if (State == MODBUS_STATE_MESSAGE_RECEIVED) //ASCII сообщение принято.
  {
    //В принятом пакете должно быть нечетное количество байт.
    //Следовательно в счетчике должно быть чило четное.
    //Так же количество байт в принятом пакете должно быть не менее 9
    if (((Counter1 & 0x01) == 0x00) and (Counter1 >= 9))
    {

      State = MODBUS_STATE_MESSAGE_VERIFIED; //Принятое сообщение проверенно на корректность.
    }
    else
    {
      State = MODBUS_STATE_RESET;
      ErrorCounter++;
    }
  }

  if (State == MODBUS_STATE_MESSAGE_VERIFIED) //Принятое сообщение проверенно на корректность.
  {
    //Преобразование ASCII пакета в пакет HEX.
    for (unsigned int i = 1; (i <= (Counter1 - 3)); i = i + 2)
    {
      Counter2 = (i - 1) / 2;
      Buffer2[Counter2] = TwoASCIItoByte(Buffer1[i + 1], Buffer1[i]);
    }
    State = MODBUS_STATE_CONVERT_ASII_TO_HEX; //Принятое сообщение преобразованно из формата ASCII в HEX.
  }

  if (State == MODBUS_STATE_CONVERT_ASII_TO_HEX) //Принятое сообщение преобразованно из формата ASCII в HEX.
  {
    //Рассчет и проверка контрольной суммы LRC.
    uint16_t TmpSum = 0;
    for (uint16_t i = 0; (i <= (Counter2 - 1)); i = i + 1)
    {
      TmpSum = (0xFF & (TmpSum +  (uint16_t)Buffer2[i]));
    }
    uint8_t LCR = (uint8_t)(((~ TmpSum) + 1) & 0xFF);
    if (LCR == Buffer2[Counter2])
    {
      State = MODBUS_STATE_LCR_VERIFIED; //Контрольная сумма верная.
    }
    else
    {
      State = MODBUS_STATE_RESET;
      ErrorCounter++;
    }
  }

  //Проверка адреса MODBUS.
  if (State == MODBUS_STATE_LCR_VERIFIED) //Контрольная сумма в принятом сообщении корректная.
  {
    if (SlaveAddress == Buffer2[0])
    {
      State = MODBUS_STATE_ADR_VERIFIED; //Адресс сходится.
    }
    else
    {
      State = MODBUS_STATE_RESET;
    }
  }
  //Достаем из буфера 2 PDU.
  if (State == MODBUS_STATE_ADR_VERIFIED)
  {
    for (uint16_t i = 1; (i <= (Counter2 - 1)); i = i + 1)
    {
      Counter3 = i - 1;
      Buffer3[Counter3] = Buffer2[i];
    }
    State = MODBUS_STATE_READ_PDU;
  }
}

/****************************************************************************************/

void FbModbusProcessingPDU(struct Modbus *p, struct GlobalVar *ptr)
{
  //Количество 16 битных регистров MODBUS 32слова 64байта MW[0]...MW31.
  const uint16_t SIZE_MODBUS_REGISTER = (sizeof(ptr->MW) / 2);
  //Декодирование PDU.
  uint8_t CurrentModbusFunction = Buffer3[0];
  uint16_t StartingAddress = 0;
  uint16_t EndingAddress = 0;
  uint16_t QuantityOfRegister = 0;
  uint16_t ByteCounter = 0;
  //Селектрор функций.
  if (State == MODBUS_STATE_READ_PDU)
  {
    State = MODBUS_STATE_FUN_ERROR; //Сообщение об ошибке.
    if (CurrentModbusFunction == FUN_READ_HOLDING_REGISTERS)
    {
      State = MODBUS_STATE_FUN_READ_HOLDING_REGISTERS; //Функция 3 MODBUS.
    }
    if (CurrentModbusFunction == FUN_WRITE_MULTIPLE_HOLDING_REGISTERS)
    {
      State = MODBUS_STATE_FUN_WRITE_MULTIPLE_HOLDING_REGISTERS; //Функция 16 MODBUS.
    }
  }
  //Реализация функций MODBUS.
  switch (State)
  {
    //Сообщение об ошибке.
    case MODBUS_STATE_FUN_ERROR:
      {
        Buffer3[0] = CurrentModbusFunction;
        Buffer3[1] = ERROR_ILLEGAL_FUNCTION;
        Counter3 = 1;
        State = MODBUS_STATE_PDU_PROCESSING_OK;
        ErrorCounter++;
        break;
      }
    //Функция 3 MODBUS.
    case MODBUS_STATE_FUN_READ_HOLDING_REGISTERS:
      {
        StartingAddress = TwoByteToWord(Buffer3[2], Buffer3[1]);
        QuantityOfRegister = TwoByteToWord(Buffer3[4], Buffer3[3]);
        EndingAddress = StartingAddress + (QuantityOfRegister - 1);
        ByteCounter = QuantityOfRegister * 2;
        if (
          ((StartingAddress > (SIZE_MODBUS_REGISTER - 1)) and (EndingAddress > (SIZE_MODBUS_REGISTER - 1))) or
          (QuantityOfRegister > (SIZE_MODBUS_REGISTER - 1))
        )
        {
          //Запрошен адресс регистра которого нет.
          Buffer3[0] = CurrentModbusFunction;
          Buffer3[1] = ERROR_ILLEGAL_DATA_ADDRESS; //ILLEGAL DATA ADDRESS
          Counter3 = 1;
          ErrorCounter++;
        }
        else
        {
          //Формирование ответа на запрос.
          Buffer3[0] = CurrentModbusFunction;
          Buffer3[1] = (uint8_t)ByteCounter;
          for (uint16_t i = 1; (i <= ByteCounter); i = i + 2)
          {
            Buffer3[i + 1] = WordToByteHi(ptr->MW[StartingAddress + ((i - 1) / 2)]);
            Buffer3[i + 2] = WordToByteLo(ptr->MW[StartingAddress + ((i - 1) / 2)]);
          }
          Counter3 = (uint8_t)(ByteCounter + 1);
        }
        State = MODBUS_STATE_PDU_PROCESSING_OK;
        break;
      }
    //Функция 16 MODBUS.
    case MODBUS_STATE_FUN_WRITE_MULTIPLE_HOLDING_REGISTERS:
      {
        StartingAddress = TwoByteToWord(Buffer3[2], Buffer3[1]);
        QuantityOfRegister = TwoByteToWord(Buffer3[4], Buffer3[3]);
        EndingAddress = StartingAddress + (QuantityOfRegister - 1);
        ByteCounter = QuantityOfRegister * 2;
        if (
          (
            (StartingAddress > (SIZE_MODBUS_REGISTER - 1))
            and (EndingAddress > (SIZE_MODBUS_REGISTER - 1))
          )
          or (QuantityOfRegister > (SIZE_MODBUS_REGISTER - 1))
          or (ByteCounter != ((uint16_t)Buffer3[5]))
        )
        {
          //Запрошен адресс регистра которого нет.
          Buffer3[0] = CurrentModbusFunction;
          Buffer3[1] = ERROR_ILLEGAL_DATA_ADDRESS; //ILLEGAL DATA ADDRESS
          Counter3 = 1;
          ErrorCounter++;
        }
        else
        {
          //В качестве ответа используем часть запроса.
          Counter3 = 4;
          //Запись значений в регистры MODBUS.
          for (uint16_t i = 0; (i < QuantityOfRegister); i = i + 1)
          {
            ptr->MW[StartingAddress + i] =
              TwoByteToWord
              (
                Buffer3[i * 2 + 7], //Младший.
                Buffer3[i * 2 + 6] //Старший.
              );
          }
        }
        State = MODBUS_STATE_PDU_PROCESSING_OK;
        break;
      }
  }
}

/****************************************************************************************/

void FbModbusConvertPDUtoASCII(struct Modbus *p)
{
  //Добавляем к PDU адресс MODBUS.
  if (State == MODBUS_STATE_PDU_PROCESSING_OK)
  {
    Buffer2[0] = SlaveAddress;
    for (uint16_t i = 0; (i <= Counter3); i = i + 1)
    {
      Counter2 = i + 1;
      Buffer2[Counter2] = Buffer3[i];
    }
    State = MODBUS_STATE_PDU_ADD_ADR;
  }

  //Добавляем к PDU контрольную сумму LRC.
  if (State == MODBUS_STATE_PDU_ADD_ADR)
  {
    uint16_t TmpSum = 0;
    for (uint16_t i = 0; (i <= Counter2); i = i + 1)
    {
      TmpSum = (0xFF & (TmpSum +  (uint16_t)Buffer2[i]));
    }
    uint8_t LCR = (uint8_t)(((~ TmpSum) + 1) & 0xFF);
    Counter2 = Counter2 + 1;
    Buffer2[Counter2] = LCR;
    State = MODBUS_STATE_PDU_ADD_LCR;
  }

  //Преобразование HEX пакета в пакет ASCII.
  if (State == MODBUS_STATE_PDU_ADD_LCR)
  {
    //Добавляем символ начала пакета.
    Buffer1[0] = START_BYTE;
    for (uint16_t i = 0; (i <= Counter2); i = i + 1)
    {
      Counter1 = ((i * 2) + 1);
      Buffer1[Counter1] = Hi4BitInByteToASCII(Buffer2[i]);
      Buffer1[Counter1 + 1] = Lo4BitInByteToASCII(Buffer2[i]);
    }
    //Добавляем символы конца пакета.
    Counter1 = Counter1 + 2;
    Buffer1[Counter1] = STOP1_BYTE; //cr
    Counter1 = Counter1 + 1;
    Buffer1[Counter1] = STOP2_BYTE; //lf
    Counter1 = Counter1 + 1; // ЧТО ЗА ХЕРНЯ !!!!!!!!!
    State = MODBUS_STATE_PDU_ADD_START_STOP_BYTES;
  }
  //Передаем первый байт ответного пакета, осталные передадуться по прерыванию.
  if (State == MODBUS_STATE_PDU_ADD_START_STOP_BYTES)
  {
    UDR = Buffer1[0];
    State = MODBUS_STATE_TX_START;
  }
}

/****************************************************************************************/

void FbModbusTxPacketASCII(struct Modbus *p)
{
  //Первый символ ответного пакета передан.
  if (State == MODBUS_STATE_TX_START)
  {
    Counter4 = Counter4 + 1;
    UDR = Buffer1[Counter4];
    if (Counter4 >= Counter1)
    {
      State = MODBUS_STATE_TX_STOP;
    }
  }
  //Последний символ ответного пакета передан.
  if (State == MODBUS_STATE_TX_STOP)
  {
    State = MODBUS_STATE_RESET;
    Counter1 = 0;
    Counter2 = 0;
    Counter3 = 0;
    Counter4 = 0;

  }
}

/****************************************************************************************/

uint16_t TwoByteToWord(uint8_t ByteLo, uint8_t ByteHi)
{
  return ( (((uint16_t)ByteHi) << 8) | ((uint16_t)ByteLo) );
}

uint8_t WordToByteLo(uint16_t InputWord)
{
  return ( (uint8_t)(InputWord & 0xFF) );
}

uint8_t WordToByteHi(uint16_t InputWord)
{
  return ( (uint8_t)((InputWord & 0xFF00) >> 8) );
}

/****************************************************************************************/

uint8_t Lo4BitInByteToASCII(uint8_t InputByte)
{
  uint8_t result;
  switch (InputByte & 0x0F)
  {
    case 0x00 : result = 0x30; break;
    case 0x01 : result = 0x31; break;
    case 0x02 : result = 0x32; break;
    case 0x03 : result = 0x33; break;
    case 0x04 : result = 0x34; break;
    case 0x05 : result = 0x35; break;
    case 0x06 : result = 0x36; break;
    case 0x07 : result = 0x37; break;
    case 0x08 : result = 0x38; break;
    case 0x09 : result = 0x39; break;
    case 0x0A : result = 0x41; break;
    case 0x0B : result = 0x42; break;
    case 0x0C : result = 0x43; break;
    case 0x0D : result = 0x44; break;
    case 0x0E : result = 0x45; break;
    case 0x0F : result = 0x46; break;
    default   : result = 0x00; break;
  }
  return result;
}

uint8_t Hi4BitInByteToASCII(uint8_t InputByte)
{
  uint8_t result;
  switch (InputByte & 0xF0)
  {
    case 0x00 : result = 0x30; break;
    case 0x10 : result = 0x31; break;
    case 0x20 : result = 0x32; break;
    case 0x30 : result = 0x33; break;
    case 0x40 : result = 0x34; break;
    case 0x50 : result = 0x35; break;
    case 0x60 : result = 0x36; break;
    case 0x70 : result = 0x37; break;
    case 0x80 : result = 0x38; break;
    case 0x90 : result = 0x39; break;
    case 0xA0 : result = 0x41; break;
    case 0xB0 : result = 0x42; break;
    case 0xC0 : result = 0x43; break;
    case 0xD0 : result = 0x44; break;
    case 0xE0 : result = 0x45; break;
    case 0xF0 : result = 0x46; break;
    default   : result = 0x00; break;
  }
  return result;
}

uint8_t TwoASCIItoByte(uint8_t LoASCII, uint8_t HiASCII)
{
  uint8_t Lo4Bit = 0; //Младшие 4бита.
  uint8_t Hi4Bit = 0; //Старшие 4бита.
  switch (LoASCII)
  {
    case 0x30 : Lo4Bit = 0x00; break;
    case 0x31 : Lo4Bit = 0x01; break;
    case 0x32 : Lo4Bit = 0x02; break;
    case 0x33 : Lo4Bit = 0x03; break;
    case 0x34 : Lo4Bit = 0x04; break;
    case 0x35 : Lo4Bit = 0x05; break;
    case 0x36 : Lo4Bit = 0x06; break;
    case 0x37 : Lo4Bit = 0x07; break;
    case 0x38 : Lo4Bit = 0x08; break;
    case 0x39 : Lo4Bit = 0x09; break;
    case 0x41 : Lo4Bit = 0x0A; break;
    case 0x42 : Lo4Bit = 0x0B; break;
    case 0x43 : Lo4Bit = 0x0C; break;
    case 0x44 : Lo4Bit = 0x0D; break;
    case 0x45 : Lo4Bit = 0x0E; break;
    case 0x46 : Lo4Bit = 0x0F; break;
    default   : Lo4Bit = 0x00; break;
  }
  switch (HiASCII)
  {
    case 0x30 : Hi4Bit = 0x00; break;
    case 0x31 : Hi4Bit = 0x10; break;
    case 0x32 : Hi4Bit = 0x20; break;
    case 0x33 : Hi4Bit = 0x30; break;
    case 0x34 : Hi4Bit = 0x40; break;
    case 0x35 : Hi4Bit = 0x50; break;
    case 0x36 : Hi4Bit = 0x60; break;
    case 0x37 : Hi4Bit = 0x70; break;
    case 0x38 : Hi4Bit = 0x80; break;
    case 0x39 : Hi4Bit = 0x90; break;
    case 0x41 : Hi4Bit = 0xA0; break;
    case 0x42 : Hi4Bit = 0xB0; break;
    case 0x43 : Hi4Bit = 0xC0; break;
    case 0x44 : Hi4Bit = 0xD0; break;
    case 0x45 : Hi4Bit = 0xE0; break;
    case 0x46 : Hi4Bit = 0xF0; break;
    default   : Hi4Bit = 0x00; break;
  }
  return (Lo4Bit | Hi4Bit);
}

/*
  uint16_t Limit(uint16_t In, uint16_t Max, uint16_t Min)
  {
  uint16_t Out = 0;
  if (In >= Max) {
    Out = Max;
  } else {
    if (In <= Min) {
      Out = Min;
    } else {
      Out = In;
    }
  }
  return Out;
  }
*/

/****************************************************************************************/

int16_t  uint16_to_int16(uint16_t In) //MODBUS поддержка int16
{
  union {
    uint16_t uint16;
    int16_t int16;
  } Convertor;
  Convertor.uint16 = In;
  return Convertor.int16;
}

uint16_t int16_to_uint16(int16_t  In) //MODBUS поддержка int16
{
  union {
    uint16_t uint16;
    int16_t int16;
  } Convertor;
  Convertor.int16 = In;
  return Convertor.uint16;
}

/****************************************************************************************/

float two_uint16_to_float32(uint16_t InRegisterLo, uint16_t InRegisterHi) //MODBUS поддержка float32
{
  union {
    uint16_t uint16[2];
    float float32;
  } Convertor;
  Convertor.uint16[1] = InRegisterHi;
  Convertor.uint16[0] = InRegisterLo;
  return Convertor.float32;
}

uint16_t float32_to_uint16_register_lo(float In) //MODBUS поддержка float32
{
  union {
    uint16_t uint16[2];
    float float32;
  } Convertor;
  Convertor.float32 = In;
  return Convertor.uint16[0];
}

uint16_t float32_to_uint16_register_hi(float In) //MODBUS поддержка float32
{
  union {
    uint16_t uint16[2];
    float float32;
  } Convertor;
  Convertor.float32 = In;
  return Convertor.uint16[1];
}

/****************************************************************************************/

uint32_t two_uint16_to_uint32(uint16_t InRegisterLo, uint16_t InRegisterHi) //MODBUS поддержка uint32
{
  union {
    uint16_t uint16[2];
    uint32_t uint32;
  } Convertor;
  Convertor.uint16[1] = InRegisterHi;
  Convertor.uint16[0] = InRegisterLo;
  return Convertor.uint32;
}

uint16_t uint32_to_uint16_register_lo(uint32_t In) //MODBUS поддержка uint32
{
  union {
    uint16_t uint16[2];
    uint32_t uint32;
  } Convertor;
  Convertor.uint32 = In;
  return Convertor.uint16[0];
}

uint16_t uint32_to_uint16_register_hi(uint32_t In) //MODBUS поддержка uint32
{
  union {
    uint16_t uint16[2];
    uint32_t uint32;
  } Convertor;
  Convertor.uint32 = In;
  return Convertor.uint16[1];
}

/****************************************************************************************/

int32_t two_uint16_to_int32(uint16_t InRegisterLo, uint16_t InRegisterHi) //MODBUS поддержка int32
{
  union {
    uint16_t uint16[2];
    uint32_t int32;
  } Convertor;
  Convertor.uint16[1] = InRegisterHi;
  Convertor.uint16[0] = InRegisterLo;
  return Convertor.int32;
}

uint16_t int32_to_uint16_register_lo(int32_t In) //MODBUS поддержка int32
{
  union {
    uint16_t uint16[2];
    uint32_t int32;
  } Convertor;
  Convertor.int32 = In;
  return Convertor.uint16[0];
}

uint16_t int32_to_uint16_register_hi(int32_t In) //MODBUS поддержка int32
{
  union {
    uint16_t uint16[2];
    uint32_t int32;
  } Convertor;
  Convertor.int32 = In;
  return Convertor.uint16[1];
}

/****************************************************************************************/

//READ HOLDING REGISTERS
//Example MODBUS ASCII request:
//     |-ADU--------------------------------------------| (ADU = Application Data Unit)
//                 |-PDU--------------------|             (PDU = Protocol Data Unit)
//HMI: 3A 30 31 30 33 30 30 30 32 30 30 30 31 46 39 0D 0A //Rx message ASCII HEX
//CNT  01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17
//HMI:  :  0  1  0  3  0  0  0  2  0  0  0  1  F  9 CR LF //Rx message string
//HMI: 3A    01    03    00    02    00    01    F9 0D 0A //Rx message HEX
//      |     |     |     |     |     |     |     |  |  |
//      |     |     |     |     |     |     |     |  |  +- Stop byte LF
//      |     |     |     |     |     |     |     |  +---- Stop byte CR
//      |     |     |     |     |     |     |     +------- Checksum LCR
//      |     |     |     |     |     |     +------------- PDU Register count low byte
//      |     |     |     |     |     +------------------- PDU Register count high byte
//      |     |     |     |     +------------------------- PDU Register start address low byte
//      |     |     |     +------------------------------- PDU Register start address high byte
//      |     |     +------------------------------------- PDU Modbus function code
//      |     +------------------------------------------- Modbus slave address
//      +------------------------------------------------- Start byte ":"
//HMI: 3A    01    03    00    02    00    01    F9 0D 0A //Rx message HEX
//LCR =  not(01 +  03 +  00 +  02 +  00 +  01)+1=F9
//
//Example MODBUS ASCII response:
//     |-ADU--------------------------------------| (ADU = Application Data Unit)
//                 |-PDU--------------|             (PDU = Protocol Data Unit)
//PLC: 3A 30 31 30 33 30 32 30 30 30 30 46 41 0D 0A //Tx message ASCII HEX
//CNT  01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
//PLC:  :  0  1  0  3  0  2  0  0  0  0  F  A CR LF //Tx message ASCII string
//PLC: 3A    01    03    02    00    00    FA 0D 0A //Tx message ASCII HEX
//      |     |     |     |     |     |     |  |  |
//      |     |     |     |     |     |     |  |  +- Stop byte LF
//      |     |     |     |     |     |     |  +---- Stop byte CR
//      |     |     |     |     |     |     +------- Checksum LCR
//      |     |     |     |     |     +------------- PDU Register value low byte
//      |     |     |     |     +------------------- PDU Register value high byte
//      |     |     |     +------------------------- PDU Byte count (after this)
//      |     |     +------------------------------- PDU Modbus function code
//      |     +------------------------------------- Modbus slave address
//      +------------------------------------------- Start byte ":"
//PLC: 3A    01    03    02    00    00    FA 0D 0A //Tx message ASCII HEX
//LCR =  not(01 +  03 +  02 +  00 +  00)+1=FA

//WRITE MULTIPLE HOLDING REGISTERS
//Example MODBUS ASCII request:
//     |-ADU--------------------------------------------------------------| (ADU = Application Data Unit)
//                 |-PDU--------------------------------------|             (PDU = Protocol Data Unit)
//HMI: 3A 30 31 31 30 30 30 30 32 30 30 30 31 30 32 30 30 30 37 45 33 0D 0A //Rx message ASCII HEX
//CNT  01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23
//HMI:  :  0  1  1  0  0  0  0  2  0  0  0  1  0  2  0  0  0  7  E  3 CR LF
//HMI: 3A    01    10    00    02    00    01    02    00    07    E3 0D 0A //Rx message HEX
//      |     |     |     |     |     |     |     |     |     |     |  |  |
//      |     |     |     |     |     |     |     |     |     |     |  |  +- Stop byte LF
//      |     |     |     |     |     |     |     |     |     |     |  +---- Stop byte CR
//      |     |     |     |     |     |     |     |     |     |     +------- Checksum LCR
//      |     |     |     |     |     |     |     |     |     +------------- PDU Register value low byte
//      |     |     |     |     |     |     |     |     +------------------- PDU Register value high byte
//      |     |     |     |     |     |     |     +------------------------- PDU Byte count (after this)
//      |     |     |     |     |     |     +------------------------------- PDU Number of register low byte
//      |     |     |     |     |     +------------------------------------- PDU Number of register high byte
//      |     |     |     |     +------------------------------------------- PDU Register start address low byte
//      |     |     |     +------------------------------------------------- PDU Register start address high byte
//      |     |     +------------------------------------------------------- PDU Modbus function code
//      |     +------------------------------------------------------------- Modbus slave address
//      +------------------------------------------------------------------- Start byte ":"
//HMI: 3A    01    10    00    02    00    01    02    00    07    E3 0D 0A //Rx message HEX
//LCR =  not(01 +  10 +  00 +  02 +  00 +  01 +  02 +  00 +  07)+1=E3
//
//Example MODBUS ASCII response:
//     |-ADU--------------------------------------------| (ADU = Application Data Unit)
//                 |-PDU--------------------|             (PDU = Protocol Data Unit)
//HMI: 3A 30 31 31 30 30 30 30 32 30 30 30 31 45 43 0D 0A //Rx message ASCII HEX
//CNT  01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17
//HMI:  :  0  1  1  0  0  0  0  2  0  0  0  1  E  C CR LF
//HMI: 3A    01    10    00    02    00    01    EC 0D 0A //Rx message HEX
//      |     |     |     |     |     |     |     |  |  |
//      |     |     |     |     |     |     |     |  |  +- Stop byte LF
//      |     |     |     |     |     |     |     |  +---- Stop byte CR
//      |     |     |     |     |     |     |     +------- Checksum LCR
//      |     |     |     |     |     |     +------------- PDU Number of register low byte
//      |     |     |     |     |     +------------------- PDU Number of register high byte
//      |     |     |     |     +------------------------- PDU Register start address low byte
//      |     |     |     +------------------------------- PDU Register start address high byte
//      |     |     +------------------------------------- PDU Modbus function code
//      |     +------------------------------------------- Modbus slave address
//      +------------------------------------------------- Start byte ":"
//HMI: 3A    01    10    00    02    00    01    EC 0D 0A //Rx message HEX
//LCR =  not(01 +  10 +  00 +  02 +  00 +  01)+1=EC

/****************************************************************************************/

//  +---------+
//  | GNU GPL |
//  +---------+
//  |
//  |
//  .= .-_-. =.
// ((_/)o o(\_))
//  `-'(. .)`-'
//  |/| \_/ |\
//  ( |     | )
//  /"\_____/"\
//  \__)   (__/
// @COPYLEFT ALL WRONGS RESERVED :)
// Author: VA
// Contacts: DIY.PLC.314@gmail.com
// License: GNU GPL v2
