#technicke_vybaveni_pocitacu
# Integrované periférie
* umožňují zpracování a manipulaci s různými druhy signálů
* klíčové pro komunikace, zpracování obrazu, zvuku aj.
* schopny rychlého zpracování signálů
* jsou často integrovány přímo do čipu
* jsou schopny zpracovávat signály v reálném čase
# Výhody a nevýhody
## Výhody
* CPU může zpracovávat různé druhy signálů (digitální i analogový)
* nové CPU obsahují více jader, což umožňuje paralelní zpracování více signálů současně
* CPU lze rozšiřovat pomocí různých periferií a rozšiřujících karet, což umožňuje připojení k dalším zařízením
* CPU jsou běžnější a jednodušší na nakupování a údržbu než specializované čipy, což může snížit náklady
## Nevýhody
* CPU jsou navrženy pro obecné úkoly a mohou mít omezený výkon pro určité aplikace, které vyžadují vysokou rychlost zpracování signálů (např. komprese, dekomprese, zpracování obrazu a zvuku)
* CPU mají tendenci mít vyšší latenci ve srovnání s specializovanými čipy, což může být problém pro aplikace, které vyžadují rychlou odezvu
* CPU obvykle vyžadují více energie než specializované čipy, což může být nevýhodné pro bateriově napájená zařízení
* Specializované čipy mohou být efektivnější než CPU, protože jsou optimalizovány pro konkrétní operace
# Kalibrace
* úprava výstupních hodnot aby odpovídali přesně daným hodnotám
* klíčový krok pro dosažení optimálního výkonu a přesnosti
* při kalibraci je dobré zvážit
	* přepracování kódu pro zpracování signálu může zvýšit efektivitu; použití vhodných algoritmů a datových struktur nebo vhodného programovacího jazyka
	* využití hardwarové akcelerace
	* použití správného CPU
	* využití více jader CPU
	* pravidelné testování a ladění
# Filtry
* CPU mohou být využity pro implementaci různých typů filtrů
* řád filtru určuje přesnost modelu přenosové charakteristiky filtru
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
* lze popsat dvěma způsoby, vnějším popisem a vnitřním popisem
	* vnější popis považuje systém za neznámý objekt; zobrazení: **vstup → výstup**
	* u filtru s vnitřním popisem známe strukturu systému; zobrazení: **vstup → stav systému → výstup**
# AD multiplex
* je [[MO4 Signály#AD]|AD převodník]] s multiplexorem
* multiplexor umožňuje přepínat mezi různými analogovými vstupy na jednom mikrokontroléru
* umožňuje jednomu MCU zpracovávat více analog. vstupů současně
* užitečný pro např. monitorování senzorů, zpracování zvuku
* snižuje náklady na výrobu desky plošných spojů
# Napěťová reference
* stabilní a přesně známá hodnota napětí
* slouží jako kalibrační bod
* používá se k určení přesné hodnoty napětí pro např. AD převodník
* obvykle el. obvod generující konstantní napětí s minimálním šumem
* další využití: přesné měření teploty, napětí a proudu, v zpracování obrazu a zvuku, další oblasti vyžadující přesné měření
![Typické použití napěťové reference během AD převodu](https://vyvoj.hw.cz/files/redaktor1396/01_9.png)
# Rekonstrukce a záznam signálu
## Rekonstrukce
* teoreticky je bezchybná pokud je dodržena [[MO4 Signály#Vzorkovací teorém|podmínka]] 
* obnova a generace analog. signálů na základě digi. dat
* MCU postupně posílá digitální vzorky které jsou konvertovány na odpovídající analogovou hodnotu
## Záznam
* analogový signál nejprve vzorkujeme
* poté převedeme AD převodníkem na digitální
* digi. signál pak zpracujeme podle potřeby
* pokud byl signál po vzorkování upraven, může být potřeba rekonstruovat signál (z digi. do analog)
* zrekonstruovaný signál lze pak uložit v různých formátech
# DA převodník pomocí PWM
* umožňuje rekonstrukci analog. signálu z digi. dat pomocí cyklické pulsní šířkové modulace (PWM)
* MCU musí mít vestavěný modul PWM
* PWM
	* technika používaná k regulaci průměrného výstupního napětí nebo průměrného výstupního proudu digi. signálu
	* řídí výkon nebo intenzitu nějakého zařízení
	* myšlenka spočívá v cyklickém střídání rychlých pulzů v digitálním signálu
	* doba ve kterém je impuls ve stavu "zapnuto," se nazývá šířka pulzu; průměrné napětí nebo proud na výstupu je řízen šířkou pulsů
	* užitečné pro řízení zařízení, která mají nepřerušovaný výstup, a umožňuje dosáhnout variabilního výkonu