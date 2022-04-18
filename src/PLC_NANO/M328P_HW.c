#include <stdint.h>
#include <stdbool.h>
#include <iso646.h>
#include <avr/io.h>
#include "M328P_HW.h"

#define SET_BIT(Var,Bit) ( Var = Var |  (1 << (Bit)) )
#define RST_BIT(Var,Bit) ( Var = Var & ~(1 << (Bit)) )

//Для ADM2486BRVZ
#define INIT_LED() (DDRB  |=  (1 << 5))
#define LED_ON()   (PORTB |=  (1 << 5))
#define LED_OFF()  (PORTB &= ~(1 << 5))

//Описание регистров в книге:
//Евстифеев А.В. Микроконтроллеры AVR семейства Mega руководство пользователя

/****************************************************************************************/

void USART0_INIT(void) //Инициализация USART0
{
  //Настройка UART0 9600 8N1
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
  UBRR0H =   0; //Скорость передачи 9600 бит/с ошибка 0.2%
  UBRR0L = 103; //Скорость передачи 9600 бит/с ошибка 0.2%
  //16000000/(16*(103+1)) = 9615.38 бит/с фактическая скорость.
  return;
}

void USART0_RX_ON(void)
{
  LED_OFF();
  //UCSR0B = 0b10010000; //Включаем приемник
  RST_BIT(UCSR0B, TXCIE0); //Запрет прерывания по завершении передачи.
  RST_BIT(UCSR0B,  TXEN0); //Запрет передачи.
  SET_BIT(UCSR0B, RXCIE0); //Разрешение прерывания по завершении приема.
  SET_BIT(UCSR0B,  RXEN0); //Разрешение приема.
  return;
}

void USART0_TX_ON(void)
{
  LED_ON();
  //UCSR0B = 0b01001000; //Включаем передатчик
  RST_BIT(UCSR0B, RXCIE0); //Запрет прерывания по завершении приема.
  RST_BIT(UCSR0B,  RXEN0); //Запрет приема.
  SET_BIT(UCSR0B, TXCIE0); //Разрешение прерывания по завершении передачи.
  SET_BIT(UCSR0B,  TXEN0); //Разрешение передачи.
  return;
}

uint8_t USART0_READ_BYTE(void) //Читаем байт из USART0;
{
  return UDR0;
}

void USART0_WRITE_BYTE(uint8_t In)
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

void TIMER1_INIT(void)
{
  //Настраиваем прерывание каждые 1ms
  //ATmega328p 16MHz
  //HW Timer 1 CTC mode сброс при совпадении
  //500Hz = 16000000/(2*64*(1+249)) //data sheet
  //500Hz = 2ms period = 1ms time pulse (time call ISR)
  OCR1AH = 0; //регистр сравнения
  OCR1AL = 249; //регистр сравнения
  RST_BIT(TCCR1A, WGM10); //регистр управления CTC mode сброс при совпадении
  RST_BIT(TCCR1A, WGM11); //регистр управления CTC mode сброс при совпадении
  SET_BIT(TCCR1B, WGM12); //регистр управления CTC mode сброс при совпадении
  RST_BIT(TCCR1B, WGM13); //регистр управления CTC mode сброс при совпадении
  SET_BIT(TCCR1B,  CS10); //регистр управления Предделитель 64
  SET_BIT(TCCR1B,  CS11); //регистр управления Предделитель 64
  RST_BIT(TCCR1B,  CS12); //регистр управления Предделитель 64
  TCCR1C = 0; //регистр управления
  SET_BIT(TIMSK1, OCIE1A); //маскирование прерываний Совпадение А таймера1.
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
