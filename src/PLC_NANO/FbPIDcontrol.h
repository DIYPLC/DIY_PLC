//ПИД-регулятор.
//         DbPIDcontrol
//    +--------------------+
//    |    FbPIDcontrol    |
// ->-|ProcessVariable  Out|->-
//   -|Setpoint            |
//   -|Kp                  |
//   -|Ki                  |
//   -|Kd                  |
//   -|Kdf                 |
//   -|DBmax               |
//   -|DBmin               |
//   -|OutMax              |
//   -|OutMin              |
//   -|Ts                  |
//   -|Manual              |
//   -|ManOn               |
//    +--------------------+
/*
  Пример вызова программы. Выполнять код каждые Ts = 0.1 с.
  static struct DbPIDcontrol DbPIDcontrol1 = {0};
  DbPIDcontrol1.ProcessVariable = 0.0              ; //Измеренное значение регулируемого параметра.
  DbPIDcontrol1.Setpoint        = 0.0              ; //Заданное значение регулируемого параметра.
  DbPIDcontrol1.Kp              = 0.001            ; //Коэффициент усиления пропорциональный.
  DbPIDcontrol1.Ki              = 0.001            ; //Коэффициент усиления интегральный.
  DbPIDcontrol1.Kd              = 0.0              ; //Коэффициент усиления дифференциальный.
  DbPIDcontrol1.Kdf             = 1.0              ; //Коэффициент фильтрации дифференциальный Kdf=1/Tdf.
  DbPIDcontrol1.DBmax           =  0.001           ; //Зона нечувствительности к ошибке регулирования, максимум.
  DbPIDcontrol1.DBmin           = -0.001           ; //Зона нечувствительности к ошибке регулирования, минимум.
  DbPIDcontrol1.OutMax          = 100.0            ; //Максимальное значение сигнала управления.
  DbPIDcontrol1.OutMin          = 0.0              ; //Минимальное значение сигнала управления.
  DbPIDcontrol1.Ts              = 0.1              ; //Шаг дискретизации по времени в секундах.
  DbPIDcontrol1.Manual          = 25.0             ; //Сигнал управления в ручном режиме работы.
  DbPIDcontrol1.ManOn           = false            ; //Включить ручной режим работы регулятора.
  FbPIDcontrol(&DbPIDcontrol1)                     ; //ПИД-регулятор.
  //                            = DbPIDcontrol1.Out; //Сигнал управления на исполнительный механизм.
*/

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

struct DbPIDcontrol
{
  //Входные переменные, сохраняемые.
  float ProcessVariable; //Измеренное значение регулируемого параметра.
  float Setpoint       ; //Заданное значение регулируемого параметра.
  float Kp             ; //Коэффициент усиления пропорциональный.
  float Ki             ; //Коэффициент усиления интегральный.
  float Kd             ; //Коэффициент усиления дифференциальный.
  float Kdf            ; //Коэффициент фильтрации дифференциальный Kdf=1/Tdf.
  float DBmax          ; //Зона нечувствительности к ошибке регулирования, максимум.
  float DBmin          ; //Зона нечувствительности к ошибке регулирования, минимум.
  float OutMax         ; //Максимальное значение сигнала управления.
  float OutMin         ; //Минимальное значение сигнала управления.
  float Ts             ; //Шаг дискретизации по времени в секундах.
  float Manual         ; //Сигнал управления в ручном режиме работы.
  bool  ManOn          ; //Включить ручной режим работы регулятора.
  //Выходные переменные, сохраняемые.
  float Out            ; //Сигнал управления на исполнительный механизм.
  //Внутренние переменные, сохраняемые.
  float Er             ; //Ошибка регулирования.
  float Ppart          ; //Пропорциональная составляющая регулятора.
  float Ipart          ; //Интегратор интегральной составляющей регулятора.
  float Dpart          ; //Дифференциальная составляющая регулятора.
  float Dintegral      ; //Интегратор дифференциальной составляющей регулятора.
};

void FbPIDcontrol(struct DbPIDcontrol *p);

#ifdef __cplusplus
}
#endif
