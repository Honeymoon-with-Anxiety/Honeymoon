;************************************************************
;************************ linked list ***********************
;************************************************************
;	implements the linked list with a node having two parts:
;	data and next. The data part has a variable size and 
;	the actual size will be provided as an argument to 
;	the new function. The next size contains the pointer 
;	to the next node. The first node is called the head
;	the last node has the next address zeroed out
.CSEG
.EQU 	pllist		= 2 	;size of the linked list pointer
;********* llnode
.EQU	llnext		= 2		;size of address - two bytes
.EQU	llnode_sz	= 2		;size of the linked list node
							;excluding the data node
.EQU	llnxtoffset	= 0		;next node offset
.EQU	lldtoffset	= 2		;data offset


;*********************************************************
;********************* initialize the linked list to have 
;head at label arg0, blocks starting at address arg1
;arg2 elements, with the size of data node arg3, 
.MACRO ll_new ; headptrlabel, absAddresFirstNode, numElements,sizeDataNode
	push r17

	ldi ZL, low(@1)
	sts @0, ZL	;store the address of the first node
	ldi ZH, high(@1) 
	sts @0+1, ZH;stored the address of the first node
	ldi r17,@2				;load the number of els
	cpi ZL,0	;check if address is zero, done if yes
	brne llnewcont
	cpi ZH,0
	breq llnewdone;first node the addres 0! done!
   llnewcont:
	mov YL, ZL
	mov YH, ZH
  llinitloop:
  	mov ZL, YL
	mov ZH, YH	
	adiw YH:YL, llnext+@3	;Y has the address of  the 
							;next node assuming 
							;all nodes have the same size
    st Z+,YL
	st Z,YH 
	
	dec r17
	cpi r17, 0
	brne llinitloop
	st Y+, r17
	st Y, r17	;end of list to zero
  llnewdone:

  pop r17
.ENDMACRO


;******* get head *********
;loads the address of the 
;linked list head label (arg0)
;into address register Low (arg1)
;and High (arg2) 
.MACRO ll_get_head ;listname, addressOfHeadLow,addressOfHeadHigh
	lds @1, @0
	lds @2, @0+1 ;address of the first node in Z
.ENDMACRO

;************************************* set head ************
;sets the pointer of a label arg0 to arg1,arg2 (L,H)
.MACRO ll_set_head ; listname, addressOfHeadL,addressOfHeadH
	sts   @0,@1
	sts @0+1,@2
.ENDMACRO

;******* ll_head_extract **********
;extracts the first node of the linked 
;list label (arg0), and holds
;the address of the node in (arg1) and (arg2) 
;address register (Low,High). 
;The address of the extracted node is in 
.MACRO ll_head_extract ; LLname, XL,XH
	lds ZL, @0
	lds ZH, @0+1
	mov @1,ZL
	mov @2,ZH
	ld YL, Z+
	ld YH, Z
	sts   @0,YL
	sts @0+1,YH
.ENDMACRO



;** ll_head_insert **
;head inserts a node into 
;the linked list labeled arg0, 
;and holds the address 
;of the extracted node 
;in arg1 and arg2 (Low,High).  
.MACRO ll_head_insert ; LLname, XL,XH
	
	lds ZL, @0
	lds ZH, @0+1	; load the address stored at the head ptr
	
	sts @0, @1
	sts @0+1, @2	;store the address of the new node at the head

	mov YL, @1
	mov YH, @2
	st Y+,ZL
	st Y,ZH	
.ENDMACRO

;********************* EXTRACT NODE *****************************
;extracts a node with address (arg1,arg2) (XL,XH) 
;YOU CANNOT SUPPLY THE ADDRESS IN Y or Z or r17!!!!!
;from llist named arg0. The pointer to the node is already in
;the address register so you just have to rehook
;the pointers. returns NULL if the node is not found
.MACRO ll_extract ; listName, &nodeL, &nodeH
	push r16
	push r17

	lds ZL, @0
	lds ZH, @0+1 ;address of the first block in Z

	cp ZL,@1	 ;if the low addresses aren't equal
				 ;just continue looking	
	brne llextloop
	cp ZH,@2
	brne llextloop
	;you have to rehook the head
	ld YL, Z+
	ld YH, Z
	sts   @0,YL
	sts @0+1,YH
	rjmp llnotfound	;it was the first address so rehook		
	;you will have to traverse from the start
	;to find the node before the address to be extracted
llextloop:		
   	ld YL,Z+
	ld YH,Z 
	cpi YL,0	;check for the end of the list
	brne llnotend
	cpi YH,0
	brne llnotend
	clr @1			;address was not found so
	clr @2			;set the register to null and leave
	rjmp llnotfound
llnotend:
	cp @1,YL
	brne llmoveon
	cp @2, YH
	brne llmoveon
	rjmp llrehook	;Z has the prevoius node address
llmoveon:
	mov ZL, YL
	mov ZH, YH
	rjmp llextloop
llrehook:	;rehooking part
	ld r16, Y+
	ld r17, Y
	sbiw ZH:ZL,1
	st Z+, r16
	st Z,r17
llnotfound:

	pop r17
	pop r16
