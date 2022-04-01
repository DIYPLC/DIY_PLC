/*
!!!ЧЕРНОВИК!!!
Питание +5 Вольт.
AVR Studio v4.18
Язык C
Компилятор gcc без оптимизации -O0
Программатор / отладчик JTAG ICE от www.olimex.com
Микроконтроллер ATmega32.
Частота кварца 14745600 Гц.
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 14745600UL

//Глобальные переменные.
/*
Так как архитектура контроллера и языка не поддерживает тип данных bool
то применяем вместо bool восьми битовое беззнаковое целое цисло.
При этом:
FALSE это число равное 0
TRUE это число не равное 0
Для TRUE желательно использовать значение 255 = ~0 
так как при этом корректно работает битовая логика с переменными.
*/
//Отобращение ввода вывода контроллера в переменные
uint8_t X1=0;//Дискретный вход
uint8_t X2=0;//Дискретный вход
uint8_t Y1=0;//Дискретный выход
uint8_t LedRun=0;//Светодиод ПЛК в работе
//Алгоритм фильтрации импульсов
uint8_t X1previous=0;//Предидущее значение входа X1
uint8_t X1EdgePos=0;//Детектор нарастающего фронта X1
uint8_t X1EdgeNeg=0;//Детектор ниспадающего фронта X1
uint8_t FilterState=0;//Граф состояний для алгоритма фильтрации


//Алгоритм генератора импульсов
uint8_t GeneratorState=0;//Граф состояний для алгоритма генератора импульсов
uint8_t GeneratorCounter=0;//Локальный счетчик заготовок для формирования импульсов;
uint16_t GeneratorTimer=0;//Таймер для формирования импульса заготовки
const uint16_t GeneratorTimePulse =20;//Время импульса генератора  20раз * 10мс = 200мс
const uint16_t GeneratorTimePause =20;//Время паузы генератора 20раз * 10мс = 200мс

//Прерывание каждые 10ms.
ISR(TIMER1_COMPA_vect){
//Запретить все прерывания.
cli();

//Чтение дискретного входа X1 X2 с аппаратной инверсией.
//uint8_t LocalTemp1 = PINB;
if ((PINB & 0b00000010) == 0){X1=0b11111111;}
else{X1=0;}
if ((PINB & 0b00000001) == 0){X2=0b11111111;}
else{X2=0;}
//Детектор нарастающего фронта X1
X1EdgePos=X1 & (~X1previous);
//Детектор ниспадающего фронта X1
X1EdgeNeg=(~X1) & X1previous;
//Запомнить предидущее состояние входа Х1
X1previous=X1;


if (X1EdgePos) {GeneratorCounter=GeneratorCounter+1;}


//Основной алгоритм фильтрации
switch (FilterState){
case 0:{
	break;}
//если что то пошло не так
default:{
	FilterState=0;
	break;}
}//switch (State1)

//Генератор импульсов 1импульс=1заготовка
switch (GeneratorState){
//ожидание заготовки
case 0:{
	if(GeneratorCounter!=0)
	{GeneratorState=1;}
	break;}
//Заготовка пришла формируем нарастающий фронт импульса
case 1:{
	Y1=0b11111111;
	//Быстро включить Y1.
	asm volatile ("SBI %0,%1" :/* no outputs */: "I" (_SFR_IO_ADDR(PORTD)),"I" (6) );
	GeneratorState=2;
	break;}
//Формируем время импульса
case 2:{
	if(GeneratorTimer>=GeneratorTimePulse){
	GeneratorTimer=0;
	GeneratorState=3;}
	else{
	GeneratorTimer=GeneratorTimer+1;}
	break;}
//Заготовка пришла формируем ниспадающий фронт импульса
case 3:{
	Y1=0;
	//Быстро выключить Y1.
	asm volatile ("CBI %0,%1" :/* no outputs */: "I" (_SFR_IO_ADDR(PORTD)),"I" (6) );
	GeneratorState=4;
	break;}
//Формируем время паузы
case 4:{
	if(GeneratorTimer>=GeneratorTimePause){
	GeneratorTimer=0;
	GeneratorCounter=GeneratorCounter-1;
	GeneratorState=0;}
	else{
	GeneratorTimer=GeneratorTimer+1;}
	break;}
//если что то пошло не так
default:{
	GeneratorState=0;
	break;}
}//switch (State2)

//Разрешить все прерывания.
sei();
}//ISR(TIMER1_COMPA_vect)

int main (void) {

//Настройа портов вывода
DDRA = DDRA | 0b00000001; //PA0 на вывод
DDRA = DDRA | 0b00000010; //PA1 на вывод
DDRD = DDRD | 0b01000000; //PD6 на вывод
DDRD = DDRD | 0b10000000; //PD7 на вывод
DDRC = DDRC | 0b00000001; //PC0 на вывод

//Настройа портов ввода
DDRB = DDRB & 0b11111110; //PB0 на вывод
DDRB = DDRB & 0b11111101; //PB1 на вывод

//Настройка прерывания каждые 10мс
/*
Таймер 1 в режиме CTC
(14745600Гц/1024)=14400Гц.
(1/14400Гц)*144=0.01с.
144dec=90hex
*/
OCR1AH=0x00;
OCR1AL=0x90; 
TCCR1A=0b00000000;
TCCR1B=0b00001101; //Предделитель 1024
TIMSK=0b00010000; //OCIE1A=1 Совпадение А таймера1.

//Разрешить все прерывания.
sei();

//Бесконечный цикл используется только для индикации.
while (1) {

//Чтение дискретного входа X1 с аппаратной инверсией.
if ((PINB & 0b00000010) == 0){X1=0b11111111;}
else{X1=0;}

//Чтение дискретного входа X2 с аппаратной инверсией.
if ((PINB & 0b00000001) == 0){X2=0b11111111;}
else{X2=0;}

//Светодиод RUN.
LedRun=~0;

//Запись дискретного выхода Y1
if (Y1 == 0) {
PORTD=PORTD & 0b10111111;}
else {
PORTD=PORTD | 0b01000000;}

//Сведодиодная подсветка для X1
if (X1 == 0) {
PORTA=PORTA & 0b11111110;}
else {
PORTA=PORTA | 0b00000001;}

//Сведодиодная подсветка для X2
if (X2 == 0) {
PORTA=PORTA & 0b11111101;}
else {
PORTA=PORTA | 0b00000010;}

//Сведодиодная подсветка для Y1
if (Y1 == 0) {
PORTC=PORTC & 0b11111110;}
else {
PORTC=PORTC | 0b00000001;}

//Сведодиодная подсветка для RUN
if (LedRun == 0) {
PORTD=PORTD & 0b01111111;}
else {
PORTD=PORTD | 0b10000000;}

} //while (1)
} //int main (void)
