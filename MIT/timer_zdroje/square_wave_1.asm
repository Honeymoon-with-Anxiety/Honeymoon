;***************************************************************************************************************
;
;   timer using CTC to refine resolution of the timer
;
;***************************************************************************************************************
.NOLIST
.include	"m16def.inc"
.LIST

.DEF	ZeroReg		= r1
.DEF	Cnt0		= r15
.DEF	TmpReg		= r19

.CSEG

.equ clock_1    = (1<<CS00)            ;   no prescale
.equ clock_8    = (1<<CS01)            ;   divide main clock by 8
.equ clock_64   = (1<<CS01)|(1<<CS00)  ;   divide main clock by 64
.equ clock_256  = (1<<CS02)            ;   divide main clock by 256
.equ clock_1024 = (1<<CS02)|(1<<CS00)  ;   divide main clock by 1024

.equ TimerTopVal    = 50               ;   value to trigger the interrutp at

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
		jmp	TWI				; Two-wire Serial Interface Handler
		jmp	EXT_INT2		; External Interrup Request 2 Handler
		jmp	TIM0_COM		; Timer0 Compare Match Handler
		jmp	SPM_RDY			; Store Program Memory Ready


;**************************** Reset interrupt starts here ****************************************************************
		.ORG	0x0030
Reset:		
		clr	ZeroReg			; clear these registers
		clr Cnt0

		ldi	TmpReg, low(RAMEND)	; Initialize stack pointer to highest address in internal SRAM
		out	SPL, TmpReg
		ldi	TmpReg, high(RAMEND)
		out	SPH, TmpReg

		ldi	TmpReg, 0b10000000	; disable JTAG interface
		out	MCUCSR, TmpReg		; this has to be done with 
		out	MCUCSR, TmpReg		; two instructions

		ldi TmpReg, clock_1     ; clock select
        ori TmpReg, (1<<WGM01)  ; also configure for TimerTopVal from OCR0 
		out TCCR0, TmpReg

		ldi TmpReg, (1<<OCIE0)	; timer 0 compare match interrupt enable bit
		out TIMSK,TmpReg		; set the bit

        ldi TmpReg, TimerTopVal ; TimerTopVal load
        out OCR0, TmpReg        ; set TimerTopVal to trigger the interrupt

		out TCNT0, ZeroReg		; clear TimerTopVal in the ounter

		ldi	TmpReg, 0xFF
		out DDRA, TmpReg		; port A will display the key code
		out DDRB, TmpReg		; set the unused to input
		out PortA,TmpReg		; enable pullups
		out PortB, TmpReg		; enable pullups

		out	DDRC, TmpReg		; set direction of port C (all outputs)
		out	DDRD, TmpReg		; set direction of port D (all outputs)

		out	PortC, ZeroReg		; set port C to 0x00 (disable all pull-ups)
		out	PortD, ZeroReg		; set port D to 0x00 (disable all pull-ups)	
		sei						; set global interrupts
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
;TIM0_COM:
SPM_RDY:	reti


;**** ISR for the timer zero compare match ****
TIM0_COM:
	in	TmpReg, SREG		
	push	TmpReg			; push the status register
	
	inc Cnt0 				; increase count0

	pop	TmpReg
	out	SREG, TmpReg		; restore the status register
	reti
;************ END TIMER0 ISR ***********

Main:		
		com Cnt0
		out	PortA, Cnt0		; display the number of times timer has expired
		com Cnt0 		
		rjmp	Main		; main loop	




