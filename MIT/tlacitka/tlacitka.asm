;===========================================================;
;						  INCLUDES  						;
;===========================================================;

.include "M16.inc"
.include "LedOn.inc"
.include "Scan.inc"
.include "Delay.inc"
.include "SegmentUp.inc"
.include "SegmentDown.inc"
.include "Disassemble2.inc"

;.include "./includes/M16"
;.include "./includes/LedOn"
;.include "./includes/Scan"
;.include "./includes/Delay"
;.include "./includes/SegmentUp"
;.include "./includes/SegmentDown"
;.include "./includes/Disassemble"

;===========================================================;
;							MAIN							;
;===========================================================;

Higher:
	ldi r16, 1
	com r16
	out portA,r16
	rcall SegmentUp
	ldi r16,1
rjmp Main;m

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
rjmp Main;m

Dex:
	ldi r23,8
	com r23
	out portA,r23
	ldi r23,0
rjmp Main;m

Main:	

	ldi PDelReg, 200

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

		ldi TmpReg,0b00010100
		and TmpReg,Key
		breq Hex
		
		ldi TmpReg,0b00011000
		and TmpReg,Key
		breq Dex
		
		cpi r16,1
		breq Higher

		cpi r16,2
		breq Lower
		
rjmp Main10		


