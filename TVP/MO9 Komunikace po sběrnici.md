#technicke_vybaveni_pocitacu 
# Komunikace
## Synchronní
* přenosy se [[MO3 Počítačové architektury číslicových strojů#Synchronizace|synchronizují]] pomocí společného hodinového signálu *(CLK)*
* CLK
	* je generován [[MO8 Jednoduché sériové sběrnice#Základní typy|masterem]]
	* určuje, kdy mají být data čtena nebo zapsaná
	* určuje rychlost přenosu dat
* data jsou posílána v [[MO8 Jednoduché sériové sběrnice#Pakety|rámcích]]; obsahují bit určující čas čtení/zápisu
* přenosy jsou náchylnější na rušení elektromagnetickým polem; ztráty se objevují také i na přenosech ve velké vzdálenosti
## Asynchronní
* místo hodin komunikace používá dva signály navíc, zejména start a stop bity ke znázornění začátku a konce každého bytu dat
* zařízení mezi sebou komunikují různou rychlostí; rychlosti jsou nastavovány pomocí baudové rychlosti *(počet bitů přenesených za jednu sekundu; rychlost musí být stejně nastavená na obou stranách)*
* náchylnější na chyby dat; obsahuje [[MO6 Přenos informace#Parita|paritní bity]] sloužící k opravě chyb
# Přidělení sběrnice
## Obvody
* MUX
	* umožňují přepínat mezi vícero vstupy
	* mohou vybírat konkrétní zařízení, které se připojí ke sběrnici, nebo signál, který bude na sběrnici vyslán
* adresový dekodér
	* vstup dva či více bitů
	* pokud se na adresní sběrnici objeví adresa konkrétního zařízení, dekodér aktivuje výběrový vodič tohoto zařízení
	* každé zařízení může mít svůj dekodér, nebo může být jeden společný
		* pokud se dekodér používá pro více zařízení, dekodér s $n$ počtem bitů se dá použít až pro $2^n$ zařízení; obvod `74154` má 4 adresní vstupy, tudíž může obsloužit 16 zařízení ($2^4$)
	* někdy označována jako demultiplexor
	![Čtyři stavy dekodéru 2 na 4](https://upload.wikimedia.org/wikipedia/commons/8/8d/2to4demux.svg)
* enkodér priority
	* přiřazují prioritu zařízením na sběrnici
	* určující pořadí přenosu dat po sběrnici
* sběrnicový řadič
	* spravují přístup ke sběrnici
	* zajišťují koordinaci komunikace mezi periferními zařízeními
* signály řazení
	* k označení zařízení které může komunikovat na sběrnici
	* např.: Chip Select *(CS)*