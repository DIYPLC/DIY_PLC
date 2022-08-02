//Программирование в стиле ПЛК версия от 24.07.2022.
//Библиотека LibPlc.
//В файле FcTaskCyclic1.c Пример ПИД- регулятора давления.
//В файле FcTask100ms.c Пример мигания светодиодом.
//В файле MODBUS.c Сеть MODBUS ASCII SALVE ADR1 RS485 для SCADA/HMI.
//Ресурсы ПЛК в GlobalVar.h
//Arduino Nano (ATmega328p 16MHz 5VDC)
//Arduino IDE 1.8.13
//Windows 10 pro 64bit
//программатор по умолчанию AVRISP mkll old boot loader
#include <stdint.h>
#include "GlobalVar.h" //Глобальные переменные ПЛК.
#include "M328P_HW.h" //Аппаратно зависимые функции ATmega328p 16MHz 5VDC
#include "MODBUS.h" //Сеть MODBUS ASCII SALVE.
#include "PLC.h"
#include "FcTaskCyclic1.h" //Задача выполняется с плавающим временем цикла.
#include "FcTask100ms.h" //Задача выполняется каждые 100ms.

struct Modbus Modbus0 = {0}; //Сеть MODBUS ASCII SALVE.
struct GlobalVar GV = {0}; //Глобальные переменные ПЛК.

// Дерево вызовов.
// 
// int main(void); //PLC_NANO.ino or main.cpp
//   while (1)
//     |
//     +-void FcTaskCyclic1(bool Reset, uint32_t Ts_ms); //FcTaskCyclic1.c
//       |
//       +-void Fb1PIRCA1(struct Db1PIRCA1 *p); //Fb1PIRCA1.c
//         |
//         +-void FbPIDcontrol(struct DbPIDcontrol *p); //FbPIDcontrol.c

int main(void)
{
  GPIO_INIT();
  TIMER1_INIT(); //Настраиваем прерывание каждые 100ms
  TIMER2_INIT(); //Настраиваем прерывание каждые 1ms
  USART0_INIT(); //Инициализация USART0 9600 8N1
  Modbus0.SlaveAddress = 1; //Адресс устройства в сети MODBUS ASCII.
  sei(); //Включить все прерывания.
  Calc_Ts_ms(GV.Uptime_ms); //Время предидущего скана ПЛК [мс].
  FcTaskCyclic1(true, 0); //Задача выполняется с плавающим временем цикла.
  FcTask100ms(true, 0); //Задача выполняется каждые 100ms.
  while (1)
  {
    GV.Ts_ms = Calc_Ts_ms(GV.Uptime_ms); //Время предидущего скана ПЛК [мс].
    GV.Ts_ms_max = Calc_Ts_ms_max(GV.Ts_ms); //Максимальное время скана ПЛК [мс].
    PLC_Digital_input_cyclic(&GV) ;
    FcTaskCyclic1(false, GV.Ts_ms); //Задача выполняется с плавающим временем цикла.
    PLC_Digital_output_cyclic(&GV);
    //Карта регистров MODBUS HOLDING REGISTERS  Slave Address 1
    //HMI <-- MW[ 0] <-- PLC (uint32) Uptime_ms
    //HMI <-- MW[ 1] <-- PLC (uint32) Uptime_ms
    //HMI <-- MW[ 2] <-- PLC (uint16) Ts_ms
    //HMI <-- MW[ 3] <-- PLC (uint32) Ts_ms_max
    //HMI <-- MW[ 4] <-- PLC (uint32) Ts_ms_max
    //HMI <-- MW[ 5] <-- PLC (uint16) ErrorCounter
    //HMI --> MW[ 6] --> PLC (uint16) HmiSetpoint
    //HMI --> MW[ 7] --> PLC (uint16) HmiControlSignalManual
    //HMI --> MW[ 8] --> PLC (uint16) HmiControlWord
    //HMI <-- MW[ 9] <-- PLC (uint16) HmiProcessVariable
    //HMI <-- MW[10] <-- PLC (uint16) HmiControlSignal
    //HMI <-- MW[11] <-- PLC (uint16) HmiStatusWord
    //HMI <-- MW[12] <-- PLC (uint16) HmiErrorWord
    GV.MW[0] = uint32_to_uint16_register_lo(GV.Uptime_ms);
    GV.MW[1] = uint32_to_uint16_register_hi(GV.Uptime_ms);
    GV.MW[2] = (uint16_t)GV.Ts_ms;
    GV.MW[3] = uint32_to_uint16_register_lo(GV.Ts_ms_max);
    GV.MW[4] = uint32_to_uint16_register_hi(GV.Ts_ms_max);
    GV.MW[5] = Modbus0.ErrorCounter;
  }
}

ISR(TIMER2_COMPA_vect) //Циклическое прерывание каждую 1ms
{
  cli(); //Выключить все прерывания.
  GV.Uptime_ms = GV.Uptime_ms + 1;
  sei(); //Включить все прерывания.
}

ISR(TIMER1_COMPA_vect) //Циклическое прерывание каждые 100ms
{
  FcTask100ms(false, 100); //Задача выполняется каждые 100ms.
}

ISR (USART_RX_vect) //Прерывание USART0 Байт принят.
{
  //MODBUS Receive and processing.
  Modbus0.UDR = USART0_READ_BYTE(); //Читаем байт из USART0
  FbModbusRxPacketASCII(&Modbus0); //Принимаем ASCII сообщение.
  FbModbusConvertASCIItoPDU(&Modbus0);
  if (Modbus0.State >= MODBUS_STATE_MESSAGE_RECEIVED)
  {
    FbModbusProcessingPDU(&Modbus0, &GV);
    FbModbusConvertPDUtoASCII(&Modbus0);
    if (Modbus0.State == MODBUS_STATE_TX_START)//Transmin one byte, after transmin in interrupt
    {
      USART0_TX_ON(); //Включаем передатчик
      USART0_WRITE_BYTE(Modbus0.UDR); //Пишем байт в USART0
    }
  }
}

ISR (USART_TX_vect) //Прерывание USART0 Байт передан.
{
  FbModbusTxPacketASCII(&Modbus0); //MODBUS response to request.
  USART0_WRITE_BYTE(Modbus0.UDR); //Пишем байт в USART0
  if (Modbus0.State == MODBUS_STATE_RESET)
  {
    USART0_RX_ON(); //Включаем приемник
  }
}

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
