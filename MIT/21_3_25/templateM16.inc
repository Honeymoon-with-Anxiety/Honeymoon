;***********************************
;	lab example number one
;***********************************
;=========Includes =================

.NOLIST
.include	"m16def.inc"
.LIST

;====== Register definitions =======
.DEF   	TmpReg      		= r16   ; temp register
.DEF   	ZeroReg				= r0
.DEF	new_sample_index 	= r18	; new look up table position 

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
		jmp	ADC_COMP		; ADC Conversion Complete Handler
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
; TIM0_COM:
SPM_RDY:	reti


;************************************************
		
		.ORG	0x0030
Reset:		
	
		clr	ZeroReg
		ldi	TmpReg, low(RAMEND)	; Stack Ptr
		out	SPL, TmpReg
		ldi	TmpReg, high(RAMEND)
		out	SPH, TmpReg

		ldi	TmpReg, 0b10000000	; Disable JTAG interface
		out	MCUCSR, TmpReg
		out	MCUCSR, TmpReg

		ldi	TmpReg, 0xFF
		out	DDRA, TmpReg		; Set direction of port A (all inputs)
		out	DDRB, TmpReg		; Set direction of port B (all inputs)
		out	DDRC, TmpReg		; Set direction of port C (all outputs)
		out	DDRD, TmpReg		; Set direction of port D (all outputs)

		out	PortA, ZeroReg		; Set port A to 00h
		out	PortB, ZeroReg		; Set port A to 00h
		out	PortC, ZeroReg		; Set port A to 00h
		out	PortD, ZeroReg		; Set port A to 00h

		rjmp	Main
;**************************************************


load_SINE_sample:
   ldi    ZL, low(sine_tbl * 2)
   ldi    ZH, high(sine_tbl * 2) ; inicializace ukazatele Z
   inc    new_sample_index	 ; zvyseni indexu vzorku
   andi   new_sample_index, 0x7F ; mod 128 (128 samples number sine table) 
   add    ZL, new_sample_index	 ; calculate the sample's address
   adc    ZH, ZeroReg            ; Z now has the correct address of the sample
   lpm	  r0, Z			 ; the sample is in the r0 register
   lsl	  r0	                 ; samples in sine_tbl are in the range 0 to 127, so multiply by 2
   				 ; in order to get the range 0 to 256, with 7-bit resolution 								
   out OCR0, r0
ret

TIM0_COM:
	push   TmpReg      ; Uloz docasny registr
   	in     TmpReg,SREG ; Nacti status registr
   	push   TmpReg      ; Uloz status registr
   	push   ZL
   	push   ZH          ; Uloz ukazatele Z
   	push   r0          ; Uloz zeroreg

	rcall load_SINE_sample

   	pop   r0          ; Obnov zeroreg
	pop   ZH
	pop   ZL          ; Obnov ukazatele Z
   	pop   Tmpreg
   	out   SREG,TmpReg ; Obnov status registr
   	pop   TmpReg      ; Obnov docasny registr
reti
