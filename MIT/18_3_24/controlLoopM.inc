increaseLoopM:
	inc loopM
	cpi loopM, 16
	brsh increaseLoopMReset
	rjmp retPoint
	increaseLoopMReset:
	clr loopM
	rjmp retPoint

decreaseLoopM:
	dec loopM
	cpi loopM, 0
	brsh decreaseLoopMReset
	rjmp retPoint
	decreaseLoopMReset:
	ldi loopM, 16
	rjmp retPoint
