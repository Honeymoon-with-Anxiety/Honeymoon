;***************************************************************************
;*						A SLIGHTHLY SIMPLIDIED
;* A P P L I C A T I O N   N O T E   F O R   T H E   A V R   F A M I L Y
;*
;* Number               : AVR314
;* File Name            : "dtmf.asm"
;* Title                : DTMF Generator
;* Date                 : 00.06.27
;* Version              : 1.1
;* Target MCU           : Any AVR with SRAM, 8 I/O pins and PWM
;*
;* DESCRIPTION
;* This Application note describes how to generate DTMF tones using a single
;* 8 bit PWM output.
;*
;***************************************************************************
.include "m16def.inc"
;**************************************************************************
;  REGISTERS
;**************************************************************************
.DEF	Xold		= r10               ; old look up table position
.DEF	Xnew		= r11				; new look up table position 
.DEF	Xsw			= r12				; the step width according to the FQ
.DEF   	TmpReg      = r16                   ; temp register
.DEF   	ZeroReg		= r17
.DEF	Buf1		= r18
.DEF	Buf2		= r19
;====================================== DATA segment ===========================================================
.DSEG
;===================================== EEPROM segment ==========================================================
.ESEG
;========================================= MACROs ==============================================================
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
;**************************** Reset interrupt starts here ****************************************************************
		.ORG	0x0030
Reset:		
		clr	ZeroReg
		ldi TmpReg,1
		mov Xsw, TmpReg
		mov Buf1,ZeroReg		;the slower version

		ldi	TmpReg, low(RAMEND)	; Initialize stack pointer to highest address in internal SRAM
		out	SPL, TmpReg
		ldi	TmpReg, high(RAMEND)
		out	SPH, TmpReg

		ldi	TmpReg, 0b10000000	; disable JTAG interface
		out	MCUCSR, TmpReg		; this has to be done with 
		out	MCUCSR, TmpReg		; two instructions


;TIMER1A CONFIGURATION - remember OC1A (pin to drive) is pin 5 of port D
		ldi TmpReg,(1<<WGM10)|(1<<COM1A1);partial config for Phase & Fq correct pwm
		out TCCR1A,TmpReg
		
		ldi TmpReg, (1<<WGM13)|(1<<CS10); PWM phase correct no clock division 
		out TCCR1B, TmpReg


		ldi TmpReg, 0x0
		out OCR1AH, ZeroReg		; init OCR1AH & OCR1AL
		ldi TmpReg, 0x5			; OCR1AH is a 16-bit register 
		out OCR1AL, TmpReg		; so you have to write the High byte first

		ldi TmpReg, (1<<OCIE1A)	; timer 0 overflow flag
		out TIMSK,TmpReg		; set the flag
				
		;config the pD5 (the OC1A)
		ldi TmpReg, (1<<DDD5)	; set pd5 for output and the rest for input
		out	DDRD, TmpReg		
		
		;set the rest of the ports for output
		ldi	TmpReg, 0xFF
		out DDRA, TmpReg		;set the rest of the ports for output
		out DDRB, TmpReg		
		out	DDRC, TmpReg		
		out PortA,TmpReg		
		out PortB, TmpReg		
		out	PortC, ZeroReg		
		
		sei						; enable global interrupts by setting the I bit
								; in the status register
		rjmp Main
;*************************** end reset interrupt routine ******************


;********************************** Unused interrupt vectors ***************************************************
EXT_INT0:
EXT_INT1:
TIM2_COM:
TIM2_OVF:
TIM1_CAP:
;TIM1_COMA: ;using this one for PWM
TIM1_COMB:
TIM1_OVF:
TIM0_OVF: 
SPI_STC:
UART_DRE:
UART_TXC:
UART_RXC:
ADC_COMP:
EE_RDY:
ANA_COMP:
TWI:
EXT_INT2:
TIM0_COM:
SPM_RDY:	reti
;**************************************************************************
; 			INTERRUPT SERVICE ROUTINE for TIM1_COMA
;**************************************************************************
TIM1_COMA:
   	push   TmpReg    			; Store temporary register
   	in     TmpReg,SREG
   	push   TmpReg               ; Store status register
   	push   ZL
   	push   ZH                   ; Store Z-Pointer
   	push   r0                   ; Store R0 Register

	inc Buf1
	cp Buf1, ZeroReg
	brne noconfig

;	inc Buf2					; modify  the tone here
;	ldi TmpReg, 0
;	cp Buf2, TmpReg
;	brne noconfig				; modify the tone here

	ldi TmpReg, 0x7
	inc Xsw
	and Xsw,TmpReg
	
noconfig:
	out PortA, Buf2
	out PortB, Xsw
	
	; atomic write into two registers
	cli							;disable interrupts
	add Xnew,Xsw				;add the step width to manipulate the FQ
	rcall getsample				;the new TOP value in r0
	out OCR1AH, ZeroReg			;your samples are only 7 bits
	out OCR1AL,r0 				;but you have 16-BIT REGISTER available

   	pop     r0                           ; Restore R0 Register
   	pop     ZH
   	pop     ZL                           ; Restore Z-Pointer
   	pop     Tmpreg
   	out     SREG,TmpReg                  ; Restore SREG
   	pop     TmpReg                       ; Restore temporary register;
   	reti

;************************MAIN**********************************
main: rjmp  main ; the interrupt is doing everything

;******************   GET SAMPLE   ******************************
;****************************************************************
getsample:
   ;remember Xnew has the offset to the next sample to use
   ;it may be loaded with value higher than 128 so you will
   ;need to adjust it with modular division

   ldi    TmpReg,0x7f
   and    Xnew,TmpReg                   ;mod 128 (128 samples number sine table)

   ldi    ZL,low(sine_tbl*2)			;load the base offset low
   ldi    ZH,high(sine_tbl*2)			;load the base offset high
   add    ZL,Xnew						;calculate the sample's address
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






