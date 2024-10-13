#include <stdint.h>
#include <stdbool.h>
#include <iso646.h>
#include "FbFilterNaN.h"

#define In    p->In
#define Out   p->Out
#define Alarm p->Alarm

void FbFilterNaN(struct DbFilterNaN *p)
{
  union
  {
    float    float32;
    uint32_t uint32;
    uint16_t uint16[2];
    uint8_t  uint8[4];
  } Convertor;
  Convertor.float32 = In;

  if ( 0x7F800000 == (Convertor.uint32 & 0x7F800000) )
  {
    Out   = 0.0;
    Alarm = true;
  }
  else
  {
    Out   = In;
    Alarm = false;
  }

  return;
}

//Если In==(NaN или Inf или -Inf) то Out=0 иначе Out=In.
// hex 7F800000 = bin 01111111_10000000_00000000_00000000
//Стандарт IEEE 754.

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
