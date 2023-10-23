;***************************************************************************************************************
; Program	: UART test 0
; Hardware	: MB-ATmega16(L) v1.3 (Xtall 14.7456MHz)
;		: Mini LED module left
;		: Mini LED module right
; Author	: Ing. Ivan Miksanek jr.
;***************************************************************************************************************

;***************************************************************************************************************
; Short description
; -----------------
; Program includes 16-bit counter which is incremented 
; by value received by UART. After a byte
; is received and added to counter the actual counter value 
; is transmitted by UART. Also
; the value is displayed on two mini LED modules inserted in connector CON1.
; Counter can be reseted to zero by sending 0 by UART.
;
; MB-ATmega16 board configuration: JP3 (1-3, 2-4), JP4 (3-5, 4-6)
;***************************************************************************************************************


;====================================== Includes ===============================================================
.NOLIST
.include	"m16def.inc"
.LIST


;====================================== Constants ==============================================================
;.EQU	BaudConst	= 7	; = Round(14.7456Mhz / (16 * 115200) - 1)
.EQU	BaudConst	= 95	; = Round(14.7456Mhz / (16 * 9600) - 1)


;================================== Register definitions =======================================================
.DEF	ZeroReg		= r1
.DEF	TmpReg		= r16

.DEF	Counter0	= r2
.DEF	Counter1	= r3

.DEF 	OldChar		= r14
.DEF 	NewChar		= r15
.DEF	RecData		= r17
.DEF	Received	= r18
.DEF	SendData	= r19
 




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


;**************************************** Reset ****************************************************************
		.ORG	0x0030
Reset:		clr	ZeroReg

		ldi	TmpReg, low(RAMEND)	; Initialize stack pointer to highest address in internal SRAM
		out	SPL, TmpReg
		ldi	TmpReg, high(RAMEND)
		out	SPH, TmpReg

		ldi	TmpReg, 0b10000000	; Disable JTAG interface
		out	MCUCSR, TmpReg
		out	MCUCSR, TmpReg


;  	Enable receiver and transmitter and receive complete interrupt 
;	and data register empty interrupt (transmitter)
		ldi	TmpReg, (1<<RXCIE)|(1<<RXEN)|(1<<TXEN)|(1<<UDRIE)
		out	UCSRB, TmpReg

; Set no. of bits to 8 no parity
		ldi	TmpReg, (1<<URSEL)|(3<<UCSZ0)
		out	UCSRC, TmpReg

		ldi	TmpReg, BaudConst	; Set baud rate to BaudConst
		out	UBRRL, TmpReg
		out	UBRRH, ZeroReg

		ldi	TmpReg, 0xFF
		out	DDRA, TmpReg		; Set direction of port A (all outputs)
		out	DDRB, TmpReg		; Set direction of port B (all outputs)
		out	DDRC, ZeroReg		; Set direction of port C (all inputs)
		out	DDRD, ZeroReg		; Set direction of port D (all inputs)

		out	PortA, TmpReg		; Set port A to FFh
		out	PortB, TmpReg		; Set port A to FFh
		out	PortC, TmpReg		; Set port A to FFh
		out	PortD, TmpReg		; Set port A to FFh

		mov	Counter0, ZeroReg
		mov	Counter1, ZeroReg

		mov	RecData, ZeroReg
		mov	Received, ZeroReg

		sei
		rjmp	Main
	

;***** ISR FOR UART RECEIVE COMPLETE INTERRUPT *****
;want to take the received character and if it
;is a small case turn it into its upper case.
;if it is an upper case turn it into a lower case
;if it is neither, return question mark.
UART_RXC:
	in RecData, UDR
	
	;lower cases 97 to 122
	cpi RecData, 97
	brsh lower_case 		; branch if same or higher

	;upper cases 65 to 90
	cpi RecData, 65
	brsh upper_case
	rjmp non_alpha
					
lower_case:
	cpi RecData, 123
	brsh non_alpha
	subi RecData, 32 		; change to upper case   
	mov SendData, RecData	; load the sender
	rjmp was_alpha

upper_case:
	cpi RecData, 91
	brsh non_alpha
	subi RecData, -32
	rjmp was_alpha

non_alpha:
	ldi SendData, 63	; load  the question mark
	rjmp finish_config

was_alpha:
	mov SendData,RecData
finish_config:
	in TmpReg, UCSRB	;disable this interrupt
	ori TmpReg, (1<<UDRIE)
	out UCSRB, TmpReg
reti

;***** ISR FOR THE DATA REGISTER EMPTY *****
;when the recieve complete interrupt is done
;updating the received character, you want to 
;send it back immediatelly - i.e. to enable
;UART_DRE from UART_RXC
UART_DRE:
	out UDR, SendData	;send data
	in TmpReg, UCSRB	;disable this interrupt
	andi TmpReg, 0b11011111
	out UCSRB, TmpReg
reti


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
UART_TXC:
ADC_COMP:
EE_RDY:
ANA_COMP:
TWI:
EXT_INT2:
TIM0_COM:
SPM_RDY:	reti


;***************************************************************************************************************
;*************************************** M A I N ***************************************************************
;***************************************************************************************************************
Main:	
		out	PortA, SendData
		rjmp	Main			; jmp to loop start



