;====================================== Includes ===============================================================
.NOLIST
.include	"m16def.inc"
.LIST
;====================================== Constants ==============================================================

;================================== Register definitions =======================================================
.EQU DispDataP = PortC  ;display data port
.EQU DispDataD = DDRc	;display data direction register
.EQU DispDataI = PinC	;display data coming in to port C
.EQU DispCtrlP = PortD	;display data control (the three pins) port


.DEF	ZeroReg		= r1
.DEF	Row			= r2
.DEF	Column		= r3
.DEF	Scrap		= r4
.DEF 	inReg		= r15
.DEF	DispPos		= r16	;position in the LED display
							;so zero is the first digit 
							;(left to ritght)
.DEF	TmpReg		= r17	;temporary register / scratch pad
.DEF	offset		= r19	;used in reading and writing bytes  

.def 	TmpKey		= r24
.DEF	Key			= r25

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
		ldi XL, low(1)
		ldi XH, high(1)		
		clr	ZeroReg
		ldi	TmpReg, low(RAMEND)	; Initialize stack pointer to highest address in internal SRAM
		out	SPL, TmpReg
		ldi	TmpReg, high(RAMEND)
		out	SPH, TmpReg

		ldi	TmpReg, 0b10000000	; disable JTAG interface
		out	MCUCSR, TmpReg		; this has to be done with 
		out	MCUCSR, TmpReg		; two instructions

		ldi	TmpReg, 0xFF
		out DDRA, TmpReg		; port A will display the key code
		out DDRB, TmpReg		; set the unused to input
		out PortA,TmpReg		; enable pullups
		out PortB, TmpReg		; enable pullups

		out	DDRC, TmpReg		; set direction of port C (all outputs)
		out	DDRD, TmpReg		; set direction of port D (all outputs)

		out	PortC, ZeroReg		; set port C to 0x00 (disable all pull-ups)
		out	PortD, ZeroReg		; set port D to 0x00 (disable all pull-ups)	
		clr DispPos
		rjmp Main
;*************************** end reset interrupt routine ******************
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

.include "scan_delay"
.include "seg_nahoru"
.include "seg_dolu"
.include "HD_tabulky"

;***************************************************************************************************************
;*************************************** M A I N ***************************************************************
;***************************************************************************************************************
nad:

ldi r16, 1
com r16
out portA,r16
rcall segment
ldi r16,1
rjmp main

pod: 
ldi r16,2
com r16
out portA,r16
rcall segmentdolu
ldi r16,2
rjmp main

hex:
ldi r23,4
com r23
out portA,r23
ldi r23,1
rjmp main

dex:
ldi r23,8
com r23
out portA,r23
ldi r23,0
rjmp main

main:
	
;	rcall LedOn
;	clr r16
;	rcall segment
	
	ldi PDelReg, 200
	Main10:
		
		
		clr	Key

		rcall scan
		com Key
		
		ldi TmpReg,0b00010001
		and TmpReg,Key
		breq nad


		ldi TmpReg,0b00010010
		and TmpReg,Key
		breq pod

		ldi TmpReg,0b00010100
		and TmpReg,Key
		breq hex
		
		ldi TmpReg,0b00011000
		and TmpReg,Key
		breq dex

		cpi r16,1
		breq nad

		cpi r16,2
		breq pod
		

		
rjmp	Main10		


