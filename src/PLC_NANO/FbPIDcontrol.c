#include <stdint.h>
#include <stdbool.h>
#include <iso646.h>
#include "FbPIDcontrol.h"

#define PV              p->PV
#define SP              p->SP
#define Kp              p->Kp
#define Ki              p->Ki
#define Kd              p->Kd
#define Kdf             p->Kdf
#define ERMAX           p->ERMAX
#define ERMIN           p->ERMIN
#define MVMAX           p->MVMAX
#define MVMIN           p->MVMIN
#define Ts              p->Ts
#define Manual          p->Manual
#define OnMan           p->OnMan
#define MV              p->MV
#define Er              p->Er
#define Ppart           p->Ppart
#define Ipart           p->Ipart
#define Dpart           p->Dpart
#define Dintegral       p->Dintegral

void FbPIDcontrol(struct DbPIDcontrol *p)
{

  //Временные переменные, не сохраняемые.
  float Auto; //Выход ПИД- алгоритма и вход переключателя режимов работы.
  float Sw  ; //Выход с переключателя режимов работы.

  //Ошибка регулирования.
  Er = SP - PV;

  //Зона нечувствительности к ошибке.
  if ((ERMIN < Er) and (Er < ERMAX))
  {
    Er = 0.0;
  }

  //Пропорциональная составляющая.
  Ppart = Kp * Er;

  //Интегральная составляющая.
  if (0.0 == Ki)
  {
    Ipart = 0.0;
  }
  else
  {
    Ipart = Ipart + Ki * Er * Ts;
  }

  //Дифференциальная составляющая.
  if (0.0 == Kd)
  {
    Dpart = 0.0;
    Dintegral = 0.0;
  }
  else
  {
    Dpart = (Er * Kd - Dintegral) * Kdf;
    Dintegral = Dintegral + Dpart * Ts;
  }

  //Сигнал управления.
  Auto = Ppart + Ipart + Dpart;

  //Переключение режима работы "Ручной / Автоматический".
  if (OnMan)
  {
    Sw = Manual;
  }
  else
  {
    Sw = Auto;
  }

  //Амплитудный ограничитель- максимум.
  if (Sw >= MVMAX)
  {
    MV = MVMAX;
    //Ограничение интегральной составляющей методом обратного вычисления.
    Ipart = MV - (Ppart + Dpart);
  }

  //Амплитудный ограничитель- минимум.
  if (Sw <= MVMIN)
  {
    MV = MVMIN;
    //Ограничение интегральной составляющей методом обратного вычисления.
    Ipart = MV - (Ppart + Dpart);
  }

  //Амплитудный ограничитель- без ограничений.
  if ((MVMIN < Sw) and (Sw < MVMAX))
  {
    MV = Sw;
    if (OnMan)
    {
      //Ограничение интегральной составляющей методом обратного вычисления.
      Ipart = MV - (Ppart + Dpart);
    }
  }

  return;
}

// Передаточная функция регулятора (при Ts -> 0):
//
//          MV(s)               1              s
// W(s) = -------- = Kp + Ki * --- + Kd * -------------
//          ER(s)               s          Tdf * s + 1
//
// ER(s) = SP(s) - PV(s).
// Tdf = 1 / Kdf

// Передаточная функция интегратора:
//
//         Ts * z
// W(z) = --------
//         z - 1
//
// Численное интегрирование методом прямоугольников.
// y = y + x * Ts;

