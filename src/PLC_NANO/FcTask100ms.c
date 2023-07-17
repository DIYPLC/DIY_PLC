#include <stdint.h>         //uint8_t...uint64_t int8_t...int64_t
#include <stdbool.h>        //bool true false
#include <iso646.h>         //and or not
#include "FcTask100ms.h"    //Задача вызывается каждые 100ms.
#include "GlobalVar.h"      //Глобальные переменные ПЛК.
#include "FbGSS.h"          //Генератор сигналов и псевдослучайных чисел.

extern struct GlobalVar GV; //Глобальные переменные ПЛК.

void FcTask100ms(bool Reset, uint32_t Ts_ms) //Задача выполняется каждые 100ms.
{
  float Ts = ((float)Ts_ms) * 0.001; //Шаг дискретизации по времени в секундах.

  //Генератор сигналов и псевдослучайных чисел.
  //             DbGSS
  //    +---------------------+
  //    |        FbGSS        |
  //   -|Amplitude        Sine|->-
  //   -|Period         Cosine|->-
  //   -|Phase      RectangleR|->-
  //   -|Offset     RectangleB|->-
  //   -|PulseTime    Triangle|->-
  //   -|Ts               Prnd|->-
  //    +---------------------+
  static struct DbGSS DbGSS1 = {0};
  DbGSS1.Amplitude = 1.0              ; //Амплитуда выходного сигнала.
  DbGSS1.Period    = 1.0              ; //Период выходного сигнала [с].
  DbGSS1.Phase     = 0.0              ; //Фаза выходного сигнала [рад].
  DbGSS1.Offset    = 0.0              ; //Постоянная составляющая выходного сигнала.
  DbGSS1.PulseTime = 0.5              ; //Время импульса [с].
  DbGSS1.Ts        = Ts               ; //Шаг дискретизации по времени [с].
  FbGSS(&DbGSS1)                      ;
  //               = DbGSS1.Sine      ; //Синусоидальный сигнал.
  //               = DbGSS1.Cosine    ; //Косинусоидальный сигнал.
  //               = DbGSS1.RectangleR; //Прямоугольный сигнал вещественный.
  GV.Do2           = DbGSS1.RectangleB; //Прямоугольный сигнал булевый.
  //               = DbGSS1.Triangle  ; //Треугольный, линейно нарастающий и убывающий сигнал.
  //               = DbGSS1.Prnd      ; //Псевдослучайные числа в диапазоне 0...1.


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
