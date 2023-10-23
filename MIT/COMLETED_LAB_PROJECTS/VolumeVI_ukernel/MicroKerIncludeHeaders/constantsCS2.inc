.CSEG

.EQU SEM_MAX  = 12
.EQU TASK_MAX = 6
.EQU MBOX_MAX = 5
.EQU HSTK_SIZE  = 50
.EQU DSTK_SIZE  = 50


.EQU TCB_size = 5		;size in bytes of this block
.EQU SP_offset= 0		;HW stack offset from the start of the block
.EQU FIRST_Time_offset=2	;status is: RUNNING,RUNNABLE,DELAYED,or WAITING
.EQU PRIO_offset=3		;priority of the task
.EQU DELAY_offset=4		;number of ticks to keep the task sleeping
.EQU pTCB_size=2		;size of the pointer to a TCB
.EQU STACK_SIZE_MAX=50
 





;*********************************************************
;********************* SCB DECLARATION *******************
;*********************************************************
.EQU scb_count		= 1 ;semaphore value
.EQU scb_pTCB		= 2 ;sema Q, tasks waiting on this Sema  
.EQU scb_pSCB		= 2 ;ptr to the next semaphore (assume LL) 
.EQU scb_sz			= scb_count+scb_pTCB+scb_pSCB 
.EQU scb_cooffset	= 0 ;offsets of count
.EQU scb_pToffset	= 1	;start of the TCB struct
.EQU scb_pSoffset	= 3 ;
;*********************************************************
;******************* END SCB DECLARATION ***************** 
;*********************************************************



;*********************************************************
;********************* MCB DECLARATION *******************
;*********************************************************
.EQU mcb_pSendSem	= 2 ;Semaphore for sending to this mailbox
.EQU mcb_pRecvSem	= 2 ;Semaphore for receiving to this mailbox
.EQU mcb_pMsg		= 2 ;message pointer
.EQU mcb_pNext		= 2 ;pointer to the next mailbox
.EQU mcb_sz = mcb_pSendSem+mcb_pRecvSem+mcb_pMsg+mcb_pNext
.EQU mcb_Soffset 	= 0 ;offset of the send semaphore
.EQU mcb_Roffset	= 2 ;offset of the recieve sema
.EQU mcb_Moffset	= 4 ;offset of the message
.EQU mcb_Noffset	= 6 ;offset of the next mailbox
;*********************************************************
;****************** END MCB DECLARATION ******************
;*********************************************************
 


;*********************************************************
;**************** CENTRAL TABLE DECLARATION **************
;*********************************************************
.EQU ctbl_systime  	= 1
.EQU ctbl_idlecntr 	= 1
.EQU ctbl_TCBused	= 2	;pointer to used TCBs
.EQU ctbl_TCBfree	= 2	;pointer to unused TCBs
.EQU ctbl_TCBcurr	= 2	;pointer to the block of currently running Task
.EQU ctbl_TCBrunq	= 2	;pointer to the highest priority runable task
.EQU ctbl_SCBused	= 2 ;pointer to used semaphores
.EQU ctbl_SCBfree	= 2	;pointer to unused semaphores 
.EQU ctbl_MCBused	= 2	;pointer to used mailboxes
.EQU ctbl_MCBfree	= 2 ;pointer to unused mailboxes
.EQU ctbl_sz        = 18;size of the central table
.EQU ctbl_stmoffset	  =  0; base offsets from the start of the 	
.EQU ctbl_idloffset	  =  1; central table
.EQU ctbl_Tusedoffset =  2;
.EQU ctbl_Tfreeoffset =  4;
.EQU ctbl_Tcuroffset  =  6;
.EQU ctbl_Trunqoffset =  8;	
.EQU ctbl_Susedoffset = 10;
.EQU ctbl_Sfreeoffset = 12;
.EQU ctbl_Musedoffset = 14;
.EQU ctbl_Mfreeoffset = 16;
;*********************************************************
;************* END CENTRAL TABLE DECLARATION *************
;*********************************************************







.CSEG

.exit