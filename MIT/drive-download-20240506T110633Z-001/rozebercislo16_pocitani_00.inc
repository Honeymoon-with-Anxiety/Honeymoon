.DSEG
soucasna_uprava: .byte 1	;velikost kterou budu aplikovat k soucasnemu cislu
velikost_upravy: .byte 1 ;typ operace jako +-*/ 
.CSEG
;set_num16_SRAM	;jsou jako 	makra ve rozebercislo hlavicce
;get_num16_SRAM	;			makro ve rozebercislo

.equ plus 		= 0b00000000
.equ minus		= 0b00000001
.equ division	= 0b00000010
.equ multip		= 0b00000011

;jak to volat jednoduse?
;init_Y soucasna_uprava
.MACRO init_Y
	ldi YL, low(@0)
	ldi YH, high(@0)
.ENDMACRO


;pozor... operation as a constant
.MACRO set_operation
	push YH
	push YL
	push r16
		init_Y soucasna_uprava
		ldi r16, @0
		ST Y, r16
	pop r16
	pop YL
	pop YH
.ENDMACRO

;the operation will be loaded 
;into the register supplied as
;argument 0
.MACRO get_operation
	push YH
	push YL
		init_Y soucasna_uprava
		LD @0, Y
	pop YL
	pop YH
.ENDMACRO

;amount to be supplied in a register
.MACRO set_amount_change
	push YH
	push YL
		init_Y velikost_upravy
		ST Y, @0
	pop YL
	pop YH
.ENDMACRO

;read the amount into register
;supplied as arg 0 (@0)
.MACRO get_amount_change 
	push YH
	push YL
		init_Y velikost_upravy
		LD @0, Y
	pop YL
	pop YH
.ENDMACRO

;initialize soucasna_uprava na plus
.MACRO init_operation
	push YH
	push YL
	push r16
		init_Y soucasna_uprava
		ldi r16, plus
		ST Y, r16
	pop r16
	pop YL
	pop YH
.ENDMACRO


;init velikost upravy na 1
.MACRO init_velikost_uprava
	push YH
	push YL
	push r16
		init_Y velikost_upravy
		ldi r16, 1
		ST Y, r16
	pop r16
	pop YL
	pop YH
.ENDMACRO


;modify the 16-bit number in SRAM
;with the operation and the amout
;of change
.def amount_of_change	= r19
.def numH				= r18
.def numL				= r17
.def operation2do		= r16
.def TmpL				= r16
.def TmpH				= r19
.def ZeroReg			= r0
pocitani16_uprav_cislo:
	push ZeroReg
	push operation2do
	push numL
	push numH
	push amount_of_change

		clr ZeroReg
		get_operation operation2do
		get_num16_SRAM numH, numL
		get_amount_change amount_of_change
		cpi r16, plus
		breq addition_uprav_cislo_16
			;subtract here
			sub numL, amount_of_change
			sbc numH, ZeroReg
			rjmp done_execute_operation_16
		addition_uprav_cislo_16:
			add numL, amount_of_change
			adc numH, ZeroReg

		done_execute_operation_16:
		;gotta make sure the number 
		;is withing 0 and 9999. If not,
		;I will reset it to 0000
		ldi TmpL, low(10000)
		ldi TmpH, high(10000)
		cp numL, TmpL
		cpc numH, TmpH
		brsh pocitani_reset_num16
			;lets check less than zero...
			clr TmpL
			clr TmpH
			cp numL, TmpL
			cpc numH, TmpH
			brlt pocitani_reset_num16
				rjmp done_uprav_cislo_16
			
		pocitani_reset_num16:
			clr numL
			clr numH

		done_uprav_cislo_16:
			set_num16_SRAMr numH, numL

	pop amount_of_change
	pop numH
	pop numL
	pop operation2do
	pop ZeroReg
ret
