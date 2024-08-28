;***************************************************************************************************************
; Program	: AVR evaluation kit test - Single LED digit test
; Version	: v1.0
; Hardware	: MB-ATmega16(L) v1.3 (Xtall 14.7456MHz)
;			: multiplexed keyboard and 4 LED display 
; Author	: Maschio
;***************************************************************************************************************

;***************************************************************************************************************
; Short description
; -----------------
; Program shows basic interaction of leds and keyboard - i.e.
; input/output 
; 0, 1,2,3,4,5,6,7,8,9,A,B,C,D,E,F (in hex). The Multiplexed 
; LED and Keyboard module is connected to CON2 (i.e. PortC & PortD).
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
.EQU DispDataP = PortC  ;display data port
.EQU DispDataD = DDRC	;display data direction register
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

;registers used in delay functions
.DEF	PDelReg		= r20
.DEF	PDelReg0	= r21
.DEF	PDelReg1	= r22
.DEF	PDelReg2	= r23
.DEF	TmpKey		= r24
.DEF	Key			= r25
;====================================== DATA segment ===========================================================
.DSEG
	Display:	.BYTE 4	;this is the variable array storing the 
						;digits that should go on the display
						;offset zero is the first digit (left to right)
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


;*********************** Delay (PDelReg[ms]) *********************
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
;******************************** end delay function *****************


;********************** begin display off *************************
;turns off the display
LedOff:
		in		TmpReg, DispCtrlP	
		andi	TmpReg, 0b11101111	;this is the code to turn it off
		out		DispCtrlP, TmpReg
		ret
;*********************** end turn off the display *****************

;*********************** begin led on *****************************
;turns on the led display
LedOn:
		in 		TmpReg, DispCtrlP
		andi 	TmpReg, 0b11110011
		ori 	TmpReg, 0b00010000	;this is the code to turn it on
		out 	DispCtrlP, TmpReg
		ret
;************************ end led on ******************************

