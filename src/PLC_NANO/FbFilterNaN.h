//Фильтр NaN и Inf для чисел REAL.
//      DbFilterNaN
//    +-------------+
//    | FbFilterNaN |
// ->-|In        Out|->-
//    |        Alarm|-
//    +-------------+
/*
  Пример вызова программы.
  static struct DbFilterNaN DbFilterNaN1 = {0};
  DbFilterNaN1.In = 0.0               ; //Вход.
  FbFilterNaN(&DbFilterNaN1)          ; //Фильтр NaN и Inf для чисел REAL.
  //              = DbFilterNaN1.Out  ; //Выход.
  //              = DbFilterNaN1.Alarm; //Флаг ошибки.
*/

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

struct DbFilterNaN
{
  //Входные переменные, сохраняемые.
  float In   ; //Вход.
  //Выходные переменные, сохраняемые.
  float Out  ; //Выход.
  bool  Alarm; //Флаг ошибки.
};

void FbFilterNaN(struct DbFilterNaN *p);

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
// https://github.com/DIYPLC
// https://oshwlab.com/diy.plc.314?tab=project&page=1
// https://3dtoday.ru/blogs/diy-plc
// https://t.me/DIY_PLC
