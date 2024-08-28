;***********************************
;	lab example number one
;***********************************
;=========Includes =================
;
.NOLIST
.include	"m16def.inc"
.LIST

;====== Register definitions =======
.DEF	ZeroReg 	= r0
.DEF	TmpReg		= r19
.DEF	PDelReg		= r20
.DEF	PDelReg0	= r21
.DEF	PDelReg2	= r2
.DEF	PDelReg1	= r22

;=====+== PROGRAM segment ==========
.CSEG
;******** Interrupt vectors ********
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


;******* Reset ********
;********************************** Unused interrupt vectors ***************************************************
EXT_INT0:
EXT_INT1:
TIM2_COM:
TIM2_OVF:
TIM1_CAP:
TIM1_COMA:
TIM1_COMB:
TIM1_OVF:
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


;************************************************
		
		.ORG	0x0030

TIM0_OVF:
	ldi TmpReg,0xFF
	out PortA,TmpReg
	rcall Toggle
reti

Toggle:
	sbis PortA, 3
	rjmp ToggleOn
	cbi PortA, 3

ret

ToggleOn:
	sbi PortA, 3
ret

Reset:
	clr	ZeroReg
	ldi	TmpReg, low(RAMEND)	; Stack Ptr
	out	SPL, TmpReg
	ldi	TmpReg, high(RAMEND)
	out	SPH, TmpReg

	ldi	TmpReg, 0b10000000	; Disable JTAG interface
	out	MCUCSR, TmpReg
	out	MCUCSR, TmpReg

	ldi	TmpReg, 0xFF
	out	DDRA, TmpReg		; Set direction of port A (all inputs)
	out	DDRB, TmpReg		; Set direction of port B (all inputs)
	out	DDRC, TmpReg		; Set direction of port C (all outputs)
	out	DDRD, TmpReg		; Set direction of port D (all outputs)

	out	PortA, ZeroReg		; Set port A to 00h
	out	PortB, ZeroReg		; Set port A to 00h
	out	PortC, ZeroReg		; Set port A to 00h
	out	PortD, ZeroReg		; Set port A to 00h

;	NO PRESCALING
	ldi TmpReg, (0<<CS02)|(0<<CS01)|(1<<CS00) ; clock select
	out TCCR0, TmpReg
;	ENABLE LOCAL INTERRUPTION
	ldi TmpReg, (1<<TOIE0)	; timer 0 overflow flag
	out TIMSK,TmpReg		; set the flag
	out TCNT0, ZeroReg		; clear the value in the counter

	sei
rjmp	Main
;**************************************************
.DEF	buf1		= r24
.DEF	buf2		= r25
;************** Delay (PDelReg[ms]) ***************
; this is a delay subroutine
 Delay1m:	mov	PDelReg2, PDelReg
 Delay1m0:	ldi	PDelReg0, 20
 Delay1m1:	ldi	PDelReg1, 245
 Delay1m2:	dec	PDelReg1
 		brne	Delay1m2
 		dec	PDelReg0
 		brne	Delay1m1
 		dec	PDelReg2
 		brne	Delay1m0
		ret
;**************************************************
