.include "../templateM16.inc"
.include "C:/Users/admin/Documents/DominikJuza/tlacitka/LedOn.inc"
.include "C:/Users/admin/Documents/DominikJuza/tlacitka/Scan.inc"
.include "C:/Users/admin/Documents/DominikJuza/tlacitka/SegmentUp.inc"
.include "C:/Users/admin/Documents/DominikJuza/tlacitka/SegmentDown.inc"
.include "C:/Users/admin/Documents/DominikJuza/tlacitka/Disassemble2.inc"

; Definice
 .def TmpKey = r18
 .def key = r23
;
 .EQU DispDataP = PortC  ;display data port
 .EQU DispDataD = DDRC	;display data direction register
 .EQU DispDataI = PinC	;display data coming in to port C
 .EQU DispCtrlP = PortD	;display data control (the three pins) port
; End of Definice

Higher:
	ldi r16, 1
	com r16
	out portA,r16
	rcall SegmentUp
	ldi r16,1
rjmp Main

Lower:
	ldi r16,2
	com r16
	out portA, r16
	rcall SegmentDown
	ldi r16, 2
rjmp Main

Hex:
	ldi r23,8
	com r23
	out portA,r23
	ldi r23,1
rjmp Main

Dex:
	ldi r23,8
	com r23
	out portA,r23
	ldi r23,0
rjmp Main;

Main:
	ldi PDelReg, 200
	rcall Hex

	Main10:
		clr	Key

		rcall Scan
		com Key

		ldi TmpReg,0b00010001
		and TmpReg,Key
		breq Higher

		ldi TmpReg,0b00010010
		and TmpReg,Key
		breq Lower

		cpi r16,1
		breq Higher

		cpi r16,2
		breq Lower

rjmp Main
