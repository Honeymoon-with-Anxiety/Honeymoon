;************************
;header file config timer
;************************
.equ clk_div_0		= (1<<CS00)
.equ clk_div_64 	= (1<<CS00)|(1<<CS01)
.equ clk_div_256	= (1<<CS02)



config_clock_div:
;	ldi TmpReg,(1<<CS00);|(1<<CS01)    ; clock select 
	out TCCR0, TmpReg

ret


config_top_val:
		ldi TmpReg, 32			;set overflow value
		out OCR0, TmpReg 
ret

