

.NOLIST
.include "m16def.inc"
.include "..\MicroKerIncludeHeaders\constdef1.inc"	;it's in the parrent directory
.include "..\MicroKerIncludeHeaders\coredef1.inc"	;stacks and QUES
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

		rcall T1A_config			;config the quantum 
		rcall init				;set up the stacks, pointers etc.

								;enable global interrupts
		rjmp	Main
	
;**********************************************************************************
;************************ CONFIGURATION OF THE TIMER COUNTER 1 ********************
;									AS THE HEARTBEAT
;**********************************************************************************
T1A_config:
		clr TmpReg
		out TCCR1A,TmpReg
		ldi TmpReg, (1<<WGM12)|(1<<CS11)|(1<<CS10); CTC/64 
		out TCCR1B, TmpReg

		ldi TmpReg, 0x0
		out OCR1AH, ZeroReg		; init OCR1AH & OCR1AL
		ldi TmpReg, 0xF			; initial quantum size 
		out OCR1AL, TmpReg		; so you have to write the High byte first

		ldi TmpReg, (1<<OCIE1A)	; timer 0 overflow flag
		out TIMSK,TmpReg		; set the flag
		ret				;return from here back to reset
;*******************************************************************************

;*************************** THIS WILL BE THE QUANTUM GIVER *********************** 
QUANTUM_ISR:
	;save current stack top and replace it with 
	;the hardware stack
	rjmp yield_from_tick
	yietck:
reti; re-enable interrupt and start a new context

yield_from_tick:
	rjmp save_context
	scntx:	;done saving context
									;rcall incrementTick
	rjmp switch_context;
	swcntx:	;done switching context
	rjmp restore_context;
	rcntx:	;done restoring context
rjmp yietck					;get out of this function

;*******************************************
save_context:
	push r0
	in r0,SREG
	push r0
	cli ;disable interrupts after you save the status!
	push r1
	push r2
	push r3
	push r4
	push r5
	push r6
	push r7
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
	push r16
	push r17
	push r18
	push r19
	push r20
	push r21
	push r22
	push r23
	push r24
	push r25
	push r26
	push r27
	push r28
	push r29
	push r30
	push r31
	lds  XL, pCurTCB	;you have the address where to store SP
	lds  XH, pCurTCB+1	;in X
	in r0, SPL
	st X+, r0
	in r0, SPH
	st X+,r0			;the SP is stored at the appropriate TCB
rjmp scntx
;**************************************************************************
;**************************************************************************
switch_context:
	;you have to change the stacks here
	ldi ZL, low(pCurTCB)	;load the address of pointer to CurTCB
	ldi ZH, high(pCurTCB)	;
	lds XH, pCurTCB+1		;load the value of the pointer
	lds XL, pCurTCB			;X holds the address of current TCB
	ldi YL, low(ATCB)		;load the address of Task Control Block A
	ldi YH,	high(ATCB)
	cp XL,YL
	brne notA				;the addresses do not match so the current 					
							;TCB is that of task B, so switch to A
	ldi YL, low(BTCB)		;load the address of Task Control Block B
	ldi YH,	high(BTCB)
	rjmp dnsw
notA:	
	ldi YL, low(ATCB)		;load the address of Task Control Block B
	ldi YH,	high(ATCB)
dnsw:	
	st Z+, YL				;store the address of cur TCB 
	st Z, YH				;pCurTCB now points to ATCB or BTCB
rjmp swcntx
;**************************************************************************
;**************************************************************************
restore_context:
	lds ZH, pCurTCB+1		;The address of new TCB in Z
	lds ZL, pCurTCB
							;check if it's been run before
	ldd TmpReg, Z+FIRST_Time_offset
	cpi TmpReg, 0x1
	
	brne run_before
	;clear the flag
	ldi TmpReg, 0x0
	std Z+FIRST_Time_offset, TmpReg
	rjmp btask	;it must be BTASK so jump into it

run_before:
	lds ZH, pCurTCB+1		;The address of new TCB in Z
	lds ZL, pCurTCB
	ld YL,Z+
	out SPL,YL
	ld YH,Z+
	out SPL, YL

	pop r31
	pop r30
	pop r29
	pop r28
	pop r27
	pop r26
	pop r25
	pop r24
	pop r23
	pop r22
	pop r21
	pop r20
	pop r19
	pop r18
	pop r17
	pop r16
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop r7
	pop r6
	pop r5
	pop r4
	pop r3
	pop r2
	pop r1
	pop r0
	out SREG, r0

	;clear the interrupt flag
	push TmpReg
	ldi TmpReg, (1<<OCF1A)
	out TIFR, TmpReg
	pop TmpReg
	pop r0
