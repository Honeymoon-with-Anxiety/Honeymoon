.CSEG
.EQU TCB_size 			= 5	;size in bytes of this block
.EQU SP_offset			= 0	;HW stack offset from the start of the block
.EQU FIRST_Time_offset	= 2	;status is: RUNNING,RUNNABLE,DELAYED,or WAITING
.EQU PRIO_offset		= 3	;priority of the task
.EQU DELAY_offset		= 4	;number of ticks to keep the task sleeping
.EQU pTCB_size			= 2	;size of the pointer to a TCB
.EQU STACK_SIZE_MAX		=50	;maximum size of the stack

.CSEG

.exit