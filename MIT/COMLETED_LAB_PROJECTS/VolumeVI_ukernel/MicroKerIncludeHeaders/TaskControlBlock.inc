.CSEG
;******************************
;*****    TCB DECLARATION *****
;******************************
;	pointers are two bytes
;****************************** 
;If you want to use the follwing 
;code, make sure that your TCB 
;blocks are in an array called
;'TCBs'. The arrays length is
;TASK_MAX


;maximum number of tasks
.EQU TASK_MAX			= 5	

;status definitions
.EQU RUNNABLE = 0b00000100
.EQU RUNNING  = 0b00000010
.EQU WAITING  = 0b00000001
.EQU DELAYED  = 0b00000000


.EQU tcb_pHWstk_offset	= 0 ;1 HW stack TOP pointer
.EQU tcb_pSWstk_offset	= 2	;2 SW stack TOP pointer
.EQU tcb_pSemQ_offset 	= 4	;3 semaphore Q pointer
.EQU tcb_stat_offset	= 6	;4 status of this process
.EQU tcb_prio_offset	= 7	;5 priority of this process
.EQU tcb_delay_offset	= 8	;6 clock ticks to sleep
.EQU tcb_sz 			= 9	;TASK CONTROL BLOCK SIZE is 9B  			

;**********************************
;** macros operating on the TCB  **
;**********************************

;initializes array of TASK_MAX TCB's 
;given the address label in arg0
;where the first TCB is to be located.
;
;It has to be given the address of 
;the first HW stack in its array of 
;HW stacks and the address
;of the first SW stack in its array of 
;SW stacks.
;
;when you do your SRAM layout, you have 
;define the label for the array
.MACRO TCBinitArray
	push r16	;loop counter
	push r17	;zero register
	push r18	;constants register
	push ZL		;pointer to TCB
	push ZH
	push YL		;pointer to HWstacks
	push YH
	push XL		;pointer to SWstacks
	push XH
	ldi r16, TASK_MAX
	ldi ZL, low(TCBs)
	ldi ZH, high(TCBs)	
	ldi YL, low(HWstacks)
	ldi YH, high(HWstacks)
	ldi XL, low(SWstacks)
	ldi XH, high(SWstacks)
	adiw YH:YL, STACK_SIZE_MAX	;init to the top
	adiw XL:XH, STACK_SIZE_MAX	;you will push towards
								;lower address
	clr r17

	TCBinitLoop:
		TCBsetHWstk ZL,ZH,YL,YH
		TCBsetSWstk ZL,ZH,XL,XH
		TCBsetSemQ ZL,ZH, r17,r17	;set it to NULL
		ldi r18, RUNNABLE
		TCBsetstatus	ZL,ZH, r18
		ldi r18, 32
		TCBsetPrio ZL,ZH, r18
		clr r18
		TCBsetDelay ZL,ZH,r18
		adiw ZH:ZL,tcb_sz			;advance tcb pointer
		adiw YH:YL,STACK_SIZE_MAX	;advance to next HW stack
		adiw XH:XL,STACK_SIZE_MAX	;advance to next SW stack
		
		dec r16
		cpi r16, 0
		brne TCBinitLoop
		
	pop XH
	pop XL
	pop YH
	pop YL
	pop ZH
	pop ZL
	pop r18
	pop r17
	pop r16
	
.ENDMACRO

;************************************
;			TCBpushAllHW
;************************************
;pushes all stacks to check proper 
;fuction assuming all TCB's are in the
;'TCBs' array and all pointers are initialized 
;IT DOES NOT SAVE THE TOP OF THE STACK 
;AT ITS TCB!!!  
.MACRO TCBpushAllHW
	push XL
	push XH
	push r16
	push r17
	push r18
	push r19

	ldi XL,low(TCBs)	;load the first stk
	ldi XH,high(TCBs)
	ldi r19, TASK_MAX	

TCBpushAll1:
	
	TCBgetHWstk XL,XH,r16, r17	;load stk TOP at X
	out SPL, r16
	out SPH, r17
	ldi r18, STACK_SIZE_MAX

TCBpushAll2:
	push r18
	dec r18
	cpi r18, 0
	brne TCBpushAll2
	
	adiw XH:XL, tcb_sz	;move to the next TCB
	dec r19				;decrease the tcb counter
	cpi r19, 0
	brne TCBpushAll1

	pop r19
	pop r18
	pop r17
	pop r16
	pop XH
	pop XL
.ENDMACRO




;************************************
;			TCBpopAllHW
;************************************
;pops all stacks to check proper 
;fuction assuming all TCB's are in the
;'TCBs' array and all pointers are initialized 
;IT DOES NOT SAVE THE TOP OF THE STACK 
;AT ITS TCB!!! 
.MACRO TCBpopAllHW
	push XL
	push XH
	push r16
	push r17
	push r18
	push r19

	ldi XL,low(TCBs)	;load the first stk
	ldi XH,high(TCBs)
	ldi r19, TASK_MAX	

