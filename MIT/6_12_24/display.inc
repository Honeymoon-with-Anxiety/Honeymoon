.equ stovky_offset = 1
.equ desitky_offset = 2
.equ jednotky_offset = 3

nactiCislo:
    rcall initZCharTable
    add ZL, selectedChar
    adc ZH, ZeroReg
ret

zobrazCislo:
    lpm character, Z
    out DispDataP, character
ret

zobrazovaciPodprogram:
    rcall nactiCislo
    rcall zobrazCislo
ret

initYdisplayRAM:
	ldi YL, low(disp_RAM)
	ldi YH, high(disp_RAM)
ret

initZCharTable:
	ldi ZL, low(2*display)
	ldi ZH, high(2*display)
ret

initXCharEndTable:
	ldi XL, low(2*konec_display)
	ldi XH, high(2*konec_display)
ret

clearDisplay:
	std Y+0, ZeroReg
	std Y+1, ZeroReg
	std Y+2, ZeroReg
	std Y+3, ZeroReg
ret

initDisplay:
	rcall initYdisplayRAM
	rcall clearDisplay
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
		std Y+0, TmpReg
		clr TmpReg
	rncDesitky:
		cpi number, 10
		brlo rncJednotky
		subi number, 10
		inc TmpReg
		cpi number, 10
		brsh rncDesitky
		std Y+1, TmpReg
		clr TmpReg
	rncJednotky:
		std Y+2, number
		clr number
