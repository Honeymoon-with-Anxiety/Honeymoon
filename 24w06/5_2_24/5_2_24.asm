.include "./templateM16.inc"

;Makra
.MACRO seg_led_pwr_on
	sbi DispCtrlP, 4
.ENDMACRO

.MACRO seg_led_pwr_off
	cbi DispCtrlP, 4
.ENDMACRO

.MACRO digit_units_ON
	sbi DispCtrlP, 3
	sbi DispCtrlP, 2
.ENDMACRO

.MACRO digit_tens_ON
	sbi DispCtrlP, 3
	cbi DispCtrlP, 2
.ENDMACRO

.MACRO digit_hundreds_ON
	cbi DispCtrlP, 3
	sbi DispCtrlP, 2
.ENDMACRO

.MACRO digit_thousands_ON
	cbi DispCtrlP, 3
	cbi DispCtrlP, 2
.ENDMACRO

.MACRO rozeberCislo
	ldi number,@0
	rcall rozeberNaCislice
.ENDMACRO

.MACRO rozeberCisloMove
	mov number,@0
	rcall rozeberNaCislice
.ENDMACRO
;End of Makra

;Memory
.DSEG
	DisplaySRAM: .byte 4
.CSEG

; Definice
.def character = r16
.def selectedChar = r17
.def number = r18
.def numberSum = r23
.def loopM = r24

.EQU DispDataP = PortC  ;display data port
.EQU DispDataD = DDRC	;display data direction register
.EQU DispDataI = PinC	;display data coming in to port C
.EQU DispCtrlP = PortD	;display data control (the three pins) port
; End of Definice

initY:
    ldi YL, low (DisplaySRAM)
    ldi YH, high(DisplaySRAM)
ret

initZ:
    ldi ZL, low(2*segmentovka)
    ldi ZH, high(2*segmentovka)
ret

initDisplay:
	rcall initY
	std Y+0, ZeroReg
	std Y+1, ZeroReg
	std Y+2, ZeroReg
	std Y+3, ZeroReg
ret

nactiCislo:
    rcall initZ
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

rozeberNaCislice:
	rncStovky:
		cpi number, 100
		brlo rncDesitky
		subi number, 100
		inc numberSum
		cpi number, 100
		brsh rncStovky
		std Y+1, numberSum
		clr numberSum
	rncDesitky:
		cpi number, 10
		brlo rncJednotky
		subi number, 10
		inc numberSum
		cpi number, 10
		brsh rncDesitky
		std Y+2, numberSum
		clr numberSum
	rncJednotky:
		std Y+3, number
		clr number
ret

Main:
	seg_led_pwr_on
	rcall initDisplay
	rozeberCisloMove loopM
;	rozeberCislo 128

	ldd selectedChar, Y+0
	ldi PDelReg, 5
	rcall Delay1m
	digit_thousands_ON
	rcall zobrazovaciPodprogram

	ldd selectedChar, Y+1
	ldi PDelReg, 5
	rcall Delay1m
	digit_hundreds_ON
	rcall zobrazovaciPodprogram

	ldd selectedChar, Y+2
	ldi PDelReg, 5
	rcall Delay1m
	digit_tens_ON
	rcall zobrazovaciPodprogram

	ldd selectedChar, Y+3
	ldi PDelReg, 5
	rcall Delay1m
	digit_units_ON
	rcall zobrazovaciPodprogram

	inc loopM
rjmp Main

segmentovka:
;     87654321,   87654321
.db	0b11000000, 0b11111001		; '0', '1'
.db	0b10100100, 0b10110000		; '2', '3'
.db	0b10011001, 0b10010010		; '4', '5'
.db	0b10000010, 0b11111000		; '6', '7'
.db	0b10000000, 0b10010000		; '8', '9'
.db	0b10001000, 0b10000011		; 'A', 'B'
.db	0b11000110, 0b10100001		; 'C', 'D'
.db	0b10000110, 0b10001110		; 'E', 'F'
.exit
