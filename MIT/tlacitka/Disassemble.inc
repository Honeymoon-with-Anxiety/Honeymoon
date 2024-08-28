;++++++++++++++++++++++++++++;
;     DISASSAMBLE NUMBER     ;
;++++++++++++++++++++++++++++;

disassamble_number11:
	cpi r23,0
	breq disassamble_number3


;++++++++++++++++++++++++++++;
;    DISASSAMBLE NUMBER 2    ;
;++++++++++++++++++++++++++++;

disassamble_number2:	
	clr Accuracy
	ldi r19, high (4095)
	ldi r18, low (4095)
	cp  r20, r18
	cpc  r24, r19
	brlo Hundreds12

	Thousands21:
		inc Accuracy
		sub r20, r18
		sbc r24, r19
		cp  r20, r18
		cpc  r24, r19
		brsh Thousands21

	std Y+Thousands, Accuracy
	clr Accuracy

	Hundreds12:
		ldi r19, high (255)
		ldi r18, low (255)
		cp  r20, r18
		cpc  r24, r19
		brlo Tens1

	Hundreds2:
		inc Accuracy
		sub r20, r18
		sbc r24, r19
		cp  r20, r18
		cpc  r24, r19
		brsh Hundreds2

	std Y+Hundreds, Accuracy
	clr Accuracy

	Tens1:	
		ldi r19, high (16)
		ldi r18, low (16)
		cp  r20, r18
		cpc  r24, r19
		brlo Units122

	Tens121:
		inc Accuracy
		sub r20, r18
		sbc r24, r19
		cp  r20, r18
		cpc  r24, r19
		brsh Tens121
	
	std Y+Tens, Accuracy
	clr Accuracy
	
	Units122:
		ldi r19, high (1)
		ldi r18, low (1)
		cp  r20, r18
		cpc  r24, r19
		brlo Done2

	Units12:
		inc Accuracy
		sub r20, r18
		sbc r24, r19
		cp  r20, r18
		cpc  r24, r19
		brsh Units12
	
	Done2:
	std Y+Units, Accuracy
ret

;++++++++++++++++++++++++++++++;
;     DISASSAMBLE NUMBER 3     ;
;++++++++++++++++++++++++++++++;

disassamble_number3:		
	clr Accuracy
	ldi r19, high (1000)
	ldi r18, low (1000)
	cp  r20, r18
	cpc  r24, r19
	brlo Hundreds111

	Thousands11:
		inc Accuracy
		sub r20, r18
		sbc r24, r19
		cp  r20, r18
		cpc  r24, r19
		brsh Thousands11

	std Y+Thousands, Accuracy
	clr Accuracy

	Hundreds111:
		ldi r19, high (100)
		ldi r18, low (100)
		cp  r20, r18
		cpc  r24, r19
		brlo Tens111

	Hundreds11:
		inc Accuracy
		sub r20, r18
		sbc r24, r19
		cp  r20, r18
		cpc  r24, r19
	brsh Hundreds11

	std Y+Hundreds, Accuracy
	clr Accuracy

	Tens111:	
		ldi r19, high (10)
		ldi r18, low (10)
		cp  r20, r18
		cpc  r24, r19
		brlo Units111

	Tens11:
		inc Accuracy
		sub r20, r18
		sbc r24, r19
		cp  r20, r18
		cpc  r24, r19
		brsh Tens11
	
	std Y+Tens, Accuracy
	clr Accuracy
	
	Units111:
		ldi r19, high (1)
		ldi r18, low (1)
		cp  r20, r18
		cpc  r24, r19
		brlo Done11

	Units11:
		inc Accuracy
		sub r20, r18
		sbc r24, r19
		cp  r20, r18
		cpc  r24, r19
		brsh Units11
	
	Done11:
	std Y+Units, Accuracy
ret

.exit
