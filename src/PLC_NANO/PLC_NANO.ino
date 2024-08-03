//Программирование в стиле ПЛК версия от 23.09.2023.
//Библиотека LibPlc.
//В файле FcTask100ms.c Пример мигания светодиодом.
//В файле MODBUS.c Сеть MODBUS ASCII SALVE ADR1 RS485 для SCADA/HMI.
//Ресурсы ПЛК в GlobalVar.h
//Arduino Nano (ATmega328p 16MHz 5VDC)
//Arduino IDE 1.8.13
//Windows 10 pro 64bit
//программатор по умолчанию AVRISP mkll old boot loader
#include <stdint.h>
#include <stdbool.h>
#include <iso646.h>
#include <math.h>
#include <avr/interrupt.h>
#include "GlobalVar.h" //Глобальные переменные ПЛК.
#include "M328P_HW.h" //Аппаратно зависимые функции ATmega328p 16MHz 5VDC
#include "MODBUS.h" //Сеть MODBUS ASCII SALVE.
#include "FcTaskCyclic.h" //Задача выполняется с плавающим временем цикла.
#include "FcTask100ms.h" //Задача выполняется каждые 100ms.
#include "FbTs.h"
#include "FbBlink.h"
#include "FbFilterA.h"

#define F_CPU 16000000UL
#define SetBit(Var,Bit)   ( (Var) = (Var) |  (1 << (Bit)) )
#define ResetBit(Var,Bit) ( (Var) = (Var) & ~(1 << (Bit)) )
#define MW GV.MW

struct Modbus Modbus0 = {0}; //Сеть MODBUS ASCII SALVE.
struct GlobalVar GV = {0}; //Глобальные переменные ПЛК.
static struct DbTs DbTs1 = { 0 };
static struct DbBlink DbBlink1 = { 0 };
static struct DbFilterA DbFilterA1 = { 0 };

int main(void)
{
  GPIO_INIT();
  TIMER1_INIT(); //Настраиваем прерывание каждые 100ms
  TIMER2_INIT(); //Настраиваем прерывание каждые 1ms
  USART0_INIT(); //Инициализация USART0 9600 8N1
  Modbus0.SlaveAddress = 1; //Адресс устройства в сети MODBUS ASCII.
  sei(); //Включить все прерывания.

  GV.Reset = true;
  //Расчет времени скана.
  //             DbTs
  //    +---------------------+
  //    |        FbTs         |
  //   -|millis          Ts_ms|->-
  //   -|Reset              Ts|->-
  //    |            Ts_ms_max|->-
  //    |             Uptime_s|->-
  //    +---------------------+
  DbTs1.millis = GV.millis_ms   ; //millis() Arduino.
  DbTs1.Reset  = GV.Reset       ; //Сброс при перезагрузке.
  FbTs(&DbTs1)                  ; //Расчет времени скана.
  GV.Ts_ms     = DbTs1.Ts_ms    ; //Шаг дискретизации по времени [мс].
  GV.Ts        = DbTs1.Ts       ; //Шаг дискретизации по времени [с].
  GV.Ts_ms_max = DbTs1.Ts_ms_max; //Максимальное время скана [мс].
  GV.Uptime_s  = DbTs1.Uptime_s ; //Время в работе [мс].

  FcTaskCyclic(GV.Reset, GV.Ts_ms); //Задача выполняется с плавающим временем цикла.
  FcTask100ms(true, 0)            ; //Задача выполняется каждые 100ms.

  while (1)
  {
    PLC_Digital_input_cyclic(&GV) ;

    GV.Reset = false;
    //Расчет времени скана.
    //             DbTs
    //    +---------------------+
    //    |        FbTs         |
    //   -|millis          Ts_ms|->-
    //   -|Reset              Ts|->-
    //    |            Ts_ms_max|->-
    //    |             Uptime_s|->-
    //    +---------------------+
    DbTs1.millis = GV.millis_ms   ; //millis() Arduino.
    DbTs1.Reset  = GV.Reset       ; //Сброс при перезагрузке.
    FbTs(&DbTs1)                  ; //Расчет времени скана.
    GV.Ts_ms     = DbTs1.Ts_ms    ; //Шаг дискретизации по времени [мс].
    GV.Ts        = DbTs1.Ts       ; //Шаг дискретизации по времени [с].
    GV.Ts_ms_max = DbTs1.Ts_ms_max; //Максимальное время скана [мс].
    GV.Uptime_s  = DbTs1.Uptime_s ; //Время в работе [мс].

    FcTaskCyclic(GV.Reset, GV.Ts_ms); //Задача выполняется с плавающим временем цикла.

    PLC_Digital_output_cyclic(&GV);
  }
}

ISR(TIMER2_COMPA_vect) //Циклическое прерывание каждую 1ms
{
  cli(); //Выключить все прерывания.
  GV.millis_ms = GV.millis_ms + 1; //Аналог Arduino millis();
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
//
// https://www.youtube.com/@DIY_PLC
// https://github.com/DIYPLC
