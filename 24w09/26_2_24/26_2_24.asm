.include "../templateM16.inc"

;Makra
.include "makra.inc"
;End of Makra

;Memory
.DSEG
	DisplaySRAM: .byte 4
.CSEG

; Definice
.def character = r16
.def selectedChar = r17
.def number = r18
.def TmpKey = r19
.def loopM = r24
.def key = r25

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
ret

;getKeyRc:
;	row_scan:
;		ldi TmpReg, 0x0f
;		out DispDataD,TmpReg
;		ldi TmpKey, 0b00001111	;detects all rows
;		com TmpKey
;		andi TmpKey, 0x0F
;		out DispDataP, TmpKey
;		nop nop nop nop  nop nop nop nop ;it works without them
;		in TmpKey, DispDataI
;		andi TmpKey, 0xF0
;		or Key, TmpKey
;		clr TmpKey
;	ret
;	;and the second nible
;	col_scan:
;		ldi TmpReg, 0xf0
;		out DispDataD,TmpReg
;		ldi TmpKey, 0b11110000	;detects all rows
;		com TmpKey
;		andi TmpKey, 0xF0
;		out DispDataP, TmpKey
;		nop nop nop nop  nop nop nop nop ;it works without them
;		in TmpKey, DispDataI	;read a key
;		andi TmpKey, 0x0F
;		or Key,TmpKey
;		ldi TmpReg, 0x0f
;		eor Key,TmpReg
;		ret
;ret

increaseLoopM:
	inc loopM
ret

decreaseLoopM:
	dec loopM
ret

Main:
	clr TmpReg
Loop:
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

	rcall increaseLoopM

;  	ldi PDelReg, 5
;  	rcall Delay1m
;  	rcall getKeyRc
;  	cpi key, 0x88
;  	brne Loop
;  	cpi key, 0x77
;  	breq increaseLoopM
;  	cpi key, 0xB7
;  	breq decreaseLoopM
rjmp Main

.include "charTable.inc"
