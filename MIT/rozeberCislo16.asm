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

.DSEG
number16: 			.byte 2	;stores the 16-bit number to ripup into digits
number16_digits:	.byte 4	;stores the four digits of the 16-bit number
.CSEG

;********* makra pro rozebrani cisla na cislice
.MACRO set_num16_SRAM
	push r16
	push r17
	push YH
	push YL

		ldi r16, low(@0)
		ldi r17, high(@0)
		ldi YL, low(number16)
		ldi YH, high(number16)
		std Y+0, r17
		std	Y+1, r16

	pop YL
	pop YH
	pop r17
	pop r16
.ENDMACRO

;makro pro nacteni 16-bit cisla do par
;r17:r16 kde CH:CL
.MACRO get_num16_SRAM
	push YH
	push YL

		ldi YL, low(number16)
		ldi YH, high(number16)
		ldd  @0, Y+0	;HIGH
		ldd	 @1, Y+1	;LOW

	pop YL
	pop YH
.ENDMACRO

.MACRO clear_SRAM_display
	push ZeroReg
	push YH
	push YL	

		clr ZeroReg
		ldi YL, low(number16_digits)
		ldi YH, high(number16_digits)
		std Y+0, ZeroReg
		std	Y+1, ZeroReg
		std Y+2, ZeroReg
		std	Y+3, ZeroReg

	pop YL
	pop YH
	pop ZeroReg
.ENDMACRO


Main:

	set_num16_SRAM 2002
	get_num16_SRAM r18, r17
	clear_SRAM_display
	
rjmp Main
