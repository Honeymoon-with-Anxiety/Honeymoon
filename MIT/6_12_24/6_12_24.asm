.include "templateM16.inc"

.DSEG
disp_RAM: .byte 4
.CSEG

Main:
	
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
