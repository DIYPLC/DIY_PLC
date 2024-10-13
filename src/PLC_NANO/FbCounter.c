#include <stdint.h>
#include <stdbool.h>
#include <iso646.h>
#include "FbCounter.h"

#define Inc      p->Inc
#define Dec      p->Dec
#define Reset    p->Reset
#define SetValue p->SetValue
#define Value    p->Value
#define Cnt      p->Cnt
#define Ovf      p->Ovf
#define IncPrev  p->IncPrev
#define DecPrev  p->DecPrev
#define LIM_MAX  2147483647 //Максимальное значение счетчика.
#define LIM_MIN -2147483648 //Минимальное значение счетчика.

void FbCounter(struct DbCounter *p)
{

  //Прямой счет по нарастающему фронту импульсов +1.
  if (Inc and not(IncPrev))
  {
    if (Cnt >= LIM_MAX) //Ограничение сверху.
    {
      Cnt = LIM_MAX;
      Ovf = true;
    }
    else //Прямой счет.
    {
      Cnt = Cnt + 1;
      Ovf = false;
    }
  }

  //Обратный счет по нарастающему фронту импульсов -1.
  if (Dec and not(DecPrev))
  {
    if (Cnt <= LIM_MIN) //Ограничение снизу.
    {
      Cnt = LIM_MIN;
      Ovf = true;
    }
    else //Обратный счет.
    {
      Cnt = Cnt - 1;
      Ovf = false;
    }
  }

  //Установить значение счетчика.
  if (SetValue)
  {
    Cnt = Value;
  }

  //Сбросить счетчик.
  if (Reset)
  {
    Cnt = 0;
  }

  //Запомнить предыдущее состояние входа.
  IncPrev = Inc;
  DecPrev = Dec;

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
// Date: 2014 - 2024
// License: GNU GPL-2.0-or-later
// https://www.gnu.org/licenses/old-licenses/gpl-2.0.html
// https://www.youtube.com/watch?v=n1F_MfLRlX0
//
// See also:
// https://www.youtube.com/@DIY_PLC
// https://github.com/DIYPLC
// https://oshwlab.com/diy.plc.314?tab=project&page=1
// https://3dtoday.ru/blogs/diy-plc
// https://t.me/DIY_PLC
