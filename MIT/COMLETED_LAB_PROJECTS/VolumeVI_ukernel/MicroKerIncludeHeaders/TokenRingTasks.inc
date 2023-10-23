;embryonic token ring simulation file


;**************************
;	  TOKEN RING TASK 1
;**************************
;task creating the message 
;and sending the message to 
;token ring task TKR_task2
TKR_TASK1:

	ldi YL,low(msg)
	ldi YH,high(msg)
	movw r20:r21,YL:YH

	ldi r16,'h'
	st Y+,r16
	ldi r16,'e'
	st Y+,r16
	ldi r16,'l'
	st Y+,r16
	ldi r16,'l'
	st Y+,r16
	ldi r16,'o'	
	st Y+,r16

	;send the message the first time around
	get_label_ptr pMbox2, XL, XH
	mbox_send XL,XH, r20, r21
		
	tkr1_loop:
		;receive the message from TKR3
		get_label_ptr pMbox1, XL,XH
		mbox_recv XL,XH,r20,r21
		;send the message to the 
		;task immediatelly after 
		;this one
		get_label_ptr pMbox2, XL,XH
		mbox_send XL,XH,r20,r21
		;clean the mailbox to receive
		;the message pointer next time
		;around
		get_label_ptr pMbox1, XL,XH
		MCB_set_msg_ptr XL,XH,ZeroReg,ZeroReg
	rjmp tkr1_loop
	nop
	nop

;**************************
;	  TOKEN RING TASK 2
;**************************
;sending the message to 
;token ring task TKR_task3
TKR_TASK2:
		
	tkr2_loop:
		;receive to your own mailbox
		;you will block when your 
		;mailbox is empty
		get_label_ptr pMbox2,XL,XH
		mbox_recv XL,XH,r20,r21
		;send to the next task's mailbox
		get_label_ptr pMbox3,XL,XH
		mbox_send XL,XH,r20,r21
		;clean the mailbox to receive
		;the message pointer next time
		;around
		get_label_ptr pMbox2, XL,XH
		MCB_set_msg_ptr XL,XH,ZeroReg,ZeroReg
	rjmp tkr2_loop
	nop
	nop





;*********************************
;     TASK 3 OF THE TOKEN RING
;*********************************
TKR_TASK3:
		
	tkr3_loop:
		;receive to your own mailbox
		;you will block when your 
		;mailbox is empty
		get_label_ptr pMbox3,XL,XH
		;clean the mailbox
		;MCB_set_msg_ptr XL,XH,ZeroReg,ZeroReg
		mbox_recv XL,XH,r20,r21
		;send to the next task's mailbox
		get_label_ptr pMbox1, XL,XH
		mbox_send XL,XH,r20,r21
		;clean the mailbox to receive
		;the message pointer next time
		;around
		get_label_ptr pMbox3, XL,XH
		MCB_set_msg_ptr XL,XH,ZeroReg,ZeroReg
	rjmp tkr3_loop
	nop
	nop