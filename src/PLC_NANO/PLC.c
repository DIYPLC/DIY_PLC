#include <stdint.h>
#include <stdbool.h>
#include <iso646.h>
#include "PLC.h"

uint32_t Calc_Ts_ms(uint32_t Uptime_ms) //Время предидущего скана ПЛК [мс].
{
  //Рассчет шага дискретизации по времени [мс].
  //На вход функции подать millis() или его аналоги.
  //Функцию можно вызвать только в одном месте циклически.
  //     +-------------------+
  //  ->-|Uptime_ms     Ts_ms|->-
  //     +-------------------+
  static uint32_t Time_previous_ms = 0; //Предыдущее значение времени [мс].
  uint32_t Ts_ms = 0; //Шаг дискретизации по времени [мс].
  if (Time_previous_ms <= Uptime_ms)
  {
    Ts_ms = Uptime_ms - Time_previous_ms; //разность времени без переполнения (займа).
  }
  else
  {
    //Срока ниже или просто вычитание дает через несколько минут работы хз почему 0xffffff01
    ;//Ts_ms = (0xFFFFFFFF - Time_previous_ms) + Uptime_ms + 1; //разность времени при переполнении.
  }
  Time_previous_ms = Uptime_ms; //Запомнить предидущее состояние.
  return Ts_ms;
}

uint32_t Calc_Ts_ms_max(uint32_t Ts_ms) //Максимальное время скана ПЛК [мс].
{
  //     +-------------------+
  //  ->-|Ts_ms     Ts_ms_max|->-
  //     +-------------------+
  static uint32_t Ts_ms_max = 0;
  if (Ts_ms > Ts_ms_max)
  {
    Ts_ms_max = Ts_ms;
  }
  return Ts_ms_max;
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
