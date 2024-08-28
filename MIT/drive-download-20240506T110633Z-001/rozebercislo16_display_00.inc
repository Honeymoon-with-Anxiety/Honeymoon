;*******************************************
;	this is the display header
;*******************************************
;asi to budete chtit preorganizovat a 
;kultivovat...
;a je to testovano pouze castecne
;*******************************************



;**************************
;add port_config to RESET..
;**************************
port_config:
		out DDRA, ZeroReg		; set the unused to input
		out DDRB, ZeroReg
		out PortA,TmpReg		; enable pullups
		out PortB, TmpReg		; enable pullups

		ldi	TmpReg, 0xFF
		out	DDRC, TmpReg		; set direction of port C (all outputs)
		out	DDRD, TmpReg		; set direction of port D (all outputs)

		out	PortC, ZeroReg		; set port C to 0x00 (disable all pull-ups)
		out	PortD, ZeroReg		; set port D to 0x00 (disable all pull-ups)
ret

;========= Register definitions ==========
.EQU DispDataP = PortC  ;display data port
.EQU DispDataD = DDRC	;display data direction register
.EQU DispDataI = PinC	;display data coming in to port C
.EQU DispCtrlP = PortD	;display data control (the three pins) port

.MACRO seg_led_pwr_on 
	sbi DispCtrlP, 4
.ENDMACRO

.MACRO seg_led_pwr_off
	cbi DispCtrlP, 4
.ENDMACRO

.MACRO digit_units_ON
	sbi DispCtrlP,3
	sbi DispCtrlP, 2
.ENDMACRO

.MACRO digit_tens_ON
	sbi DispCtrlP,3
	cbi DispCtrlP, 2
.ENDMACRO	

.MACRO digit_hundreds_ON
	cbi DispCtrlP,3
	sbi DispCtrlP, 2
.ENDMACRO

.MACRO digit_thousands_ON
	cbi DispCtrlP,3
	cbi DispCtrlP, 2
.ENDMACRO


.DEF	ZeroReg		= r0
.DEF 	inReg		= r15


;registers used in delay functions
.DEF	PDelReg0	= r21
.DEF	PDelReg1	= r22
.DEF	PDelReg2	= r23
;*********************** Delay (PDelReg[ms]) *********************
;put the amount of milisec as argument 0 for the macro
.MACRO Delay1mM
	push PDelReg2
	push PDelReg1
	push PDelReg0
		ldi PDelReg2, @0
		Delay1m0:	ldi	PDelReg0, 20
		Delay1m1:	ldi	PDelReg1, 245
		Delay1m2:	dec	PDelReg1
				brne	Delay1m2
				dec	PDelReg0
				brne	Delay1m1
				dec	PDelReg2
				brne	Delay1m0
	pop PDelReg0
	pop PDelReg1
	pop PDelReg2
.ENDMACRO
;******************************** end delay function *****************
;****************************** display number ***********************
;This function displays a number (in Hex). 
;It assumes that the number is loaded in offset register, so 
;if the number to be displayed is 3 offset has to equal to 3. 
;
;The character codes are read from CharTab, which is a table
;for segment LED codes.
;********************************************************************
DispChar:	
		ldi	ZH, high(2 * CharTab)	; Convert TmpReg to apropriate character and
		ldi	ZL, low(2 * CharTab)	; display it on LED display.
		add	ZL, offset				; add offset to table base address
		adc	ZH, ZeroReg
		lpm	TmpReg, Z	;load program memory pointed to by Z into TmpReg
		out	DispDataP, TmpReg;send it to the port
ret
;********************** end display number ************************ 

;********************** begin display off *************************
;turns off the display
LedOff:
		in		TmpReg, DispCtrlP	
		andi	TmpReg, 0b11101111
		out		DispCtrlP, TmpReg
		ret
;*********************** end turn off the display *****************

;*********************** begin led on *****************************
;turns on the led display
LedOn:
		in 		TmpReg, DispCtrlP
		andi 	TmpReg, 0b11110011
		ori 	TmpReg, 0b00010000
		out 	DispCtrlP, TmpReg
		ret
;************************ end led on ******************************




;jak volat makra? 
;set_operation plus
.DEF	TmpReg		= r17	;temporary register / scratch pad
.DEF	offset		= r19	;used in reading and writing bytes  
show_units_16:
	read_digit16 _units_16, offset
	digit_units_ON
	rcall DispChar ;code in TmpReg
	Delay1mM 5
ret

show_tens_16:
	read_digit16 _tens_16, offset
	digit_tens_ON
	rcall DispChar ;code in TmpReg
	Delay1mM 5
ret

show_hundreds_16:
	read_digit16 _hundreds_16, offset
	digit_hundreds_ON
	rcall DispChar ;code in TmpReg
	Delay1mM 5
ret

show_thousands_16:
	read_digit16 _thousands_16, offset
	digit_thousands_ON
	rcall DispChar ;code in TmpReg
	Delay1mM 5
ret

zobraz_cislo_16:
	init_Y number16_digits	;init Y to sram block where the digit component of the number to display
							;is stored
	seg_led_pwr_on
	rcall show_units_16
	rcall show_tens_16
	rcall show_hundreds_16
	rcall show_thousands_16
ret


;************************ character table
CharTab:	.db	0b11000000, 0b11111001		; '0', '1'
			.db	0b10100100, 0b10110000		; '2', '3'
			.db	0b10011001, 0b10010010		; '4', '5'
			.db	0b10000010, 0b11111000		; '6', '7'
			.db	0b10000000, 0b10010000		; '8', '9'
			.db	0b10001000, 0b10000011		; 'A', 'B'
			.db	0b11000110, 0b10100001		; 'C', 'D'
			.db	0b10000110, 0b10001110		; 'E', 'F'

