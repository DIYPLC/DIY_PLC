//Зона нечувствительности.
//      DbDeadBand
//    +------------+
//    | FbDeadBand |
// ->-|In       Out|->-
//   -|ERMAX       |
//   -|ERMIN       |
//    +------------+
/*
  Пример вызова программы.
  static struct DbDeadBand DbDeadBand1 = {0};
  DbDeadBand1.In    =  0.0  ; //Вход зоны нечувствительности.
  DbDeadBand1.ERMAX =  0.001; //dead band - Зона нечувствительности верхняя граница.
  DbDeadBand1.ERMIN = -0.001; //dead band - Зона нечувствительности нижняя граница.
  FbDeadBand(&DbDeadBand1)  ; //Зона нечувствительности.
  //       = DbDeadBand1.Out; //Выход зоны нечувствительности.
*/

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

struct DbDeadBand
{
  //Входные переменные, сохраняемые.
  float In   ; //Вход зоны нечувствительности.
  float ERMAX; //dead band - Зона нечувствительности верхняя граница.
  float ERMIN; //dead band - Зона нечувствительности нижняя граница.
  //Выходные переменные, сохраняемые.
  float Out  ; //Выход зоны нечувствительности.
};

void FbDeadBand(struct DbDeadBand *p);

#ifdef __cplusplus
}
#endif

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
// https://github.com/DIYPLC/LIB_PLC
// https://oshwlab.com/diy.plc.314/PLC_HW1_SW1
// https://3dtoday.ru/3d-models/mechanical-parts/body/korpus-na-din-reiku
// https://t.me/DIY_PLC
