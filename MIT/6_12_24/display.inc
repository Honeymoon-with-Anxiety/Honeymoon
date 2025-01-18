.equ tisic_offset = 0
.equ stovky_offset = 1
.equ desitky_offset = 2
.equ jednotky_offset = 3

initYdisplayRAM:
	ldi YL, low(disp_RAM)
	ldi YH, high(disp_RAM)
ret

initZCharTable:
	ldi ZL, low(display)
	ldi ZH, high(display)
ret

initXCharEndTable:
	ldi XL, low(konec_display)
	ldi XH, high(konec_display)
ret

clearDisplay:
	std Y+0, ZeroReg
	std Y+1, ZeroReg
	std Y+2, ZeroReg
	std Y+3, ZeroReg
ret

initDisplay:
	initYdisplayRAM
	clearDisplay
ret

rozeberNaCislice:
	clr TmpReg
	rncStovky:
		cpi number, 100
		brlo rncDesitky
		subi number, 100
		inc TmpReg
		cpi number, 100
		brsh rncStovky
		std Y+1, TmpReg
		clr TmpReg
	rncDesitky:
		cpi number, 10
		brlo rncJednotky
		subi number, 10
		inc TmpReg
		cpi number, 10
		brsh rncDesitky
		std Y+2, TmpReg
		clr TmpReg
	rncJednotky:
		std Y+3, number
		clr number
