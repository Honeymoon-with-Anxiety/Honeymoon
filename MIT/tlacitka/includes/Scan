scan:
	ldi TmpReg, 0x0F
	out DispDataD,TmpReg

	nop nop nop
	in TmpKey, DispDataI
	or Key, TmpKey
		
	ldi TmpReg, 0xF0
	out DispDataD,TmpReg

	nop nop nop nop nop
	in TmpKey, DispDataI
	or Key, TmpKey
	eor Key,TmpReg

	ldi TmpReg, 0xFF
	out DispDataD,TmpReg
ret

.exit
