.NOLIST
.include "m16def.inc"
.include "..\MicroKerIncludeHeaders\TImem.inc"
.include "..\MicroKerIncludeHeaders\TaskControlBlock.inc"
.include "..\MicroKerIncludeHeaders\LinkedList.inc"
.include "..\MicroKerIncludeHeaders\CentralTable.inc"
.include "..\MicroKerIncludeHeaders\stack.inc"	;it's in the parrent directory


.include "..\MicroKerIncludeHeaders\coreCS3.inc"	;stacks and QUES
.include "..\MicroKerIncludeHeaders\macrosCS3.inc"

.LIST

;***** Subroutine Register Variables

.def	A		=r13			;first value to be compared
.def	B		=r14			;second value to be compared
.def	endL	=r17			;end of data array low address
.def	endH	=r18			;end of data array high address
.def	TmpReg	=r21
.def	ZeroReg	=r20

.ORG	0x0000
		jmp	RESET			; Reset Handler
		jmp	EXT_INT0		; External Interrupt Request 0 Handler
		jmp	EXT_INT1		; External Interrupt Request 1 Handler
		jmp	TIM2_COM		; Timer2 Compare Match Handler
		jmp	TIM2_OVF		; Timer2 Overflow Handler
		jmp	TIM1_CAP		; Timer1 Capture Handler

		jmp	QUANTUM_ISR		; Timer1 Compare Match A Handler
							; will provide the time slicing

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


;**************************************** Reset ****************************************************************
		.ORG	0x0030
Reset:		
		clr	ZeroReg				; kernel stack
		ldi	TmpReg, low(RAMEND)	; Initialize stack pointer SRAM
		out	SPL, TmpReg			; just for two calls
		ldi	TmpReg, high(RAMEND)
		out	SPH, TmpReg
		

		ldi	TmpReg, 0b10000000	; Disable JTAG interface
		out	MCUCSR, TmpReg
		out	MCUCSR, TmpReg

		ldi	TmpReg, 0xFF
		out	DDRA, TmpReg		; Set direction of port A (all outputs)
		out	DDRB, TmpReg		; Set direction of port B (all outputs)
		out	DDRC, TmpReg		; Set direction of port C (all outputs)
		out	DDRD, TmpReg		; Set direction of port D (all outputs)

		out	PortA, ZeroReg		; Set port A to 00h
		out	PortB, ZeroReg		; Set port A to 00h
		out	PortC, ZeroReg		; Set port A to 00h
		out	PortD, ZeroReg		; Set port A to 00h

		Quantum_config			;config the quantum 
								;enable global interrupts
		CS3_CTBL_init_table
		rjmp	Main
	


QUANTUM_ISR:
	yield_from_tick
reti
;**********************************************************************************

;********************************** Unused interrupt vectors ***************************************************
EXT_INT0:
EXT_INT1:
TIM2_COM:
TIM2_OVF:
TIM1_CAP:
;TIM1_COMA:	;quantum slicer
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

Main:
	create_shell
Main1:

rjmp Main1	

;********************
;**     SHELL      **
;********************
;this will become the 
;shell so it should 
;have be a loop waiting
;for commands and running
;only when there is 
;a command to exec.
;(in the future...)
;- also, in order to
;avoid coding user GUI
;it will be getting
;the commands over RS232 
shell:
create_task TaskA,1
create_task TaskB,2
create_task TaskC,3
create_task TaskD,4
rjmp Main1


;********************
;**     TASK A     **
;********************
TaskA:
	ldi r17,1
	and r17, r18
	cpi r17,0
	breq even_A
	ldi r16, 0xA
	rjmp ExecA

  even_A:
  	ldi r16, 0xAA

  ExecA:
  	ldi r17, 8
	loop_even_A:
	push r16
	dec r17
	cpi r17,0
	brne loop_even_A

	ldi r17, 8
	loop_odd_A:
	pop r16
	dec r17
	cpi r17,0
	brne loop_odd_A
	inc r18
	rjmp TaskA
	



;********************
;**     TASK B     **
;********************
TaskB:
	ldi r17,1
	and r17, r18
	cpi r17,0
	breq even_B
	ldi r16, 0xB
	rjmp ExecB

  even_B:
  	ldi r16, 0xBB

  ExecB:
  	ldi r17, 8	;pushing eight values
	loop_even_B:
	push r16
	dec r17
	cpi r17,0
	brne loop_even_B

	ldi r17, 8
	loop_odd_B:
	pop r16
	dec r17
	cpi r17,0
	brne loop_odd_B
	inc r18
	rjmp TaskB

	
;********************
;**     TASK C     **
;********************
TaskC:
	ldi r17,1
	and r17, r18
	cpi r17,0
	breq even_C
	ldi r16, 0xC
	rjmp ExecC

  even_C:
  	ldi r16, 0xCC

  ExecC:
  	ldi r17, 8	;pushing eight values
	loop_even_C:
	push r16
	dec r17
	cpi r17,0
	brne loop_even_C

	ldi r17, 8
	loop_odd_C:
	pop r16
	dec r17
	cpi r17,0
	brne loop_odd_C
	inc r18
	rjmp TaskC
	

;********************
;**     TASK D     **
;********************
TaskD:
	ldi r17,1
	and r17, r18
	cpi r17,0
	breq even_D
	ldi r16, 0xD
	rjmp ExecD

  even_D:
  	ldi r16, 0xDD

  ExecD:
  	ldi r17, 8	;pushing eight values
	loop_even_D:
	push r16
	dec r17
	cpi r17,0
	brne loop_even_D

	ldi r17, 8
	loop_odd_D:
	pop r16
	dec r17
	cpi r17,0
	brne loop_odd_D
	inc r18
	rjmp TaskD
	
	