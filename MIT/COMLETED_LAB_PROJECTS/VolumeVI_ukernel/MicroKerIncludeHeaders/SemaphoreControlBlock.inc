;SemaphoreControlBlock.inc file
;WARNING! Eventhough this implementation
;is semi-functional, it may be practical
;to do it differently depending on
;your requirements. What follows is 
;just for demo purposes in high school
;environment



 


;Semaphore operations are 
;atomic. they should be coded as 
;critical sections. This is implemented 
;by disabling interrupts.

.CSEG
;***************************
;			SCB
;***************************
;semaphore control block
.EQU scb_count_offset 	= 0	;	The value of the semaphore.
.EQU scb_pSemQ_offset	= 1	;	Pointer to the queue of tasks waiting for
							; 	this particular semaphore.
.EQU SCB_sz				= 3	; 	size of SCB is 5 bytes

;***********************************
;			SCBinitArray
;***********************************
;initializes array of TASK_MAX SCB's 
;given the address label in arg0
;where the first SCB is to be located.
;
;
;when you do your SRAM layout, you have 
;to define the label for the array of the 
;semaphore control blocks - it will be 
;called SCBs
;
;In essence all you have to do here is
;just link the SCB's in a linked list
;after you call this macro
.MACRO SCBinitArray
	push r16	;loop counter
	push r17	;zero register
	push ZL		;pointer to TCB
	push ZH

	ldi r16, TASK_MAX	;iterator - number of SCBs
	ldi ZL, low(SCBs)
	ldi ZH, high(SCBs)	
	clr r17

	SCBinitLoop:
	;set count to zero
		std Z+scb_count_offset, r17
	;set pointer to semaphore Q to NULL
		std Z+scb_pSemQ_offset, r17
		std Z+scb_pSemQ_offset+1, r17

		adiw ZH:ZL,scb_sz			;advance scb pointer

		dec r16
		cpi r16, 0
		brne SCBinitLoop
		
	pop ZH
	pop ZL
	pop r18
	pop r17
	pop r16
.ENDMACRO

;just a lazy argumented version
;so that I don't have to rewrite 
;the other programs
.MACRO ASCBinitArray
	push r16	;loop counter
	push r17	;zero register
	push ZL		;pointer to TCB
	push ZH

	ldi r16, @0	;iterator - number of SCBs
	ldi ZL, low(SCBs)
	ldi ZH, high(SCBs)	
	clr r17

	SCBinitLoop:
	;set count to zero
		std Z+scb_count_offset, r17
	;set pointer to semaphore Q to NULL
		std Z+scb_pSemQ_offset, r17
		std Z+scb_pSemQ_offset+1, r17

		adiw ZH:ZL,scb_sz			;advance scb pointer

		dec r16
		cpi r16, 0
		brne SCBinitLoop
		
	pop ZH
	pop ZL
	pop r18
	pop r17
	pop r16
.ENDMACRO


;***************************
;	  SEMAPHORE CREATE
;***************************
;extracts an SCB from freeSCBQ,
;inserts it into used SCBs and 
;returns pointer to the semaphore's
;SCB in return registers
;you will later move the SCB back 
;and forth from the used and free
;SCB Queues using this returned SCB
;address
;arg0 pointer to the SCB low (return)
;arg1 pointer to the SCB high (return)
;arg2 initial number of tasks (input arg)
;allowed access this semaphore
.MACRO sem_create
ENTER_CRITICAL_SECTION
	ll_head_extract pSCB_freeQ, XL, XH
	ll_head_insert pSCB_usedQ, XL,XH
	;set the initial count
		;now the address of the node containing the 
		;pointer to semaphore's SCB is in X
		ll_get_data_ptr XL,XH,@0,@1
		;now the return arguments contain
		;the pointer to the SCB
		mov ZL,@0
		mov ZH,@1
		std Z+scb_count_offset, @2 
EXIT_CRITICAL_SECTION
.ENDMACRO


