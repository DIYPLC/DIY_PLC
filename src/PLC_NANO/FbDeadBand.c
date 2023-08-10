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
// License: GNU GPL v2
//
// https://www.youtube.com/@DIY_PLC
// https://github.com/DIYPLC