TCBpopAll1:
	
	TCBgetHWstk XL,XH,r16, r17	;load stk TOP at X
	out SPL, r16
	out SPH, r17
	ldi r18, STACK_SIZE_MAX

TCBpopAll2:
	pop r18
	dec r18
	cpi r18, 0
	brne TCBpopAll2
	
	adiw XH:XL, tcb_sz	;move to the next TCB
	dec r19				;decrease the tcb counter
	cpi r19, 0
	brne TCBpopAll1

	pop r19
	pop r18
	pop r17
	pop r16
	pop XH
	pop XL
.ENDMACRO

;************************************
;			TCBsetHWstk
;************************************
; sets the pointer to the Task's HW stack. arg0,arg1 (L,H)
; is the address of this TCB, arg2,arg3 (L,H) is the returned 
; addresses of the stack
.MACRO TCBsetHWstk ; &TCBL,&TCBH, &HWL, &HWH
	mov ZL, @0			 
	mov ZH, @1			;Z has address of this TCB
	std Z+tcb_pHWstk_offset, @2
	std Z+tcb_pHWstk_offset+1,@3 
.ENDMACRO 

;get the pointer to the HWstack
; gets the pointer to the Task's HW stack. arg0,arg1 (L,H)
;is the address of this TCB, arg2,arg3 (L,H) is the address 
;of the stack returned 
.MACRO TCBgetHWstk	; &TCBL, &TCBH, &HWL, &HWH    
	mov ZL, @0			 
	mov ZH, @1			;Z has address of this TCB
	ldd @2, Z+tcb_pHWstk_offset	;load low
	adiw ZH:ZL,1
	ldd @3, Z+tcb_pHWstk_offset ;load high
.ENDMACRO 


.MACRO TCBgetSWstk	; &TCBL, &TCBH, &SWL, &SWH    
	mov ZL, @0			 
	mov ZH, @1			;Z has address of this TCB
	ldd @2, Z+tcb_pSWstk_offset	;load low
	adiw ZH:ZL,1
	ldd @3, Z+tcb_pSWstk_offset ;load high
.ENDMACRO 

.MACRO TCBsetSWstk ; TCBL,TCBH,HWL,HWH
	mov ZL, @0			 
	mov ZH, @1			;Z has address of this TCB
	std Z+tcb_pSWstk_offset, @2
	std Z+tcb_pSWstk_offset+1,@3 
.ENDMACRO


.MACRO TCBgetstatus	; &TCBL, &TCBH, regstatus
;push ZL
;push ZH        
	mov ZL, @0			 
	mov ZH, @1			;Z has address of this TCB
	ldd @2, Z+tcb_stat_offset
;pop ZL
;pop ZH
.ENDMACRO 

.MACRO TCBsetstatus	; &TCBL, &TCBH, regstatus  
;push ZL
;push ZH  
	mov ZL, @0			 
	mov ZH, @1			;Z has address of this TCB
	std Z+tcb_stat_offset, @2
;pop ZL
;pop ZH
.ENDMACRO 


.MACRO TCBgetprio	; &TCBL, &TCBH, prioreg    
	mov ZL, @0			 
	mov ZH, @1			;Z has address of this TCB
	ldd @2, Z+tcb_prio_offset	
.ENDMACRO 

.MACRO TCBsetprio	; &TCBL, &TCBH, regprio    
	mov ZL, @0			 
	mov ZH, @1			;Z has address of this TCB
	std Z+tcb_prio_offset, @2 
.ENDMACRO 

.MACRO TCBgetdelay	; &TCBL, &TCBH, delayreg    
	mov ZL, @0			 
	mov ZH, @1			;Z has address of this TCB
	ldd @2, Z+tcb_delay_offset	
.ENDMACRO 

.MACRO TCBsetdelay	; &TCBL, &TCBH, regdelay    
	mov ZL, @0			 
	mov ZH, @1			;Z has address of this TCB
	std Z+tcb_delay_offset, @2
.ENDMACRO 

.MACRO TCBgetSemQ	; &TCBL, &TCBH, &SEMQL, &SEMQH    
	mov ZL, @0			 
	mov ZH, @1			;Z has address of this TCB
	ldd @2, Z+tcb_pSemQ_offset	;load low
	adiw ZH:ZL,1
	ldd @3, Z+tcb_pSemQ_offset ;load high
.ENDMACRO 


.MACRO TCBsetSemQ ; TCBL,TCBH,semQL,semQH
	mov ZL, @0			 
	mov ZH, @1			;Z has address of this TCB
	std Z+tcb_pSemQ_offset, @2
	std Z+tcb_pSemQ_offset+1,@3 
.ENDMACRO 
;*********************************************************
;******************* END TCB DECLARATION ***************** 
;*********************************************************

.CSEG
.EXIT

;you will also need to search the list for max prio 