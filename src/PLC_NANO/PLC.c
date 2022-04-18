#include <stdint.h>
#include <stdbool.h>
#include <iso646.h>
#include <avr/io.h>
#include "GlobalVar.h"
#include "PLC.h"

#define Uptime_ms     p->Uptime_ms     //[мс].
#define Ts_ms         p->Ts_ms         //[мс].
#define Ts            p->Ts            //[с].
#define Reset         p->Reset         //
#define Ts_ms_max     p->Ts_ms_max     //[мс].
#define Pulses_1000ms p->Pulses_1000ms //[мс].

#define SET_BIT(Var,Bit) ( Var = Var |  (1 << (Bit)) )
#define RST_BIT(Var,Bit) ( Var = Var & ~(1 << (Bit)) )

void PLC_Ts_ms(struct GlobalVar *p)
{
  //Рассчет шага дискретизации по времени [мс].
  //На вход функции подать millis() или его аналоги.
  //Функцию можно вызвать только в одном месте циклически.
  //     +-------------------+
  //  ->-|Uptime_ms     Ts_ms|->-
  //     +-------------------+

  static uint32_t Time_previous_ms = 0; //Предыдущее значение времени [мс].

  if (Time_previous_ms <= Uptime_ms)
  {
    Ts_ms = Uptime_ms - Time_previous_ms; //разность времени без переполнения (займа).
  }
  else
  {
    //Срока ниже или просто вычитание дает через несколько минут работы хз почему 0xffffff01
    //Ts_ms = (0xFFFFFFFF - Time_previous_ms) + Uptime_ms + 1; //разность времени при переполнении.
  }

  Time_previous_ms = Uptime_ms; //Запомнить предидущее состояние.

  return;
}

void PLC_Ts(struct GlobalVar *p)
{
  //     +-------------------+
  //  ->-|Ts_ms            Ts|->-
  //     +-------------------+

  Ts = ((float)Ts_ms) * 0.001;

  return;
}

void PLC_Ts_ms_max(struct GlobalVar *p)
{
  //     +-------------------+
  //  ->-|Ts_ms     Ts_ms_max|->-
  //     +-------------------+

  if (Ts_ms > Ts_ms_max)
  {
    Ts_ms_max = Ts_ms;
  }

  return;
}

void PLC_Pulses_1000ms(struct GlobalVar *p)
{
  //     +----------------------+
  //  ->-|Ts_ms    Pulses_1000ms|->-
  //  ->-|Reset                 |
  //  ->-|TIME_PERIOD           |
  //  ->-|TIME_PULSE            |
  //     +----------------------+

  const uint32_t TIME_PERIOD = 1000; //[мс].
  const uint32_t TIME_PULSE  = 500 ; //[мс].
  static uint32_t Timer1 = 0;

  if ((Timer1 >= TIME_PERIOD) or Reset)
  {
    Timer1 = 0;
  }
  else
  {
    Timer1 = Timer1 + Ts_ms;
  }

  if (Timer1 <= TIME_PULSE)
  {
    Pulses_1000ms = true;
  }
  else
  {
    Pulses_1000ms = false;
  }

  return;
}

void PLC_Digital_output_cyclic(struct GlobalVar *p)
{
  if (p->Do0)
  {
    (PORTB |= (1 << 5)); //LED_ON();
  }
  else
  {
    (PORTB &= ~(1 << 5)); //LED_OFF();
  }
  return;
}

void PLC_Digital_input_cyclic(struct GlobalVar *p)
{
  return;
}

void Program_delay_500ms(void)
{
  const uint64_t ARDUINO_NANO_MAGIC_CONST = 101218;
  volatile uint64_t i = 0;
  while (i <= ARDUINO_NANO_MAGIC_CONST)
  {
    i = i + 1;
  }
}

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
