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

.def iterator=r16
.def hodA=r18
.def hodB=r19
.def iterator_vln=r20
.def iterator_vlt=r22
.equ podminka_skoku=10

podminena_smycka_od_tri:

	ldi iterator, 3
	loopl_od_tri:
		; instrukce

		inc iterator
		cpi iterator, podminka_skoku
		brne loopl_od_tri
ret

podminena_smycka_od_nuly:

	clr iterator
	loopl_od_nuly:
		; instrukce

		inc iterator
		cpi iterator, podminka_skoku
		brne loopl_od_nuly
ret

rozhodovaci_vetev:
	;ldi hodA, 213
	ldi hodA, 10
		
	cpi hodA, 10 ;compare
	brne rozhodovaci_vetev_else ;branch if not equal
	ldi hodB, 5
	rjmp rozhodovaci_vetev_hotovo

	rozhodovaci_vetev_else:
		ldi hodB, 7

	rozhodovaci_vetev_hotovo:
ret

switch_vetev:
	;ldi hodA, 10

	case10:
		cpi hodA, 10
		brne case20
		ldi hodB, 5 ;instrukce pokud hodA = 10
		nop
		nop
		rcall rozhodovaci_vetev_hotovo

	case20:
		cpi hodA, 20
		brne case30
		ldi hodB, 7 ;instrukce pokud hodA = 20
		nop
		nop
		rcall rozhodovaci_vetev_hotovo

	case30:
		cpi hodA, 30
		brne rozhodovaci_vetev_hotovo
		ldi hodB, 25 ;instrukce pokud hodA = 30
		nop
		nop
		rcall rozhodovaci_vetev_hotovo
ret

vlozena_smycka:
	clr iterator_vln
	vlozeny_loop_od_nuly:
			
			ldi iterator_vlt, 3
			;clr iterator_vlt
			vlozeny_loop_od_tri:
				; instrukce

				inc iterator_vlt
				cpi iterator_vlt, podminka_skoku
 				brne vlozeny_loop_od_tri

		inc iterator_vln
		cpi iterator_vln, podminka_skoku
		brne vlozeny_loop_od_nuly

	
ret

vlozeny_podprogram:
	ldi hodA, 15
	RCALL switch_vetev
	cpi hodB, 7

ret

Main:
	rcall podminena_smycka_od_nuly
	rcall podminena_smycka_od_tri
	rcall rozhodovaci_vetev
	rcall switch_vetev
	rcall vlozena_smycka
	rcall vlozeny_podprogram

rjmp Main
