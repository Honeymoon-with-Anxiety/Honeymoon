;***********************************************
;			TImem.inc
;***********************************************
;This file contains macros to ease the reading 
;of sram operations
;***********************************************
.CSEG

.EQU ptr_sz = 2
;*********** SET POINTER FROM REGISTERS**********
;takes label in arg0 and stores
;the address in arg1L,arg2H in it
.MACRO set_ptr
	sts @0,@1
	sts @0+1,@2
.ENDMACRO

;*********** SET POINTER TO ABSOLUTE ADDRESS **********
;takes label in arg0 and stores
;the address in 0xXXXX in it
.MACRO set_ptri
	sts @0,@1
.ENDMACRO

;*********** GET POINTER **********
;takes label in arg0 and loads
;the address stored in it in arg1L, arg2H
.MACRO get_ptr
	lds @1, @0
	lds @2, @0+1
.ENDMACRO

;******************** SET BYTE TO IMMEDIATE****
;sets the label arg0 referring to a
;to equal to  a single byte value to 
;register arg1
.MACRO TIset_bytei
	push r16
	ldi r16, @1
	sts @0, r16
	pop r16
.ENDMACRO

;******************* SET BYTE TO REGISTER******
;sets the label to the supplied register value
.MACRO TIset_byte
	sts @0, @1
.ENDMACRO

;******************* GET BYTE IN A LABEL ******
;retrieves a byte from label in arg0, and puts
;it in register (arg1)
.MACRO TIget_byte
	lds @1, @0
.ENDMACRO

.exit