;***************************************************************************************************************
; Program	: UART test 0
; Hardware	: MB-ATmega16(L) v1.3 (Xtall 14.7456MHz)
; Author	: Maschio
;***************************************************************************************************************

;***************************************************************************************************************
; Short description
; -----------------
; Program includes 16-bit counter which is incremented 
; by value received by UART. After a byte
; is received and added to counter the actual counter value 
; is transmitted by UART. Also
; the value is displayed on two mini LED modules inserted in connector CON1.
; Counter can be reseted to zero by sending 0 by UART.
;
; MB-ATmega16 board configuration: JP3 (1-3, 2-4), JP4 (3-5, 4-6)
;***************************************************************************************************************


;====================================== Includes ===============================================================
.NOLIST
.include	"m16def.inc"
.include 	"RS232.inc"
.LIST


;====================================== Constants ==============================================================
;.EQU	BaudConst	= 7	; = Round(14.7456Mhz / (16 * 115200) - 1)
.EQU	BaudConst	= 95	; = Round(14.7456Mhz / (16 * 9600) - 1)


;================================== Register definitions =======================================================
.DEF	ZeroReg		= r1
.DEF	TmpReg		= r16

.DEF	Xnew0		= r17
.DEF 	Xnew1		= r18
.DEF	Xnew2		= r19
.DEF	Xnew3		= r20



.DEF	SendData	= r21
 
.DEF	Counter0	= r25

;*************************************************
;you will be loading samples from different tables
;*************************************************
; the first argument is the table (the label of)to load from
;the second argument is the base offset (in a register)
;the third argument is the return value in a register
.MACRO LoadSample
   	andi    @1,0x7F                   ;mod 128 (128 samples number sine table)
   	ldi    	ZL,low(@0*2)			;load the base offset low
   	ldi    	ZH,high(@0*2)			;load the base offset high
   	add    	ZL,@1						;calculate the sample's address
   	adc    	ZH,ZeroReg                    ;Z now has the correct address of the sample
   	lpm	  	@2,Z							;the sample is in the r0 register
.ENDMACRO

;===================================== PROGRAM segment =========================================================
.CSEG

;*********************************** Interrupt vectors *********************************************************
		.ORG	0x0000
		jmp	RESET			; Reset Handler
		jmp	EXT_INT0		; External Interrupt Request 0 Handler
		jmp	EXT_INT1		; External Interrupt Request 1 Handler
		jmp	TIM2_COM		; Timer2 Compare Match Handler
		jmp	TIM2_OVF		; Timer2 Overflow Handler
		jmp	TIM1_CAP		; Timer1 Capture Handler
		jmp	TIM1_COMA		; Timer1 Compare Match A Handler
		jmp	TIM1_COMB		; Timer1 Compare Match B Handler
		jmp	TIM1_OVF		; Timer1 Overflow Handler
		jmp	TIM0_OVF		; Timer0 Overflow Handler
		jmp	SPI_STC			; SPI Transfer Complete Handler

		jmp	UART_RXC		; UART RX Complete Handler
		jmp	UART_DRE		; UART Data Register Empty Handler
		jmp	UART_TXC		; UART TX Complete Handler

		jmp	ADC_COMP		; ADC Conversion Complete Handler
		jmp	EE_RDY			; EEPROM Write Complete (Ready) Handler
		jmp	ANA_COMP		; Analog Comparator Handler
		jmp	TWI			; Two-wire Serial Interface Handler
		jmp	EXT_INT2		; External Interrup Request 2 Handler
		jmp	TIM0_COM		; Timer0 Compare Match Handler
		jmp	SPM_RDY			; Store Program Memory Ready


;**************************************** Reset ****************************************************************
		.ORG	0x0030
Reset:		
		clr	ZeroReg
		clr Counter0

		clr Xnew0		
	 	clr Xnew1		
		clr Xnew2		
		clr Xnew3

		ldi	TmpReg, low(RAMEND)	; Initialize stack pointer to highest address in internal SRAM
		out	SPL, TmpReg
		ldi	TmpReg, high(RAMEND)
		out	SPH, TmpReg

		ldi	TmpReg, 0b10000000	; Disable JTAG interface
		out	MCUCSR, TmpReg
		out	MCUCSR, TmpReg
		
		;timer counter 0 config
		ldi TmpReg, (1<<WGM01)|(1<<CS02)|(1<<CS00)
		out TCCR0, TmpReg
		ldi TmpReg, 50
		out OCR0,TmpReg
		ldi TmpReg, (1<<OCIE0)	;enable the timer	
		out TIMSK, TmpReg


