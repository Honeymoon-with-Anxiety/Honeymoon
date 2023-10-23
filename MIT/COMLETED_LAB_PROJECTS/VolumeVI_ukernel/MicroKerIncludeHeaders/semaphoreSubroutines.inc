
;***************************
;		SEMAPHORE SIGNAL
;***************************
;sem_signal() first examines 
;semaphore’s wait-queue. 
;If there are any tasks waiting on the semaphore, 
;the first one is de-queued and 
;re-scheduling occurs (contingent upon your protocol). 
;If the wait-queue is empty, 
;the semaphore value is simply 
;incremented by one and calling task is resumed.

;since this is a subroutine we 
;need to pass the arguments on the stack
;normally this would be passed on the 
;software stack but here it's just 
;assumed that the user will set
;the address of the SCB in Z register
sem_signal:
push r16
push r17
push r18
ENTER_CRITICAL_SECTION
	ldd r16, Z+scb_pSemQ_offset	;get the head of SemQ
	ldd r17, Z+scb_pSemQ_offset+1

	cpi r16, 0	;check if semQ is empty
	brne sems_semQ_not_empty
	cpi r17, 0
	brne sems_semQ_not_empty
	;so here the SemQ is empty
	;since there are no
	;tasks waiting on this sema, increase count
	;and bail
	ld r18, Z	;increase the count
	inc r18
	st Z,r18
	rjmp sems_done 
sems_semQ_not_empty:
	;r16,r17 points to the TCB of the 
	;task waiting on this semaphore which
	;is currently at the head of this SemQ.
	;Since the task is also at the SelectQ with
	;status waiting, all you have to do is deque
	;it from SemQ and change its status. The scheduler
	;will pick it up next context switch  
	SemQ_head_extract ZL,ZH,r16,r17
	;change the task's status
	ldi r18, RUNNABLE
	TCBsetstatus r16,r17,r18

sems_done:
EXIT_CRITICAL_SECTION
pop r18
pop r17
pop r16
ret
;***************************


;***************************
;		SEMAPHORE WAIT
;***************************
;Semaphores are manipulated with  
;sem_wait() and sem_signal(). 
;sem_wait() first tests the value of semaphore. 
;If the value is positive, 
;it is decremented by one and 
;the calling task is resumed. 
;If the value is zero, 
;the calling task is suspended 
;and it is put to semaphore’s wait 
;queue until some other task sem_signal()s the semaphore.
sem_wait:
ENTER_CRITICAL_SECTION
push r16
push r17
push r18
push r19
	ld r16, Z	;get count
	cpi r16, 1
	brsh semw_pass
	; so you will have to wait
	get_label_ptr pCur, r17,r18
	;address of the node 
	;containing the TCB address in r17,r18
	ll_get_data_ptr r17,r18,r16,r19
	;pointer to the TCB to suspend in r16,r19
	SemQ_tail_insert ZL,ZH,r16,r19
	ldi r18, WAITING
	TCBsetstatus r16,r19,r18;suspend the task
	;since you will be waiting you can suspend
	;this task - i.e. force context switch.
	;Here it will be done simply by 
	;shortening the quantum slice
	;to force the round robin to switch
		ldi r18, (1<<WGM12)|(1<<CS10); no prescaling
		out TCCR1B, r18
	;the worst case is when the counter is zero
	;then round robin still has to count to TOP
	;which is F in our case. Pop is 2 clock cycles
	;each so you have 2x4=8. sei is 1, ret is 4 to 5
	;clock cycles. Total: 8+1+4=13, so insert 2 nops
	nop nop
	rjmp semw_done
semw_pass:
	dec r16
	st Z,r16
semw_done:
	pop r19
	pop r18
	pop r17
	pop r16
EXIT_CRITICAL_SECTION
ret

