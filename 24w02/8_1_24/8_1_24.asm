.include "../templateM16.inc"

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
;End of Makra

; Definice
.def character = r16
.def selectedCharItr = r17
.def selectedChar = r18

.EQU DispDataP = PortC  ;display data port
.EQU DispDataD = DDRC	;display data direction register
.EQU DispDataI = PinC	;display data coming in to port C
.EQU DispCtrlP = PortD	;display data control (the three pins) port
; End of Definice

initZ:
    ldi ZL, low(2*segmentovka)
    ldi ZH, high(2*segmentovka)
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

Main:
	seg_led_pwr_on

	ldi selectedChar, 6
	ldi PDelReg, 5
	rcall Delay1m
	digit_thousands_ON
	rcall zobrazovaciPodprogram

 	ldi selectedChar, 9
	ldi PDelReg, 5
	rcall Delay1m
	digit_hundreds_ON
	rcall zobrazovaciPodprogram

	ldi selectedChar, 6
	ldi PDelReg, 5
	rcall Delay1m
	digit_tens_ON
	rcall zobrazovaciPodprogram

	ldi selectedChar, 9
	ldi PDelReg, 5
	rcall Delay1m
	digit_units_ON
	rcall zobrazovaciPodprogram
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
