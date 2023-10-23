;***************************
;** 	CETNRAL TABLE 	  **
;** the actual labels are **
;** in CoreCS3 SRAM layout**
;***************************
.EQU pCur_offset		= 0;Pointer to currently running task's TCB
.EQU pRunQ_offset		= 2;pointer to Queue containing runable tasks
						;the next task to run is at the head 
.EQU pSelectQ_offset 	= 4;pointer to the Queue to select tasks
						;for insertion into the RunQ
.EQU pTCBfreeQ_offset 	= 6;Pointer to unused Task Control Blocks
.EQU pSCB_usedQ_offset	= 8;Pointer to used semaphores
.EQU pSCB_freeQ_offset	=10;Pointer to unused semaphores
.EQU pMCB_usedQ_offset	=12;Pointer to used mailboxes
.EQU pMCB_freeQ_offset	=14;Pointer to unused mailboxes	
.EQU systime_offset 	=15;Timer ticks since last boot 
.EQU idle_time_offset 	=16;CPU idle time 
.EQU ker_version_offset =17;kernel version - ?? 
.EQU ker_running_offset =18;kernel is running flag
.EQU CTBL_sz			=19;SIZE OF THE CENTRAL TABLE 19B		
;**********************************************************
;THIS LAYOUT WILL BE COPIED IN THE SRAM

;***************************
;**  INIT CENTRAL TABLE   **
;***************************
;will initialize all the 
;data members of the CTBL
;The Queues are assumed to 
;be initialized by their own
;member functions. The central
;table init macro is just calling
;them in order to set up the kernel
;data structures and to initialize
;them 
.MACRO CTBL_init_table
	clr r16	;NULL pointer
	
	set_label_ptr pCur, r16,r16
	set_label_ptr pRunQ, r16,r16
	set_label_ptr pSelectQ, r16,r16
	
	;now you are setting up the task
	;control blocks, and putting the 
	;pointers to them into the TCBfreeQ
	;the first node starts at 0x74 - right
	;at the end of the central table
	ll_new pTCBfreeQ, 0x74, TASK_MAX-1, ptr_sz
	CTBL_init_freeQ TCBfreeQ, TCBs, tcb_sz
	TCBinitArray 			;init the TCB array
	TCBpushAllHW ;test it
	
	;now you are setting up the semaphore
	;control blocks, and putting the 
	;pointers to them into the SCBfreeQ
	;the first node starts at 0x88 - right
	;at the end of the TCBfreeQ
	;
	;you are also allocating for more semaphores then you
	;need for this simulation so you can use them in tasks
	ll_new pSCB_freeQ, 0x88, (3*TASK_MAX)-1, ptr_sz
	ACTBL_init_freeQ SCBfreeQ, SCBs, scb_sz, 3*TASK_MAX
	ASCBinitArray 3*TASK_MAX
	clr r16
	set_label_ptr pSCB_usedQ,r16,r16	;so far you haven't used any


	;now you are setting up the Mailbox
	;control blocks, and putting the 
	;pointers to them into the MCBfreeQ
	;the first node starts at 0xC0 - right
	;at the end of the SCBfreeQ
	ll_new pMCB_freeQ, 0xC4, TASK_MAX-1, ptr_sz
	CTBL_init_freeQ MCBfreeQ, MCBs, mcb_sz
	MCBinitArray
	clr r16
	set_label_ptr pMCB_usedQ, r16,r16
	
	TIset_bytei systime, 0
	TIset_bytei idle_time, 0
	TIset_bytei ker_version, 1
	TIset_bytei ker_running, 3
	
.ENDMACRO


;***************************
;**  INIT CENTRAL TABLE   **
;***************************
;will initialize all the 
;data members of the CTBL
;The Queues are assumed to 
;be initialized by their own
;member functions. The central
;table init macro is just calling
;them in order to set up the kernel
;data structures and to initialize
;them 
.MACRO PCCTBL_init_table
	clr r16	;NULL pointer
	
	set_label_ptr pCur, r16,r16
	set_label_ptr pRunQ, r16,r16
	set_label_ptr pSelectQ, r16,r16
	
	;now you are setting up the task
	;control blocks, and putting the 
	;pointers to them into the TCBfreeQ
	;the first node starts at 0x74 - right
	;at the end of the central table
	ll_new pTCBfreeQ, 0x74, TASK_MAX-1, ptr_sz
	CTBL_init_freeQ TCBfreeQ, TCBs, tcb_sz
	TCBinitArray 			;init the TCB array
	TCBpushAllHW ;test it
	
	;now you are setting up the semaphore
	;control blocks, and putting the 
	;pointers to them into the SCBfreeQ
	;the first node starts at 0x88 - right
	;at the end of the TCBfreeQ
	;
	;you are also allocating for more semaphores then you
	;need for this simulation so you can use them in tasks
	ll_new pSCB_freeQ, 0x88, TASK_MAX-1, ptr_sz
	CTBL_init_freeQ SCBfreeQ, SCBs, scb_sz
	SCBinitArray
	clr r16
	set_label_ptr pSCB_usedQ,r16,r16	;so far you haven't used any

	;MCBs are still unused
	clr r16
	set_label_ptr pMCB_freeQ, r16,r16
	set_label_ptr pMCB_usedQ, r16,r16
	
	TIset_bytei systime, 0
	TIset_bytei idle_time, 0
	TIset_bytei ker_version, 1
	TIset_bytei ker_running, 3
	
