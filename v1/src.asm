/* 
	������ ������.
�1. �������� ����� ��������.
�2. ���� ������ ������� ����� 160�� �� �3 ����� �1
�3. �������� ����� �����.
�4. ���� ����� ����� ����� 40�� �� �5 ����� �1
�5. ���� ����� � ������ ������ �������� �� ��������� �������� ������� ������� ���������.
�6. ���� �1.

��� ������������� �� ������� Ts =0,5ms.
*/

.include "tn2313def.inc"
;������������� ���������� � ������
#define tmp R16 ;��������� ���������� ���� ������������
#define SensorNew R17 ;����� ������ PIND.4
#define SensorOld R18 ;������ B2D PIND.5
#define SensorNewPrevios R19 ;���������� ��������� �������
#define SensorOldPrevios R20 ;���������� ��������� �������
#define Output R21 ;����� �� CTI PORTD.6
#define ti1L R22 ;������ ������� ��������L
#define ti1H R23 ;������ ������� ��������H
#define tp1L R24 ;������ ������ �����L
#define tp1H R25 ;������ ������ �����H
#define gtL R26 ;��������� ���������- ������L
#define gtH R27 ;��������� ���������- ������H
#define Status R28 ;������ ����� ���������
#define gpcnt R29 ;��������� ���������- ������� ���������

.equ TRUE = 0b00000001
.equ FALSE = 0b00000000
.equ ti1Lmax = 0x40 ;0x(160ms x2) ���� ���� ���1
.equ ti1Hmax = 0x01
.equ tp1Lmax = 0x50 ;0x(40ms x2) ���� ���� ����1
.equ tp1Hmax = 0x00
.equ gtiL = 0x90 ;0x(200ms x2) ������������ ��� ���
.equ gtiH = 0x01
.equ gtendL = 0x20 ;0x(400ms x2) ��� ������ ��� ���
.equ gtendH = 0x03

;������� �������� ���������� tiny2313
.org 0x0000 rjmp RESET ; Reset Handler
.org 0x0001 rjmp RESET ; External Interrupt0 Handler
.org 0x0002 rjmp RESET ; External Interrupt1 Handler
.org 0x0003 rjmp RESET ; Timer1 Capture Handler
.org 0x0004 rjmp TIM1_COMPA ; Timer1 CompareA Handler
.org 0x0005 rjmp RESET ; Timer1 Overflow Handler
.org 0x0006 rjmp RESET ; Timer0 Overflow Handler
.org 0x0007 rjmp RESET ; USART0 RX Complete Handler
.org 0x0008 rjmp RESET ; USART0,UDR Empty Handler
.org 0x0009 rjmp RESET ; USART0 TX Complete Handler
.org 0x000A rjmp RESET ; Analog Comparator Handler
.org 0x000B rjmp RESET ; Pin Change Interrupt
.org 0x000C rjmp RESET ; Timer1 Compare B Handler
.org 0x000D rjmp RESET ; Timer0 Compare A Handler
.org 0x000E rjmp RESET ; Timer0 Compare B Handler
.org 0x000F rjmp RESET ; USI Start Handler
.org 0x0010 rjmp RESET ; USI Overflow Handler
.org 0x0011 rjmp RESET ; EEPROM Ready Handler
.org 0x0012 rjmp RESET ; Watchdog Overflow Handler

;�������������
RESET:
LDI R16,0x00
MOV R0,R16
MOV R1,R16
MOV R2,R16
MOV R3,R16
MOV R4,R16
MOV R5,R16
MOV R6,R16
MOV R7,R16
MOV R8,R16
MOV R9,R16
MOV R10,R16
MOV R11,R16
MOV R12,R16
MOV R13,R16
MOV R14,R16
MOV R15,R16
MOV R16,R16
MOV R17,R16
MOV R18,R16
MOV R19,R16
MOV R20,R16
MOV R21,R16
MOV R22,R16
MOV R23,R16
MOV R24,R16
MOV R25,R16
MOV R26,R16
MOV R27,R16
MOV R28,R16
MOV R29,R16
MOV R30,R16
MOV R31,R16
LDI tmp,0xDF ;��������� ����� � ����� ���
OUT SPL,tmp
SBI DDRD,6 ;��������� PD6 �� �����
SBI DDRD,3 ;��������� PD3 �� �����
SBI DDRB,4 ;��������� PB4 �� �����
SBI DDRB,3 ;��������� PB3 �� �����
SBI DDRB,2 ;��������� PB2 �� �����
SBI DDRB,1 ;��������� PB1 �� �����
SBI DDRB,0 ;��������� PB0 �� �����
;��������� ���������� �������1 ������ 500���
LDI tmp,0x07
OUT OCR1AH,tmp
LDI tmp,0xD0
OUT OCR1AL,tmp
LDI tmp,0b00000000
OUT TCCR1A,tmp
LDI tmp,0b00001001
OUT TCCR1B,tmp
LDI tmp,0b01000000
OUT TIMSK,tmp
;������ ������ ����� ��� ������������� ����������� ��������� �������
;SensorNew.0=PIND.4
;SensorOld.0=PIND.5
IN tmp,PIND
BST tmp,4 ;push bit T
BLD SensorNew,0 ;pop bit T
BST tmp,5 ;push bit T
BLD SensorOld,0 ;pop bit T
;SensorOldPrevios=SensorOld
;SensorNewPrevios=SensorNew
MOV SensorOldPrevios,SensorOld
MOV SensorNewPrevios,SensorNew
SEI ;��������� ����������

