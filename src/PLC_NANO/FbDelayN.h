// Блок задержки сигнала на 100 тактов.
//      DbDelayN
//    +----------+
//    | FbDelayN |
// ->-|In     Out|->-
//    +----------+
/*
  Пример вызова программы.
  static struct DbDelayN DbDelayN1 = {0};
  DbDelayN1.In = 0.0          ; //Вход.
  FbDelayN(&DbDelayN1)        ; // Блок задержки сигнала на 100 тактов.
  //           = DbDelayN1.Out; //Выход.
*/

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

struct DbDelayN
{
  //Входные переменные, сохраняемые.
  float    In        ; //Вход.
  //Выходные переменные, сохраняемые.
  float    Out       ; //Выход.
  //Внутренние переменные, сохраняемые.
  float    Buffer[98+1]; //Буфер задержки сигнала
};

void FbDelayN(struct DbDelayN *p);

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
