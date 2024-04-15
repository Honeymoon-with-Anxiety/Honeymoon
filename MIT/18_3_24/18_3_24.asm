.include "../templateM16.inc"
.include "makra.inc"

; Definice
.def selectedChar = r16
.def loopM = r17
.def TmpKey = r18
.def key = r23

.EQU DispDataP = PortC  ;display data port
.EQU DispDataD = DDRC	;display data direction register
.EQU DispDataI = PinC	;display data coming in to port C
.EQU DispCtrlP = PortD	;display data control (the three pins) port
; End of Definice

scan:
	clr key	;storage for the scaned key
	ldi TmpReg, 0x0F	;config for input of the row
	out DispDataD,TmpReg	;configure to scan the row
	clr TmpKey
	out DispDataP, TmpKey	;disable the pullups
	nop nop nop nop nop nop nop nop	;wait to reconfigure
	in TmpKey, DispDataI	;read in the row
	andi TmpKey, 0xF0	;mask out the row bits
	or key, TmpKey	;record it in the key variable
	clr TmpKey
;and the second nible
	ldi TmpReg, 0xF0
	out DispDataD,TmpReg
	out DispDataP, TmpKey
	nop nop nop nop nop nop nop nop
	in TmpKey, DispDataI	;read the column
	andi TmpKey, 0x0F
	or key,TmpKey
	ldi TmpReg, 0x0F
	eor key,TmpReg
ret

.include "zobrazovaciHlava.inc"
.include "controlLoopM.inc"

Main:
	rcall scan
	out PortA, key
	nop nop nop nop nop nop nop nop ;wait to kill a living book

	cpi key, 0b00000000
	rjmp retPoint
	nop
	cpi key, 0b10001000
  	breq increaseLoopM
  	nop
 	cpi key, 0b01001000
 	breq decreaseLoopM
	nop
	retPoint:
	clr key
	digit_units_ON
	ldi selectedChar, 9
	//mov selectedChar, loopM
;  	ldi PDelReg, 250
;  	rcall Delay1m
 	rcall zobrazovaciPodprogram
	seg_led_pwr_on

rjmp Main

.include "charTable.inc"
