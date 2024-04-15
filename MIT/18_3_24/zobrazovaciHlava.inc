initZ:
    ldi ZL, low(2*segmentovka)
    ldi ZH, high(2*segmentovka)
ret

nactiCislo:
    rcall initZ
    add ZL, selectedChar
    adc ZH, ZeroReg
ret

zobrazCislo:
    lpm TmpReg, Z
    out DispDataP, TmpReg
ret

zobrazovaciPodprogram:
    rcall nactiCislo
    rcall zobrazCislo
ret
