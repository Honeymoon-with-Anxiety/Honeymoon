;SRAM LAYOUT OF OUR MICROKERNEL
;-NO MEMORY MANAGER...
.DSEG
.org 0x60	
;****************************
;	CENTRAL TABLE STRUCTURE
;		-SRAM LAYOUT-
;****************************
	pCur: .BYTE ptr_sz
	pRunQ: .BYTE ptr_sz
	pSelectQ: .BYTE ptr_sz
	pTCBfreeQ: .BYTE ptr_sz

	pSCB_usedQ: .BYTE ptr_sz
	pSCB_freeQ: .BYTE ptr_sz

	pMCB_usedQ: .BYTE ptr_sz
	pMCB_freeQ: .BYTE ptr_sz

	systime: .BYTE 1
	idle_time: .BYTE 1
	ker_version: .BYTE 1
	ker_running: .BYTE 1
;****************************


;***************************************
;      ALLOCATE THE TCB FREE QUEUE
;***************************************
TCBfreeQ: .BYTE TASK_MAX*(ptr_sz+ptr_sz)
;***************************************

;***************************************
;      ALLOCATE THE SCB FREE QUEUE
;***************************************
;you could easily have a taks having more
;than one semaphore.
SCBfreeQ: .BYTE 3*TASK_MAX*(ptr_sz+ptr_sz)
;***************************************

;***************************************
;      ALLOCATE THE MCB FREE QUEUE
;***************************************
;you could easily have a taks having more
;than one mailbox.
MCBfreeQ: .BYTE TASK_MAX*(ptr_sz+ptr_sz)
;***************************************

;********************************
;ALLOCATE THE TASK CONTROL BLOCKS
;********************************	
TCBs: .BYTE TASK_MAX*tcb_sz
;********************************

;********************************
;ALLOCATE SEMAPHORE CONTROL BLOCKS
;********************************	
SCBs: .BYTE  3*TASK_MAX*SCB_sz 
;each mailbox has two semaphores
;********************************

;********************************
;ALLOCATE MAILBOX CONTROL BLOCKS
;********************************
MCBs: .BYTE TASK_MAX*MCB_sz
;********************************


;**************************************
;		  ALLOCATE THE STACKS
;**************************************
HWstacks: .BYTE TASK_MAX*STACK_SIZE_MAX
SWstacks: .BYTE TASK_MAX*STACK_SIZE_MAX
;**************************************

.CSEG; continue with code going into flash

.exit

;this defines the stacks 
;and queues i.e. the SRAM part 
;of the kernel