;������� ���������
MAIN:
;����� ������ ������ � ����������� �� JP1
;if PD0=0 then TRANZIT else FILTER_ON
IN tmp,PIND
BST tmp,0 ;PD0 push bit T
BRTS FILTER_ON
BRTC TRANZIT
;------------------------------------------------------------------
;������ ���������� ����� ������ ��� ����������
TRANZIT:
;PB0=PD4
IN tmp,PIND
COM tmp ;���101�� ����������� ���� ������� not.
BST tmp,4 ;PD4 push bit T
BRTS SET_PB0_TRANZIT
BRTC CLEAR_PB0_TRANZIT
SET_PB0_TRANZIT: 
SBI PORTB,0
RJMP LABEL_TRANZIT
CLEAR_PB0_TRANZIT: 
CBI PORTB,0
LABEL_TRANZIT:
;PD6=PD5
IN tmp,PIND
COM tmp ;���101�� ����������� ���� ������� not.
BST tmp,5 ;PD5 push bit T
BRTS SET_PD6_TRANZIT
BRTC CLEAR_PD6_TRANZIT
SET_PD6_TRANZIT: 
SBI PORTD,6
RJMP LABEL_TRANZIT2
CLEAR_PD6_TRANZIT: 
CBI PORTD,6
LABEL_TRANZIT2:
;���� ���������� ����� ������� ����� ��� 4 ����������.
SBI PORTB,4
SBI PORTB,3
SBI PORTB,2
SBI PORTB,1
RJMP MAIN ;����������� ���� ������� ���������.
;����� ���������� ����� ������ ��� ����������
;------------------------------------------------------------------
;������ ���������� ����� ������ � �����������
FILTER_ON:
CBI PORTB,0 ;���������� ������� �������� 1
;SensorNew.0=PIND.4
;SensorOld.0=PIND.5
IN tmp,PIND
COM tmp ;���101�� ����������� ���� ������� not.
BST tmp,4 ;push bit T
BLD SensorNew,0 ;pop bit T
BST tmp,5 ;push bit T
BLD SensorOld,0 ;pop bit T
;PORTD.6=Output.0
BST Output,0 ;push bit T
BRTS SET_PD6
BRTC CLEAR_PD6
SET_PD6: 
SBI PORTD,6
RJMP LABEL1
CLEAR_PD6: 
CBI PORTD,6
LABEL1:
RJMP MAIN ;����������� ���� ������� ���������.
;����� ���������� ����� ������ � �����������
;����� main
;------------------------------------------------------------------

;���������� �� ������� ������ 500���
TIM1_COMPA:
;��������� "�����������" � ��������� ���
CLI
sbi PORTD,3 ;������� T=0,5ms
PUSH tmp
IN tmp,SREG
PUSH tmp
;���������� ����� ���������
CPI Status,3
BRNE TEST_STATUS2
RCALL STATUS3 
TEST_STATUS2:
CPI Status,2
BRNE TEST_STATUS1
RCALL STATUS2 
TEST_STATUS1:
CPI Status,1
BRNE TEST_STATUS0
RCALL STATUS1 
TEST_STATUS0:
CPI Status,0
BRNE TEST_STATUS_END
RCALL STATUS0 
TEST_STATUS_END:
RCALL PULSE_GENERATOR
;��������� ���������� ��������� ������.
MOV SensorNewPrevios,SensorNew
MOV SensorOldPrevios,SensorOld
;������������ "�����������" � ��������� ���
POP tmp
OUT SREG,tmp
POP tmp
cbi PORTD,3 ;������� T=0,5ms
SEI
RETI

STATUS0: ;�������� ������ ������� ��������.
;���������
SBI PORTB,4
CBI PORTB,3
CBI PORTB,2
CBI PORTB,1
;����� ����������� ��������
LDI ti1L,0x00
LDI ti1H,0x00
LDI tp1L,0x00
LDI tp1H,0x00
;�������� �� �����
PUSH SensorNewPrevios
COM SensorNewPrevios ;NOT
AND SensorNewPrevios,SensorNew
BST SensorNewPrevios,0 ;push bit T
POP SensorNewPrevios
BRTC EXIT_STATUS0 ;if T=0 ��� �� �����
LDI Status,1 ;if T=1 ��� �����
EXIT_STATUS0:
RET

