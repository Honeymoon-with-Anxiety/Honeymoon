.EQU DispDataP = PortC  ;display data port
.EQU DispDataD = DDRC	;display data direction register
.EQU DispDataI = PinC	;display data coming in to port C
.EQU DispCtrlP = PortD	;display data control (the three pins) port
.DEF selChar = r19

.MACRO clearDisplaySRAM
	push ZeroReg
	push YH
	push YL

	clr ZeroReg
	ldi YL, low(number16Digits)
	ldi YH, high(number16Digits)

	std Y+0, ZeroReg
	std Y+1, ZeroReg
	std Y+2, ZeroReg
	std Y+3, ZeroReg

	pop YL
	pop YH
	pop ZeroReg
.ENDMACRO

.MACRO displayPart
	push ZeroReg
	push TmpReg
	push YH
	push YL

	clr ZeroReg
	clr TmpReg
	ldi YL, low(number16Digits)
	ldi YH, high(number16Digits)
	ldi ZL, low(2*segmentovka)
	ldi ZH, high(2*segmentovka)

	ldi TmpReg, @0
	cpi TmpReg, 4
	brge displayPartReturn

	ldd TmpReg, Y+@0
	add ZL, TmpReg
	adc ZH, ZeroReg

	sbi DispCtrlP, 4 ;set_led_pwr_on
	sbi DispCtrlP, 3 ;digit_units_on
	sbi DispCtrlP, 2 ;digit_units_on
	clr TmpReg
	lpm TmpReg, Z
	out DispDataP, TmpReg

	displayPartReturn:
	pop YL
	pop YH
	pop TmpReg
	pop ZeroReg
.ENDMACRO

.MACRO readDigit //(int offset, reg destination)
	ldd @1, Y+@0
.ENDMACRO

displayChar:
	initLowHigh 2*segmentovka, ZL, ZH
	add ZL, selChar
	adc ZH, ZeroReg
	lpm TmpReg, Z
	out DispDataP, TmpReg
ret

zobrazCislo16b:
; 	initLowHigh number16Digits, YL, YH
	sbi DispCtrlP, 4

	readDigit 3, selChar //units
	sbi DispCtrlP, 3
	sbi DispCtrlP, 2
	rcall displayChar
	ldi PDelReg, 5
	rcall Delay1m

	readDigit 2, selChar //tens
	sbi DispCtrlP, 3
	cbi DispCtrlP, 2
	rcall displayChar
	ldi PDelReg, 5
	rcall Delay1m

	readDigit 1, selChar //hundr
	cbi DispCtrlP, 3
	sbi DispCtrlP, 2
	rcall displayChar
	ldi PDelReg, 5
	rcall Delay1m

	readDigit 0, selChar //thou
	cbi DispCtrlP, 3
	cbi DispCtrlP, 2
	rcall displayChar
	ldi PDelReg, 5
	rcall Delay1m
ret
