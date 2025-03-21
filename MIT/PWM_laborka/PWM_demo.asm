;***************************************************************************
;*						A SLIGHTHLY SIMPLIDIED
;* A P P L I C A T I O N   N O T E   F O R   T H E   A V R   F A M I L Y
;*
;*
;* DESCRIPTION
;* This Application note describes how to generate waveforms on single
;* 8 bit PWM output. Using TIMER0, 8-bit PWM, through OC0, a.k.a PB3
;*
;***************************************************************************
.include "m16def.inc"
;**************************************************************************
;  REGISTERS
;**************************************************************************
.DEF   	TmpReg      		= r16   ; temp register
.DEF   	ZeroReg				= r17
.DEF	new_sample_index 	= r18	; new look up table position 
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
		
		;set the rest of the ports for output
		ldi	TmpReg, 0xFF
		out DDRA, TmpReg		
	;	out DDRB, TmpReg		
		out	DDRC, TmpReg		
		out PortA,TmpReg		
		out PortB, TmpReg		
		out	PortC, ZeroReg		
		
		rcall CONFIG_TIM0_COM
		rcall ALLOW_interrupt_on_TIM0_COM

		sei						; enable global interrupts by setting the I bit
								; in the status register
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
;TIM0_COM: ;PWM 2019 demo...
SPM_RDY:	reti

;*************************** CONFIG PWM OUTPUT PIN *
.EQU OC0 = PB3
config_PWM_pin_TIM0_COM:
	ldi TmpReg, (1<<DDB3)	; set PB3 for output
	out	DDRB, TmpReg		; of PWM signal TIM_COM0
ret
;***************************************************

;*************************** CONFIG TIM0_COM *******
CONFIG_TIM0_COM:
	rcall config_PWM_pin_TIM0_COM
	ldi TmpReg, (1<<WGM00)|(1<<WGM01); fast PWM
	ori TmpReg, (0<<COM00)|(1<<COM01); clear OC0 pin on compare match
									 ; set OC0 on TOP val 
	ori TmpReg, (0<<CS02)|(0<<CS01)|(1<<CS00); no prescale 
	out TCCR0, TmpReg	
ret

;*************************** OCIE on TIM0 ******
ALLOW_interrupt_on_TIM0_COM:
	ldi TmpReg, (1<<OCIE0)
	out TIMSK, TmpReg
ret
;***************************************************

;*************************** 50 PERCENT DUTY *******
SET_DUTY_50_TIM0_COM:
	ldi TmpReg, 127
	out OCR0, TmpReg
ret
;***************************************************

;*************************** generate RAMP *********
generate_PWM_RAMP_on_PB3:
	in TmpReg, OCR0
	inc TmpReg
	inc TmpReg
	out OCR0, TmpReg
ret
;***************************************************

;******************   GET SAMPLE   ******************************
;****************************************************************
load_SINE_sample:
   ;remember Xnew has the offset to the next sample to use
   ;it may be loaded with value higher than 128 so you will
   ;need to adjust it with modular division
   ldi    ZL,low(sine_tbl*2)			;load the base offset low
   ldi    ZH,high(sine_tbl*2)			;load the base offset high
   inc    new_sample_index				;get the next one
   andi   new_sample_index,0x7F         ;mod 128 (128 samples number sine table) 
   add    ZL,new_sample_index			;calculate the sample's address
   adc    ZH,ZeroReg                    ;Z now has the correct address of the sample
   lpm	  r0,Z							;the sample is in the r0 register
   lsl	  r0	;samples in sine_tbl are in the range 0 to 127, so multiply by 2
   				;in order to get the range 0 to 256, with 7-bit resolution 								
   out OCR0, r0
ret




;*************************** FILTER DEMO 2019*******
TIM0_COM:
	push   TmpReg    			; Store temporary register
   	in     TmpReg,SREG
   	push   TmpReg               ; Store status register
   	push   ZL
   	push   ZH                   ; Store Z-Pointer
   	push   r0                   ; Store R0 Register

;	rcall SET_DUTY_50_TIM0_COM
;	rcall generate_PWM_RAMP_on_PB3
	rcall load_SINE_sample

   	pop     r0                           ; Restore R0 Register
   	pop     ZH
   	pop     ZL                           ; Restore Z-Pointer
   	pop     Tmpreg
   	out     SREG,TmpReg                  ; Restore SREG
   	pop     TmpReg     
reti
;***************************************************


;************************MAIN**********************************
main: rjmp  main ; the interrupt is doing everything



;*************************** SIN TABLE *************************************
; Samples table : one period sampled on 128 samples and
; quantized on 7 bits
;******************************************************************************
sine_tbl:
.db 64,67
.db 70,73
.db 76,79
.db 82,85
.db 88,91
.db 94,96
.db 99,102
.db 104,106
.db 109,111
.db 113,115
.db 117,118
.db 120,121
.db 123,124
.db 125,126
.db 126,127
.db 127,127
.db 127,127
.db 127,127
.db 126,126
.db 125,124
.db 123,121
.db 120,118
.db 117,115
.db 113,111
.db 109,106
.db 104,102
.db 99,96
.db 94,91
.db 88,85
.db 82,79
.db 76,73
.db 70,67
.db 64,60
.db 57,54
.db 51,48
.db 45,42
.db 39,36
.db 33,31
.db 28,25
.db 23,21
.db 18,16
.db 14,12
.db 10,9
.db 7,6
.db 4,3
.db 2,1
.db 1,0
.db 0,0
.db 0,0
.db 0,0
.db 1,1
.db 2,3
.db 4,6
.db 7,9
.db 10,12
.db 14,16
.db 18,21
.db 23,25
.db 28,31
.db 33,36
.db 39,42
.db 45,48
.db 51,54
.db 57,60






