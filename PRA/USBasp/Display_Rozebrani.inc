.def cislo = r16
.def accu = r17

.DEF	PDelReg		= r20
.DEF	PDelReg0	= r21
.DEF	PDelReg1	= r22
.DEF	PDelReg2	= r2

;*********************************
.dseg
	disp_RAM: .byte 4
.cseg
;*********************************

.equ jednotky_offset = 3

number_break_up:
		clr accu

	
	
;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++	
	jedna1:
		
		ldi r19, high (1)
		ldi r18, low (1)

		cp  r20, r18
		cpc  r24, r19
		brlo done


	jedno:
		inc accu

		sub r20, r18
		sbc r24, r19

		cp  r20, r18
		cpc  r24, r19
		brsh jedno
	
	done:
		std Y+jednotky_offset, accu
ret
;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
jednotky:
	ldi r20, 0b00011100
	out portA, r20
	clr r18
	ldd r19, Y+jednotky_offset	
	add ZL, r19
	adc ZH, ZeroReg
	lpm r18, Z		
	out portB,r18

	ldi PDelReg, 1
	rcall Delay1m
ret

vymazat_disp:
	std Y+jednotky_offset, ZeroReg
	
ret

init_Y_displ_RAM:
	ldi YL, low(disp_RAM)
	ldi YH, high(disp_RAM)
ret

init_Z_na_moje_tabulka:
	ldi ZL, low(2*display)
	ldi ZH, high(2*display)
ret

segment:	
	clr cislo
	ldi r25, 1

	adiw XL, 1
	adc XH, ZeroReg
	
	mov r24, XH
	mov r20, XL
	
	rcall init_Y_displ_RAM
	rcall vymazat_disp
	rcall number_break_up
	
	rcall init_Z_na_moje_tabulka
		

	loop:
		inc cislo
		rcall jednotky
		rcall init_Z_na_moje_tabulka

		cpi r16, 200
		brne loop
ret

;==================================================

;************** Delay (PDelReg[ms]) ***************

Delay1m:	mov	PDelReg2, PDelReg
Delay1m0:	ldi	PDelReg0, 20
Delay1m1:	ldi	PDelReg1, 245
Delay1m2:	dec	PDelReg1
		brne	Delay1m2
		dec	PDelReg0
		brne	Delay1m1
		dec	PDelReg2
		brne	Delay1m0
ret
