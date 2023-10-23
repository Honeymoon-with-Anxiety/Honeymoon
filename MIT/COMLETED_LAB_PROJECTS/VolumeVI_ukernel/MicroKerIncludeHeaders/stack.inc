.EQU STACK_SIZE_MAX  = 50

;*********************************************************
;**************** STACK  CLASS  DECLARATION **************
;*********************************************************
;this functions as a stack block where the actual storage
;place is somewhere else. You have to supply the label as
;an argument. The label will store the address of the entire
;structure		 
.CSEG
.EQU pstk			=	2		;size of the pointer to the stack
.EQU stk_num_els	=	1	  	;size of the location storing the number of elements
.EQU stk_sz			=   1		;size of the location storing the stack size
.EQU stk_top		=	2		;address of the top of the stack
.EQU stk_numeoffset	=   0		;offset of the number of elements
.EQU stk_soffset	=	1		;offset of the size of the stack
.EQU stk_tpoffset	=   2 		;offset of the top
.EQU stk_boffset	=   4		;offset of the body
;******************************** stack functions ********
;initialize the pointer to the stack with an address in hex
; Label is argument0, address is given as arg1 in hex
;for now it should be done by memory manager
.macro stk_ptr
	ldi r17, low(@1)
	sts @0, r17	;store the class's address
	ldi r17, high(@1) 
	sts @0+1, r17	
.endmacro


;init this stack given the label as arg0
;the label has to contain the address of the space
;allocated to the stack. The size of the stack is
;given as arg1
.macro stk_new
		lds ZL, @0	  	;load the address stored at the label
		lds ZH, @0+1		;declaring the stack;
		clr r17				;clear the register, you will have 0 els
		std Z+stk_numeoffset,r17	;init number of elements to zero

		ldi r17, stk_soffset		;put the stack's size address
		add	ZL, r17					;into Z register
		clr r17			
		adc	ZH, r17
		ldi r17, @1			;load stack size into r17
		st Z+,r17					;size is stored and Z points
		
		inc r17
		add r17,ZL					;low address of the top in r17
		st Z+, r17		
		clr r17
		mov r18,ZH
		adc r18, r17
		st Z+, r18					;address of the top stored
			
		ldi r17, @1						
  stkbody:							;init the body of the stack
		st Z+, r17
		dec r17
		cpi r17,0
		brne stkbody	  
.endmacro



;returns the actual size of the stack 
;stack name is arg1, register where you want the 
;size is arg2
.macro stk_get_sz
	lds ZL, @0	  	;load the pointer of the stack
	lds ZH, @0+1
	ldd @1, Z+stk_soffset	
.endmacro


;returns the size of the entire class structure
;stack name is arg1, register where you want the 
;size is arg2
;(you may need it when trying to glue one stack 
;after another)
.macro stk_getsz
	lds ZL, @0	  	;load the pointer of the stack
	lds ZH, @0+1
	ldd @1, Z+stk_soffset
	subi @1, -stk_boffset	
.endmacro

;loads atmel SP with the top of stack named agr0
.macro stk_ldSP
	lds ZL, @0	  		;load the address stored at the label	
	lds ZH, @0+1		;declaring the stack;
	ldd r17, Z+stk_tpoffset
	out	SPL, r17
	ldd r17, Z+stk_tpoffset+1
	out	SPH, r17
.endmacro


;stores atmel SP into stk top location of stack arg1
.macro stk_stSP
	lds ZL, @0	  		;load the address stored at the label	
	lds ZH, @0+1		;declaring the stack;
	in r17,SPL
	std Z+stk_tpoffset,r17
	in r17,SPH
	std Z+stk_tpoffset+1, r17
.endmacro

;This is for the software stack if you need it
;.macro stk_pop
;.endmacro

.CSEG
.exit