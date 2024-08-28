;***********************************
;	1 disp USB programator
;***********************************
;=========Includes =================
.NOLIST
.include	"tn261def.inc"
.LIST
;============== Register definitions =============================================
.DEF ZeroReg = r0
.DEF TmpReg = r16
	
;============== PROGRAM segment ==================================================*
.CSEG
;************** Interrupt vectors *************************************************
		.ORG	0x0000			; Program address
		rjmp	RESET				; Reset, ext, pwr-on, brwn-out, wdt
		rjmp	EXT_INT0				; External Interrupt Request 0 
		rjmp	PCHNG_INT1				; Pin Change Interrupt Request
		rjmp	TIMER1_COMPA		; Timer1 Compare Match A
		rjmp	TIMER1_COMPB		; Timer1 Compare Match B
		rjmp	TIMER1_OVF			; Timer1 Overflow
		rjmp	TIMER0_OVF			; Timer0 Overflow
		rjmp	USI_START			; USI Start
		rjmp	USI_OVF				; USI Overflow
		rjmp	EE_RDY				; EEPROM Ready
		rjmp	ANA_COMP			; Analog Comparator
		rjmp	ADC_DONE			; ADC Conversion Complete
		rjmp	WDOG_TIM				; Watchdog Timeout
		rjmp	EXT_INT1				; External Interrupt Request 1
		rjmp	TIMER0_COMPA		; Timer0 Compare Match A
		rjmp	TIMER0_COMPB		; Timer0 Compare Match B
		rjmp	TIMER0_CAPT			; Timer0 Capture Event
		rjmp	TIMER1_COMPD		; Timer1 Compare Match D
		rjmp	FAULT_PROTECTION	; Timer1 Fault Protection
;************** Unused interrupt vectors 	; **********************************
;		RESET:			; Reset, ext, pwr-on, brwn-out, wdt
		EXT_INT0:			; External Interrupt Request 0 
		PCHNG_INT1:			; Pin Change Interrupt Request
		TIMER1_COMPA:		; Timer1 Compare Match A
		TIMER1_COMPB:		; Timer1 Compare Match B
		TIMER1_OVF:		; Timer1 Overflow
		TIMER0_OVF:		; Timer0 Overflow
		USI_START:		; USI Start
		USI_OVF:		; USI Overflow
		EE_RDY:			; EEPROM Ready
		ANA_COMP:		; Analog Comparator
		ADC_DONE:			; ADC Conversion Complete
		WDOG_TIM:			; Watchdog Timeout
		EXT_INT1:			; External Interrupt Request 1
		TIMER0_COMPA:		; Timer0 Compare Match A
		TIMER0_COMPB:		; Timer0 Compare Match B
		TIMER0_CAPT:		; Timer0 Capture Event
		TIMER1_COMPD:		; Timer1 Compare Match D
		FAULT_PROTECTION:	; Timer1 Fault Protection
reti
;************************************************
		
		.ORG	0x0030
Reset:		
		clr	ZeroReg
		ldi	TmpReg, low(RAMEND)	; Stack Ptr
		out	SPL, TmpReg
	
		ldi TmpReg, 0xFF
		out DDRA, TmpReg

		rjmp	Main
;***************************************


.include "Display_Rozebrani.inc"


Main:



rjmp Main

		ldi TmpReg, 1
		out PortA, TmpReg

	ldi PdelReg, 100
	rcall Delay1m

display:
.db	0b00010010, 0b10011111		; '0', '1'
.db	0b00110001, 0b00010101		; '2', '3'
.db	0b10011100, 0b01010100		; '4', '5'
.db	0b01000000, 0b00011111		; '6', '7'
.db	0b00010000, 0b00000100		; '8', '9'
.db	0b00011000, 0b11010000		; 'A', 'B'
.db	0b01110010, 0b10010001		; 'C', 'D'
.db	0b01110000, 0b01111000		; 'E', 'F'
konec_display:
