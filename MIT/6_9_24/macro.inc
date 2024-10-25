;noprescaling
.equ div_1    = (1<<CS00)
;prescaler /8
.equ div_8    = (1<<CS01)
;prescaler /64
.equ div_64   = (1<<CS01)|(1<<CS00)
;prescaler /128
.equ div_256  = (1<<CS02)
;prescaler /256
.equ div_1024 = (1<<CS02)|(1<<CS00)

;set top value
.macro top_val_config
        push TmpReg
	ldi TmpReg, @0
	out OCR0, TmpReg
	out TCNT0, ZeroReg
        pop TmpReg
.endmacro

;set clock divident
.macro clock_div_config
	in r17, TCCR0
	andi r17, 0b11111000
	ldi r16, @0
	or r17, r16
	out tccr0, r17
.endmacro

;set timer
.macro timer_config
	top_val_config @0
	clock_div_config @1 	
.endmacro
