
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
.DEF	ZeroReg		= r1
.DEF	TmpReg		= r17
.DEF	AnaReg		= r18
.DEF	buf			= r16
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
		clr AnaReg
		clr buf
		ldi	TmpReg, low(RAMEND)	; Initialize stack pointer to highest address in internal SRAM
		out	SPL, TmpReg
		ldi	TmpReg, high(RAMEND)
		out	SPH, TmpReg

		ldi	TmpReg, 0b10000000	; disable JTAG interface
		out	MCUCSR, TmpReg		; this has to be done with 
		out	MCUCSR, TmpReg		; two instructions

		;clear ACME bit in SFIOR to select AIN1(PB3) as negative input 
		;of the comparator, ADC multiplexor is off
		in TmpReg, SFIOR
		andi TmpReg, 0xF7	;
		out SFIOR,TmpReg

		;configure the analog comparator (ACSR) to
		;enable interrupt
		;trigger interrupt on output toggle ACS1,ACS0 zero
		clr TmpReg
		ldi TmpReg, (1<<ACIE)
		out ACSR,TmpReg

		ldi	TmpReg, 0xFF
		out DDRA, TmpReg		; port A will display the key code
		out DDRB, TmpReg		; set the unused to input
		out PortA,TmpReg		; enable pullups
		out PortB, TmpReg		; enable pullups

		out	DDRC, TmpReg		; set direction of port C (all outputs)
		out	DDRD, TmpReg		; set direction of port D (all outputs)

		out	PortC, ZeroReg		; set port C to 0x00 (disable all pull-ups)
		out	PortD, ZeroReg		; set port D to 0x00 (disable all pull-ups)	
		sei
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
;ANA_COMP:
TWI:
EXT_INT2:
TIM0_COM:
SPM_RDY:	reti



;ISR for the comparator
ANA_COMP:
	inc buf
	cpi buf, 0xFF
	brne notyet
	inc AnaReg
notyet:
reti



;************************** end bit_pos *******************************
;***************************************************************************************************************
;*************************************** M A I N ***************************************************************
;***************************************************************************************************************

				
Main:
		mov r15,AnaReg
		com r15
		out PortC, r15
		ldi TmpReg,0xF	
		out PortD, TmpReg
		rjmp	Main			; loop	





