
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
; Program demonstrates the function of ADC
;
; MB-ATmega16 board configuration:
;		JP1 (1-3, 2-4); JP2 (3-4, 5-6); JP3 (1-3, 2-4), JP4 (1-3, 2-4)
;***************************************************************************************************************
.NOLIST
.include	"m16def.inc"
.LIST

.DEF	ZeroReg		= r1
.DEF	buf			= r16
.DEF	TmpReg		= r17
.DEF	ADCReg		= r18
.DEF	buf2		= r19
.DEF	StartConvFlag = r20

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
		jmp	TWI				; Two-wire Serial Interface Handler
		jmp	EXT_INT2		; External Interrup Request 2 Handler
		jmp	TIM0_COM		; Timer0 Compare Match Handler
		jmp	SPM_RDY			; Store Program Memory Ready


;*************** Reset interrupt starts here ****************
		.ORG	0x0030
Reset:		
		clr	ZeroReg
		clr ADCReg
		clr buf
		clr buf2
		clr StartConvFlag
		ldi StartConvFlag,(1<<ADSC)
		ldi	TmpReg, low(RAMEND)	; Initialize stack pointer
		out	SPL, TmpReg
		ldi	TmpReg, high(RAMEND)
		out	SPH, TmpReg

		ldi	TmpReg, 0b10000000	; disable JTAG interface
		out	MCUCSR, TmpReg		; this has to be done with 
		out	MCUCSR, TmpReg		; two instructions


		;configure the analog comparator (ACSR) to
		;enable interrupt
		;trigger interrupt on output toggle ACS1,ACS0 zero
		clr TmpReg
		ldi TmpReg, (1<<ADEN)|(1<<ADIE)
		out ADCSRA,TmpReg	;enable the adc interrupt and turn on the adc

		clr TmpReg
		ldi TmpReg, (1<<ADLAR)|(1<<REFS0)|(1<<MUX0)|(1<<MUX1)|(1<<MUX2)
		;left adjust,AVCC internal reference, pinADC7=PA7 for input
		out ADMUX,TmpReg


		;configure the timer0
		clr TmpReg
		out TCNT0,TmpReg
		ldi TmpReg, (1<<CS02)|(1<<CS00);clk/1024
		out TCCR0, TmpReg		

		clr TmpReg
		ldi TmpReg, (1<<TOIE0)
		out TIMSK,TmpReg


		ldi	TmpReg, 0xFF
		out	DDRC, TmpReg		; set direction of port C (all outputs)
		out	DDRD, TmpReg		; set direction of port D (all outputs)

		clr TmpReg
		out DDRA, TmpReg		; port A will be reading the sample
		out DDRB, TmpReg		; so set it for input
		out PortA,TmpReg		; disable pullups
		out PortB, TmpReg		; disable pullups
		
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
;TIM0_OVF: 
SPI_STC:
UART_DRE:
UART_TXC:
UART_RXC:
;ADC_COMP:
EE_RDY:
ANA_COMP:
TWI:
EXT_INT2:
TIM0_COM:
SPM_RDY:	reti



;ISR for the ADC
;you will be using it in single conversion mode 
;becaue it makes no sense to sample potentiometer
;at 100kHz. The ISR will just read the sample value
;from the ADCH data register and load it into a GP register
;for displaying 
ADC_COMP:
	in ADCReg, ADCH
reti


;timer will determine when to sample (start the conversion) 
;by setting the ADSC flag of ADCSRA register. After the conversion
;completes you will get the ADC_COMP interrupt and load the sample
TIM0_OVF:
	inc buf
	cpi buf, 10
	brne goon ;set the ADCflag if the time has come
	clr buf
	inc buf2
	out PortC, buf2
	in StartConvFlag, ADCSRA
	ori StartConvFlag, (1<<ADSC)
	out ADCSRA, StartConvFlag
goon:
reti

;********** M A I N ***********
Main:		
		com ADCReg
		out PortD, ADCReg
		rjmp	Main			; loop	






