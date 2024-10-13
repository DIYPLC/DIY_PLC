#include <stdint.h>
#include <stdbool.h>
#include <iso646.h>
#include "FbTriggerRS.h"

#define S p->S
#define R p->R
#define Q p->Q

void FbTriggerRS(struct DbTriggerRS *p)
{

  //RS- Триггер.
  Q = (Q or S) and (not(R));

  return;
}

//   Релейная интерпритация.
//  |                       |
//  |   R       S       Q   |
//  +--|/|--+--| |--+--( )--+
//  |       |       |       |
//  |       |   Q   |       |
//  |       +--| |--+       |
//  |                       |

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
