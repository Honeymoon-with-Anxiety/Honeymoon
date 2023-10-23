;***********************************
;your second simulation lab is 
;an OOP-like implementation of
;circular buffer 
;***********************************
;=========Includes =================
.NOLIST
.include	"m16def.inc"
.include 	"TImem.inc"
.include 	"CircBuffer.inc"
.LIST
;====== Register definitions =======
.DEF ZeroReg = r0
.DEF TmpReg  = r16
;=====+== PROGRAM segment ==========
.CSEG
;******** Interrupt vectors ********
		.ORG	0x0000
		jmp	RESET			; Reset Handler
		
;******* Reset ********
		.ORG	0x0030
Reset:		
		clr ZeroReg
		rjmp	Main
	

;**************************************************
;********************** MAIN **********************
;**************************************************
;testing the circular buffer capabilities
Main:
	TIinit_circular_buffer TIBuffStruct, 0x8
	

	T2IBuff_space_left TIBuffStruct, r16
roomLeft:
	inc r18
	TIwrite_circular_buffer TIBuffStruct, r18
	T2IBuff_space_left TIBuffStruct, r16
	
	cpi r16, 2
	brsh roomLeft

dataleft:
	TIread_circular_buffer TIBuffStruct, r19
	T2IBuff_space_left TIBuffStruct, r16

	cpi r16, 1
	brsh dataleft
	
	rjmp roomLeft
	
rjmp Main	



