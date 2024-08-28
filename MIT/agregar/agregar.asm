.include "../templateM16.inc"
.include "numCtrl.inc"
.include "displayCtrl.inc"

/*
*	Operation Plus = 0
*	Operation Minus = 1
*	Operation Multiplicating = 2
*	Operation Dividing = 3
*/

Main:
	setNum16SRAM 2002
	getNum16SRAM r18, r17
	clearDisplaySRAM
	setOperation 0
	ldi r16, 2
	setChange 2

	mainL:
		rcall makeChange
		rcall rozeberNaCislice16b
		rcall zobrazCislo16b
	rjmp mainL
rjmp Main

.include "C:/Users/admin/Music/Vasek/26_2_24/charTable.inc"
