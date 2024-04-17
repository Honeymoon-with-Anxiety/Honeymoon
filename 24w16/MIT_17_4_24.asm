.include "../templateM16.inc"

/*
0) zdroj rozdělit podle fce
1) nechci trvale držet data v registrech - málo registrů
2) nechci COEZI
3) zkusit roz<něco> s SRAM
4) zkusit ukládání na zásobník

rozdělit číslo
zobrazit číslo
detekce kb
reagování na kb
*/

; Makra
;	pro rozebrani na cislice
	.MACRO setNum16SRAM
		push r16
		push r17
		push YH
		push YL
		
		ldi r16, low(@0)
		ldi r17, high(@0)
		ldi YL, low(number16)
		ldi YH, high(number16)
		std Y+0, r17
		std Y+1, r16
		
		pop YL
		pop YH
		pop r17
		pop r16
	.ENDMACRO
	.MACRO getNum16SRAM ; načtení 16-bit čísla z SRAM (r17:r16 >> CH:CL)
		push YH
		push YL
		
		ldi YL, low(number16)
		ldi YH, high(number16)
		ldd @0, Y+0
		ldd @1, Y+1
		
		pop YL
		pop YH
	.ENDMACRO
	.macro clearDisplay
		push ZeroReg
		
		clr ZeroReg
		ldi YL, low(number16Digits)
		ldi YH, high(number16Digits)
		
		pop ZeroReg
	.endmacro

.DSEG
	number16: .byte 2 ; uchovává 16-bit číslo pro rozebráni na číslice
	number16Digits: .byte 4
.CSEG

Main:
	setNum16SRAM 1000
	getNum16SRAM r18, r17
rjmp Main