;******* SemQ_head_extract **********
;extracts the first node of the semaphore Q
;recall that a semaphore is defined by its 
;control block - SCB 
;arg0 SCB address Low
;arg1 SCB address High
;returns the address of the TCB to extract in
;arg2 address of TCB to unsuspend Low
;arg3 address of TCB to unsuspend High
;use any registers for arguments except
;for Z  
.MACRO SemQ_head_extract ; SCBL,SCBH,tcbL,tcbH
push r16
push r17
push ZL
push ZH
push YL
push YH
	mov ZL, @0
	mov ZH, @1	;Z points to SCB
	ldd YL, Z+scb_pSemQ_offset
	ldd YH, Z+scb_pSemQ_offset+1;you have the 
	;TCB to wake up at Y 

	;now fix the semQ up
	;1) get the pointer to the next 
	;Task waiting on this semaphore
	ldd r16, Y+tcb_pSemQ_offset
	ldd r17, Y+tcb_pSemQ_offset+1
	;2) store the address at the SCB
	;(semQ head)
	std Z+scb_pSemQ_offset,r16
	std Z+scb_pSemQ_offset+1,r17
	;3) set the extracted node's semQ pointer
	;to NULL
	clr r16
	std Y+tcb_pSemQ_offset,r16
	std Y+tcb_pSemQ_offset+1,r16
	;4) return the extracted TCB address 
	mov @2, YL
	mov @3, YH
pop YH
pop YL
pop ZH
pop ZL
pop r17
pop r16
.ENDMACRO


;******* SemQ_tail_insert **********
;inserts the TCB of a task to be waiting
;on this semaphore into its semaphore Queue
;recall that a semaphore is defined by its 
;control block - SCB 
;arg0 SCB address Low
;arg1 SCB address High
;returns the address of the TCB to extract in
;arg2 address of TCB to suspend Low
;arg3 address of TCB to suspend High
;use any registers for arguments except
;for Z  
.MACRO SemQ_tail_insert ; SCBlow, SCBhigh, TCBlow, TCBhigh 
push r16
push YL
push YH

;clr r16
	mov ZL, @0
	mov ZH, @1	;Z points to SCB
	ldd YL, Z+scb_pSemQ_offset
	ldd YH, Z+scb_pSemQ_offset+1;you have the 
	;address of the first TCB at Y (or possibly NULL)

	;1) check if the Q is empty
	cpi YL,0	
	brne semQ_not_empty
	cpi YH,0
	brne semQ_not_empty
	;at this point you know that no
	;tasks are waiting on this semaphore
		;so set the semQ head to point to
		;the TCB and tcb_pSemQ to NULL 
		std Z+scb_pSemQ_offset,@2
		std Z+scb_pSemQ_offset+1,@3
		mov ZL,@2
		mov ZH,@3
		std Z+tcb_pSemQ_offset, ZeroReg
		std Z+tcb_pSemQ_offset+1,ZeroReg
		rjmp semQ_tins_done

	;2) since the Q was not empty,
	;find the end of the list
	semQ_not_empty:
		ldd ZL, Y+tcb_pSemQ_offset
		ldd ZH, Y+tcb_pSemQ_offset+1	;load the TCB of the next task waiting 
										;Y is pointing to into Z

		cpi ZL,0		;check if there is anything in the Q
		brne semQcont
		cpi ZH,0
		brne semQcont

			;it was the last TCB so 
			;replace the final NULL
			;by the address of this TCB
			std Y+tcb_pSemQ_offset, @2
			std Y+tcb_pSemQ_offset+1,@3
			;and set the pointer to next 
			;block waiting to NULL
			mov YL,@2
			mov YH,@3
			clr ZL
			std Y+tcb_pSemQ_offset,ZL
			std Y+tcb_pSemQ_offset+1,ZL
			rjmp semQ_tins_done
semQcont:
	mov YL, ZL
	mov YH, ZH
	rjmp semQ_not_empty	

semQ_tins_done:

pop YH
pop YL
pop r16
.ENDMACRO



.exit

;you will be initializing the Q 
;of free SCB's in the central table