;  	Enable receiver and transmitter and receive complete interrupt 
;	and data register empty interrupt (transmitter)
		ldi	TmpReg, (1<<RXCIE)|(1<<RXEN)|(1<<TXEN);|(1<<UDRIE)
		out	UCSRB, TmpReg

; Set no. of bits to 8 no parity
		ldi	TmpReg, (1<<URSEL)|(3<<UCSZ0)
		out	UCSRC, TmpReg

		ldi	TmpReg, BaudConst	; Set baud rate to BaudConst
		out	UBRRL, TmpReg
		out	UBRRH, ZeroReg

		ldi	TmpReg, 0xFF
		out	DDRA, TmpReg		; Set direction of port A (all outputs)
		out	DDRB, TmpReg		; Set direction of port B (all outputs)
		out	DDRC, ZeroReg		; Set direction of port C (all inputs)
		out	DDRD, ZeroReg		; Set direction of port D (all inputs)

		out	PortA, TmpReg		; Set port A to FFh
		out	PortB, TmpReg		; Set port A to FFh
		out	PortC, TmpReg		; Set port A to FFh
		out	PortD, TmpReg		; Set port A to FFh

		sei
		rjmp	Main
	
;*** TIM0_COM ***
;this ISR will send the X_ON after it
;expires and then it will disable itself
TIM0_COM:
	inc counter0
	andi counter0,0x3
	
	cpi counter0,0
	breq SineTable
	
	cpi counter0,1
	breq triangTable
	
	cpi counter0, 2
	breq squarTable
	
	LoadSample pwm_tbl, Xnew3, r0
	inc Xnew3
	andi Xnew3,0x7F
	rjmp send_it
	
	
triangTable:
	LoadSample triang_tbl, Xnew1, r0
	;inc Xnew1
	subi Xnew1,-4
	andi Xnew1,0x7F
	rjmp send_it

squarTable:
	LoadSample squar_tbl, Xnew2, r0
	inc Xnew2
	andi Xnew2,0x7F
	rjmp send_it
	
SineTable:
	LoadSample sine_tbl, Xnew0, r0
	inc Xnew0
	andi Xnew0,0x7F
	rjmp send_it	

send_it:
	mov SendData, r0
	out UDR, r0
reti
;********************************** Unused interrupt vectors ***************************************************
EXT_INT0:
EXT_INT1:
TIM2_COM:
TIM2_OVF:
TIM1_CAP:
TIM1_COMA:
TIM1_COMB:
TIM1_OVF:
TIM0_OVF:

UART_TXC:
UART_RXC:
UART_DRE:

SPI_STC:
ADC_COMP:
EE_RDY:
ANA_COMP:
TWI:
EXT_INT2:
	;TIM0_COM:
SPM_RDY:	reti


;***************************************************************************************************************
;*************************************** M A I N ***************************************************************
;***************************************************************************************************************
Main:	
		out	PortA, SendData
		rjmp	Main			; jmp to loop start

;******************   GET SAMPLE   ******************************
;****************************************************************
getsample:
   ;remember Xnew has the offset to the next sample to use
   ;it may be loaded with value higher than 128 so you will
   ;need to adjust it with modular division

   ldi    TmpReg,0x7f
   and    Xnew1,TmpReg                   ;mod 128 (128 samples number sine table)

   ldi    ZL,low(sine_tbl*2)			;load the base offset low
   ldi    ZH,high(sine_tbl*2)			;load the base offset high
   add    ZL,Xnew1						;calculate the sample's address
   adc    ZH,ZeroReg                    ;Z now has the correct address of the sample
   lpm	  r0,Z							;the sample is in the r0 register
   ret



