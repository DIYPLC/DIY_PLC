//Программирование в стиле ПЛК версия от 27.03.2022.
//Библиотека LibPlc для gcc детально не протестирована, нет MODBUS.
//Основной алгоритм в FcTaskCyclic1.c
//Ресурсы ПЛК в GlobalVar.h
//Arduino Nano
//Arduino IDE 1.8.13
//Windows 10 pro 64bit
#include <stdint.h>
#include "GlobalVar.h"
#include "PLC.h"
#include "FcTaskCyclic1.h"
//#include "FcTaskCyclic2.h"

struct GlobalVar GV = {0};

void Plotter_UART(float line1, float line2)
{
  Serial.print(line1);
  Serial.print(',');
  Serial.println(line2);
  return;
}

void Plotter_UART_init(void)
{
  Serial.begin(9600);
  Serial.println("line1, line2");
}

void setup()
{
  Plotter_UART_init()      ;
  GV.Uptime_ms = millis()  ; //Время работы ПЛК [мс].
  GV.Ts_ms = 0             ; //Время предидущего скана ПЛК [мс].
  GV.Ts = 0.0              ; //Время предидущего скана ПЛК [с].
  GV.Reset = true          ; //Флаг первого скана ПЛК.
  PLC_Pulses_1000ms(&GV)   ; //Генератор импульсов для ПЛК, меандр с периодом 1000[мс].
  FcTaskCyclic1()          ;
  //FcTaskCyclic2()        ;
  PLC_Digital_output_init();
}

void loop()
{
  GV.Uptime_ms = millis()       ; //Время работы ПЛК [мс].
  PLC_Ts_ms(&GV)                ; //Время предидущего скана ПЛК [мс].
  PLC_Ts(&GV)                   ; //Время предидущего скана ПЛК [с].
  GV.Reset = false              ; //Флаг первого скана ПЛК.
  PLC_Ts_ms_max(&GV)            ; //Максимальное время скана ПЛК [мс].
  PLC_Pulses_1000ms(&GV)        ; //Генератор импульсов для ПЛК, меандр с периодом 1000[мс].
  PLC_Digital_input_cyclic(&GV) ;
  FcTaskCyclic1()               ; //Регулятор давления
  //FcTaskCyclic2()             ; //тест компиляции LibPlc
  PLC_Digital_output_cyclic(&GV);
  Plotter_UART(GV.tmp_floats[0], GV.tmp_floats[1]);
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
