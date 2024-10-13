//Мигалка.
//            DbBlink
//    +---------------------+
//    |       FbBlink       |
//   -|Time_on_ms        Out|->-
//   -|Time_off_ms          |
//   -|Ts_ms                |
//   -|Reset                |
//    +---------------------+
/*
  Пример вызова программы. Выполнять код каждые Ts_ms = 100 ms.
  static struct DbBlink DbBlink1 = {0};
  DbBlink1.Time_on_ms  = 500         ; //Время импульса [мс].
  DbBlink1.Time_off_ms = 500         ; //Время паузы [мс].
  DbBlink1.Ts_ms       = 100         ; //Шаг дискретизации по времени [мс].
  DbBlink1.Reset       = false       ; //Сброс при перезагрузке.
  FbBlink(&DbBlink1)                 ; //Мигалка.
  //                   = DbBlink1.Out; //Мигающая лампочка.
*/

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

struct DbBlink {
  //Входные переменные, сохраняемые.
  uint32_t Time_on_ms ; //Время импульса [мс].
  uint32_t Time_off_ms; //Время паузы [мс].
  uint32_t Ts_ms      ; //Шаг дискретизации по времени [мс].
  bool     Reset      ; //Сброс при перезагрузке.
  //Выходные переменные, сохраняемые.
  bool Out; //Мигающая лампочка.
  //Внутренние переменные, сохраняемые.
  uint32_t Timer1; //Внутренний таймер [мс].
  uint8_t  State1; //Внутренний граф состояния.
};

void FbBlink(struct DbBlink *p);

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