.ENDMACRO

 
;******************************************************
;inserts an llnode with address arg1,arg2 (L,H) into the linked 
;list named arg0. The address of the llnode has to be 
;supplied as (arg1,arg2) (XL,XH) 
;YOU CANNOT SUPPLY THE ADDRESS IN Y or Z or r17!!!!!
;the insertion will go at the end
.MACRO ll_tail_insert ; list_name, &nodeL, &nodeH 
	lds ZL, @0
	lds ZH, @0+1 ;address of the first node in Z-
	;check if the list is empty
	cpi ZL,0	
	brne llntempty
	cpi ZH,0
	brne llntempty
	ldi ZL,low(@0)
	ldi ZH,high(@0)
	st Z+, @1
	st Z, @2
	;the list was empty so
	;the node next to this is NULL
		;simpler
		;	mov ZL,@1
		;	mov ZH,@2
		;	st Z+, ZeroReg
		;	st Z,ZeroReg
	clr YL
	ll_set_next @1,@2,YL,YL	;slightly more OOPish
	rjmp llins_done
	;find the end of the list
llntempty:
	ld YL, Z+
	ld YH, Z	;load whatever Z is pointing to in Y

	cpi YL,0	
	brne llinscont
	cpi YH,0
	brne llinscont
	sbiw ZH:ZL,1
	st Z+, @1
	st Z,@2
	mov YL,@1
	mov YH,@2
	clr ZL
	st Y+,ZL
	st Y,ZL
	rjmp llins_done
llinscont:
	mov ZL, YL
	mov ZH, YH
	rjmp llntempty
	;you have reached the end of the list	
llins_done:
.ENDMACRO
;******************end ll_insert ************************** 


;****************************** get next ******************
;given the address of this node (arg0,arg1), returns
;the address of the next node in the linked list (arg2,arg3)
.MACRO ll_get_next ; &thisL, &thisH, &nextL, &nextH
	cpi @0,0
	brne llgnextnotnull
	cpi @1,0
	brne llgnextnotnull
	ldi @2,0
	ldi @3,0	;this address is null so set next null too
	rjmp llgnextnull
llgnextnotnull:
	mov ZL, @0
	mov ZH, @1
	ld @2,Z+
	ld @3,Z 
llgnextnull:
.ENDMACRO


;***************** set next ******************
;given the address of this node (arg0,arg1), sets
;the address of the next node in the linked list (arg2,arg3)
.MACRO ll_set_next ; &thisL, &thisH, &nextL, &nextH
	cpi @0,0
	brne llsnextnotnull
	cpi @1,0
	brne llsnextnotnull
	rjmp llsnextnull
llsnextnotnull:
	mov ZL, @0
	mov ZH, @1
	st 	Z+, @2
	st 	Z,	@3 
llsnextnull:
.ENDMACRO

;******************************************************************
;********************** finds a node in a linked list *************
;******************************************************************
;searches linked list with name arg0, for criterion in arg1
;and returns the address of the node containing the criterion
;in arg2 and arg3 (L,H) if the node doesn't exist, returns
;NULL pointer (the list must not be empty)
.MACRO ll_find_max_prio ; llname, critoffsetfromllnodeaddress, addLnodecont,addHnodecont 
	ll_gethead @0,ZL,ZH
	ldi r17,0
	ldi r19,0
	mov r15,r17	;address of the TCB containing the highest priority
llfndprio:
;examine the node pointed to by Z
	ldd r18, Z+lldtoffset+@1	;load the priority
	cp r17, r18
	brlo llprioreset
	ld YL, Z+
	ld YH, Z	;load next block into Y	
	mov ZL,YL
	mov ZH,YH
	cpi YL,0	
	brne llfndprio
	cpi YH,0
	brne llfndprio	;you have reached the end so load the address
					;of the maximum 
	rjmp llmaxprioend
llprioreset:
	mov r17, r18
	mov r19,ZL
	mov r15,ZH
	rjmp llfndprio
llmaxprioend:
	mov @2, r19
	mov @3, r15
.ENDMACRO


;*********************
;	sets the pointer
;	to the data block 
;	in the data part 
;	of the node
;*********************
;arg0 thisnodeL, thisnodeH, dataPtrL, dataPtrH
.MACRO ll_set_data_ptr
	push ZL
	push ZH
		mov ZL,@0
		mov ZH,@1
		;essentially just setting a byte
		;to a value - just without the 
		;TImem.inc header
		std Z+lldtoffset,@2
		std Z+lldtoffset+1,@3
	pop ZH
	pop ZL
.ENDMACRO


;*********************
;	gets the pointer
;	to the data block 
;	in the data part 
;	of the node
;*********************
;arg0 thisnodeL, thisnodeH, dataPtrL, dataPtrH
.MACRO ll_get_data_ptr
	push ZL
	push ZH
		mov ZL,@0
		mov ZH,@1
		;essentially just loding a byte
		;to a value - just without the 
		;TImem.inc header
		ldd @2,Z+lldtoffset
		ldd @3,Z+lldtoffset+1
	pop ZH
	pop ZL
.ENDMACRO

.CSEG
.exit