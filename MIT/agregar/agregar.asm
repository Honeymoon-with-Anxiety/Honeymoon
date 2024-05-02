.include "../templateM16.inc"
.include "numCtrl.inc"
.include "displayCtrl.inc"

.MACRO initY
	ldi YL, low(@0)
	ldi YH, high(@0)
.ENDMACRO

/*
*	Operation Plus = 0
*	Operation Minus = 1
*	Operation Multiplicating = 2
*	Operation Dividing = 3
*/

Main:
	setNum16SRAM 2002
	clearDisplaySRAM
; 	rcall rozeberNaCislice16b
	setOperation 3
	getOperation r16
rjmp Main

.include "C:/Users/admin/Music/Vasek/26_2_24/charTable.inc"