// Перечень сокращений.
//
// Fb          - Function block       - Функциональный блок.
// Db          - Data block           - Блок данных.
// PIDcontrol  - PID Controller       - ПИД- регулятор (пропорционально интегрально дифференциальный регулятор).
// SP          - Set Point            - Заданное значение.
// PV          - Process Variable     - Измеренное значение.
// MV          - Manipulated Variable - Сигнал управления.
// ER          - Error                - Ошибка регулирования, рассогласование.
// ERMAX       - Erorr maximum        - Максимум зоны нечувствительности.
// ERMIN       - Erorr minimum        - Минимум зоны нечувствительности.
// MVMAX       - MV maximum           - Максимум сигнала управления.
// MVMIN       - MV minimum           - Минимум сигнала управления.
// Ts          - Sample Time          - Шаг дискретизации по времени.
// ManOn       - Manual on            - Включить ручной режим управления.
// Sw          - Switch               - Переключатель.
// CW          - Control Word         - Слово (ui16 бит) управления (по битам).
// SW          - Status Word          - Слово (ui16 бит) состояния (по битам).
// EW          - Error Word           - Слово (ui16 бит) ошибок (по битам).
// Альтернативные варианты имен.
// CV          - Control Variable     - Измеренное значение.
// PV          - Process Value        - Измеренное значение.
// CS          - Control Signal       - Сигнал управления.
// MV          - Manipulated Value    - Сигнал управления.
// OP          - Output Power         - Сигнал управления.

// Характеристики ПИД- регулятора.
//
// Ограничение интегральной составляющей методом обратного вычисления.
// Зона нечувствительности к ошибке регулирования для устранения небольших колебаний регулятора в установившемся режиме работы.
// Амплитудное ограничение выходного сигнала для предотвращения подачи сигнала управления, который превышает физические возможности исполнительного механизма.
// Встроенный в дифференциальную составляющую фильтр низких частот, для устранения дифференцирования шумов измерения.
// Фильтр шума- дискретное апериодическое звено первого порядка.
// Переключение режимов управления РУЧНОЙ / АВТОМАТ.
// Безударный переход из ручного режима в автоматический.
// Безударный переход из автоматического режима в ручной.
// Принудительное обнуление интегратора интегральной составляющей при Ki=0.
// Принудительное обнуление интегратора дифференциальной составляющей при Kd=0.
// Численное интегрирование методом прямоугольников.
// Нет ни одной операции деления.
// Протестировано на PLC SIEMENS SIMATIC S7-300 в блоке OB35 (Ts=0,1c).

// Известные недостатки ПИД- регулятора.
//
// При переходе из автоматического режима в ручной безударный переход отсутствует, если не подвязать через внешний тег переменную выхода MV к входу MANUAL.
// Безударный переход работает только если Ki не равен нолю.
// Необходимо следить, чтобы верхняя граница зоны нечувствительности была больше или равна нижней.
// Необходимо следить, чтобы верхняя граница амплитудного ограничителя была больше нижней.
// Необходимо следить, чтобы коэффициент Kdf был больше ноля.
// Необходимо помнить, что коэффициент Kdf обратно пропорционален постоянной времени фильтра.
// Прямоугольный интегратор имеет меньшую точность, чем трапецеидальный.
// Арифметика с плавающей точкой работает медленнее целочисленной.
// Точность вычислений не контролируется.
// Необходимо следить при наладке, чтобы не было слишком малых измеренных значений и интегральной составляющей при большом выходном сигнале.
// Иначе интегрирование может остановиться и за того, что мы пытаемся прибавить очень маленькое число к очень большому, а точность типа данных не позволяет это сделать.
// ПИ- закон регулирования с апериодическим объектом управления по определе-нию не может безошибочно «отрабатывать» линейно нарастающий сигнал задания.
// Сигналы SP и PV нужно ограничивать вне регулятора,
// диаппазоны ограничения для SP и PV должны быть одинаковыми,
// если этого не сделать то будут проблемы в автоматическом режиме работы при активной работе амплитудного ограничителя,
// например SP=90% PV=110% ожидаем MV=0%, но при изменении PV возрастает MV хотя должно быть MV=0%.

