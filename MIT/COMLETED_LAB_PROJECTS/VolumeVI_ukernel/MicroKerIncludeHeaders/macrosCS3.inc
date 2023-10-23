.MACRO ENTER_CRITICAL_SECTION 
	cli 
.ENDMACRO	;disable interrupts

.MACRO EXIT_CRITICAL_SECTION  
	sei 
.ENDMACRO	;enable interrupts


;**************************************
;	This is a kernel macro so 
;	no registers are saved
;	arg0 label of the task to create
;	arg1 priority in a register
;	
.MACRO create_task
	ENTER_CRITICAL_SECTION
;save the old stack pointer!!
;and restore it at the end of this
push r18
push r19
in r18, SPL
in r19, SPH
	ll_head_extract pTCBfreeQ,XL,XH
	;X should have the address to a ll_node
	;containing the address to a free TCB
	ll_get_data_ptr XL,XH,YL,YH
	;Y should have the address of the free
	;TCB for this process. So let's initialize it.
	;Let's initialize the stack
	TCBgetHWstk YL,YH,r16,r17
	out SPL, r16
	out SPH, r17
	ldi r16, low(@0)	;push the fn address
	push r16
	ldi r16, high(@0);push the fn High address
	push r16

	clr r16		;zero for r0 to pop
	push r16
	;ready the SREG 
	ldi r16, 0b10000000	;for status register
						;with global interrupts 
						;enabled
	push r16	;push SREG

	;clear the registers
	ldi r16, 31
	clr r17
	CTloopHWstk:
		push r17
		dec r16
		cpi r16,0
	brne CTloopHWstk
	
	;you also need to save the top of
	;the HW stack 
	;because you will be restoring your 
	;context from it first time the new
	;task gets the CPU
	in r15,SPL
	in r16,SPH 
	TCBsetHWstk YL,YH,r15,r16

	ldi r16, RUNNABLE
	TCBsetstatus YL,YH,r16
	ldi r16,@1
	TCBsetprio YL,YH,r16
	clr r16
	TCBsetdelay YL,YH, r16

	ll_tail_insert pRunQ, XL,XH

;restore the old stack
out SPL, r18
out SPH, r19
pop r19
pop r18
EXIT_CRITICAL_SECTION
.ENDMACRO	;create task
;**************************************


;**************************************
;** 	CREATE SHELL - NULL TASK 	 **
;**		the first task to run		 **
;**************************************
;this will be your future shell 
;executing commands, creating and killing
;tasks.
;It can always run so it never leaves the 
;runQ. It will just be the first task
;that creates a few tasks for now
.MACRO create_shell
	ll_head_extract pTCBfreeQ,XL,XH
	;X should have the address to a ll_node
	;containing the address to a free TCB
	ll_get_data_ptr XL,XH,YL,YH
	;Y should have the address of the free
	;TCB for this process. So let's initialize it.
	;Let's initialize the stack
	TCBgetHWstk YL,YH,r16,r17
	out SPL, r16
	out SPH, r17
	
	ldi r16, RUNNING
	TCBsetstatus YL,YH,r16
	ldi r16,7
	TCBsetprio YL,YH,r16
	TCBsetdelay YL,YH, r16

	;since it is the first task,
	;just insert it into pCur Queue
	ll_head_insert pCur, XL,XH
	rjmp shell
.ENDMACRO



;**************************************
;** 	CONFIG TIMER COUNTER 1 		 **
;**		AS THE QUANTUM SLICER		 **
;**************************************
;you will have to add arguments as you
;develop this macro to adjust the clock 
;and the slice size
.MACRO Quantum_config
		clr TmpReg
		out TCCR1A,TmpReg
		ldi TmpReg, (1<<WGM12)|(1<<CS11)|(1<<CS10); CTC/64 
		;ldi TmpReg, (1<<WGM12)|(1<<CS10); no prescaling
		out TCCR1B, TmpReg

		ldi TmpReg, 0x0
		out OCR1AH, ZeroReg		; init OCR1AH & OCR1AL
		ldi TmpReg, 0xF			; initial quantum size 
								; if you use control tasks
								; you can reconfigure this so
								; that a task get only an optimized
								; slice
		out OCR1AL, TmpReg		; so you have to write the High byte first

		ldi TmpReg, (1<<OCIE1A)	; timer 0 overflow flag
		out TIMSK,TmpReg
		clr TmpReg
		out TCNT1H,TmpReg
		out TCNT1L,TmpReg		
