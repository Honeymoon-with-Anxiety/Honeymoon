;***********************************
;	lab example number one
;***********************************
;=========Includes =================
.NOLIST
.include	"m16def.inc"
.include 	"TImem.inc"
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

.DSEG 
.ORG $60
my_pointer: .BYTE ptr_sz
.CSEG

Main:
	ldi XH, 0x00
	ldi XL, 0xA0
	set_ptr my_pointer, XL, XH
	TIget_byte my_pointer, TmpReg
	inc XL
	set_ptr my_pointer, XL, XH
	TIget_byte my_pointer, TmpReg
	
rjmp Main	



















