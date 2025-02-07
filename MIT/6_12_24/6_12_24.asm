.include "templateM16.inc"
.include "makra.inc"
.include "display.inc"

;====== Register definitions =======
;ZeroReg = r0
;ADCReg = r16
;MaskReg = r17
;Cislo = r18
;TmpReg = r19
;number = r20
;PDelReg = r21
;PDelReg0 = r22
;PDelReg2 = r23
;PDelReg1 = r24

.DSEG
disp_RAM: .byte 4
.CSEG

Main:
	clr number
	in ADCReg, ADCH
	
	adiw XL, 1
	adc XH, ZeroReg
	
	mov r26, XH
	mov r27, XL
	
	rcall initDisplay
	rcall rozeberNaCislice
	rcall initZCharTable
	
	loop:
		in number, ADCH
		rcall rozeberNaCislice
		
		ldd selectedChar, Y+0
		ldi PDelReg, 5
		rcall Delay1m
		digit_hundreds_ON
		rcall zobrazovaciPodprogram
		
		ldd selectedChar, Y+1
		ldi PDelReg, 5
		rcall Delay1m
		digit_tens_ON
		rcall zobrazovaciPodprogram

		ldd selectedChar, Y+2
		ldi PDelReg, 5
		rcall Delay1m
		digit_units_ON
		rcall zobrazovaciPodprogram
rjmp Main

display:
.db 0b11000000,0b11111001 ;0,1
.db 0b10100100,0b10110000 ;2,3
.db 0b10011001,0b10010010 ;4,5
.db 0b10000010,0b11111000 ;6,7
.db 0b10000000,0b10010000 ;8,9
.db 0b10001000,0b10000011 ;A,b
.db 0b11000110,0b10100001 ;C.d
.db 0b10000110,0b10001110 ;E,F
konec_display:
