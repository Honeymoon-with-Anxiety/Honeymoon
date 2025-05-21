;
.NOLIST
.include	"m16def.inc"
.include    "macro.inc"
.LIST



;====== Register definitions =======

.DEF	ZeroReg		= r1
.DEF	TmpReg		= r21
.DEF	ADCReg		= r18
.DEF 	MaskReg		= r19

.def cislo = r16
.def accu = r17



.equ tisic_offset = 0
.equ stovky_offset = 1
.equ desitky_offset = 2
.equ jednotky_offset = 3

.dseg
	disp_RAM: .byte 4
.cseg

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
		;jmp	ADC_COMP		; ADC Conversion Complete Handler
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

		sei ; enable global interrupt
		rjmp Main
;***************************************

;************** Delay (PDelReg[ms]) ***************
.DEF	PDelReg		= r20
.DEF	PDelReg0	= r23
.DEF	PDelReg1	= r22
.DEF	PDelReg2	= r2
; this is a delay subroutine 
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

init_Y_displ_RAM:
	ldi YL, low(disp_RAM)
	ldi YH, high(disp_RAM)
ret

init_Z_na_moje_tabulka:
	ldi ZL, low(2*display)
	ldi ZH, high(2*display)
ret

init_X_na_konec_moje_tabulka:
	ldi XL, low(2*konec_display)
	ldi XH, high(2*konec_display)
ret

vymazat_disp:
	std Y+tisic_offset, ZeroReg
	std Y+stovky_offset, ZeroReg
	std Y+desitky_offset, ZeroReg
	std Y+jednotky_offset, ZeroReg
ret

;++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
number_break_up:;

	clr accu
;++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	

		cpi  cislo, 16
	
		brlo jedna1

	deset:
		inc accu

		subi cislo, 16
		

		cpi  cislo, 16
		brsh deset
	
	std Y+desitky_offset, accu
	clr accu
	
;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++	
	jedna1:
		
	
		cpi  cislo, 1

		brlo done


	jedno:
		inc accu

		subi cislo, 1
		

		cpi  cislo, 1
		
		brsh jedno
	
	done:
		std Y+jednotky_offset, accu
ret
;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
jednotky:
	ldi r20, 0b00011100
	out portD, r20
	clr r18
	ldd r19, Y+jednotky_offset	
	add ZL, r19
	adc ZH, ZeroReg
	lpm r18, Z		
	out portC,r18

	ldi PDelReg, 1
	rcall Delay1m
ret

desitky:
	ldi r20, 0b00011000
	out portD, r20
	clr r18
	ldd r19, Y+desitky_offset	
	add ZL, r19
	adc ZH, ZeroReg
	lpm r18, Z		
	out portC,r18

	ldi PDelReg, 1
	rcall Delay1m
ret

stovky:
	ldi r20, 0b00010100
	out portD, r20
	clr r18
	ldd r19, Y+stovky_offset	
	add ZL, r19
	adc ZH, ZeroReg
	lpm r18, Z		
	out portC,r18

	ldi PDelReg, 1
	rcall Delay1m
ret

tisice:
	ldi r20, 0b00010000
	out portD, r20
	clr r18
	ldd r19, Y+tisic_offset	
	add ZL, r19
	adc ZH, ZeroReg
	lpm r18, Z		
	out portC,r18

	ldi PDelReg, 1
	rcall Delay1m
ret

Main:
	clr cislo
	in ADCReg, ADCH

	adiw XL, 1
	adc XH, ZeroReg
	
	mov r24, XH
	mov r20, XL
	
	rcall init_Y_displ_RAM
	rcall vymazat_disp
	rcall number_break_up
	
	rcall init_Z_na_moje_tabulka
		

	loop:
		in cislo,ADCH
		rcall number_break_up
		rcall jednotky
		rcall init_Z_na_moje_tabulka

		rcall desitky
		rcall init_Z_na_moje_tabulka

		rcall stovky
		rcall init_Z_na_moje_tabulka
	
		rcall tisice
		rcall init_Z_na_moje_tabulka
		
		rjmp loop

rjmp Main


display:
.db 0b11000000,0b11111001 ;0,1
.db 0b10100100,0b10110000 ;2,3
.db 0b10011001,0b10010010 ;4,5
.db 0b10000010,0b11111000 ;6,7
.db 0b10000000,0b10010000 ;8,9
.db 0b10001000,0b10000011 ;A,b
.db 0b11000110,0b10100001 ;C.d
.db 0b10000110,0b10001110 ;E,F
konec_display:


