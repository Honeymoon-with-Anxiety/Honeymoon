---
tags:
  - technicke_vybaveni_pocitacu
---
# Integrované periférie
* umožňují zpracování a manipulaci s různými druhy signálů
* klíčové pro komunikace, zpracování obrazu, zvuku aj.
* schopny rychlého zpracování signálů
* jsou často integrovány přímo do čipu
* jsou schopny zpracovávat signály v reálném čase

# Výhody a nevýhody
## Výhody
1) CPU může zpracovávat různé druhy signálů (digitální i analogový)
2) nové CPU obsahují více jader, což umožňuje paralelní zpracování více signálů současně
3) CPU lze rozšiřovat pomocí různých periferií a rozšiřujících karet, což umožňuje připojení k dalším zařízením
4) CPU jsou běžnější a jednodušší na nakupování a údržbu než specializované čipy, což může snížit náklady
## Nevýhody
1) CPU jsou navrženy pro obecné úkoly a mohou mít omezený výkon pro určité aplikace, které vyžadují vysokou rychlost zpracování signálů (např. komprese, dekomprese, zpracování obrazu a zvuku)
2) CPU mají tendenci mít vyšší latenci ve srovnání s specializovanými čipy, což může být problém pro aplikace, které vyžadují rychlou odezvu
3) CPU obvykle vyžadují více energie než specializované čipy, což může být nevýhodné pro bateriově napájená zařízení
4) Specializované čipy mohou být efektivnější než CPU, protože jsou optimalizovány pro konkrétní operace
# Kalibrace
* klíčový krok pro dosažení optimálního výkonu a přesnosti
* při kalibraci je dobré zvážit
	* přepracování kódu pro zpracování signálu může zvýšit efektivitu; použití vhodných algoritmů a datových struktur nebo vhodného programovacího jazyka
	* využití hardwarové akcelerace
	* použití správného CPU
	* využití více jader CPU
	* pravidelné testování a ladění
# Filtry
* CPU mohou být využity pro implementaci různých typů filtrů
* filtr s nízkou propustí
	* propouští signály s frekvencemi nižšími než určitý práh; potlačuje vyšší frekvence
	* používán v audio technice pro potlačení šumu nebo vyhlazení signálu
* filtr s vysokou propustí
	* propouští signály s frekvencemi vyššími než určitý práh; potlačuje nižší frekvence
	* použit pro izolaci vyšších frekvencí
* pásmový filtr
	* propouští signály v určitém frekvenčním pásmu; potlačuje všechny ostatní
* filtr na potlačení šumu
	* používá se k potlačení šumu v signálu
	* implementován různými algoritmy
* filtr pásmové přenosové funkce
	* navržen tak, aby propouštěl signály v určitém pásmu frekvencí; potlačuje signály mimo pásmo
	* užíván pro selektivní filtrování
* filtr s konečnou odezvou
	* mají pevný počet koeficientů
	* používány pro vyhlazování
 
![Příklad blokového schématu FIR filtru, který realizuje klouzavý průměr.](https://upload.wikimedia.org/wikipedia/commons/d/d2/FIR_Filter_%28Moving_Average%29.svg)

* filtr s nekonečnou odezvou
	* mají zpětnou vazbu
	* použity pro zesílení nebo odstranění oscilací
* adaptivní filtr
	* mohou se sami aktualizovat na základě signálu
	* užitečné při potlačení echa nebo adaptivní potlačení šumu
# A/D multiplex
* je [[MO4 Signály#AD]|AD převodník]] s multiplexorem
* multiplexor umožňuje přepínat mezi různými analogovými vstupy na jednom mikrokontroléru
* užitečný pro např. monitorování senzorů, zpracování zvuku
# Napěťová reference
* stabilní a přesně známá hodnota napětí
* slouží jako kalibrační bod
* používá se k určení přesné hodnoty napětí pro např. AD převodník
* obvykle el. obvod generující konstantní napětí s minimálním šumem
* další využití: přesné měření teploty, napětí a proudu, v zpracování obrazu a zvuku, další oblasti vyžadující přesné měření
![Typické použití napěťové reference během AD převodu](https://vyvoj.hw.cz/files/redaktor1396/01_9.png)