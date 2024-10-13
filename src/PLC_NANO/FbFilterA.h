//Фильтр апериодический.
//      DbFilterA
//    +-----------+
//    | FbFilterA |
// ->-|In      Out|->-
//   -|Tf         |
//   -|Ts         |
//    +-----------+
/*
  Пример вызова программы. Выполнять код каждые Ts = 0.1с.
  static struct DbFilterA DbFilterA1 = {0};
  DbFilterA1.In = 0.0           ; //Входной сигнал до фильтрации.
  DbFilterA1.Tf = 1.0           ; //Постоянная времени фильтра [с].
  DbFilterA1.Ts = 0.1           ; //Шаг дискретизации по времени [с].
  FbFilterA(&DbFilterA1)        ; //Фильтр апериодический.
  //            = DbFilterA1.Out; //Выходной сигнал после фильтрации.
*/

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

struct DbFilterA
{
  //Входные переменные, сохраняемые.
  float In ; //Входной сигнал до фильтрации.
  float Tf ; //Постоянная времени фильтра [с].
  float Ts ; //Шаг дискретизации по времени [с].
  //Выходные переменные, сохраняемые.
  float Out; //Выходной сигнал после фильтрации.
};

void FbFilterA(struct DbFilterA *p);

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