.ENDMACRO 
;**************************************


;stretches quantum again after it 
;was shortened down by a blocking 
;semaphore
.MACRO Qua_extend
		ldi TmpReg, (1<<WGM12)|(1<<CS11)|(1<<CS10); CTC/64 
		;ldi TmpReg, (1<<WGM12)|(1<<CS10); no prescaling
		out TCCR1B, TmpReg	
.ENDMACRO 


;***********************
; 	  RESET QUANTUM
;***********************
;turns on round robin 
;after a context switch
;-it also mops up accumulated 
;timer tics, clears the 
;OCF1A flag and reconfigures
;the timer just in case it got 
;messed up by a semaphore  
.MACRO reset_quantum
		push r16
		
		;clear accumulated tics
		clr r16
		out TCNT1H, r16
		out TCNT1L, r16
		;clear the OCF1A flag
		ldi r16, (1<<OCF1A)
		out TIFR, r16
		;enable quantum slicer
		in r16, TIMSK
		ori r16, (1<<OCIE1A)
		out TIMSK, r16
		;reconfigure the timer
		ldi r16, (1<<WGM12)|(1<<CS11)|(1<<CS10); CTC/64 
		out TCCR1B, r16

		pop r16
.ENDMACRO


;**************************************
;**		MKInitListOfPointers 	 	 **
;**		initializes the pointer		 **
;**		to TCB at each node  		 **
;**************************************
;you have to have the list set up first
;and the array of consecutive bocks ready
;arg0 - label of the linked list to init
;arg1 - label of the array of blocks
;arg0 is a pointer
;arg1 is the label of the first block
;(the abs address of) 
.MACRO MKInitListOfPointers
	push ZL
	push ZH
	push YL
	push YH
	push r16

	ll_get_head @0,ZL,ZH
	ldi YL, low(TCBs)
	ldi YH, high(TCBs)
	ldi r16,TASK_MAX

MKinitLOP:
	;set the pointer to the data
	;in the linked list
	ll_set_data_ptr,ZL,ZH,YL,YH	
	adiw ZH:ZL,(ptr_sz+ptr_sz)
	adiw YH:YL,tcb_sz 	;when you deal with
						;mailboxes and 
						;semaphores, the block size will
						;change 

	dec r16
	cpi r16,0
	brne MKinitLOP

	pop r16
	pop YH
	pop YL
	pop ZH
	pop ZL
.ENDMACRO 
;**************************************


;**************************************
;**		save context of the process  **
;**				leaving CPU			 **
;**************************************
;you may be able to do some optimizing
;of the context saving time by 
;organizing your usage of registers 
.MACRO save_context	
	push r0
	in r0,SREG
	push r0
ENTER_CRITICAL_SECTION
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
	ll_get_head pCur,XL,XH
	ll_get_data_ptr XL,XH,YL,YH
	;Y has address of 
	;the TCB to store SP
	in r15, SPL
	in r16, SPH
	TCBsetHWstk YL,YH,r15,r16 ;the SP is stored at the appropriate TCB
.ENDMACRO


;****************************
;		RESTORE CONTEXT
;****************************
.MACRO restore_context
	ll_get_head pCur,XL,XH
	ll_get_data_ptr XL,XH,YL,YH
	TCBgetHWstk YL,YH,r15,r16
	ldi r17,RUNNING
	TCBsetstatus YL,YH,r17
	out SPL, r15
	out SPH, r16
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
	out SREG, r0	;by doing this you are essentially 
					;exiting the criticat section
	pop r0
.ENDMACRO

;***********************
;	  SWITCH CONTEXT
;***********************
;initializes the pCur ptr
;and SP to those of the 
;ask to run 
.MACRO switch_context
	;let's check if there is 
	;a task to switch to first
	ll_get_head pRunQ, XL,XH
	cpi XL, 0
	brne switch_conOK
	cpi XH, 0
	brne switch_conOK
	rjmp context_sw_done
