#include <stdint.h>
#include <stdbool.h>
#include <iso646.h>
#include "FbDeadBand.h"

#define In    p->In
#define ERMAX p->ERMAX
#define ERMIN p->ERMIN
#define Out   p->Out

void FbDeadBand(struct DbDeadBand *p)
{

  //Зона нечувствительности.
  if ((ERMIN < In) and (In < ERMAX))
  {
    Out = 0.0;
  }
  else
  {
    Out = In;
  }

  return;
}

// Условное графическое обозначение.
//
//          ERMAX
//      +-----------+
//      |           |
//      |       /   |
//      |      /    |
//      |      |    |
// In->-|   +--+    |->-Out
//      |   |       |
//      |  /        |
//      | /         |
//      |           |
//      +-----------+
//          ERMIN

// Статическая характеристика.
//
//                +Out
//                  |        *
//                  |       *
//                  |      *
//                  |     *
//                  |     *
//                  |     *
//             ERMIN|     *
//            |<--->|     *
//            |     |     *
// -In <------*************--> +In
//            *     |     |
//            *     |<--->|
//            *     |ERMAX
//            *     |
//            *     |
//            *     |
//           *      |
//          *       |
//         *        |
//                -Out

// Временная характеристика.
//
// +In
// |            *
// |           * *
// |----------*---* -----------------
// |         *     *               |
// |        *       *              | ERMAX
// |       *         *             |
// +------*-----------*----------------------> t[s]
// |     *             *           |
// |    *               *          | ERMIN
// |   *                 *         |
// |--*-------------------*----------
// | *                     *
// |*                       *
// -In
//
// +Out
// |            *
// |           * *
// |----------*---* -----------------
// |          *   *                |
// |          *   *                | ERMAX
// |          *   *                |
// +--*********---*********------------------> t[s]
// |  *                   *        |
// |  *                   *        | ERMIN
// |  *                   *        |
// |--*-------------------*----------
// | *                     *
// |*                       *
// -Out

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