STATUS1: ;��������� ������������ ������� �������� � �������� ������� �����.
;���������
CBI PORTB,4
SBI PORTB,3
CBI PORTB,2
CBI PORTB,1
;��������� ������������ �������
LDI tmp,1
ADD ti1L,tmp
LDI tmp,0
ADC ti1H,tmp
;����� ������� ���� ������� ������ ��������� �������
//ti1max-ti1
LDI tmp,ti1Lmax
SUB tmp,ti1L
LDI tmp,ti1Hmax
SBC tmp,ti1H
BRCS OVERFLOV_EXIT_STATUS1;if c=1 goto...
;�������� �� ����
PUSH SensorNew
COM SensorNew ;NOT
AND SensorNew,SensorNewPrevios
BST SensorNew,0 ;push bit T
POP SensorNew
BRTC EXIT_STATUS1 ;if T=0 ��� �� ����
LDI Status,2 ;if T=1 ��� ����
EXIT_STATUS1:
RET
OVERFLOV_EXIT_STATUS1:
LDI Status,0
RET 

STATUS2: ;��������� ������������ ������ ����� � �������� ������� ������.
;���������
CBI PORTB,4
CBI PORTB,3
SBI PORTB,2
CBI PORTB,1
;��������� ������������ �������
LDI tmp,1
ADD tp1L,tmp
LDI tmp,0
ADC tp1H,tmp
;����� ������� ���� ������� ������ ��������� �������
//tp1max-tp1
LDI tmp,tp1Lmax
SUB tmp,tp1L
LDI tmp,tp1Hmax
SBC tmp,tp1H
BRCS OVERFLOV_EXIT_STATUS2;if c=1 goto...
;�������� �� �����
PUSH SensorNewPrevios
COM SensorNewPrevios ;NOT
AND SensorNewPrevios,SensorNew
BST SensorNewPrevios,0 ;push bit T
POP SensorNewPrevios
BRTC EXIT_STATUS2 ;if T=0 ��� �� �����
LDI Status,3 ;if T=1 ��� �����
EXIT_STATUS2:
RET
OVERFLOV_EXIT_STATUS2:
LDI Status,0
RET

STATUS3: ;������ ��������� ���� �������� �� ����� ����������� ������� ��������.
;���������
CBI PORTB,4
CBI PORTB,3
CBI PORTB,2
SBI PORTB,1
;SensorNew&SensorOld
MOV tmp,SensorNew
AND tmp,SensorOld
BST tmp,0 ;push bit T
BRTC EXIT_STATUS3 ;if T=0...
INC gpcnt ;if SensorNew&SensorOld=1 then counter+1
EXIT_STATUS3:
LDI Status,0;Status=0
RET

PULSE_GENERATOR: ;��������� ��������� 1�������=1���������
;if gpcnt=0 retunr
CPI gpcnt,0
BREQ EXIT_PULSE_GENERATOR
;gt+1
LDI tmp,1
ADD gtL,tmp
LDI tmp,0
ADC gtH,tmp
;if gt < gti then Output=1 esle Output=0
PUSH gtH
PUSH gtL
LDI tmp,gtiL //gt-gti
SUB gtL,tmp
LDI tmp,gtiH 
SBC gtH,tmp 
POP gtL
POP gtH
BRCS SET_OUT_TRUE
BRCC SET_OUT_FALSE
SET_OUT_TRUE:
LDI Output,1
RJMP GENERATOR_NEXT_IF_2
SET_OUT_FALSE:
LDI Output,0
GENERATOR_NEXT_IF_2: 
;if gt > gtend then gt=0
;if gt > gtend then gpcnt-1
PUSH gtH
PUSH gtL
LDI tmp,gtendL //gt-gtend
SUB gtL,tmp
LDI tmp,gtendH 
SBC gtH,tmp 
POP gtL
POP gtH
BRCC DEC_COUNTER
BRCS EXIT_PULSE_GENERATOR
DEC_COUNTER:
DEC gpcnt
LDI gtL,0
LDI gtH,0
EXIT_PULSE_GENERATOR:
RET

;DEBUG:
;ti=1mks tp=1mks 4 000 000 hz ZQ
;SBI PORTB,4 ;RT cntrl for debug
;SBI DDRB,4 ;��������� PB4 �� ����� RT cntrl for debug
;CBI PORTB,4 ;RT cntrl for debug
;rjmp DEBUG