switch_conOK:
	ll_head_extract pCur,XL,XH
	ll_tail_insert pSelectQ,XL,XH
	ll_head_extract pSelectQ, XL,XH
	ll_tail_insert pRunQ,XL,XH
	ll_head_extract pRunQ,XL,XH
	ll_head_insert pCur,XL,XH
context_sw_done:
.ENDMACRO
;***********************


;***********************
;	YIELD FROM TICK
;***********************
;saves the context of the
;task leaving the CPU
;switches the pCur,SP and
;restores the context of
;the oncoming task
.MACRO yield_from_tick
	save_context
	switch_context
	restore_context
.ENDMACRO
;***********************


;***********************
;	YIELD FROM TICK
;	   SEMAPHORES
;***********************
;saves the context of the
;task leaving the CPU
;switches the pCur,SP and
;restores the context of
;the oncoming task
;
;uses the schedule macro 
.MACRO sema_yield_from_tick
	save_context
	schedule
	dispatch
	restore_context
	reset_quantum
.ENDMACRO
;***********************



;***********************
;		SCHEDULE 		
;***********************
;1) checks the status of
;the task leaving the processor
;and tail_inserts it at SelectQ if if
;the task is not runnable. if the 
;task is runable tail_inserts it
;at the RunQ
;
;2) scans the SelectQ for 
;any runnable tasks and 
;tail_inserts them at the RunQ

;RUNNABLE = 0b00000100
;RUNNING  = 0b00000010
;WAITING  = 0b00000001
;DELAYED  = 0b00000000

.MACRO schedule
		ll_head_extract pCur,XL,XH	
		;X points to the node
		;containing the TCB to 
		;examine


		;get the TCB pointer into r16,r17
		ll_get_data_ptr XL,XH,r16,r17
		;check status of the leaving task
		TCBgetstatus r16,r17,r18
		cpi r18, RUNNING	;so just its quantum ran out
		breq sch_run
		;at this point the task has to 
		;be either DELAYED or WAITING
		;because its status was changed
		;from RUNNABLE to RUNNING at schedule
		ll_tail_insert pSelectQ,XL,XH
		rjmp sch_select_new
	sch_run:
		ldi r18, RUNNABLE	
		TCBsetstatus r16,r17,r18	;change status to runnable
		ll_tail_insert pRunQ,XL,XH
	sch_select_new:
		;now just scan the SelectQ for any tasks that
		;changed status to RUNNABLE, and tail_insert
		;them to RunQ
		ll_get_head pSelectQ, XL,XH
		shed_loop:
			;check if you are at the end of SelectQ
			cpi XL,0
			brne shed_selQ_not_empty
			cpi XH,0
			brne shed_selQ_not_empty
			rjmp sc_done
		
		shed_selQ_not_empty:
			ll_get_data_ptr XL,XH,r16,r17
			TCBgetstatus r16,r17,r18
			cpi r18,RUNNABLE
			breq sch_move
			;you have to extract from selectQ
			;and tail_insert at the RunQ
		sch_advance:
			mov r16, XL
			mov r17, XH
			ll_get_next r16,r17, XL,XH
			rjmp shed_loop
		sch_move:
			ll_extract pSelectQ, XL,XH
			ll_tail_insert pRunQ, XL,XH
			rjmp sch_advance 
		sc_done:
.ENDMACRO
;***********************

;***********************
; DO THE CONTEXT SWITCH		
;***********************
;takes the task at the head
;of RunQ and puts is at pCur
;recall that there always is 
;the NULL task (your shell)
;to be runnable
.MACRO dispatch
	;let's check if there is 
	;a task to switch to first
	ll_get_head pRunQ, XL,XH
	cpi XL, 0
	brne disp_switch_conOK
	cpi XH, 0
	brne disp_switch_conOK
	rjmp semcontext_sw_done
disp_switch_conOK:
	ll_head_extract pRunQ,XL,XH
	ll_head_insert pCur,XL,XH
semcontext_sw_done:
.ENDMACRO
;***********************