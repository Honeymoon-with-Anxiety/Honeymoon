;***********************************
;	lab example number one
;***********************************
;=========Includes =================
.NOLIST
.include	"m16def.inc"
.LIST
;====== Register definitions =======
.DEF ZeroReg = r0
.DEF TmpReg  = r16
;=====+== PROGRAM segment ==========
.CSEG
;******** Interrupt vectors ********
		.ORG	0x0000
		jmp	RESET			; Reset Handler

;******* Reset ********
		
		.ORG	0x0030
Reset:		
		clr	ZeroReg
		ldi	TmpReg, low(RAMEND)	; Initialize stack pointer to highest address in internal SRAM
		out	SPL, TmpReg
		ldi	TmpReg, high(RAMEND)
		out	SPH, TmpReg

		ldi	TmpReg, 0b10000000	; Disable JTAG interface
		out	MCUCSR, TmpReg
		out	MCUCSR, TmpReg

		
		out	DDRA, ZeroReg		; Set direction of port A (all inputs)
		out	DDRB, ZeroReg		; Set direction of port B (all inputs)
		ldi	TmpReg, 0xFF
		out	DDRC, TmpReg		; Set direction of port C (all outputs)
		out	DDRD, TmpReg		; Set direction of port D (all outputs)

		out	PortA, ZeroReg		; Set port A to 00h
		out	PortB, ZeroReg		; Set port A to 00h
		out	PortC, ZeroReg		; Set port A to 00h
		out	PortD, ZeroReg		; Set port A to 00h

		rjmp	Main
;**************************************************
;********************** MAIN **********************
;**************************************************
;testing the circular buffer capabilities


Main:
		out PortC, TmpReg
		inc TmpReg
		in r17, PinA
		in r18, PinB
rjmp Main	




















