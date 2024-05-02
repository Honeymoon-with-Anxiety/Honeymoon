.EQU DispDataP = PortC  ;display data port
.EQU DispDataD = DDRC	;display data direction register
.EQU DispDataI = PinC	;display data coming in to port C
.EQU DispCtrlP = PortD	;display data control (the three pins) port


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
