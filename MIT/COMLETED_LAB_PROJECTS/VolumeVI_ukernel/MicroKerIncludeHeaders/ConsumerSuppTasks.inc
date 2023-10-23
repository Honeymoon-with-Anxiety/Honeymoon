;********************
;**    SUPPLIER    **
;** 	W/MUTEX	   **
;********************
SupplierMutex:
.DSEG
	;pMutex, pEmpty, pFull are pointers to semaphores
	pMutex: .BYTE ptr_sz			;mutex for controlling the critical section initially 1
	pEmpty: .BYTE ptr_sz			;counts empty buffer slots - initially 8
	pFull:	.BYTE ptr_sz			;counts full slots - initially 0
	Basket : .BYTE CircularBuffer_sz+10	;allocate the buffer
.CSEG
	ldi r18,1
	sem_create r16,r17,r18				;creating the mutex (r17,r18 are return registers
										;of the SCB corresponding to this mutex
	set_label_ptr pMutex,r16,r17		;storing the address of the SCB in its pointer

	ldi r18,2
	sem_create r16,r17,r18				;creating the Empty semaphore
	set_label_ptr pEmpty,r16,r17
	
	ldi r18,0
	sem_create r16,r17,r18				;creating the Full semaphore
	set_label_ptr pFull,r16,r17		

	;now initialize the basket for the muffins
	TIinit_circular_buffer Basket, 8

	clr r15		;r15 holds the generated item
	SuppMutexLoop:
		inc r15				;produce the item	
		
		get_label_ptr pEmpty, ZL,ZH
		rcall sem_wait		;wait on Empty

		get_label_ptr pMutex, ZL,ZH
		rcall sem_wait		;wait on Mutex

		TIwrite_circular_buffer Basket, r15 ;put the item in the basket

		rcall sem_signal	;signal Mutex (leaving the critical section)

		get_label_ptr pFull, ZL,ZH
		rcall sem_signal	;signal Full
	
	rjmp SuppMutexLoop
	nop
	nop



;********************
;**    CONSUMER    **
;** 	W/MUTEX	   **
;********************
ConsumerMutex:
	
	clr r15
	ConsMutexLoop:

	get_label_ptr pFull, ZL,ZH
	rcall sem_wait						;wait on Full (decrement Full)

	get_label_ptr pMutex, ZL,ZH
	rcall sem_wait						;enter the critical section
	
	TIread_circular_buffer Basket, r15	;remove the item

	rcall sem_signal					;leave the critical section
	
	get_label_ptr pEmpty, ZL,ZH
	rcall sem_signal					;increment the count of empty slots
	
	rjmp ConsMutexLoop
	nop
	nop
