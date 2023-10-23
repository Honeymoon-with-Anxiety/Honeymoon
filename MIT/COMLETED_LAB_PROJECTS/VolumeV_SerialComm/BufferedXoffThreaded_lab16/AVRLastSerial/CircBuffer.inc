;filename: CircBuffer.inc
;
;*************************************************************************
;***			CIRCULAR BUFFER STRUCT CONSTANTS DEFINITIONS 		   ***
;*************************************************************************
;you will acces individual members of the struct by adding these offsets
;to the base address
;*************************************************************************
.CSEG
.EQU TIFront_offset 			= 0
.EQU TIEnd_offset				= 1
.EQU TICount_offset 			= 2
.EQU TIFlags_offset 			= 3
.EQU TIModulus_offset 			= 4			; modulus equals data size
.EQU TIData_offset		 		= 5
.EQU CircularBuffer_sz 			= 1+1+1+1+1 ; variable data piece follows
;*************************************************************************
;***					END BUFFER STRUCT DEFS 						   ***
;************************************************************************* 


;*************************************************************************
;***				CIRCULAR BUFFER STRUCT SRAM LAYOUT 		   		   ***
;*************************************************************************
;This is how it will be layed out in SRAM once you place the circ buff  
;*************************************************************************
.DSEG
.org 0x60		;	put it somewhere safe in the  SRAM
CBuffIn : .BYTE CircularBuffer_sz+10 	;the structure right behind it
CBuffOut: .BYTE CircularBuffer_sz+10
;you  will put many of these buffers somewhere else in your program
;*************************************************************************
;***					END BUFFER SRAM LAYOUT 						   ***
;************************************************************************* 


;******* MODULAR INCREMENT *****
;base address to modularly increment an offset in as arg0
;tha actual offset in arg1 as a constant
.MACRO TIMod_inc
	push r16
	push r17
	TIget_byte @0+TIModulus_offset,r17
	TIget_byte @0+@1, r16 ;have the value to increment
	inc r16
	cp r16,r17	;check if it's equal to modulus
	brlo TIMod_inc_ok
	clr r16
TIMod_inc_ok:
	TIset_byte @0+@1, r16
	pop r17
	pop r16
.ENDMACRO



;************* FRONT TO END DISTANCE *************
;calculates distance from start to end
;end (arg0), front (arg1), modulus (arg2)
;returns the space left in the buffer in arg0 register
.MACRO TIbuf_space_left ; end, front
	sub @0, @1 	;end - front gives correct result if(e>f)
	sbrc @0,7	;branch if positive				
	add @0, @2	;so end < front
.ENDMACRO

;**** calculate the number of spaces available
;for writing
;argument 0 is the label of the buffer to check
;argument 1 is the return value register
.MACRO T2IBuff_space_left
	push r15	;r16 is  the return value so don't 
				;push it
	push r17

	TIget_byte @0+TIFront_Offset, r17
	TIget_byte @0+TIEnd_Offset, r16
	TIget_byte @0+TIModulus_offset, r15
	
	sub r16, r17 	;end - front gives correct result if(e>f)
	sbrc r16,7		;branch if positive				
	add r16, r15	;so end < front, return value in r16

	pop r17
	pop r15
.ENDMACRO

;********************** INIT CIRC BUFFER ***********************
; init circular buffer identified in arg0 and modulus in arg1 
.MACRO TIinit_circular_buffer
	push ZL
	push ZH
	TIset_bytei @0+TIFront_offset, 0
	TIset_bytei @0+TIEnd_offset	 , 0
	TIset_bytei @0+TICount_offset, 0
	TIset_bytei @0+TIFlags_offset, 0
	TIset_bytei @0+TIModulus_offset, @1
	;init the data space to 1's
	ldi TmpReg, @1
	ldi ZL, low(@0)
	ldi ZH, high(@0)
	adiw ZH:ZL, TIData_offset
	TIcircbufflp01:	;means loop01 
		st Z+, TmpReg
		dec TmpReg
		cpse TmpReg, ZeroReg
	rjmp TIcircbufflp01
	pop ZH
	pop ZL
.ENDMACRO


;*************************** read buffer ***
;reads a byte at the end of a circular buffer 
;given by label arg0, returns result at arg1 
;increases the end and decreases the buf_count
;YOU HAVE TO MAKE SURE THAT THE BUFFER IS NOT 
;			EMPTY BEFORE THE CALL
.MACRO TIread_circular_buffer
	push ZL
	push ZH
	
	ldi ZL, low(@0+TIData_offset)
	ldi ZH, high(@0+TIData_offset) 
	TIget_byte @0+TIEnd_offset, TmpReg 	;fronts's value
	add ZL, TmpReg
	adc ZH, ZeroReg 
	ld  @1,Z						;store the new byte
	;increment end and decrement count
	TIMod_inc @0, TIEnd_offset
	TIget_byte @0+TICount_offset, TmpReg
	dec TmpReg
	TIset_byte @0+TICount_offset, TmpReg
	
	pop ZH
	pop ZL
.ENDMACRO


;*************************** write buffer ***
;writes a byte at the 'front' offset of a circular buffer 
;given by label arg0 (buffer label), stores the byte value 'arg1', 
;increases the front and increases the buf_count
;YOU HAVE TO MAKE SURE THAT THE BUFFER IS NOT 
;			FULL BEFORE THE CALL
.MACRO TIwrite_circular_buffer ; buffer name(label), what to write(reg)
	push ZL
	push ZH	
	push TmpReg

	ldi ZL, low(@0+TIData_offset)
	ldi ZH, high(@0+TIData_offset) 
	TIget_byte @0+TIFront_offset, TmpReg 	;fronts's value
	add ZL, TmpReg
	adc ZH, ZeroReg 
	st Z, @1						;store the new byte
	;increment front and count
	TIMod_inc @0, TIFront_offset
	TIget_byte @0+TICount_offset, TmpReg
	inc TmpReg
	TIset_byte @0+TICount_offset, TmpReg

	pop TmpReg
	pop ZH
	pop ZL

.ENDMACRO

.exit

;AN IMPLEMENTATION OF CIRCULAR BUFFER 
;WITH ITS DEFINITIONS

