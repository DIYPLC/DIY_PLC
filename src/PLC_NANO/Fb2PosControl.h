//Регулятор двухпозиционный.
//       Db2PosControl
//     +---------------+
//     | Fb2PosControl |
//  ->-|PV           OP|->-
//    -|SP             |
//    -|HYST           |
//     +---------------+
/*
  Пример вызова программы.
  static struct Db2PosControl Db2PosControl1 = {0};
  Db2PosControl1.PV   = 0.0               ; //Измеренное значение регулируемого параметра.
  Db2PosControl1.SP   = 0.0               ; //Заданное значение регулируемого параметра.
  Db2PosControl1.HYST = 5.0               ; //Гистерезис > 0.
  Fb2PosControl(&Db2PosControl1)          ; //Регулятор двухпозиционный.
  //                   = Db2PosControl1.OP; //Выход управляющего сигнала.
*/

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

struct Db2PosControl
{
  //Входные переменные, сохраняемые.
  float PV  ; //Измеренное значение регулируемого параметра.
  float SP  ; //Заданное значение регулируемого параметра.
  float HYST; //Гистерезис > 0.
  //Выходные переменные, сохраняемые.
  bool OP   ; //Выход управляющего сигнала.
  //Внутренние переменные, сохраняемые.
  float ER  ; //Ошибка регулирования.
};

void Fb2PosControl(struct Db2PosControl *p);

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
