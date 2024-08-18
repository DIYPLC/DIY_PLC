// Программирование в стиле ПЛК версия от 18.08.2024.
// Библиотека LIB_PLC.
// В файле MODBUS.c Сеть MODBUS RTU SALVE ADR1 RS485 для SCADA/HMI.
// Ресурсы ПЛК в GlobalVar.h
// Arduino Nano (ATmega328p 16MHz 5VDC)
// Arduino IDE 1.8.13
// Windows 10 pro 64bit
// Программатор по умолчанию AVRISP mkll old boot loader

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>
#include "GlobalVar.h" // Глобальные переменные ПЛК.
#include "M328P_HW.h" // Аппаратно зависимые функции ATmega328p 16MHz 5VDC
#include "FcTaskCyclic.h" // Задача выполняется с плавающим временем цикла.
#include "MODBUS.h" // MODBUS RTU SALVE.
#include "FbTs.h"

#define SetBit(Var,Bit)   ( (Var) = (Var) |  (1 << (Bit)) )
#define ResetBit(Var,Bit) ( (Var) = (Var) & ~(1 << (Bit)) )
#define MW GV.MW

struct GlobalVar GV = {0}; //Глобальные переменные ПЛК.
static struct DbTs DbTs1 = { 0 };
static uint16_t usRegHoldingStart = REG_HOLDING_START;
static uint16_t usRegHoldingBuf[REG_HOLDING_NREGS];

int main(void)
{
  GPIO_INIT();
  TIMER2_INIT(); //Настраиваем прерывание каждые 1ms.

  eMBInit(1, 0, 9600, MB_PAR_NONE);  // MODBUS RTU SLAVE ADDRESS 1, USART0 9600 8N1.
  sei(); //Включить все прерывания.
  eMBEnable();
  usRegHoldingBuf[1] = -3; // HOLDING REGISTER 1 int16
  usRegHoldingBuf[2] = -2; // HOLDING REGISTER 2 int16

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

    (void)eMBPoll();
    usRegHoldingBuf[0] = (uint16_t)GV.Uptime_s; // HOLDING REGISTER 0 int16
    usRegHoldingBuf[3] = usRegHoldingBuf[2] + usRegHoldingBuf[1]; // HOLDING REGISTER 3 int16

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

eMBErrorCode eMBRegHoldingCB(uint8_t* pucRegBuffer, uint16_t usAddress, uint16_t usNRegs, eMBRegisterMode eMode) {
  eMBErrorCode eStatus = MB_ENOERR;
  int iRegIndex;
  if ((usAddress >= REG_HOLDING_START) && (usAddress + usNRegs <= REG_HOLDING_START + REG_HOLDING_NREGS)) {
    iRegIndex = (int)(usAddress - usRegHoldingStart);
    switch (eMode) {
      case MB_REG_READ:
        while (usNRegs > 0) {
          *pucRegBuffer++ = (uint8_t)(usRegHoldingBuf[iRegIndex] >> 8);
          *pucRegBuffer++ = (uint8_t)(usRegHoldingBuf[iRegIndex] & 0xFF);
          iRegIndex++;
          usNRegs--;
        }
        break;
      case MB_REG_WRITE:
        while (usNRegs > 0) {
          usRegHoldingBuf[iRegIndex] = *pucRegBuffer++ << 8;
          usRegHoldingBuf[iRegIndex] |= *pucRegBuffer++;
          iRegIndex++;
          usNRegs--;
        }
        break;
    }
  } else {
    eStatus = MB_ENOREG;
  }
  return eStatus;
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
