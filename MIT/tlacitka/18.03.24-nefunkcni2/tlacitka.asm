;***************************************
.include "../template2.inc"
.include "../template3.inc"
;***************************************
.dseg
	displaySRAM: .byte 4
.cseg
;***************************************

; Definitions
.def selectedNumber = r16
.def Iterator = r17

; Constants
.equ Max_Number_Units = 9
.equ Max_Number_Tens = 9
.equ Max_Number_Hundreds = 15

; Subprograms
init_Y_seg:
    ldi YL, low (displaySRAM)
    ldi YH, high (displaySRAM)
ret

initDisplay:
    rcall init_Y_seg
    std Y+0, ZeroReg
    std Y+1, ZeroReg
    std Y+2, ZeroReg
    std Y+3, ZeroReg
ret

Main:
    ;seg_led_pwr_on
    ;rcall initDisplay

Main_Loop:
	rcall LedOn

	inc selectedNumber
    cpi selectedNumber, 255

	clr Key
	rcall mv_dig

	ldi DispPos, 3
	
	mov Scrap,Key
	out DispDataP, Scrap
    ; Row scan
    rcall row_scan
    ; Column scan
    rcall col_scan

	mov Scrap, Key

		ldi TmpReg,0b00010001
		and TmpReg,Scrap
		breq q17	

		ldi TmpReg,0b00010010
		and TmpReg,Scrap
		breq q18
q17:
    ; Display thousands digit (1st from the right)
	ldi DispPos, 3
    mov Iterator, selectedNumber

    mov Iterator, selectedNumber
    andi Iterator, 0b00001111  ; Limit to 0-15 range
    rcall disp

    ; Display hundreds digit (2nd from the right)
	ldi DispPos, 2
    mov Iterator, selectedNumber
    andi Iterator, 0b11100000  ; Extract hundreds digit
    swap Iterator               ; Move it to the rightmost position

    mov Iterator, selectedNumber
    andi Iterator, 0b00001111  ; Limit to 0-15 range
    rcall disp
	
    ; Display tens digit (3rd from the right)
	ldi DispPos, 1
    mov Iterator, selectedNumber
    andi Iterator, 0b00010000  ; Extract tens digit
    swap Iterator               ; Move it to the rightmost position

    mov Iterator, selectedNumber
    andi Iterator, 0b00001111  ; Limit to 0-15 range
    rcall disp

    ; Display units digit (4th from the right)
	ldi DispPos, 0
    mov Iterator, selectedNumber
    andi Iterator, 0b00001111  ; Limit to 0-15 range

    mov Iterator, selectedNumber
    andi Iterator, 0b00001111  ; Limit to 0-15 range
    rcall disp

    ; Increment selectedNumber and loop back to Main_Loop if not reached 255
    inc selectedNumber
    cpi selectedNumber, 255
    brne Main_Loop

    ; If reached 255, reset selectedNumber to 0 and loop back to Main_Loop
    clr selectedNumber
    rjmp Main_Loop

q18:
    ; Display thousands digit (1st from the right)
	ldi DispPos, 3
    mov Iterator, selectedNumber

    mov Iterator, selectedNumber
    andi Iterator, 0b00001111  ; Limit to 0-15 range
    rcall disp

    ; Display hundreds digit (2nd from the right)
	ldi DispPos, 2
    mov Iterator, selectedNumber
    andi Iterator, 0b11100000  ; Extract hundreds digit
    swap Iterator               ; Move it to the rightmost position

    mov Iterator, selectedNumber
    andi Iterator, 0b00001111  ; Limit to 0-15 range
    rcall disp
	
    ; Display tens digit (3rd from the right)
	ldi DispPos, 1
    mov Iterator, selectedNumber
    andi Iterator, 0b00010000  ; Extract tens digit
    swap Iterator               ; Move it to the rightmost position

    mov Iterator, selectedNumber
    andi Iterator, 0b00001111  ; Limit to 0-15 range
    rcall disp

    ; Display units digit (4th from the right)
	ldi DispPos, 0
    mov Iterator, selectedNumber
    andi Iterator, 0b00001111  ; Limit to 0-15 range

    mov Iterator, selectedNumber
    andi Iterator, 0b00001111  ; Limit to 0-15 range
    rcall disp

    dec selectedNumber
    cpi selectedNumber, 255
    brne rjmp_Main_loop

    clr selectedNumber
    rjmp rjmp_Main_loop
ret

rjmp_Main_loop:
	rjmp Main_loop
ret

disp:
		out DispDataP, Scrap
		ldi TmpReg, 0xFF
		out DispDataD,TmpReg

segment_display:
	.db	0b11000000, 0b11111001		; '0', '1'
	.db	0b10100100, 0b10110000		; '2', '3'
	.db	0b10011001, 0b10010010		; '4', '5'
	.db	0b10000010, 0b11111000		; '6', '7'
	.db	0b10000000, 0b10010000		; '8', '9'
	.db	0b10001000, 0b10000011		; 'A', 'B'
	.db	0b11000110, 0b10100001		; 'C', 'D'
	.db	0b10000110, 0b10001110		; 'E', 'F'
end_of_segment_display:
