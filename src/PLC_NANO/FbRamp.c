#include <stdint.h>
#include <stdbool.h>
#include <iso646.h>
#include "FbRamp.h"

#define In      p->In
#define TAcc    p->TAcc
#define TDec    p->TDec
#define Ts      p->Ts
#define Out     p->Out
#define AccMode p->AccMode
#define DecMode p->DecMode

void FbRamp(struct DbRamp *p)
{

  AccMode = (In  > Out); // Активен режим ускорения.
  DecMode = (In  < Out); // Активен режим замедления.

  // Режим замедления.
  if (DecMode)
  {
    if (TDec <= 0.0)
    {
      Out = In;
    }
    else
    {
      Out = Out - (Ts / TDec);
    }
  }

  // Режим ускорения.
  if (AccMode)
  {
    if (TAcc <= 0.0)
    {
      Out = In;
    }
    else
    {
      Out = Out + (Ts / TAcc);
    }
  }

  // Установившийся режим.
  if ((AccMode and (Out >= In)) or (DecMode and (Out <= In)) or (In = Out))
  {
    Out = In;
  }

  return;
}

// Временная характеристика.
//
// ^ In
// |
// 1  *************
// |  *           *
// |  *           *
// |  *           *
// 0--------------------> t[s]
//
// ^ Out
// |
// |   TAcc       TDec
// |    1s        0.5s
// |  <----->     <-->
// 1        *******
// |      *        *
// |    *           *
// |  *              *
// 0--------------------> t[s]

// Блок схема.
//
// Константы    Переключатель    Интегратор
// +------+     +-----------+
// |  1   |     | In > Out  |
// | ---- |-->--|--+        |
// | TAcc |     |   \       |
// +------+     |    \      |
//              |     \     |
// +------+     |      \    |     +-----+
// |      |     |       \   |     |  1  |
// |  0   |-->--|--+     +--|-->--| --- |-->-- Out
// |      |     | In ~= Out |     |  s  |
// +------+     |           |     +-----+
//              |           |
// +------+     |           |
// |  1   |     |           |
// | ---- |-->--|--+        |
// | TDec |     | In < Out  |
// +------+     +-----------+

// @COPYLEFT ALL WRONGS RESERVED :)
// Author: VA
// Contacts: DIY.PLC.314@gmail.com
// Date start LIB_PLC: 2014
// License: GNU GPL-2.0-or-later
// https://www.gnu.org/licenses/old-licenses/gpl-2.0.html
// https://www.youtube.com/watch?v=n1F_MfLRlX0
// https://www.youtube.com/@DIY_PLC
// https://github.com/DIYPLC/LIB_PLC
// https://oshwlab.com/diy.plc.314/PLC_HW1_SW1
// https://3dtoday.ru/3d-models/mechanical-parts/body/korpus-na-din-reiku
// https://t.me/DIY_PLC
