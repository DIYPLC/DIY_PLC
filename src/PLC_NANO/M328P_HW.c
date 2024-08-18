#include <stdint.h>
#include <stdbool.h>
#include <iso646.h>
#include <avr/io.h>
#include "GlobalVar.h" //Глобальные переменные ПЛК.
#include "M328P_HW.h" //Аппаратно зависимые функции ATmega328p 16MHz 5VDC

#define SET_BIT(Var,Bit) ( Var = Var |  (1 << (Bit)) )
#define RST_BIT(Var,Bit) ( Var = Var & ~(1 << (Bit)) )

//Для ADM2486BRVZ
#define INIT_LED() (DDRB  |=  (1 << 5))
#define LED_ON()   (PORTB |=  (1 << 5))
#define LED_OFF()  (PORTB &= ~(1 << 5))

//Описание регистров в книге:
//Евстифеев А.В. Микроконтроллеры AVR семейства Mega руководство пользователя

/****************************************************************************************/

void GPIO_INIT(void)
{
  INIT_LED();
  return;
}

/****************************************************************************************/

void TIMER2_INIT(void) //Настраиваем прерывание каждые 1ms
{
  //ATmega328p 16MHz
  //8bit Timer2
  //HW Timer 1 CTC mode сброс при совпадении
  //500Hz = 16000000/(2*64*(1+249)) //data sheet
  //500Hz = 2ms period = 1ms time pulse (time call ISR)
  OCR2A = 249; //Регистр сравнения
  RST_BIT(TCCR2A, WGM20); //Регистр управления CTC mode сброс при совпадении
  SET_BIT(TCCR2A, WGM21); //Регистр управления CTC mode сброс при совпадении
  RST_BIT(TCCR2B, WGM22); //Регистр управления CTC mode сброс при совпадении
  RST_BIT(TCCR2B,  CS20); //Регистр управления Предделитель 64
  RST_BIT(TCCR2B,  CS21); //Регистр управления Предделитель 64
  SET_BIT(TCCR2B,  CS22); //Регистр управления Предделитель 64
  SET_BIT(TIMSK2, OCIE2A); //Маскирование прерываний совпадение А таймера1.
  return;
}

void Program_delay_500ms(void)
{
  //Arduino nano 16MHz
  const uint64_t ARDUINO_NANO_MAGIC_CONST = 101218;
  volatile uint64_t i = 0;
  while (i <= ARDUINO_NANO_MAGIC_CONST)
  {
    i = i + 1;
  }
}

void PLC_Digital_output_cyclic(struct GlobalVar *p)
{
  if (p->Do1)
  {
    LED_ON();
  }
  else
  {
    LED_OFF();
  }
  return;
}

void PLC_Digital_input_cyclic(struct GlobalVar *p)
{
  return;
}

/****************************************************************************************/

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