rjmp rcntx
;**********************************************************************************

;********************************** Unused interrupt vectors ***************************************************
EXT_INT0:
EXT_INT1:
TIM2_COM:
TIM2_OVF:
TIM1_CAP:
;TIM1_COMA:
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
	;create the first process
	rjmp atask
rjmp Main	

;**********************initialize the TCB's and stack, plus the curTCB pointer
init:
;(1) the init will set up Task A  to run first so it will have to also
;start up Task B
	ldi YL, low(pCurTCB)	;load the low address of pointer to CurTCB
	ldi YH, high(pCurTCB)	;load  high
	ldi XL, low(ATCB)		;load the address of Task Control Block A
	ldi XH,	high(ATCB)
	st Y+, XL				;load the pointer with the address of TCBA 
	st Y, XH				;pCurTCB now points to TCBA
;(2)
	;lets hook the stacks in the TCB's
	ldi YL, low(ATCB+SP_offset)	;load address of HW stack of task A, in its TCB  
	ldi YH, high(ATCB+SP_offset)
	ldi XL, low(ASTCK+STACK_SIZE_MAX)		;load the address of HW stack of A
	ldi XH,	high(ASTCK+STACK_SIZE_MAX)
	st Y+, XL				;store the address of HW stack A in TCBA 
	st Y, XH				;task control block A now has address of its stack
;(3)
	ldi YL, low(BTCB+SP_offset)	;load address of HW stack of task B, in its TCB  
	ldi YH, high(BTCB+SP_offset)
	ldi XL, low(BSTCK+STACK_SIZE_MAX)		;load the address of HW stack of B
	ldi XH,	high(BSTCK+STACK_SIZE_MAX)
	st Y+, XL				;store the address of HW stack B in BTCB 
	st Y, XH				;task control block A now has address of its stack
	;let's record the fact that B will be restored 
	;the first time it is run
	ldi YL, low(BTCB+FIRST_TIME_offset)	  
	ldi YH, high(BTCB+FIRST_TIME_offset) 
	ldi TmpReg, 0x1
	st Y,TmpReg	; so this will mean that B is running the first time
;(4)
;now lets init both stacks just to check if
;the lack of byte alignment will screew something up
	ldi TmpReg,STACK_SIZE_MAX
	lds YL,low(ATCB+SP_offset)	;the low byte is the second
	lds YH,high(ATCB+SP_offset+1)		;the high byte is the first
	lds ZL,low(BTCB+SP_offset)
	lds ZH,high(BTCB+SP_offset+1)	
	stkloop:
		
		st -Y,TmpReg		;init stack A
		st -Z,TmpReg		;init stack B
		subi TmpReg,1
		cp TmpReg, ZeroReg
		brne stkloop	
ret
 ;***************************** from init ********************************

;*******************task A
atask:
	cli
	lds TmpReg, low(ATCB+SP_offset)
	out SPL, TmpReg
	lds TmpReg, high(ATCB+SP_offset+1)
	out SPH, TmpReg
	;*****************************
	;if you want to be honest and 
	;go through the pCurTCB dereferrence
	;then uncomment this and comment out
	;the four lines above the asterisk line
	;*****************************
	;lds ZH, pCurTCB+1		
	;lds ZL, pCurTCB							
	;ldd TmpReg, Z+SP_offset
	;out SPL, TmpReg
	;ldd TmpReg, Z+SP_offset+1
	;out SPH, TmpReg
	sei
	aloop:
		inc TmpReg
		mov r0, TmpReg
		push r0 
		mov r1, TmpReg
		push r1
		mov r2, TmpReg
		push r2
		mov r3, TmpReg
		push r3

		pop r0 
		pop r1
		pop r2
		pop r3

		rjmp aloop

;******************task B
btask:
	cli
	lds TmpReg, low(BTCB+SP_offset)
	out SPL, TmpReg
	lds TmpReg, high(BTCB+SP_offset+1)
	out SPH, TmpReg
	sei
	bloop:
		inc TmpReg
		mov r0, TmpReg
		push r0 
		mov r1, TmpReg
		push r1
		mov r2, TmpReg
		push r2
		mov r3, TmpReg
		push r3

		pop r0 
		pop r1
		pop r2
		pop r3
		rjmp bloop

