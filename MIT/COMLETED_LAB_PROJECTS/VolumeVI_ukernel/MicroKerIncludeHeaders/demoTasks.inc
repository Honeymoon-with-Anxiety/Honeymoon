;********************
;**     TASK A     **
;********************
TaskA:
	ldi r17,1
	and r17, r18
	cpi r17,0
	breq even_A
	ldi r16, 0xA
	rjmp ExecA

  even_A:
  	ldi r16, 0xAA

  ExecA:
  	ldi r17, 8
	loop_even_A:
	push r16
	dec r17
	cpi r17,0
	brne loop_even_A

	ldi r17, 8
	loop_odd_A:
	pop r16
	dec r17
	cpi r17,0
	brne loop_odd_A
	inc r18
	rjmp TaskA
	



;********************
;**     TASK B     **
;********************
TaskB:
	ldi r17,1
	and r17, r18
	cpi r17,0
	breq even_B
	ldi r16, 0xB
	rjmp ExecB

  even_B:
  	ldi r16, 0xBB

  ExecB:
  	ldi r17, 8	;pushing eight values
	loop_even_B:
	push r16
	dec r17
	cpi r17,0
	brne loop_even_B

	ldi r17, 8
	loop_odd_B:
	pop r16
	dec r17
	cpi r17,0
	brne loop_odd_B
	inc r18
	rjmp TaskB

	
;********************
;**     TASK C     **
;********************
TaskC:
	ldi r17,1
	and r17, r18
	cpi r17,0
	breq even_C
	ldi r16, 0xC
	rjmp ExecC

  even_C:
  	ldi r16, 0xCC

  ExecC:
  	ldi r17, 8	;pushing eight values
	loop_even_C:
	push r16
	dec r17
	cpi r17,0
	brne loop_even_C

	ldi r17, 8
	loop_odd_C:
	pop r16
	dec r17
	cpi r17,0
	brne loop_odd_C
	inc r18
	rjmp TaskC
	

;********************
;**     TASK D     **
;********************
TaskD:
	ldi r17,1
	and r17, r18
	cpi r17,0
	breq even_D
	ldi r16, 0xD
	rjmp ExecD

  even_D:
  	ldi r16, 0xDD

  ExecD:
  	ldi r17, 8	;pushing eight values
	loop_even_D:
	push r16
	dec r17
	cpi r17,0
	brne loop_even_D

	ldi r17, 8
	loop_odd_D:
	pop r16
	dec r17
	cpi r17,0
	brne loop_odd_D
	inc r18
	rjmp TaskD



;********************
;**    PRODUCER A  **
;********************
;createst the semaphore
ProdTaskA:
.DSEG
	pSema01: .BYTE ptr_sz	;pointer to the semaphore
.CSEG
	ldi r18,1
	sem_create r16,r17,r18	;creating a mutex
	set_label_ptr pSema01,r16,r17	;storing the address of the SCB

;now you can use the semaphore
	
	mov ZL, r16
	mov ZH, r17
	rcall sem_wait 
	PTA01:
	rjmp PTA01


;********************
;**    PRODUCER B  **
;********************
;uses the semaphore
ProdTaskB:
	get_label_ptr pSema01, ZL,ZH
	rcall sem_wait 
	
	PTB01:
	rjmp PTB01

;********************
;**    PRODUCER C  **
;********************
;uses the semaphore
ProdTaskC:
	get_label_ptr pSema01, ZL,ZH
	rcall sem_wait 
	
	PTC01:
	rjmp PTC01

;********************
;**    PRODUCER D  **
;********************
;uses the semaphore
ProdTaskD:
	get_label_ptr pSema01, ZL,ZH
	rcall sem_signal 
	
	PTD01:
	nop
	nop
	rjmp PTD01
	nop
	nop

