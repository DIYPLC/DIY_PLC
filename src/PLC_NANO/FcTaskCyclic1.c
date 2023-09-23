#include <stdint.h>        //uint8_t...uint64_t int8_t...int64_t
#include <stdbool.h>       //bool true false
#include <iso646.h>        //and or not
#include "FcTaskCyclic1.h" //Задача вызывается циклически.
#include "GlobalVar.h"     //Глобальные переменные ПЛК.
#include "FbBlink.h"
#include "FbFilterA.h"

extern struct GlobalVar GV; //Глобальные переменные ПЛК.
static struct DbBlink DbBlink1 = { 0 };
static struct DbFilterA DbFilterA1 = { 0 };

void FcTaskCyclic1(bool Reset, uint32_t Ts_ms) //Задача выполняется с плавающим временем цикла.
{

  GV.Ts = ((float)GV.Ts_ms) * 0.001;

  //Пример работы с дискретными алгоритмами.
  //Мигалка.
  //            DbBlink
  //    +---------------------+
  //    |       FbBlink       |
  //   -|Time_on_ms        Out|->-
  //   -|Time_off_ms          |
  //   -|Ts_ms                |
  //   -|Reset                |
  //    +---------------------+
  DbBlink1.Time_on_ms = 500;  //Время импульса [мс].
  DbBlink1.Time_off_ms = 500; //Время паузы [мс].
  DbBlink1.Ts_ms = Ts_ms; //Шаг дискретизации по времени [мс].
  DbBlink1.Reset = Reset; //Сброс при перезагрузке.
  FbBlink(&DbBlink1); //Мигалка.
  GV.Do1 = DbBlink1.Out;  //Мигающая лампочка.

  //Пример работы с аналоговыми алгоритмами.
  //Фильтр апериодический.
  //      DbFilterA
  //    +-----------+
  //    | FbFilterA |
  // ->-|In      Out|->-
  //   -|Tf         |
  //   -|Ts         |
  //    +-----------+
  DbFilterA1.In = (float) DbBlink1.Out; //Входной сигнал до фильтрации.
  DbFilterA1.Tf = 0.15; //Постоянная времени фильтра [с].
  DbFilterA1.Ts = GV.Ts;  //Шаг дискретизации по времени [с].
  FbFilterA(&DbFilterA1); //Фильтр апериодический.
  //            = DbFilterA1.Out; //Выходной сигнал после фильтрации.

  return;
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