;*************************** SIN TABLE *************************************
; Samples table : one period sampled on 128 samples and
; quantized on 7 bits
;******************************************************************************
sine_tbl:
.db 64,67
.db 70,73
.db 76,79
.db 82,85
.db 88,91
.db 94,96
.db 99,102
.db 104,106
.db 109,111
.db 113,115
.db 117,118
.db 120,121
.db 123,124
.db 125,126
.db 126,127
.db 127,127
.db 127,127
.db 127,127
.db 126,126
.db 125,124
.db 123,121
.db 120,118
.db 117,115
.db 113,111
.db 109,106
.db 104,102
.db 99,96
.db 94,91
.db 88,85
.db 82,79
.db 76,73
.db 70,67
.db 64,60
.db 57,54
.db 51,48
.db 45,42
.db 39,36
.db 33,31
.db 28,25
.db 23,21
.db 18,16
.db 14,12
.db 10,9
.db 7,6
.db 4,3
.db 2,1
.db 1,0
.db 0,0
.db 0,0
.db 0,0
.db 1,1
.db 2,3
.db 4,6
.db 7,9
.db 10,12
.db 14,16
.db 18,21
.db 23,25
.db 28,31
.db 33,36
.db 39,42
.db 45,48
.db 51,54
.db 57,60

triang_tbl:
.db 60, 62
.db 64, 66
.db 68, 70
.db 72,74
.db 76,78
.db 80,82
.db 84,86
.db 88,90
.db 92,94
.db 96,98
.db 100, 102
.db 104,106
.db 108,110
.db 112,114
.db 116,118
.db 120,122
.db 124, 122
.db 120, 118
.db 116, 114
.db 112, 110
.db 108, 106
.db 104, 102
.db 100, 98
.db 96, 94
.db 92, 90
.db 88, 86
.db 84, 82
.db 80, 78
.db 76,74
.db 72,70
.db 68,66
.db 64,62
.db 60,58
.db 56,54
.db 52,50
.db 48,46
.db 44,42
.db 40,38
.db 36,34
.db 32,30
.db 28,26
.db 24,22
.db 20,18
.db 16,14
.db 12,10
.db 8,6
.db 4,2
.db 0, 2
.db 4, 6
.db 8, 10
.db 12,14
.db 16,18
.db 20,22
.db 24,26
.db 28,30
.db 32, 34
.db 36, 38
.db 40, 42
.db 44,46
.db 48,50
.db 52,54
.db 56,58
.db 60,62

squar_tbl:
.db 64, 70
.db 80, 90
.db 100, 110
.db 120,130
.db 150,200
.db 234,220
.db 138,128
.db 128,128
.db 128,128
.db 128,128
.db 128,128
.db 128,128
.db 128,128
.db 128,128
.db 128,128
.db 128,128
.db 128,128
.db 128,128
.db 128,128
.db 128,128
.db 128,128
.db 128,128
.db 128,128
.db 128,128
.db 128,128
.db 128,128
.db 138, 136
.db 124, 102
.db 90, 78
.db 56,54
.db 42,40
.db 38,36
.db 24,22
.db 20,28
.db 16,14
.db 12,10
.db 8,6
.db 4,2
.db 0,0
.db 0,0
.db 0,0
.db 0,0
.db 0,0
.db 0,0
.db 0,0
.db 0,0
.db 0,0
.db 0,0
.db 0,0
.db 0,0
.db 0,0
.db 0,0
.db 0,0
.db 0,0
.db 0,0
.db 0,0
.db 0,0
.db 0,0
.db 10,22
.db 34,36
.db 48,50
.db 52,54
.db 56,58
.db 60,62

pwm_tbl:
.db 0,31
.db 44,54
.db 63,70
.db 77,83
.db 89,95
.db 100,105
.db 109,114
.db 118,122
.db 126,130
.db 134,138
.db 141,145
.db 148,152
.db 155,158
.db 161,164
.db 167,170
.db 173,176
.db 179,182
.db 184,187
.db 190,192
.db 195,197
.db 200,202
.db 205,207
.db 210,212
.db 215,217
.db 219,221
.db 224,226
.db 228,230
.db 232,235
.db 237,239
.db 241,243
.db 245,247
.db 249,251
.db 253,170
.db 127,102
.db 85,72
.db 63,56
.db 51,46
.db 42,39
.db 36,34
.db 31,30
.db 28,26
.db 25,24
.db 23,22
.db 21,20
.db 19,18
.db 18,17
.db 17,16
.db 15,15
.db 15,14
.db 14,13
.db 13,13
.db 12,12
.db 12,11
.db 11,11
.db 11,10
.db 10,10
.db 10,10
.db 9,9
.db 9,9
.db 9,8
.db 8,8
.db 8,8
.db 8,8
.db 7,7