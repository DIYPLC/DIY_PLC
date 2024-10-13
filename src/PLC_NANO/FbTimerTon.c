#include <stdint.h>
#include <stdbool.h>
#include <iso646.h>
#include "FbTimerTon.h"

#define In          p->In
#define TimeDelayOn p->TimeDelayOn
#define Ts_ms       p->Ts_ms
#define Out         p->Out
#define Timer1      p->Timer1

void FbTimerTon(struct DbTimerTon *p)
{
  if (TimeDelayOn > 0) //Таймер включен.
  {
    if (In) //На входе 1.
    {
      if (Out) //На выходе 1.
      {
        Out = true;
        Timer1 = 0;
      }
      else //На выходе 0.
      {
        if (Timer1 >= TimeDelayOn) //Задержка включения закончилась.
        {
          Out = true;
          Timer1 = 0;
        }
        else //Задержка включения активна.
        {
          Out = false;
          Timer1 = Timer1 + Ts_ms;
        }
      }
    }
    else //Если на входе 0 то на выходе тоже 0.
    {
      Out = false;
      Timer1 = 0;
    }
  }
  else //Таймер выключен.
  {
    Out = In;
    Timer1 = 0;
  }

  return;
}

// Применение.
//
// При поступлении входного сигнала выходной сигнал появляется не сразу, а с задержкой TimeDelayOn.
// Блок может применятся как фильтр дребезга контактов дискретных входов.
// Совместно с инвертором может применяться для генерации импульсов.

// Временная характеристика.
//
//  In
//  ^
//  | TimeDelayOn           TimeDelayOn
//  |   |<--->|               |<--->|
// 1|   ***********     * *   ***********
//  |   *         *     * *   *         *
// 0*****---------*************---------*****----> t[s]
//
//  Out
//  ^
//  | TimeDelayOn           TimeDelayOn
//  |   |<--->|               |<--->|
// 1|   |     *****           |     *****
//  |   |     *   *           |     *   *
// 0***********---*******************---*****----> t[s]

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
