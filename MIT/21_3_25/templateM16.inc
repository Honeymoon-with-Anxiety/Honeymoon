;***********************************
;	lab example number one
;***********************************
;=========Includes =================

.NOLIST
.include	"m16def.inc"
.LIST

;====== Register definitions =======
.DEF TmpReg           = r16   ; temp register
.DEF ZeroReg          = r0
.DEF new_sample_index = r18	; new look up table position 
.EQU OC0 = PB3

;=====+== PROGRAM segment ==========
.CSEG
;******** Interrupt vectors ********
.ORG 0x0000
jmp RESET			; Reset Handler
jmp EXT_INT0		; External Interrupt Request 0 Handler
jmp EXT_INT1		; External Interrupt Request 1 Handler
jmp TIM2_COM		; Timer2 Compare Match Handler
jmp TIM2_OVF		; Timer2 Overflow Handler
jmp TIM1_CAP		; Timer1 Capture Handler
jmp TIM1_COMA		; Timer1 Compare Match A Handler
jmp TIM1_COMB		; Timer1 Compare Match B Handler
jmp TIM1_OVF		; Timer1 Overflow Handler
jmp TIM0_OVF		; Timer0 Overflow Handler
jmp SPI_STC			; SPI Transfer Complete Handler
jmp UART_RXC		; UART RX Complete Handler
jmp UART_DRE		; UART Data Register Empty Handler
jmp UART_TXC		; UART TX Complete Handler
jmp ADC_COMP		; ADC Conversion Complete Handler
jmp EE_RDY			; EEPROM Write Complete (Ready) Handler
jmp ANA_COMP		; Analog Comparator Handler
jmp TWI				; Two-wire Serial Interface Handler
jmp EXT_INT2		; External Interrup Request 2 Handler
jmp TIM0_COM		; Timer0 Compare Match Handler
jmp SPM_RDY			; Store Program Memory Ready

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
	clr ZeroReg
	ldi TmpReg, low(RAMEND)           ; Stack Ptr
	out SPL, TmpReg
	ldi TmpReg, high(RAMEND)
	out SPH, TmpReg

	ldi TmpReg, 0b10000000            ; Disable JTAG interface
	out MCUCSR, TmpReg
	out MCUCSR, TmpReg

	ldi TmpReg, 0xFF
	out DDRA, TmpReg                  ; Set direction of port A (all inputs)
	out DDRC, TmpReg                  ; Set direction of port C (all outputs)

	out PortA, TmpReg                 ; Set port A to 00h
	out PortB, TmpReg                 ; Set port A to 00h
	out PortC, ZeroReg                ; Set port A to 00h

	rcall nastaveniTim0CompareMatch
	rcall povolPreruseniNaTim0COM

	rjmp Main
;**************************************************

nastaveniPWM_Pinu:
	ldi TmpReg, (1<<DDB3) ; nastav pin na výstup
	out DDRB, TmpReg
ret

nastaveniTim0CompareMatch:
	rcall nastaveniPWM_Pinu

	ldi TmpReg, (1<<WGM00)|(1<<WGM01)         ; rychly PWM
	ori TmpReg, (0<<COM00)|(1<<COM01)         ; vycisti OC0 pin pri compare match
						  ; nastav OC0 na TOP hodnotu 
	ori TmpReg, (0<<CS02)|(0<<CS01)|(1<<CS00) ; no prescale 
	out TCCR0, TmpReg	
ret

povolPreruseniNaTim0COM:
	ldi TmpReg, (1<<OCIE0)
	out TIMSK, TmpReg
ret

nactiVzorekSinusovky:
	ldi    ZL, low(sine_tbl * 2)
	ldi    ZH, high(sine_tbl * 2) ; inicializace ukazatele Z
	inc    new_sample_index	      ; zvyseni indexu vzorku
	andi   new_sample_index, 0x7F ; mod 128 (128 je max cislo v tabulce) 
	add    ZL, new_sample_index   ; vypocet adresy vzorku
	adc    ZH, ZeroReg
	lpm	  r0, Z	              ; nacti vzorek z pameti programu do r0
	lsl	  r0	              ; vzorky jsou od 0 do 127, tak je vynasob 2 
	out OCR0, r0                  ; nastav na vystupni pin Output Compare Register 0 registr 0 
ret

TIM0_COM:
	push   TmpReg      ; Uloz docasny registr
   	in     TmpReg,SREG ; Nacti status registr
   	push   TmpReg      ; Uloz status registr
   	push   ZL
   	push   ZH          ; Uloz ukazatele Z
   	push   r0          ; Uloz zeroreg

	rcall nactiVzorekSinusovky

   	pop   r0           ; Obnov zeroreg
	pop   ZH
	pop   ZL           ; Obnov ukazatele Z
   	pop   Tmpreg
   	out   SREG,TmpReg  ; Obnov status registr
   	pop   TmpReg       ; Obnov docasny registr
reti
