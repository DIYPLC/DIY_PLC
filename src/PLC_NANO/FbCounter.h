//Счетчик импульсов.
//         DbCounter
//    +-----------------+
//    |    FbCounter    |
// ->-|Inc           Cnt|->-
//   -|Dec           Ovf|-
//   -|Reset            |
//   -|SetValue         |
//   -|Value            |
//    +-----------------+
/*
  Пример вызова программы.
  static struct DbCounter DbCounter1 = {0};
  DbCounter1.Inc      = false         ; //Вход импульсов +1.
  DbCounter1.Dec      = false         ; //Вход импульсов -1.
  DbCounter1.Reset    = false         ; //Сбросить счетчик на 0.
  DbCounter1.SetValue = false         ; //Установить на выходе значение VALUE.
  DbCounter1.Value    = 0             ; //Предустановленное значение счета.
  FbCounter(&DbCounter1)              ; //Счетчик импульсов.
  //                  = DbCounter1.Cnt; //Выход счетчика.
  //                  = DbCounter1.Ovf; //Флаг переполнения счетчика.
*/

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

struct DbCounter
{
  //Входные переменные, сохраняемые.
  bool    Inc     ; //Вход импульсов +1.
  bool    Dec     ; //Вход импульсов -1.
  bool    Reset   ; //Сбросить счетчик на 0.
  bool    SetValue; //Установить на выходе значение VALUE.
  int32_t Value   ; //Предустановленное значение счета.
  //Выходные переменные, сохраняемые.
  int32_t Cnt     ; //Выход счетчика.
  bool    Ovf     ; //Флаг переполнения счетчика.
  //Внутренние переменные, сохраняемые.
  bool    IncPrev ; //Предыдущее состояние входа +1.
  bool    DecPrev ; //Предыдущее состояние входа -1.
};

void FbCounter(struct DbCounter *p);

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
