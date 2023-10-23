;MailBoxControlBlock include file
;***************************
;	MAILBOX CONTROL BLOCK
;***************************
.EQU MCB_send_sema_offset 	= 0	;offset of the send sema
.EQU MCB_recv_sema_offset 	= 2	;offset of the receive sema
.EQU MCB_message_ptr_offset = 4	;offset of the message pointer
.EQU MCB_sz 				= 6 ;size of the mailbox

;***********************
;    MCB INIT ARRAY
;***********************
;Only takes the semaphores
;from the semaphore free Q
;and initializes pointers to
;two of them in each MCB
.MACRO MCBInitArray
push r15
push r16
push r17
push r18
push r19
push r20
		ldi r20,TASK_MAX
		mov r15,r20
		clr r20
		
		get_label_ptr MCBs, XL,XH
		ldi XL,low(MCBs)
		ldi XH,high(MCBs)
	mcb_inArrayLoop:
		
		ll_head_extract pSCB_freeQ, r16,r17	;get a new scb node
		ll_head_insert pSCB_usedQ, r16,r17 
		ll_get_data_ptr r16,r17,r18,r19		;get the scb pointer 
		MCB_set_send_sema XL,XH,r18,r19

		ll_head_extract pSCB_freeQ, r16,r17	;get a new scb node 
		ll_head_insert pSCB_usedQ, r16,r17
		ll_get_data_ptr r16,r17,r18,r19		;get the scb pointer 
		MCB_set_recv_sema XL,XH,r18,r19
		
		clr r18
		MCB_set_msg_ptr	XL,XH,r18,r18

		adiw XL:XH,mcb_sz
		inc r20
		cpse r20, r15
		rjmp mcb_inArrayLoop
pop r20
pop r19
pop r18
pop r17
pop r16
pop r15	
.ENDMACRO

;***********************
;	CREATE MAILBOX
;***********************
;creates message box and 
;returns the address of MCB
;created in arg0 and arg1
;arg0 - MCB created Low
;arg1 - MCB created High
.MACRO mbox_create
push YL
push YH
push r16
push r17
push r18
ENTER_CRITICAL_SECTION
	ll_head_extract pMCB_freeQ, XL,XH
	ll_head_insert pMCB_usedQ,XL,XH
	
	movw YL:YH,XL:XH
	ll_get_data_ptr YL,YH,r16,r17
	MCB_get_send_sema r16,r17, YL,YH
	ldi r18,1
	std Y+scb_count_offset, r18

	MCB_get_recv_sema r16,r17, YL,YH
	clr r18
	std Y+scb_count_offset, r18
	mov @0,r16
	mov @1,r17
EXIT_CRITICAL_SECTION
pop r18
pop r17
pop r16
pop YH
pop YL
.ENDMACRO


;***********************
;	SEND TO MAILBOX
;***********************
;send a message to the 
;mailbox - if there is 
;already a message in it,
;the calling task is suspended
;arg0 - &mboxL
;arg1 - &mboxH
;arg2 - &msgL
;arg3 - &msgH
.MACRO mbox_send
push r16
push r17
push ZL
push ZH
	MCB_get_send_sema XL,XH,r16,r17
	movw ZL:ZH,r16:r17
	rcall sem_wait 
		MCB_set_msg_ptr XL,XH,@2,@3;
	MCB_get_recv_sema XL,XH,r16,r17
	movw ZL:ZH,r16:r17
	rcall sem_signal 
pop ZH
pop ZL
pop r17
pop r16
.ENDMACRO


;***********************
;  RECEIVE FROM MAILBOX
;***********************
;receive a message from the 
;mailbox - if there is 
;already a message in it,
;the calling task is suspended
;arg0 - &mboxL
;arg1 - &mboxH
;arg2 - &msgL
;arg3 - &msgH
.MACRO mbox_recv
push r16
push r17
push ZL
push ZH
	MCB_get_recv_sema @0,@1,r16,r17
	movw ZL:ZH,r16:r17
	rcall sem_wait 
		MCB_get_msg_ptr @0,@1,@2,@3;
	MCB_get_send_sema @0,@1,r16,r17
	movw ZL:ZH,r16:r17
	rcall sem_signal
pop ZH
pop ZL 
pop r17
pop r16
.ENDMACRO 

;***********************
;	GET SEND SEMAPHORE
;***********************
;arg0 address LOW of the MCB
;arg1 address HIGH of the MCB
;arg2 sema return address LOW
;arg3 sema return address HIGH  
.MACRO MCB_get_send_sema; 
	mov ZL, @0
	mov ZH, @1
	ldd @2, Z+MCB_send_sema_offset
	ldd @3, Z+MCB_send_sema_offset+1
.ENDMACRO

;***********************
;	GET RECV SEMAPHORE
;***********************
;arg0 address LOW of the MCB
;arg1 address HIGH of the MCB
;arg2 sema return address LOW
;arg3 sema return address HIGH  
.MACRO MCB_get_recv_sema; 
	mov ZL, @0
	mov ZH, @1
	ldd @2, Z+MCB_recv_sema_offset
	ldd @3, Z+MCB_recv_sema_offset+1
.ENDMACRO

;***********************
;	GET MSG PTR OFFSET
;***********************
;arg0 address LOW of the MCB
;arg1 address HIGH of the MCB
;arg2 msg return address LOW
;arg3 msg return address HIGH  
.MACRO MCB_get_msg_ptr; 
	mov ZL, @0
	mov ZH, @1
	ldd @2, Z+MCB_message_ptr_offset
	ldd @3, Z+MCB_message_ptr_offset+1
.ENDMACRO

;***********************
;	SET SEND SEMAPHORE
;***********************
;arg0 address LOW of the MCB
;arg1 address HIGH of the MCB
;arg2 sema address LOW
;arg3 sema address HIGH  
.MACRO MCB_set_send_sema; 
	mov ZL, @0
	mov ZH, @1
	std Z+MCB_send_sema_offset,   @2
	std Z+MCB_send_sema_offset+1, @3
.ENDMACRO

;***********************
;	SET RECV SEMAPHORE
;***********************
;arg0 address LOW of the MCB
;arg1 address HIGH of the MCB
;arg2 sema address LOW
;arg3 sema address HIGH  
.MACRO MCB_set_recv_sema; 
	mov ZL, @0
	mov ZH, @1
	std Z+MCB_recv_sema_offset,   @2
	std Z+MCB_recv_sema_offset+1, @3
.ENDMACRO

;***********************
;	SET MSG PTR OFFSET
;***********************
;arg0 address LOW of the MCB
;arg1 address HIGH of the MCB
;arg2 msg address LOW
;arg3 msg address HIGH  
.MACRO MCB_set_msg_ptr; 
	mov ZL, @0
	mov ZH, @1
	std Z+MCB_message_ptr_offset,   @2
	std Z+MCB_message_ptr_offset+1, @3
.ENDMACRO