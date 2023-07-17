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

void USART0_INIT(void) //Инициализация USART0 9600 8N1
{
  //ATmega328p 16MHz
  UCSR0A = 0;
  UCSR0B = 0;
  UCSR0C = 0;
  //UCSR0A = 0;
  //UCSR0B = 0b10010000; //Включаем приемник
  //UCSR0C = 0b00000110; //Формат посылок
  RST_BIT(UCSR0A,    U2X0); //Удвоенная скорость обмена - выключена
  SET_BIT(UCSR0B,  RXCIE0); //Разрешение прерывания по завершении приема.
  SET_BIT(UCSR0B,   RXEN0); //Разрешение приема.
  RST_BIT(UCSR0B,  UCSZ02); //Формат посылок Размер передаваемого слова 8 бит.
  SET_BIT(UCSR0C,  UCSZ01); //Формат посылок Размер передаваемого слова 8 бит.
  SET_BIT(UCSR0C,  UCSZ00); //Формат посылок Размер передаваемого слова 8 бит.
  RST_BIT(UCSR0C, UMSEL01); //Асинхронный режим UART.
  RST_BIT(UCSR0C, UMSEL00); //Асинхронный режим UART.
  RST_BIT(UCSR0C,   UPM01); //Контроля и бита четности нет.
  RST_BIT(UCSR0C,   UPM00); //Контроля и бита четности нет.
  RST_BIT(UCSR0C,   USBS0); //1 Стоповый бит.
  //16000000/(16*(103+1)) = 9615.38 бит/с фактическая скорость.
  UBRR0H =   0; //Скорость передачи 9600 бит/с ошибка 0.2%
  UBRR0L = 103; //Скорость передачи 9600 бит/с ошибка 0.2%
  //16000000/(16*(51+1)) = 19230.76 бит/с фактическая скорость.
  //UBRR0H =  0; //Скорость передачи 19200 бит/с ошибка 0.2%
  //UBRR0L = 51; //Скорость передачи 19200 бит/с ошибка 0.2%
  //16000000/(16*(25+1)) = 38461.53 бит/с фактическая скорость.
  //UBRR0H =  0; //Скорость передачи 38400 бит/с ошибка 0.2%
  //UBRR0L = 25; //Скорость передачи 38400 бит/с ошибка 0.2%

  return;
}

void USART0_RX_ON(void) //Включаем приемник
{
  LED_OFF();
  //UCSR0B = 0b10010000; //Включаем приемник
  RST_BIT(UCSR0B, TXCIE0); //Запрет прерывания по завершении передачи.
  RST_BIT(UCSR0B,  TXEN0); //Запрет передачи.
  SET_BIT(UCSR0B, RXCIE0); //Разрешение прерывания по завершении приема.
  SET_BIT(UCSR0B,  RXEN0); //Разрешение приема.
  return;
}

void USART0_TX_ON(void) //Включаем передатчик
{
  LED_ON();
  //UCSR0B = 0b01001000; //Включаем передатчик
  RST_BIT(UCSR0B, RXCIE0); //Запрет прерывания по завершении приема.
  RST_BIT(UCSR0B,  RXEN0); //Запрет приема.
  SET_BIT(UCSR0B, TXCIE0); //Разрешение прерывания по завершении передачи.
  SET_BIT(UCSR0B,  TXEN0); //Разрешение передачи.
  return;
}

uint8_t USART0_READ_BYTE(void) //Читаем байт из USART0
{
  return UDR0;
}

void USART0_WRITE_BYTE(uint8_t In) //Пишем байт в USART0
{
  UDR0 = In;
  return;
}

/****************************************************************************************/

void GPIO_INIT(void)
{
  INIT_LED();
  return;
}

/****************************************************************************************/

void TIMER1_INIT(void) //Настраиваем прерывание каждые 100ms
{
  //ATmega328p 16MHz
  //16bit Timer1
  //HW Timer 1 CTC mode сброс при совпадении
  //5Hz = 16000000/(2*64*(1+24999)) //data sheet
  //5Hz = 200ms period = 100ms time pulse (time call ISR)
  OCR1AH = 0x61; //Регистр сравнения
  OCR1AL = 0xA7; //Регистр сравнения
  RST_BIT(TCCR1A, WGM10); //Регистр управления CTC mode сброс при совпадении
  RST_BIT(TCCR1A, WGM11); //Регистр управления CTC mode сброс при совпадении
  SET_BIT(TCCR1B, WGM12); //Регистр управления CTC mode сброс при совпадении
  RST_BIT(TCCR1B, WGM13); //Регистр управления CTC mode сброс при совпадении
  SET_BIT(TCCR1B,  CS10); //Регистр управления Предделитель 64
  SET_BIT(TCCR1B,  CS11); //Регистр управления Предделитель 64
  RST_BIT(TCCR1B,  CS12); //Регистр управления Предделитель 64
  TCCR1C = 0; //регистр управления
  SET_BIT(TIMSK1, OCIE1A); //Маскирование прерываний совпадение А таймера1.
  return;
}

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
  if (p->Do0)
  {
    //LED_ON();
  }
  else
  {
    //LED_OFF();
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
