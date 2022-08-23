#include <stdint.h>
#include <stdbool.h>
#include <iso646.h>
#include "FbIntegrator.h"

#define In         p->In
#define OutMax     p->OutMax
#define OutMin     p->OutMin
#define InitValue  p->InitValue
#define Ts         p->Ts
#define Reset      p->Reset
#define Out        p->Out
#define InPrevious p->InPrevious

void FbIntegrator(struct DbIntegrator *p)
{

  if (true) //Используем прямоугольный интегратор т.к. его обычно достаточно.
  {
    Out = Out + In * Ts; //Прямоугольный интегратор
  }
  else
  {
    Out = Out + (In + InPrevious) * 0.5 * Ts; // Трапецеидальный интегратор
  }

  if (Reset) //Начальные условия интегрирования применяются при сбросе.
  {
    Out = InitValue;
  }

  if (Out >= OutMax) //Ограничение верх.
  {
    Out = OutMax;
  }

  if (Out <= OutMin) //Ограничение низ.
  {
    Out = OutMin;
  }

  return;
}

// Условное графическое обозначение (точное).
//
//    +----------+
//    |  Ts * z  |
// ->-| -------- |->-
//    |   z - 1  |
//    +----------+

// Условное графическое обозначение (приближенное).
//
//    +-----+
//    |  1  |
// ->-| --- |->-
//    |  s  |
//    +-----+

// Временная характеристика.
//
// ^ Out
// |
// 3           *
// |         *
// 2       *
// |     *
// 1   *
// | *
// 0---1---2---3---> t[s]
//
// ^ In
// |
// 1************
// |
// 0---1---2---3---> t[s]

// Подаем на вход константу на выходе получаем линейную функцию.
// Подаем на вход линейную функцию на выходе получаем параболу.
// Подаем на вход функцию sin(t) на выходе получаем cos(t).
// Подаем на вход функцию e(t)   на выходе получаем e(t).

// Передаточная функция интегратора в изображении по Лапласу:
//         1
// W(s) = ---
//         s
// W(s) = Y(s) / X(s)
// X(s) = L( X(t) )
// Y(s) = L( Y(t) )
// Например подали на вход константу 2:
// X(t) = 2
// Изображение константы 2:
// L( X(t) ) = L( 2 ) = 2/s
// На выходе получили линейную функцию 2t:
// Y(t) = 2t
// Изображение линейной функции 2t:
// L( Y(t) ) = L( 2t ) = 2/(s*s)
// Тогда по определению передаточной функции получаем для интегратора:
// W(s) = Y(s) / X(s) = 2/(s*s)  /  2/s = 1/s
// W(s) = 1/s
// Преобразование Лапласа грубо говоря это преобразование Фурье в котором:
// Исходную функцию умножили на затухающую экспоненту чтобы результирующая площадь (интеграл) была конечной.
// Предел интегрирования не от -inf до +inf а 0 до +inf с той же целью чтобы площадь (интеграл) была конечной и проще было считать интеграл.
// Если вы не знаете что такое интеграл смотрите и вам откроется:)
// История математики ВВС: The Story of Maths (4 серии)
// Механическая Вселенная The Mechanical Universe… And Beyond (52 серии)

// Вывод разностного уравнения из дифференциального уравнения:
//         1
// W(p) = ---
//         p
// W(p) = Y(t) / X(t)
// p = d/dt
// Y(t) / X(t) = 1 / p
// Y(t) * p = X(t)
// Y(t) * d/dt = X(t)
// d(Y(t)) / dt = X(t)
// (Y(t) - Y(t-dt)) / dt = X(t)
// Y(t) - Y(t-dt) = X(t) * dt
// Y(t)  = Y(t-dt) + X(t) * dt
// Y = Y + X * Ts

// Прямоугольный интегратор (Integrator Backward Euler).
// Алгебраический порядок точности численного метода = 0 (ODE0)
// Вывод разностного уравнения из дискретной передаточной функции:
//         Ts * z
// W(z) = --------
//          z - 1
// W(z) = (Ts * z) / (z - 1)
// Y(z) / X(z) = (Ts * z) / (z - 1)
// Y(z) * (z - 1) = Ts * X(z) * z
// Y(z) * z - Y(z) = Ts * X(z) * z
// Y(z) * z  = Y(z) + Ts * X(z) * z
// Y(z)  = Y(z) * (z^-1) + Ts * X(z)
// Y[n]  = Y[n-1]  + Ts * X[n]
// Y = Y + X * Ts
// Практика применения в АСУТП показывает
// что достаточно нулевой алгебраической точности интегратора
// и шага дискретизации по времени Ts = 0.1s.

// Трапецеидальный интегратор (Integrator Trapezoidal).
// Алгебраический порядок точности численного метода = 1 (ODE1)
// Вывод разностного уравнения из дискретной передаточной функции:
//         Ts * (z + 1)
// W(z) = --------------
//          2 * (z - 1)
// W(z) = Ts * (z + 1) / 2 * (z - 1)
// Y(z) / X(z) = Ts * (z + 1) / 2 * (z - 1)
// Y(z) * 2 * (z - 1) = X(z) * Ts * (z + 1)
// Y(z) * z * 2 - Y(z) * 2 = X(z) * z * Ts + X(z) * Ts
// Y(z) * 2 - Y(z) * (z^-1) * 2 = X(z) * Ts + X(z) * (z^-1) * Ts
// Y(z) * 2 = Y(z) * (z^-1) * 2 + X(z) * Ts + X(z) * (z^-1) * Ts
// Y(z) = Y(z) * (z^-1) + (X(z) * Ts + X(z) * (z^-1) * Ts) / 2
// Y(z) = Y(z) * (z^-1) + (X(z) + X(z) * (z^-1)) * 0.5 * Ts
// Y[n] = Y[n-1] + (X[n] + X[n-1]) * 0.5 * Ts
// Y = Y + (X + Xprevious) * 0.5 * Ts
// Xprevious = X

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