.ENDMACRO


;***************************
;**  INIT CENTRAL TABLE   **
;***************************
;will initialize all the 
;data members of the CTBL
;The Queues are assumed to 
;be initialized by their own
;member functions. The central
;table init macro is just calling
;them in order to set up the kernel
;data structures and to initialize
;them 
.MACRO CS3_CTBL_init_table
	clr r16	;NULL pointer
	
	set_label_ptr pCur, r16,r16
	set_label_ptr pRunQ, r16,r16
	set_label_ptr pSelectQ, r16,r16
	
	;now you are setting up the task
	;control blocks, and putting the 
	;pointers to them into the TCBfreeQ
	;the first node starts at 0x74 - right
	;at the end of the central table
	ll_new pTCBfreeQ, 0x74, TASK_MAX-1, ptr_sz
	CTBL_init_freeQ TCBfreeQ, TCBs, tcb_sz
	TCBinitArray 			;init the TCB array
	TCBpushAllHW ;test it
	
	set_label_ptr pSCB_freeQ,r16,r16
	set_label_ptr pSCB_usedQ,r16,r16
	set_label_ptr pMCB_freeQ,r16,r16
	set_label_ptr pMCB_usedQ,r16,r16
	
	TIset_bytei systime, 0
	TIset_bytei idle_time, 0
	TIset_bytei ker_version, 1
	TIset_bytei ker_running, 3
	
.ENDMACRO

;*****************************
;	    INIT FREE QUEUE
;*****************************
;initializes free Q pointers to
;desired addresses. It assumes that
;Q has nodes of size 2*ptr_sz, and
;you will have to supply the size of 
;the blocks you want to point to. The
;blocks are assumed to be consecutive.
;You have to have the same number of 
;nodes in the Q as you have blocks
;you want to point to
;
;arg0 is freeQ label
;arg1 is label of the first block
;arg3 is block size
.MACRO CTBL_init_freeQ
	push r17	;zero register
	push ZL		;pointer to TCB
	push ZH
	push YL		;pointer to HWstacks
	push YH
	
	ldi ZL, low(@0)	;free Q
	ldi ZH, high(@0)
	ldi YL, low(@1)	;Blocks
	ldi YH, high(@1)
	
	clr r17
	CTBLinitLoop:
		std Z+lldtoffset,YL
		std Z+lldtoffset+1,YH
		adiw YH:YL,@2			;advance block pointer
		adiw ZH:ZL,ptr_sz+ptr_sz	;advance to next node
		inc r17
		cpi r17, TASK_MAX
		brne CTBLinitLoop
		
	pop YH
	pop YL
	pop ZH
	pop ZL
	pop r17
.ENDMACRO


;*****************************
;	    INIT FREE QUEUEA
;	  WITH LENGTH ARGUMENT
;*****************************
;initializes free Q pointers to
;desired addresses. It assumes that
;Q has nodes of size 2*ptr_sz, and
;you will have to supply the size of 
;the blocks you want to point to. The
;blocks are assumed to be consecutive.
;You have to have the same number of 
;nodes in the Q as you have blocks
;you want to point to
;
;arg0 is freeQ label
;arg1 is label of the first block
;arg2 is block size
;arg3 is the number of pointers to init
;this number is a constant
.MACRO ACTBL_init_freeQ
	push r17	;zero register
	push ZL		;pointer to TCB
	push ZH
	push YL		;pointer to HWstacks
	push YH
	
	ldi ZL, low(@0)	;free Q
	ldi ZH, high(@0)
	ldi YL, low(@1)	;Blocks
	ldi YH, high(@1)
	
	clr r17
	CTBLinitLoop:
		std Z+lldtoffset,YL
		std Z+lldtoffset+1,YH
		adiw YH:YL,@2			;advance block pointer
		adiw ZH:ZL,ptr_sz+ptr_sz	;advance to next node
		inc r17
		cpi r17, @3
		brne CTBLinitLoop
		
	pop YH
	pop YL
	pop ZH
	pop ZL
	pop r17
.ENDMACRO