//Структура регулятора:
//
// Ошибка регулирования.
//      +---+
//      |   |
// SP->-|+  |
//      |   |->-ER
// PV->-|-  |
//      |   |
//      +---+
//
// Зона нечувствительности к ошибке.
//          ERMAX
//      +-----------+
//      |           |
//      |       /   |
//      |      /    |
//      |      |    |
// ER->-|   +--+    |->-ER
//      |   |       |
//      |  /        |
//      | /         |
//      |           |
//      +-----------+
//          ERMIN
//
// Пропорциональная составляющая.
//      +---+
//      |   |
// ER->-|   |
//      | * |->-Ppart
// Kp->-|   |
//      |   |
//      +---+
//
// Интегральная составляющая.
//      +---+   +----------+
//      |   |   |          |
// ER->-|   |   |  Z * Ts  |
//      | * |->-| -------- |->-Ipart
// Kp->-|   |   |  Z - 1   |
//      |   |   |          |
//      +---+   +----------+
//
// Дифференциальная составляющая.
//                        +---+
//                        |   |
//      +---+       Kdf->-|   |
//      |   |     +---+   |   |
// ER->-|   |     |   |   | * |----------------+-->-Dpart
//      | * |--->-|+  |   |   |                |
// Kd->-|   |     |   |->-|   |                |
//      |   | +->-|-  |   |   | +----------+   |
//      +---+ |   |   |   +---+ |          |   |
//            |   +---+         |  Z * Ts  |   |
//            +-----------------| -------- |-<-+
//                              |  Z - 1   |
//                              |          |
//                              +----------+
//
// Сигнал управления.
//         +---+
//         |   |
// Ppart->-|+  |
//         |   |
// Ipart->-|+  |->-Auto
//         |   |
// Dpart->-|+  |
//         |   |
//         +---+
//
// Переключение режима работы "Ручной / Автоматический".
//          +-----+
//          |     |
// Auto--->-|-+   |
//          |  \  |
//          |   +-|->-Sw
//          |     |
// Manual->-|-+   |
//          |     |
//          +-----+
//             |
// OnMan-->----+
//
// Амплитудный ограничитель.
//          MVMAX
//      +-----------+
//      |           |
//      |       +-- |
//      |      /    |
// Sw->-|     /     |->-MV
//      |    /      |
//      | --+       |
//      |           |
//      +-----------+
//          MVMIN


// Реакция разомкнутого контура регулятора на единичное спупечатое воздействие по каналу управления.
//
// ^ ER
// |
// 1************ ER(t) = 1
// |            
// 0---1---2---3---> t[s]
//
// ^ Ppart
// |
// |************ Ppart(t) = Kp * ER
// |            
// |            
// |            
// 0---1---2---3---> t[s]
//
// ^ Ipart
// |
// 3           * Ipart(t) = Ki * t
// |         *  
// 2       *    
// |     *      
// 1   *        
// | *          
// 0---1---2---3---> t[s]
//
// ^ Dpart
// |
// 1*            Dpart(t) = Kd * (0 - exp(-(t/Tf)))
// | *          
// |  *        
// |    *       
// |      *     
// 0---------***---> t[s]
//
// ^ MV
// |
// |                               *
// |                             *
// |                           *
// |                         *
// |                       *
// |                     *
// |*                  *
// | *               *
// |  *            *
// |    *        *
// |      *    *
// |        **
// |
// |
// 0------------------------------------> t[s]

