
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
.DEF	TmpReg		= r17
.DEF	ADCReg		= r18
.DEF 	MaskReg		= r19

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
		ldi MaskReg, 0xFF
		
		ldi	TmpReg, low(RAMEND)	; Initialize stack pointer
		out	SPL, TmpReg
		ldi	TmpReg, high(RAMEND)
		out	SPH, TmpReg

		ldi	TmpReg, 0b10000000	; disable JTAG interface
		out	MCUCSR, TmpReg		; this has to be done with 
		out	MCUCSR, TmpReg		; two instructions



		clr TmpReg
		out DDRA, TmpReg		; port A will be reading the sample
		out DDRB, TmpReg		; so set it for input
		out PortA,TmpReg		; disable pullups
		out PortB, TmpReg		; disable pullups

		ldi	TmpReg, 0xFF
		out	DDRC, TmpReg		; set direction of port C (all outputs)
		out	DDRD, TmpReg		; set direction of port D (all outputs)
		
		ldi TmpReg, 0
		out	PortC, TmpReg		; set port C to 0x00 (disable all pull-ups)
		out	PortD, TmpReg		; set port D to 0x00 (disable all pull-ups)	


		;configure the Analog to Digital Convertor
		
		;turn on the ADC circuit and enable ADC interrupt
		clr TmpReg
		ldi TmpReg, (1<<ADEN); load the enable ADC bit (clear in PWR saving, sleep...)
		out ADCSRA,TmpReg	 ; enable the adc interrupt and turn on the adc

		;ADC conversion details
		clr TmpReg
		ldi TmpReg, (1<<ADLAR)			; left adjust
		ori TmpReg, (1<<REFS0)|(1<<REFS1); internal ref, with extern cap at AREF pin 
		ori TmpReg, (1<<MUX0)|(1<<MUX1)|(1<<MUX2); channel ADC7 - PA7
		out ADMUX,TmpReg ; write it


		;fire off the free running mode
		clr TmpReg
		in TmpReg, ADCSRA;
		ori TmpReg, (1<<ADPS0)|(1<<ADPS0)|(1<<ADPS0); prescaler frequency Xtal/128
		ori TmpReg, (1<<ADATE);load the free running mode bit
		ori TmpReg, (1<<ADSC); load the start the first conversion bit
		ori TmpReg, (1<<ADIE); load enable the ADC interrupt bit
		out ADCSRA, TmpReg;	write it in the ADCSRA configuration register

;		sei ; enable global interrupt
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


init_Z:
	ldi ZL, low(next_channel*2)
	ldi ZH, high(next_channel*2)
ret



load_first_channel: 
	lpm r16, Z
ret

load_second_channel:
	push ZL
	push ZH
		inc ZL
		adc ZH, ZeroReg 
		lpm r16, Z
	pop ZH
	pop ZL
ret

load_third_channel:
	push ZL
	push ZH
		inc ZL
		adc ZH, ZeroReg 
		inc ZL
		adc ZH, ZeroReg
		lpm r16, Z
	pop ZH
	pop ZL
ret

;how to count 0,1,2,3?
Load_channel_to_switch_to:
	lpm r16, Z
ret

;********** M A I N ***********
Main:
;		ldi MaskReg, 0xFF
;		sub MaskReg, ADCreg
;		out PortC, MaskReg
;		out PortD, ADCReg
	rcall init_Z
	rcall load_second_channel
	rcall load_third_channel

		rjmp	Main			; loop	
		


next_channel:
.db 0, 3
.db 5, 0


