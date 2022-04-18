//Программирование в стиле ПЛК версия от 27.03.2022.
//Библиотека LibPlc для gcc детально не протестирована, нет MODBUS.
//Основной алгоритм в FcTaskCyclic1.c
//Ресурсы ПЛК в GlobalVar.h
//Arduino Nano
//Arduino IDE 1.8.13
//Windows 10 pro 64bit
//программатор по умолчанию AVRISP mkll old boot loader
#include <stdint.h>
#include "GlobalVar.h"
#include "M328P_HW.h"
#include "MODBUS.h"
#include "PLC.h"
#include "FcTaskCyclic1.h"

struct Modbus Modbus0 = {0};
struct GlobalVar GV = {0};

int main(void)
{
  GPIO_INIT();
  TIMER1_INIT();
  USART0_INIT();
  Modbus0.SlaveAddress = 1; //Адресс устройства в сети MODBUS ASCII.
  sei(); //All interrupt on.
  GV.Ts_ms = 0             ; //Время предидущего скана ПЛК [мс].
  GV.Ts = 0.0              ; //Время предидущего скана ПЛК [с].
  GV.Reset = true          ; //Флаг первого скана ПЛК.
  PLC_Pulses_1000ms(&GV)   ; //Генератор импульсов для ПЛК, меандр с периодом 1000[мс].
  FcTaskCyclic1()          ;  //Регулятор давления
  while (1)
  {
    PLC_Ts_ms(&GV)                ; //Время предидущего скана ПЛК [мс].
    PLC_Ts(&GV)                   ; //Время предидущего скана ПЛК [с].
    GV.Reset = false              ; //Флаг первого скана ПЛК.
    PLC_Ts_ms_max(&GV)            ; //Максимальное время скана ПЛК [мс].
    PLC_Pulses_1000ms(&GV)        ; //Генератор импульсов для ПЛК, меандр с периодом 1000[мс].
    PLC_Digital_input_cyclic(&GV) ;
    FcTaskCyclic1()               ; //Регулятор давления
    PLC_Digital_output_cyclic(&GV);

    //HMI <-- MW[ 0] <-- PLC (uint32) Uptime_ms
    //HMI <-- MW[ 1] <-- PLC (uint32) Uptime_ms
    //HMI <-- MW[ 2] <-- PLC (uint16) Ts_ms
    //HMI <-- MW[ 3] <-- PLC (uint32) Ts_ms_max
    //HMI <-- MW[ 4] <-- PLC (uint32) Ts_ms_max
    //HMI <-- MW[ 5] <-- PLC (uint16) ErrorCounter
    GV.MW[0] = uint32_to_uint16_register_lo(GV.Uptime_ms);
    GV.MW[1] = uint32_to_uint16_register_hi(GV.Uptime_ms);
    GV.MW[2] = (uint16_t)GV.Ts_ms;
    GV.MW[3] = uint32_to_uint16_register_lo(GV.Ts_ms_max);
    GV.MW[4] = uint32_to_uint16_register_hi(GV.Ts_ms_max);
    GV.MW[5] = Modbus0.ErrorCounter;
  }
}

ISR (USART_RX_vect) //Прерывание USART0 Байт принят.
{
  //MODBUS Receive and processing.
  Modbus0.UDR = USART0_READ_BYTE(); //Читаем байт из USART0;
  FbModbusRxPacketASCII(&Modbus0); //Принимаем ASCII сообщение.
  FbModbusConvertASCIItoPDU(&Modbus0);
  if (Modbus0.State >= MODBUS_STATE_MESSAGE_RECEIVED)
  {
    FbModbusProcessingPDU(&Modbus0, &GV);
    FbModbusConvertPDUtoASCII(&Modbus0);
    if (Modbus0.State == MODBUS_STATE_TX_START)//Transmin one byte, after transmin in interrupt
    {
      USART0_TX_ON();
      USART0_WRITE_BYTE(Modbus0.UDR);
    }
  }
}

ISR (USART_TX_vect) //Прерывание USART0 Байт передан.
{
  FbModbusTxPacketASCII(&Modbus0); //MODBUS response to request.
  USART0_WRITE_BYTE(Modbus0.UDR);
  if (Modbus0.State == MODBUS_STATE_RESET)
  {
    USART0_RX_ON();
  }
}

ISR(TIMER1_COMPA_vect) //Циклическое прерывание каждую 1ms
{
  cli(); //All interrupt off.
  GV.Uptime_ms = GV.Uptime_ms + 1;
  sei(); //All interrupt on.
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
