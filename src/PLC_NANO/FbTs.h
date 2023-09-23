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
