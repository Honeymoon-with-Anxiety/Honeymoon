.DSEG
.org 0x60	
					;put the following definitions at the start of SRAM
pCurTCB: .BYTE pTCB_size		;pointer to the currently running Task's control block
ATCB: .BYTE TCB_size			;task A control block
BTCB: .BYTE TCB_size			;task B control block
ASTCK: .BYTE STACK_SIZE_MAX		;dedicated hardware stack of Task A 
BSTCK: .BYTE STACK_SIZE_MAX		;dedicated hardware stack of Task B
.CSEG; continue with code going into flash




.exit

;this defines the stacks 
;and queues i.e. the SRAM part 
;of the kernel