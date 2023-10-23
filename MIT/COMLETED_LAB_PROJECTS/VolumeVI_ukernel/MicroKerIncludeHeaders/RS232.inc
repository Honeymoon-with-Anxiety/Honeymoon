;RS232 definitions
;definitions for RS232 communication Driver
.EQU FC_DTRDSR      = 0x01
.EQU FC_RTSCTS      = 0x02
.EQU FC_XONXOFF     = 0x04
.EQU ASCII_BEL      = 0x07
.EQU ASCII_BS       = 0x08
.EQU ASCII_LF       = 0x0A
.EQU ASCII_CR       = 0x0D
.EQU ASCII_XON      = 0x11	;software handshake resume sending
.EQU ASCII_XOFF     = 0x13	;software handshake stop sending
.EQU START_TRANS	= 0x15	;start of transmission
.EQU END_TRANS		= 0x17	;end of transmission


;****** OPEN ******
; no arguments, since everything is
; hardcoded - which you may want to change
;******************
.MACRO open_RS232
;  	Enable receiver and transmitter and receive complete interrupt 
;	and data register empty interrupt (transmitter)
		ldi	TmpReg, (1<<RXCIE)|(1<<RXEN)|(1<<TXEN)|(1<<UDRIE)
		out	UCSRB, TmpReg

; Set no. of bits to 8 no parity
		ldi	TmpReg, (1<<URSEL)|(3<<UCSZ0)
		out	UCSRC, TmpReg

		ldi	TmpReg, BaudConst	; Set baud rate to BaudConst
		out	UBRRL, TmpReg
		out	UBRRH, ZeroReg

		;init the circular buffer for the RS232
		TIinit_circular_buffer CBuffIn, 0x8	;Written by RXC
		TIinit_circular_buffer CBuffOut, 0x8;Read by UDR
.ENDMACRO
;****** END OPEN RS232 COM PORT

;BOOL Close( void );
;******************
.MACRO close_RS232
;here just disable transmitter and receiver interrupts
.ENDMACRO 
;******** END CLOSE RS232 COM PORT


;************* read operation **********
;reads buffered RS232 port and returns the
;result in argument 0 register. You have to
;make sure there is something to read by
;calling the ReadDataWaiting Macro to see
;how many characters there are int the Q
;***************************************
.MACRO Read_RS232
	TIread_circular_buffer CBuffIn , @0
.ENDMACRO
;******** END READ DATA
	

;**** read data waiting operation *****
;check how many data pieces are there in
;in incoming buffer and returns their count
;in argument 0 register
;***************************************
.MACRO Read_Data_Waiting_RS232
	TIget_byte CBuffIn+TIcount_offset,@0
.ENDMACRO
;******** END READ DATA

;*********************************
;		WriteRS232 operation
;*********************************
;writes a byte to RS232 Port 
;the communication is buffered through out buffer
;label supplied as argument 0, and the byte
;is supplied as argument 1
.MACRO WriteRS232
	TIwrite_circular_buffer CBuffOut, @0
.ENDMACRO
;******** END SEND DATA

;int ReadDataWaiting( void );
;****************************
.MACRO ReadDataWaitingRS232
.ENDMACRO