// Интерфейс пользователя SCADA, HMI.
//
// Шрифт: Arial 12pt
// Цвет фона: R212 G208 B200
// Цвет тени: R169 G169 B169
// Цвет "Заданное значение"  : R0 G0 B255
// Цвет "Измеренное значение": R0 G176 B80
// Цвет "Сигнал управления"  : R255 G0 B0
//
// +------------------------------------------------------+---+
// | 1PIRCA1 ПИД Регулятор давления воды.                 | X |
// +------------------------------------------------------+---+
// | +-------+ +--------------------------------------------+ |
// | | 10.00 | | Заданное значение           0...10 [Bar] B | |
// | +-------+ +--------------------------------------------+ |
// | +-------+ +--------------------------------------------+ |
// | | 10.01 | | Измеренное значение         0...10 [Bar] G | |
// | +-------+ +--------------------------------------------+ |
// | +-------+ +--------------------------------------------+ |
// | |  50.0 | | Сигнал управления           0...100 [Hz] R | |
// | +-------+ +--------------------------------------------+ |
// | +---------+ +--------+ +------+ +--------+ +-----------+ |
// | | АВТОМАТ | | РУЧНОЙ | | СТОП | | ТРЕНДЫ | | НАСТРОЙКИ | |
// | +---------+ +--------+ +------+ +--------+ +-----------+ |
// | Код ошибки: 0 (OK).                                      |
// +----------------------------------------------------------+
//
// +-------------------------------------------+---+
// | 1PIRCA1 Тренды.                           | X |
// +-------------------------------------------+---+
// | Заданное значение   [Bar] B                   |
// | Измеренное значение [Bar] G                   |
// | Сигнал управления   [Hz ] R                   |
// |   ^                                           |
// |   |                                           |
// |100+                                           |
// |   |                                           |
// |   |            **********************         |
// |   |           *                               |
// |   |          *                                |
// | 50+    +----*------------------------         |
// |   |    |   *  +++++++++++++++++++++++         |
// |   |    |  *  +                                |
// |   |    | *  +                                 |
// |   |    |*  +                                  |
// |   +----+----+----+----+----+----+----+-> t[s] |
// |   0   10   20   30   40   50   60   70        |
// +-----------------------------------------------+
//
// +-------------------------------------------+---+
// | 1PIRCA1 Настройки ПИД регулятора.         | X |
// +-------------------------------------------+---+
// | +-------+ +---------------------------------+ |
// | | 0.001 | | Kp                              | |
// | +-------+ +---------------------------------+ |
// | +-------+ +---------------------------------+ |
// | | 0.001 | | Ki                              | |
// | +-------+ +---------------------------------+ |
// | +-------+ +---------------------------------+ |
// | |   0.0 | | Kd                              | |
// | +-------+ +---------------------------------+ |
// | +-------+ +---------------------------------+ |
// | | 1.000 | | Kdf                             | |
// | +-------+ +---------------------------------+ |
// | +-------+ +---------------------------------+ |
// | | 0.001 | | ERMAX                           | |
// | +-------+ +---------------------------------+ |
// | +-------+ +---------------------------------+ |
// | |-0.001 | | ERMIN                           | |
// | +-------+ +---------------------------------+ |
// | +-------+ +---------------------------------+ |
// | | 100.0 | | MVMAX                           | |
// | +-------+ +---------------------------------+ |
// | +-------+ +---------------------------------+ |
// | |   0.0 | | MVMIN                           | |
// | +-------+ +---------------------------------+ |
// +-----------------------------------------------+

// Пересчет коэффициентов регулятора "CONT_C" 
// в коэффициенты ПИД- регулятора MATLAB SIMULINK PID Controller.
//
// Передаточная функция регулятора SIMATIC FB 41 "CONT_C":
//
//         LMN(s)                   1      (TD / TM_LAG) * s
// W(s) = -------- = GAIN * (1 + ------ + -------------------)
//          ER(s)                TI * s      TM_LAG * s + 1
//
// Единицы измерения.
// ER(s) = SP_INT(s) - PV_IN(s). 0...100[%]
// TI,TD,TM_LAG [s].
// Итого получаем формулы для пересчета настроек:
// P = Kp  = GAIN
// I = Ki  = GAIN / TI
// D = Kd  = (TD / TM_LAG) * GAIN
// N = Kdf = 1 / TM_LAG
// Так же необходимо учесть что данные настройки актуальны
// только для диаппазонов входного и выходного сигнала 0...100[%].
// Время необходимо привести в секунды.

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
// License: GNU GPL v2
//
// https://www.youtube.com/@DIY_PLC
// https://github.com/DIYPLC
