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
; Program shows two basic ideas of scanning a keyboard - i.e.
; polling and interrupt driven. To see the polling method just commment
; out the scan function in the main.
;
; To see the polling method comment out the jump to the TIM0_COM ISR
; in the interrupt vectors
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
.DEF	TmpReg		= r17	;temporary register / scratch pad
.DEF	TmpKey		= r24
.DEF	Key			= r25
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
		ldi	TmpReg, low(RAMEND)	; Initialize stack pointer to highest address in internal SRAM
		out	SPL, TmpReg
		ldi	TmpReg, high(RAMEND)
		out	SPH, TmpReg

		ldi	TmpReg, 0b10000000	; disable JTAG interface
		out	MCUCSR, TmpReg		; this has to be done with 
		out	MCUCSR, TmpReg		; two instructions

		;CTC config for the interrupt keyboard scan
		ldi TmpReg, (1<<WGM01)|(1<<CS02)|(1<<CS00)
		out TCCR0,TmpReg
		out TCNT0, ZeroReg
		ldi TmpReg, 0xFF		;set the time of each scan
		out OCR0, TmpReg
		ldi TmpReg, (1<<OCIE0)
		out TIMSK, TmpReg


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

;*********************************************************
;***************** KEYBOARD SCAN INTERRUPT ***************
;*********************************************************
;comment this out to see the polling method
ATIM0_COM:
	push TmpReg
	in     TmpReg,SREG
   	push   TmpReg               ; Store status register
   	push   ZL
   	push   ZH                   ; Store Z-Pointer
   	push   r0    

		rcall scan				; experiment with how long you can wait for a rescan
		out PortB, Key			; interrupt will display the scanned key
		
	pop     r0                           ; Restore R0 Register
   	pop     ZH
   	pop     ZL                           ; Restore Z-Pointer
   	pop     Tmpreg
   	out     SREG,TmpReg                  ; Restore SREG
   	pop     TmpReg                       ; Restore temporary register;
	reti
;*********************************************************
;*************** END KEYBOARD SCAN INTERRUPT *************
;*********************************************************


;************************ Unused interrupt vectors ***********************
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
TIM0_COM:	;uncomment this to see the polling method
SPM_RDY:	reti

;*************************************************************
;**************** THE KEYBOARD SCAN FUNCTION *****************
;*************************************************************
scan:
		clr 	Key			;storage for the scaned key	
		ldi TmpReg, 0x0F	;config for input of the row
		out DispDataD,TmpReg;configure to scan the row
		clr TmpKey
		out DispDataP, TmpKey;disable the pullups
		nop nop nop nop nop nop nop nop ;wait to reconfigure
		in TmpKey, DispDataI;read in the row
		andi TmpKey, 0xF0	;mask out the row bits
		or Key, TmpKey		;record it in the key variable
		clr TmpKey
;and the second nible
		ldi TmpReg, 0xF0
		out DispDataD,TmpReg
		out DispDataP, TmpKey
		nop nop nop nop nop nop nop nop 
		in TmpKey, DispDataI	;read the column
		andi TmpKey, 0x0F
		or Key,TmpKey
		ldi TmpReg, 0x0F
		eor Key,TmpReg
ret

;******************************************************************************************
;*************************************** M A I N ******************************************
;******************************************************************************************
Main:
		rcall scan	
		out PortA, Key
		rjmp	Main		


