
;***************************************************************************************************************
; Program	: UART test 0
; Hardware	: MB-ATmega16(L) v1.3 (Xtall 14.7456MHz)
; Author	: David Del Maschio
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
.include 	"TImem.inc"
.include 	"CircBuffer.inc"
.include 	"RS232.inc"
.LIST


;====================================== Constants ==============================================================
;.EQU	BaudConst	= 7	; = Round(14.7456Mhz / (16 * 115200) - 1)
.EQU	BaudConst	= 95	; = Round(14.7456Mhz / (16 * 9600) - 1)

.EQU 	HighWaterMark 	= 5	;serial buffer almost full -  you only have 8 byte Q
.EQU	LowWaterMark	= 2

;================================== Register definitions =======================================================
.DEF	ZeroReg		= r1
.DEF	TmpReg		= r16


.DEF	Counter1	= r3

.DEF 	NewChar		= r15
.DEF	RecData		= r17
.DEF	TmpReg2		= r18
.DEF	SendData	= r19
.DEF	InBuffFull	= r20
.DEF	XOFF_SET    = r21




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
Reset:		
		clr	ZeroReg
		clr InBuffFull

		ldi	TmpReg, low(RAMEND)	; Initialize stack pointer to highest address in internal SRAM
		out	SPL, TmpReg
		ldi	TmpReg, high(RAMEND)
		out	SPH, TmpReg

		ldi	TmpReg, 0b10000000	; Disable JTAG interface
		out	MCUCSR, TmpReg
		out	MCUCSR, TmpReg




		ldi	TmpReg, 0xFF
		out	DDRA, TmpReg		; Set direction of port A (all outputs)
		out	DDRB, TmpReg		; Set direction of port B (all outputs)
		out	DDRC, ZeroReg		; Set direction of port C (all inputs)
		out	DDRD, ZeroReg		; Set direction of port D (all inputs)

		out	PortA, TmpReg		; Set port A to FFh
		out	PortB, TmpReg		; Set port A to FFh
		out	PortC, TmpReg		; Set port A to FFh
		out	PortD, TmpReg		; Set port A to FFh


		mov	RecData, ZeroReg

		sei
		rjmp	Main
	

;**************************************************
;			THE CASE CHANGING MACRO
;**************************************************
;takes a character as argument 0 converts it into
;its corresponding capital case if it is lower case
;converts it into its corresponding lower case if it
;is its upper case. The return value goes back in arg1
;also if the character supplied is not a letter it will
;return a questionmark
;**************************************************
		.MACRO flip_case
			cpi @0,END_TRANS
			breq was_alpha	

			;lower cases 97 to 122
			cpi @0, 97
			brsh lower_case 		; branch if same or higher

			;upper cases 65 to 90
			cpi @0, 65
			brsh upper_case
			rjmp non_alpha
					
		lower_case:
			cpi @0, 123
			brsh non_alpha
			subi @0, 32 		; change to upper case   
			rjmp was_alpha

		upper_case:
			cpi @0, 91
			brsh non_alpha
			subi @0, -32
			rjmp was_alpha

		non_alpha:
			ldi @1, 63	; load  the question mark
			rjmp finish_config

		was_alpha:
			mov @1,@0
		finish_config:
		.ENDMACRO
;************************** end flip case


;***** ISR FOR UART RECEIVE COMPLETE INTERRUPT *****
;want to take the received character and if it
;is a small case turn it into its upper case.
;if it is an upper case turn it into a lower case
;if it is neither, return question mark.
UART_RXC:
	in RecData, UDR
	push TmpReg

	TIwrite_circular_buffer CBuffIn, RecData
	;check if CBuffIn is reaching the high water
	;so that the UDR interrupt can send XOFF
	TIget_byte CBuffIn+TICount_offset, InBuffFull
	cpi InBuffFull, HighWaterMark
	brsh RXC_check_water
	;send XON if the water is low
	ldi TmpReg, LowWaterMark
	cp TmpReg, InBuffFull 	
	brge RXC_check_water

	;check if the UDRIE is enabled if not enable it
	sbic UCSRB, 5
	rjmp RXC_done

RXC_check_water:
	;enable DRE interrupt just in case it got disabled 
	;because the OutQ was empty - now you got something
	;is so it may get processed soon
	in TmpReg, UCSRB	
	ori TmpReg, (1<<UDRIE)
	out UCSRB, TmpReg

RXC_done:
	pop TmpReg
reti

;***** ISR FOR THE DATA REGISTER EMPTY *****
;you have to check if the RXC interrupt has 
;reported that the InQ is reaching the
;HighWaterMark, if yes then send XOFF immediatelly
; 
;If the RXC is reporting LowWaterMark, send XON, 
;otherwise keep on doing whatever you were doing 
UART_DRE:
	push TmpReg2

	;check water if it's too high or low
	cpi InBuffFull, HighWaterMark
	brsh DRE_High_Water

	cpi InBuffFull, LowWaterMark 	
	brge DRE_water_fine	;water is above low
						;	water is below low 
							;so check if XOFF was sent

	cp XOFF_SET, ZeroReg
	brne DRE_low_water

DRE_water_fine:
	;check if there is anything in the outQ
	;to send out. if not disable DRE interrupt  
	TIget_byte CBuffOut+TICount_offset, TmpReg2
	cp TmpReg2,ZeroReg
	brne OutQ_not_empty
	
	;OutQ is empty so disable yourself
	in TmpReg2, UCSRB
	andi TmpReg2, 0b11011111
	out UCSRB, TmpReg2

	pop TmpReg2
reti	;disable and return if empty

OutQ_not_empty:	;since your Q is not empty
				;send whatever is in it
	TIread_circular_buffer CBuffOut, TmpReg2
	out UDR, TmpReg2	;send data
	
	pop TmpReg2
reti

DRE_High_Water:
	ldi TmpReg2, ASCII_XOFF
	out UDR,TmpReg2
	ser XOFF_SET	;mark sending XOFF
	pop TmpReg2
	reti
	
DRE_low_Water:
	ldi TmpReg2, ASCII_XON
	out UDR,TmpReg2
	clr XOFF_SET	; clear X off since you just sent
					; Xon (it should probably be in SRAM)
					; instead of a register.

	; since we had low water, and sent XON
	; there will most likely be RXC interrupt 
	; comming to enable DRE interrupt 
	; so we just disable DRE interrupt for now
	in TmpReg2, UCSRB	
	andi TmpReg2, 0b11011111
	out UCSRB, TmpReg2

	pop TmpReg2
	reti		
;********** end uart DRE ISR ***********




;********** Unused interrupt vectors **********
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


;**************************************************
;********************** MAIN **********************
;**************************************************
;testing the circular buffer capabilities
Main:
	open_RS232

Main1:
	out PortB, SendData
	
	;check if there is anything waiting at 
	;the RS232 port
	Read_Data_Waiting_RS232 TmpReg2
	cpi TmpReg2, 0
	breq Main1 ;if nothing there won't be processing

	;if there is something then process it
	Read_RS232 TmpReg2
	
	;process the incomming data
	flip_case TmpReg2,SendData

	;write something to RS232 after processing it
	WriteRS232 SendData

	rjmp Main1	

.exit
