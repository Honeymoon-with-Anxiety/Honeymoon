
;***************************************************************************************************************
; Program	: CTC demo
; Version	: v1.0
; Hardware	: MB-ATmega16(L) v1.3 (Xtall 14.7456MHz)
;			: multiplexed keyboard and 4 LED display 
;***************************************************************************************************************

;***************************************************************************************************************
; Short description
; -----------------
; shows the basic purpose of CTC configuration of a timer.
; The program should slow down as the TOP value in OCR2 increases
;
; MB-ATmega16 board configuration:
;		JP1 (1-3, 2-4); JP2 (3-4, 5-6); JP3 (1-3, 2-4), JP4 (1-3, 2-4)
;***************************************************************************************************************

;====================================== Includes ===============================================================
.NOLIST
.include	"m16def.inc"
.LIST
;====================================== Constants ==============================================================

;================================== Register definitions =======================================================
.DEF	ZeroReg		= r1
.DEF	TmpReg		= r17
.DEF	buf1		= r24
.DEF	buf2		= r25

.CSEG		;code segment
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
		jmp	TWI				; Two-wire Serial Interface Handler
		jmp	EXT_INT2		; External Interrup Request 2 Handler
		jmp	TIM0_COM		; Timer0 Compare Match Handler
		jmp	SPM_RDY			; Store Program Memory Ready


;**************************** Reset interrupt starts here ****************************************************************
		.ORG	0x0030
Reset:		
		clr	ZeroReg
		clr buf1
		clr buf2
		
		ldi	TmpReg, low(RAMEND)	; Initialize stack pointer to highest address in internal SRAM
		out	SPL, TmpReg
		ldi	TmpReg, high(RAMEND)
		out	SPH, TmpReg

		ldi	TmpReg, 0b10000000	; disable JTAG interface
		out	MCUCSR, TmpReg		; this has to be done with 
		out	MCUCSR, TmpReg		; two instructions

		;configure timer/counter2
		ldi TmpReg, (1<<CS22)|(1<<CS20)|(1<<CS21)|(1<<WGM21) ; clock select 
		out TCCR2, TmpReg
		ldi TmpReg, 1
		out OCR2, TmpReg
		ldi TmpReg, (1<<OCIE2)	; timer 0 overflow flag
		out TIMSK,TmpReg		; set the flag
		out TCNT2, ZeroReg		; clear the value in the ounter
		;end timer/counter2 configuration

		ldi	TmpReg, 0xFF
		out DDRA, TmpReg		; port A will display the key code
		out DDRB, TmpReg		; set the unused to input
		out PortA,TmpReg		; enable pullups
		out PortB, TmpReg		; enable pullups

		out	DDRC, TmpReg		; set direction of port C (all outputs)
		out	DDRD, TmpReg		; set direction of port D (all outputs)

		out	PortC, ZeroReg		; set port C to 0x00 (disable all pull-ups)
		out	PortD, ZeroReg		; set port D to 0x00 (disable all pull-ups)	
		sei						; enable global interrupts
		rjmp Main
;*************************** end reset interrupt routine ******************
;********************************** Unused interrupt vectors ***************************************************
EXT_INT0:
EXT_INT1:
				;TIM2_COM: ;got ISR for this one
TIM2_OVF:
TIM1_CAP:
TIM1_COMA:
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


;ISR for the timer zero overflow
TIM2_COM:
	in	TmpReg, SREG	;read status
	push	TmpReg		;save status
	
	inc buf1
	cp buf1, ZeroReg	
	brne nf1
	
	inc buf2
	cp buf2, ZeroReg
	brne nf1

	;reconfigure the TOP value
	;of the counter
	in TmpReg, OCR2
	subi TmpReg,-7
	out OCR2, TmpReg

	clr buf2

nf1:

	pop	TmpReg			;pop status
	out	SREG, TmpReg	;restore status
	reti
;******* END TIMER/COUNTER 2 ISR *******

;***MAIN***
Main:		
		out	PortA, buf2
		rjmp	Main			; loop	





