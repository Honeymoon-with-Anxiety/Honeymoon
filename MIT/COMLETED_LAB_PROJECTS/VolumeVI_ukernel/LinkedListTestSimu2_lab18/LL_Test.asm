
;*******************************
;		LINKED LIST TEST
;*******************************
;	One of the important data
;	structures used in our 
;	version of microkernel
;*******************************

.NOLIST
.include "m16def.inc"
.include "..\DkerHeaders\LLV2.inc"
.LIST

;** Hard coded SRAM layout for the Linked List
.DSEG
.org $60
	run_q: .BYTE pllist		; 	future RUN QUEUE
	used_q:.BYTE pllist		;	future USED TCB QUEUE
	pCur:.BYTE pllist		; 	future pointer 
							;	to the currently running
							; 	task
.CSEG	; resume flash section again

Main:
;** ll_new arguments: 
;** 1) first node at 0x0074, 
;** 2) 3 nodes total, 
;** 3) node data size 6 bytes
	ll_new run_q, 0x0074,3,6; 
	ll_new used_q, 0x00A0,3,6 
	ll_new pCur, 0x0000, 0,6	; set pCur to NULL

;** this loop will only test that we are getting
;**	a nice task flow through the pCur pointer
;** The processes flow as follows:
;**		-from pCur to the tail of usedQ
;**		-from the head of usedQ to the
;**		 tail of runQ
;**		-from the head of runQ to pCur
loop001:
	ll_head_extract pCur, XL, XH
	ll_tail_insert used_q, XL, XH	;tail insert of pCur
	ll_head_extract used_q, XL, XH
	ll_tail_insert run_q, XL, XH
	ll_head_extract run_q, XL,XH
	ll_head_insert pCur, XL, XH
	rjmp loop001

	;*********************************init freeq to some values
rjmp Main	

