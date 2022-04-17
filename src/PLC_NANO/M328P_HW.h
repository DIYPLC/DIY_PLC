#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

void    USART0_INIT(void);
void    USART0_RX_ON(void);
void    USART0_TX_ON(void);
uint8_t USART0_READ_BYTE(void); //Читаем байт из USART0;
void    USART0_WRITE_BYTE(uint8_t In);
void    GPIO_INIT(void);
void    TIMER1_INIT(void);

//void DDRC_BIT0_WRITE(bool value);
//void PORTC_BIT0_WRITE(bool value);
//bool PINC_BIT0_READ(void);

#define INTERRUPT_OFF(); asm volatile ("cli");
#define INTERRUPT_ON(); asm volatile ("sei");
#define NOP(); asm volatile ("nop");
#define DDRB_BIT_5_SET(); asm volatile ("sbi %0,%1" :/* no outputs */: "I" (_SFR_IO_ADDR(DDRB)),"I" (5) );
#define PORTB_BIT_5_SET(); asm volatile ("sbi %0,%1" :/* no outputs */: "I" (_SFR_IO_ADDR(PORTB)),"I" (5) );
#define PORTB_BIT_5_RST(); asm volatile ("cbi %0,%1" :/* no outputs */: "I" (_SFR_IO_ADDR(PORTB)),"I" (5) );


#ifdef __cplusplus
}
#endif
