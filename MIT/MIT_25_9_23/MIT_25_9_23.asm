;***********************************
;	lab example number one
;***********************************
;=========Includes =================
;
.NOLIST
.include	"m16def.inc"
.LIST



;====== Register definitions =======
.DEF ZeroReg = r0
.DEF TmpReg = r21

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


;************************************************
		
		.ORG	0x0030
Reset:		
	
		clr	ZeroReg
		ldi	TmpReg, low(RAMEND)	; Stack Ptr
		out	SPL, TmpReg
		ldi	TmpReg, high(RAMEND)
		out	SPH, TmpReg

		ldi	TmpReg, 0b10000000	; Disable JTAG interface
		out	MCUCSR, TmpReg
		out	MCUCSR, TmpReg

		rjmp	Main
;***************************************

pp3_1:
	ldi r16, 1 ;scitane cislo 1
	ldi r17, 6 ;scitane cislo 2 
	ldi r18, 2 ;rozlozeny nasobek
	ldi r19, 1 ;rozlozeny nasobek

	add r16, r17 ;scitani 1+6, vysledek v r16
	lsl r16 ;nasobeni r16 dvemi
	add r18, r19 ;scitani nasobku
	add r18, r16 ;vysledek v r18
ret

pp3_2:
	ldi r16, 1 ;scitame cislo 1
	ldi r17, 6 ;scitame cislo 2
	add r17, r16 ;scitame 6+1, vysledek v r17
	mov r16, r17 ;k
	lsl r17
	add r16, r17
ret

pp5:
	ldi r16, 1
	ldi r17, 6
	add r17, r16
	mov r16, r17
	lsl r16
	lsl r16
	add r16, r17
ret

pp7:
	mov r17, r16
	lsl r16
	lsl r16
	lsl r16
	sub r16, r17
ret

addWithCarry_1:
	ldi r16, low(420)
	ldi r17, high(420)
	ldi r18, low(300)
	ldi r19, high(300)

	add r16, r18
	adc r17, r19
ret

addWithCarry_2:
	ldi r16, 250
	ldi r17, 7
	add r16, r17
	adc r16, ZeroReg
ret

Main:
	;rcall pp3_1
	;rcall pp3_2
	;rcall pp5

	;ldi r16, 4
	;rcall pp7

	;rcall addWithCarry_1
	rcall addWithCarry_2
rjmp Main
