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