;************************ increment mod k *************************
;k here is the modulus, i.e. 5 mod 3 is 2;
;takes a number in DispPos and increments it mod 4 (since we are only
;using a 4-digit led display. Returns the result in DispPos
;so if you wanted a general mod function you would replace the four with
;a register where the modulus is stored
mod_inc:
		inc DispPos
		cpi DispPos, 4
		breq md_r
		ret
	md_r:
		ldi DispPos,0
		ret
;************************ end increment mod k *********************

;************************** move digit ****************************
; moves digit one position over on the led display
mv_dig:
		in TmpReg, DispCtrlP
		push DispPos			;save the position on the stack
		lsl DispPos				;because you will manipulate it
		lsl DispPos				
		andi TmpReg, 0b11110011	;mask out the beeper and c2
		or TmpReg, DispPos		;or in  the manipulated code of DispPos
		ori TmpReg,0b00010000	;turn on the led display
		pop DispPos				;restore the DispPos 
		out DispCtrlP, TmpReg			;send the code to the port
		ret
;************************ end move digit **************************


;******************************** scan key *********************
;scans the key and shows it on portB
row_scan:
		ldi TmpReg, 0x0f
		out DispDataD,TmpReg
		ldi TmpKey, 0b00001111	;detects all rows 
		com TmpKey
		andi TmpKey, 0x0F
		out DispDataP, TmpKey
		nop nop nop nop  nop nop nop nop ;it works without them
		in TmpKey, DispDataI
		andi TmpKey, 0xF0
		or Key, TmpKey
		clr TmpKey
		
	ret
;and the second nible
col_scan:
		ldi TmpReg, 0xf0
		out DispDataD,TmpReg
		ldi TmpKey, 0b11110000	;detects all rows 
		com TmpKey
		andi TmpKey, 0xF0
		out DispDataP, TmpKey
		nop nop nop nop  nop nop nop nop ;it works without them
		in TmpKey, DispDataI	;read a key
		andi TmpKey, 0x0F
		or Key,TmpKey
		ldi TmpReg, 0x0f
		eor Key,TmpReg
	ret
;******************************** end scan key *****************




;***************************************************************************************************************
;*************************************** M A I N ***************************************************************
;***************************************************************************************************************

Main:
			clr 	Column
			clr 	Key
			ldi		PDelReg, 250
			clr 	offset
Main10:		
		
		rcall LedOn
		clr Key
		rcall mv_dig

		ldi DispPos,3 ; NASTAVIT ZACINAJICI POZICI
		
		mov Scrap,Key
		out DispDataP, Scrap ; you are printing bits 1,2,3,4
		
				
		rcall col_scan
		rcall row_scan
		
		
		mov Scrap, Key

		ldi TmpReg,0b00010001
		and TmpReg,Scrap
		breq q17

		ldi TmpReg,0b00010010
		and TmpReg,Scrap
		breq q18	

		ldi TmpReg,0b00010100
		and TmpReg,Scrap
		breq q20

		ldi TmpReg,0b00011000
		and TmpReg,Scrap
		breq q24

		ldi TmpReg,0b00100001
		and TmpReg,Scrap
		breq q33	

		ldi TmpReg,0b00100010
		and TmpReg,Scrap
		breq q34	

		ldi TmpReg,0b00100100
		and TmpReg,Scrap
		breq q36

		ldi TmpReg,0b00101000
		and TmpReg,Scrap
		breq q40

;************************************

		ldi TmpReg,0b01000001 ;7
		and TmpReg,Scrap
		breq zz7	

		ldi TmpReg,0b01000010 ;8
		and TmpReg,Scrap
		breq q8	

		ldi TmpReg,0b01000100 ; 9
		and TmpReg,Scrap
		breq q9

		ldi TmpReg,0b01001000 ; c
		and TmpReg,Scrap
		breq qc

		ldi TmpReg,0b10000001 ;d 
		and TmpReg,Scrap
		breq qd	

		ldi TmpReg,0b10000010 ; zero
		and TmpReg,Scrap
		breq q0	

		ldi TmpReg,0b10000100 ; F
		and TmpReg,Scrap
		breq qf

		ldi TmpReg,0b10001000 ; E
		and TmpReg,Scrap
		breq qe

		rjmp disp

.MACRO splitNumber
	ldi Number,@0
	rcall disassembleNumbers
.ENDMACRO

.MACRO splitNumberMove
	mov Number,@0
	rcall disassembleNumbers
.ENDMACRO

.MACRO up
	inc r24
.ENDMACRO

.MACRO dowm
	dec r24
.ENDMACRO

.def numberSum = r27

disassembleNumbers:
		HUNDREDS:
		cpi TmpReg, 100
		brlo TENS
		subi TmpReg, 100
		inc numberSum
		cpi TmpReg, 100
		brsh HUNDREDS
		std Y+1, numberSum
		clr numberSum
			TENS:
			cpi TmpReg, 10
			brlo UNITS
			subi TmpReg, 10
			inc numberSum
			cpi TmpReg, 10
			brsh TENS
			std Y+2, numberSum
			clr numberSum
				UNITS:
				std Y+3, TmpReg
				clr TmpReg
ret


q17:
		ldi TmpReg, 0b11111001	;1
		mov Scrap, TmpReg
		rjmp disp
q18:
	
		ldi TmpReg,0xFF
		out DispDataD, TmpReg
		ldi TmpReg, 0b10100100	;2
		mov Scrap, TmpReg
		rjmp disp
q20:
		ldi TmpReg,0b10110000 	;3
		mov Scrap,TmpReg
		rjmp disp
q24:
		ldi TmpReg,0b10001000	;A
		mov Scrap,TmpReg
		rjmp disp
		
q33:
		ldi TmpReg,0b10011001 	;4
		mov Scrap,TmpReg
		rjmp disp
q34:
		ldi TmpReg,0b10010010	;5
		mov Scrap,TmpReg
		rjmp disp

q36:
		ldi TmpReg,0b10000010 	;6
		mov Scrap,TmpReg
		rjmp disp
q40:
		ldi TmpReg,0b10000011	;B
		mov Scrap,TmpReg
		rjmp disp

zz7:
		ldi TmpReg, 0b11111000	;7
		mov Scrap, TmpReg
		rjmp disp
q8:
	
		ldi TmpReg,0xFF
		out DispDataD, TmpReg
		ldi TmpReg, 0b10000000	
		mov Scrap, TmpReg
		rjmp disp
q9:
		ldi TmpReg,0b10010000 	
		mov Scrap,TmpReg
		rjmp disp
qc:
		ldi TmpReg,0b11000110	
		mov Scrap,TmpReg
		rjmp disp
		
qd:
		ldi TmpReg,0b10100001 	
		mov Scrap,TmpReg
		rjmp disp
q0:
		ldi TmpReg,0b11000000	
		mov Scrap,TmpReg
		rjmp disp

qf:
		ldi TmpReg,0b10001110 	
		mov Scrap,TmpReg
		rjmp disp
qe:
		ldi TmpReg,0b10000110	
		mov Scrap,TmpReg
		rjmp disp

disp:
		out DispDataP, Scrap
		ldi TmpReg, 0xFF
		out DispDataD,TmpReg
		
			

rcall Delay1m

rjmp	Main10		



CharTab:	.db	0b11111001, 0b10100100		; '1', '2'
			.db	0b10110000, 0b10001000		; '3', 'A'
			.db	0b10011001,	0b10010010  	; '4', '5'
			.db	0b10000010, 0b10000011		; '6', 'B'
			.db	0b11111000, 0b10000000		; '7', '8'
			.db	0b10010000, 0b11000110		; '9', 'C'
			.db	0b10100001, 0b11000000		; 'D', '0'
			.db	0b10001110, 0b10000110 		; 'F', 'E'	


