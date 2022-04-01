/*
!!!��������!!!
������� +5 �����.
AVR Studio v4.18
���� C
���������� gcc ��� ����������� -O0
������������ / �������� JTAG ICE �� www.olimex.com
��������������� ATmega32.
������� ������ 14745600 ��.
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 14745600UL

//���������� ����������.
/*
��� ��� ����������� ����������� � ����� �� ������������ ��� ������ bool
�� ��������� ������ bool ������ ������� ����������� ����� �����.
��� ����:
FALSE ��� ����� ������ 0
TRUE ��� ����� �� ������ 0
��� TRUE ���������� ������������ �������� 255 = ~0 
��� ��� ��� ���� ��������� �������� ������� ������ � �����������.
*/
//����������� ����� ������ ����������� � ����������
uint8_t X1=0;//���������� ����
uint8_t X2=0;//���������� ����
uint8_t Y1=0;//���������� �����
uint8_t LedRun=0;//��������� ��� � ������
//�������� ���������� ���������
uint8_t X1previous=0;//���������� �������� ����� X1
uint8_t X1EdgePos=0;//�������� ������������ ������ X1
uint8_t X1EdgeNeg=0;//�������� ������������ ������ X1
uint8_t FilterState=0;//���� ��������� ��� ��������� ����������


//�������� ���������� ���������
uint8_t GeneratorState=0;//���� ��������� ��� ��������� ���������� ���������
uint8_t GeneratorCounter=0;//��������� ������� ��������� ��� ������������ ���������;
uint16_t GeneratorTimer=0;//������ ��� ������������ �������� ���������
const uint16_t GeneratorTimePulse =20;//����� �������� ����������  20��� * 10�� = 200��
const uint16_t GeneratorTimePause =20;//����� ����� ���������� 20��� * 10�� = 200��

//���������� ������ 10ms.
ISR(TIMER1_COMPA_vect){
//��������� ��� ����������.
cli();

//������ ����������� ����� X1 X2 � ���������� ���������.
//uint8_t LocalTemp1 = PINB;
if ((PINB & 0b00000010) == 0){X1=0b11111111;}
else{X1=0;}
if ((PINB & 0b00000001) == 0){X2=0b11111111;}
else{X2=0;}
//�������� ������������ ������ X1
X1EdgePos=X1 & (~X1previous);
//�������� ������������ ������ X1
X1EdgeNeg=(~X1) & X1previous;
//��������� ���������� ��������� ����� �1
X1previous=X1;


if (X1EdgePos) {GeneratorCounter=GeneratorCounter+1;}


//�������� �������� ����������
switch (FilterState){
case 0:{
	break;}
//���� ��� �� ����� �� ���
default:{
	FilterState=0;
	break;}
}//switch (State1)

//��������� ��������� 1�������=1���������
switch (GeneratorState){
//�������� ���������
case 0:{
	if(GeneratorCounter!=0)
	{GeneratorState=1;}
	break;}
//��������� ������ ��������� ����������� ����� ��������
case 1:{
	Y1=0b11111111;
	//������ �������� Y1.
	asm volatile ("SBI %0,%1" :/* no outputs */: "I" (_SFR_IO_ADDR(PORTD)),"I" (6) );
	GeneratorState=2;
	break;}
//��������� ����� ��������
case 2:{
	if(GeneratorTimer>=GeneratorTimePulse){
	GeneratorTimer=0;
	GeneratorState=3;}
	else{
	GeneratorTimer=GeneratorTimer+1;}
	break;}
//��������� ������ ��������� ����������� ����� ��������
case 3:{
	Y1=0;
	//������ ��������� Y1.
	asm volatile ("CBI %0,%1" :/* no outputs */: "I" (_SFR_IO_ADDR(PORTD)),"I" (6) );
	GeneratorState=4;
	break;}
//��������� ����� �����
case 4:{
	if(GeneratorTimer>=GeneratorTimePause){
	GeneratorTimer=0;
	GeneratorCounter=GeneratorCounter-1;
	GeneratorState=0;}
	else{
	GeneratorTimer=GeneratorTimer+1;}
	break;}
//���� ��� �� ����� �� ���
default:{
	GeneratorState=0;
	break;}
}//switch (State2)

//��������� ��� ����������.
sei();
}//ISR(TIMER1_COMPA_vect)

int main (void) {

//�������� ������ ������
DDRA = DDRA | 0b00000001; //PA0 �� �����
DDRA = DDRA | 0b00000010; //PA1 �� �����
DDRD = DDRD | 0b01000000; //PD6 �� �����
DDRD = DDRD | 0b10000000; //PD7 �� �����
DDRC = DDRC | 0b00000001; //PC0 �� �����

//�������� ������ �����
DDRB = DDRB & 0b11111110; //PB0 �� �����
DDRB = DDRB & 0b11111101; //PB1 �� �����

//��������� ���������� ������ 10��
/*
������ 1 � ������ CTC
(14745600��/1024)=14400��.
(1/14400��)*144=0.01�.
144dec=90hex
*/
OCR1AH=0x00;
OCR1AL=0x90; 
TCCR1A=0b00000000;
TCCR1B=0b00001101; //������������ 1024
TIMSK=0b00010000; //OCIE1A=1 ���������� � �������1.

//��������� ��� ����������.
sei();

//����������� ���� ������������ ������ ��� ���������.
while (1) {

//������ ����������� ����� X1 � ���������� ���������.
if ((PINB & 0b00000010) == 0){X1=0b11111111;}
else{X1=0;}

//������ ����������� ����� X2 � ���������� ���������.
if ((PINB & 0b00000001) == 0){X2=0b11111111;}
else{X2=0;}

//��������� RUN.
LedRun=~0;

//������ ����������� ������ Y1
if (Y1 == 0) {
PORTD=PORTD & 0b10111111;}
else {
PORTD=PORTD | 0b01000000;}

//������������ ��������� ��� X1
if (X1 == 0) {
PORTA=PORTA & 0b11111110;}
else {
PORTA=PORTA | 0b00000001;}

//������������ ��������� ��� X2
if (X2 == 0) {
PORTA=PORTA & 0b11111101;}
else {
PORTA=PORTA | 0b00000010;}

//������������ ��������� ��� Y1
if (Y1 == 0) {
PORTC=PORTC & 0b11111110;}
else {
PORTC=PORTC | 0b00000001;}

//������������ ��������� ��� RUN
if (LedRun == 0) {
PORTD=PORTD & 0b01111111;}
else {
PORTD=PORTD | 0b10000000;}

} //while (1)
} //int main (void)
