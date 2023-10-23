.NOLIST
.include "m16def.inc"
.include "..\MicroKerIncludeHeaders\TImem.inc"
.include "..\MicroKerIncludeHeaders\TaskControlBlock.inc"
.include "..\MicroKerIncludeHeaders\CentralTable.inc"
.include "..\MicroKerIncludeHeaders\stack.inc"	;it's in the parrent directory
.include "..\MicroKerIncludeHeaders\LinkedList.inc"

.include "..\MicroKerIncludeHeaders\SemaphoreControlBlock.inc"
.include "..\MicroKerIncludeHeaders\coresemaphores.inc"	;
.include "..\MicroKerIncludeHeaders\macrosCS3.inc"
.include "..\MicroKerIncludeHeaders\CBuffProducerConsumer.inc"
.LIST

.CSEG

;***************************
.CSEG
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
		ldi	TmpReg, 0b10000000	; Disable JTAG interface
		out	MCUCSR, TmpReg
		out	MCUCSR, TmpReg

		Quantum_config			;config the quantum 
								;enable global interrupts
		PCCTBL_init_table
		rjmp	Main
	

QUANTUM_ISR:
	sema_yield_from_tick
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


.include "..\MicroKerIncludeHeaders\semaphoreSubroutines.inc"
.include "..\MicroKerIncludeHeaders\ConsumerSuppTasks.inc"	


Main:
	create_shell

Main1:
	get_label_ptr pShellBlock,ZL,ZH
	rcall sem_wait ;block the shell from execution
rjmp Main1	
nop
nop
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
create_task ConsumerMutex,4
create_task SupplierMutex,4

.DSEG
	;pShellBlock is a pointer to semaphores
	pShellBlock: .BYTE ptr_sz;semaphore to block the shell
.CSEG
	ldi r18,0
	sem_create r16,r17,r18	;creating the shell block
	set_label_ptr pShellBlock,r16,r17
rjmp Main1



	

