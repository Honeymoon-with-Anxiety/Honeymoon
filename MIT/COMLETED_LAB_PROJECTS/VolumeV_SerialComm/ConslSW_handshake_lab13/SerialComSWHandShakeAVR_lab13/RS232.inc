;RS232 definitions
;definitions for RS232 communications
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


;BOOL Open( int nPort = 2, int nBaud = 9600 );
;****** OPEN ******
;takes one argument since we only have one port
;the only argument is the baudrate
;******************
.MACRO open
.ENDMACRO
;****** END OPEN RS232 COM PORT

;BOOL Close( void );

;	int ReadData( void *, int );
;	int SendData( const char *, int );
;	int ReadDataWaiting( void );

;	BOOL IsOpened( void ){ return( m_bOpened ); }

;//protected:
;	BOOL WriteCommByte( unsigned char );