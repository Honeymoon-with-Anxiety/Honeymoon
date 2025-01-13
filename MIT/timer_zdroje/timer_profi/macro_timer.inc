;********************************
;macro timer for simple timer lab
;********************************

.MACRO con_timer 
	ldi r16, @0
	ldi r17, @1
.ENDMACRO


.MACRO setup_timer
	ldi TmpReg, @0  
	rcall config_clock_div
	ldi r17, @1
.ENDMACRO
