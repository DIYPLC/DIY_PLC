#pragma once

#ifdef __cplusplus
extern "C"
{
#endif
//Аппаратно зависимые функции ATmega328p 16MHz 5VDC

void USART0_INIT(void); //Инициализация USART0 9600 8N1
void USART0_RX_ON(void); //Включаем приемник
void USART0_TX_ON(void); //Включаем передатчик
uint8_t USART0_READ_BYTE(void); //Читаем байт из USART0
void USART0_WRITE_BYTE(uint8_t In); //Пишем байт в USART0
void GPIO_INIT(void);
void TIMER1_INIT(void); //Настраиваем прерывание каждые 100ms
void TIMER2_INIT(void); //Настраиваем прерывание каждые 1ms
void Program_delay_500ms(void);
void PLC_Digital_output_cyclic(struct GlobalVar *p);
void PLC_Digital_input_cyclic(struct GlobalVar *p);

#define INTERRUPT_OFF(); asm volatile ("cli");
#define INTERRUPT_ON(); asm volatile ("sei");
#define NOP(); asm volatile ("nop");
#define DDRB_BIT_5_SET(); asm volatile ("sbi %0,%1" :/* no outputs */: "I" (_SFR_IO_ADDR(DDRB)),"I" (5) );
#define PORTB_BIT_5_SET(); asm volatile ("sbi %0,%1" :/* no outputs */: "I" (_SFR_IO_ADDR(PORTB)),"I" (5) );
#define PORTB_BIT_5_RST(); asm volatile ("cbi %0,%1" :/* no outputs */: "I" (_SFR_IO_ADDR(PORTB)),"I" (5) );

#ifdef __cplusplus
}
#endif
