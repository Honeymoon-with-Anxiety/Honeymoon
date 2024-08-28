.DSEG
number16: 			.byte 2	;stores the 16-bit number to ripup into digits
number16_digits:	.byte 4	;stores the four digits of the 16-bit number
.CSEG

;********* makra pro rozebrani cisla na cislice
.MACRO set_num16_SRAM
	push r16
	push r17
	push YH
	push YL

		ldi r16, low(@0)
		ldi r17, high(@0)
		ldi YL, low(number16)
		ldi YH, high(number16)
		std Y+0, r17
		std	Y+1, r16

	pop YL
	pop YH
	pop r17
	pop r16
.ENDMACRO

;makro pro nacteni 16-bit cisla do par
;r17:r16 kde CH:CL
.MACRO get_num16_SRAM
	push YH
	push YL

		ldi YL, low(number16)
		ldi YH, high(number16)
		ldd  @0, Y+0	;HIGH
		ldd	 @1, Y+1	;LOW

	pop YL
	pop YH
.ENDMACRO

.MACRO clear_SRAM_display
	push ZeroReg
	push YH
	push YL	

		clr ZeroReg
		ldi YL, low(number16_digits)
		ldi YH, high(number16_digits)
		std Y+0, ZeroReg
		std	Y+1, ZeroReg
		std Y+2, ZeroReg
		std	Y+3, ZeroReg

	pop YL
	pop YH
	pop ZeroReg
.ENDMACRO

.MACRO init_Y_number16_digits
	ldi YL, low(number16_digits)
	ldi YH, high(number16_digits)
.ENDMACRO

;assumes the Y pointer is initialized
.MACRO store_thousands
	st Y, @0
.ENDMACRO

.MACRO read_thousands
	ld @0, Y
.ENDMACRO

.MACRO store_hundreds
	std Y+1, @0
.ENDMACRO

.MACRO read_hundreds
	ldd @0, Y+1
.ENDMACRO

.MACRO store_tens
	std Y+2, @0
.ENDMACRO

.MACRO read_tens
	ldd @0, Y+2
.ENDMACRO

.MACRO store_units
	std Y+3, @0
.ENDMACRO

.MACRO read_units
	ldd @0, Y+3
.ENDMACRO

;****************************
;  ROZEBER CISLO 16 BITOVE
;****************************
;JE POTREBA ABY: 
;1. CISLO BYLO ULOZENO V SRAM 
;   V DECIMALU
;2. ZeroReg byl inicializovan
;   na nulu
;****************************
.def ZeroReg		= r0
.def counter_rc_16 	= r18
.def thousands_L	= r19; one of the pair of registers storing 1000
.def thousands_H	= r20; one of the pair of registers storing 1000
.def hundreds		= r19; recycled register to store 100
.def tens			= r19
;******************************
;	R O Z E B E R  C I S L O  * 16-BIT	
;******************************
rozeber_cislo_16:
push r0
push r16
push r17
push counter_rc_16
push thousands_L
push thousands_H

	clr ZeroReg
	clr counter_rc_16
	ldi thousands_H, high(1000)
	ldi thousands_L, low(1000)
	init_Y_number16_digits	; initialize Y pointer to the digits to display block
	get_num16_SRAM r17, r16	; using r17:r16
	loop_rc_16_THOUSANDS:
		cp r16, thousands_L
		cpc r17, thousands_H
		brlo loop_rc_store_1000s
		sub r16, thousands_L
		sbc r17, thousands_H
		inc counter_rc_16
		brsh loop_rc_16_THOUSANDS 
		loop_rc_store_1000s:
			store_thousands counter_rc_16	;storing 1000s
			
			clr counter_rc_16
			ldi hundreds, 100
			loop_rc_16_HUNDREDS:
				cpi r16, 100
				cpc r17, ZeroReg
				brlo loop_rc_store_100s
				sub r16, hundreds
				sbc r17, ZeroReg
				inc counter_rc_16
				brsh loop_rc_16_HUNDREDS
				loop_rc_store_100s:
					store_hundreds counter_rc_16 ;storing 100s
					
					clr counter_rc_16
					ldi tens, 10
					loop_rc_16_TENS:
						cpi r16, 10
						brlo loop_rc_store_tens
						sub r16, tens
						inc counter_rc_16
						brsh loop_rc_16_TENS
						loop_rc_store_tens:
							store_tens counter_rc_16 	;storing 10s
							store_units r16				;storing 1s

pop thousands_H
pop thousands_L
pop counter_rc_16
pop r17
pop r16
pop r0

ret

