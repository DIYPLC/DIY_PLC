//Расчет времени скана.
//             DbTs
//    +---------------------+
//    |        FbTs         |
//   -|millis          Ts_ms|->-
//   -|Reset              Ts|->-
//    |            Ts_ms_max|->-
//    |             Uptime_s|->-
//    +---------------------+
/*
  Пример вызова программы.
  static struct DbTs DbTs1 = {0};
  DbTs1.millis = millis()       ; //millis() Arduino.
  DbTs1.Reset  = GV.Reset       ; //Сброс при перезагрузке.
  FbTs(&DbTs1)                  ; //Расчет времени скана.
  //           = DbTs1.Ts_ms    ; //Шаг дискретизации по времени [мс].
  //           = DbTs1.Ts       ; //Шаг дискретизации по времени [с].
  //           = DbTs1.Ts_ms_max; //Максимальное время скана [мс].
  //           = DbTs1.Uptime_s ; //Время в работе [мс].
*/

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

struct DbTs {
  //Входные переменные, сохраняемые.
  uint32_t millis; //millis() Arduino.
  bool     Reset ; //Сброс при перезагрузке.
  //Выходные переменные, сохраняемые.
  uint32_t Ts_ms ; //Шаг дискретизации по времени [мс].
  float    Ts    ; //Шаг дискретизации по времени [с].
  uint32_t Ts_ms_max; //Максимальное время скана [мс].
  uint32_t Uptime_s; //Время в работе [с].
  //Внутренние переменные, сохраняемые.
  uint32_t Time_previous_ms; //Предидущее значение [мс].
  uint64_t Uptime_ms       ; //Время в работе [мс].
};

void FbTs(struct DbTs *p);

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
