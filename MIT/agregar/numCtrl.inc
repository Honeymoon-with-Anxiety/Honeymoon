.def numL = r16
.def numH = r17
.def thoL = r18
.def thoH = r20

.equ oprPlus = 0b00000000
.equ oprMinus = 0b00000001
.equ oprMulti = 0b00000010
.equ oprDiv = 0b00000011

.DSEG
	number16: .byte 2 ;uchovava 16-bit cislo pro rozebrani na cislice
	number16Digits: .byte 4 ;uchovava jednotlive cislice pro display
	editCurrent: .byte 1
	editSize: .byte 1
.CSEG

.MACRO initLowHigh
	ldi @1, low(@0)
	ldi @2, high(@0)
.ENDMACRO

.MACRO setNum16SRAM ;ulozeni 16-bit cisla do SRAM (r17:r16 << CH:CL)
	push numH
	push numL
	push YH
	push YL

	initLowHigh @0, numL, numH
	initLowHigh number16, YL, YH

	std Y+0, numH
	std Y+1, numL

	pop YL
	pop YH
	pop numL
	pop numH
.ENDMACRO

.MACRO getNum16SRAM ;nacteni 16-bit cisla z SRAM (r17:r16 >> CH:CL)
	push YH
	push YL

	initLowHigh number16, YL, YH
	ldd @0, Y+0
	ldd @1, Y+1

	pop YL
	pop YH
.ENDMACRO

.MACRO getLowNum16SRAM ;nacteni 16-bit cisla z SRAM
	push YL

	initLowHigh number16, YL, YH
	ldd @0, Y+1

	pop YL
.ENDMACRO

.MACRO getHighNum16SRAM ;nacteni 16-bit cisla z SRAM
	push YH

	initLowHigh number16, YL, YH
	ldd @0, Y+0

	pop YH
.ENDMACRO

;manualni nastaveni cisel na pozice
.MACRO getThousands
	ldd @0, Y+0
.ENDMACRO

.MACRO setThousands
	std Y+0, @0
.ENDMACRO

.MACRO getHundredts
	ldd @0, Y+1
.ENDMACRO

.MACRO setHundredts
	std Y+1, @0
.ENDMACRO

.MACRO getTens
	ldd @0, Y+2
.ENDMACRO

.MACRO setTens
	std Y+2, @0
.ENDMACRO

.MACRO getUnits
	ldd @0, Y+3
.ENDMACRO

.MACRO setUnits
	std Y+3, @0
.ENDMACRO

.MACRO getOperation
	push YH
	push YL

	initLowHigh editCurrent, YL, YH
	ld @0, Y

	pop YL
	pop YH
.ENDMACRO

.MACRO setOperation
	push r16
	push YL
	push YH
	push TmpReg

	ldi TmpReg, @0
	cpi TmpReg, 4
	brge setOperationReturn

	initLowHigh editCurrent, YL, YH
	ldi r16, @0
	st Y, r16

	setOperationReturn:
	pop TmpReg
	pop YH
	pop YL
	pop r16
.ENDMACRO

.MACRO getChange
	push YH
	push YL

	initLowHigh editSize, YL, YH
	ld @0, Y

	pop YL
	pop YH
.ENDMACRO

.MACRO setChange
	push r16
	push YL
	push YH

	initLowHigh editSize, YL, YH
	ldi r16, @0
	st Y, r16

	pop YH
	pop YL
	pop r16
.ENDMACRO

;rozklad cisel
rozeberNaCislice16b:
	push ZeroReg
	push r16
	push r17
	push r18
	push r20
	push TmpReg

	clr ZeroReg
	clr TmpReg

 	initLowHigh 1000, thoL, thoH
 	initLowHigh number16Digits, YL, YH

	getNum16SRAM r17, r16

	rncTisice:
		cp numL, thoL
		cpc numH, thoH
		brlo rncTisiceStore
		sub numL, thoL
		sbc numH, thoH
		inc TmpReg
		brsh rncTisice
		rncTisiceStore:
			setThousands TmpReg
			clr TmpReg
	rncStovky:
		cpi numL, 100
		cpc numH, ZeroReg
		brlo rncStovkyStore
		subi numL, 100
		sbc numH, ZeroReg
		inc TmpReg
		brsh rncStovky
		std Y+1, TmpReg
		rncStovkyStore:
			setHundredts TmpReg
			clr TmpReg
	rncDesitky:
		cpi numL, 10
		brlo rncDesitkyStore
		subi numL, 10
		inc TmpReg
		cpi numL, 10
		brsh rncDesitky
		rncDesitkyStore:
		setTens TmpReg
		clr TmpReg
	rncJednotky:
		setUnits numL
		clr numL
		clr numH

	pop TmpReg
	pop r20
	pop r18
	pop r17
	pop r16
	pop ZeroReg
ret
