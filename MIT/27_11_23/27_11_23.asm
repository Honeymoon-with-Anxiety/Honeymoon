;***********************************
;	lab example number one
;***********************************
;=========Includes =================
;
.NOLIST
.include	"m16def.inc"
.LIST



;====== Register definitions =======
.DEF ZeroReg = r0
.DEF TmpReg = r21
.def itr=r18
.def itrMax = r19
.def itrBBLSL = r20 ;iterator pro bblSort vnejsi smysku
.def itrBBLSLMax = r22 ;max iterator pro bblSort vnejsi smysku


; krtek a hovno

.include "vector_table_m16.inc"

;************************************************

		.ORG	0x0030
Reset:

		clr	ZeroReg
		ldi	TmpReg, low(RAMEND)	; Stack Ptr
		out	SPL, TmpReg
		ldi	TmpReg, high(RAMEND)
		out	SPH, TmpReg

		ldi	TmpReg, 0b10000000	; Disable JTAG interface
		out	MCUCSR, TmpReg
		out	MCUCSR, TmpReg

		rjmp	Main
;***************************************

.DSEG
	ugandalf: .byte 16
.CSEG

initZ:
	ldi ZL, low(2*ulozenaCisla)
	ldi ZH, high(2*ulozenaCisla)
ret

initY:
	ldi YL, low(ugandalf)
	ldi YH, high(ugandalf)
ret
initX:
	ldi XL, low(2*EndOfMojeCisla)
	ldi XH, high(2*EndOfMojeCisla)
ret

loadFromFlash:
	lpm r16, Z+
ret

saveToSRAM:
	st Y+, r16
ret

compareNums:
	ld r16, Y
	ldd r17, Y+1
	cp r16, r17
	brlt itsOk
		rcall swapNums
	itsOk:
ret

swapNums:
	st Y, r17
	std Y+1, r16
ret


loadFromFlashToSRAM:
	lpm r16, Z+ ;rcall loadFromFlash
	st Y+, r16 ;rcall saveToSRAM
	inc itrMax
	inc itrBBLSLMax

	cp ZL, XL
	cpc ZH, XH
	brne loadFromFlashToSRAM
	dec itrMax
	dec itrBBLSLMax
ret

bubbleSortInLoop:
	rcall compareNums
	adiw YH:YL, 1
	inc itr
	cp itr, itrMax
	brne bubbleSortInLoop
	dec itrMax
	rcall initY
	clr itr
ret

bblSort:
	rcall bubbleSortInLoop
	inc itrBBLSL
	cp itrBBLSL, itrBBLSLMax
	brne bblSort
	clr itrBBLSL
ret

Main:
	rcall initZ
	rcall initY
	rcall initX
	clr itrMax
	rcall loadFromFlashToSRAM
	rcall initY
	rcall bblSort
rjmp Main


.include "tabulkaSCisly.inc"
