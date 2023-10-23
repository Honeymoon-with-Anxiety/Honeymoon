.DSEG
.org 0x60
mystk:.BYTE pstk				;pointer to the stack
myLL: .BYTE pllist				;pointer to the linked list


run_q: .BYTE pllist
used_q:.BYTE pllist
pCur:.BYTE pllist


yourLL:.BYTE pllist
pCurTCB: .BYTE pTCB_size		;pointer to the currently running Task's control block
;ATCB: .BYTE TCB_size			;task A control block
;BTCB: .BYTE TCB_size			;task B control block
;ASTCK: .BYTE STACK_SIZE_MAX		;dedicated hardware stack of Task A 
;BSTCK: .BYTE STACK_SIZE_MAX		;dedicated hardware stack of Task B
.CSEG; continue with code going into flash


.MACRO ENTER_CRITICAL cli .ENDMACRO
.MACRO EXIT_CRITICAL  sei .ENDMACRO

.CSEG
.exit

;this defines the stacks 
;and queues i.e. the SRAM part 
;of the kernel