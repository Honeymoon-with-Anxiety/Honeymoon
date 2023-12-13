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
## Základní techniky
* centrální řízení
	* jedno zařízení zvoleno jako master
	* ostatní zařízení musí čekat, až budou mít právo přistoupit ke sběrnici
	* neefektivní, pokud je činnost na sběrnici vysoká
* prioritní arbitrace
	* každé zařízení má přidělenou prioritu
	* vyšší priorita má přednost
* Round Robin
	* imaginární token putuje mezi zařízeními
	* zařízení má nastavený časový úsek, jak dlouho může mít "u sebe" token
	* zařízení s tokenem smí přistoupit ke sběrnici
	* po uplinutí časového úsek u "předá" token na další zařízení
* token passing
	* podobný jako Round Robin ale bez časového úseku
	* čeká se, až zařízení odešle všechna data
* sběrnicové řadiče
* stavový automat
# Multiplexovaná sběrnice
* několik zřízení sdílí fyzické médium přenosu dat
## [[MO4 Signály#časový|Časově]]
* zařízení je přiřazen časový slot, kdy může posílat/přijímat data
* časové sloty mohou být
	1) statické - čas. slot je pevně daný
	2) dynamické - čas. slot se mění podle potřeby
* ostatní zařízení musí čekat na svůj čas. slot
* výhodou je snížení konfliktů o přístup ke sběrnici, jednoduchá implementace a efektivní využití přenos. média
![Multiplex s časovým dělením](https://upload.wikimedia.org/wikipedia/commons/e/e0/Telephony_multiplexer_system.gif)
## [[MO4 Signály#frekvenční|Frekvenčně]]
* signálům jsou přiřazené různé frekvence kmitočtového pásma po kterých jsou vysílané
* je možné realizovat amplitudovou [[MO6 Přenos informace#Modulace|modulací]]
* vysílání obsahuje více frekvencí současně
* datové toky jsou následně kombinovány do komplexního signálu
![Přenos tří signálů pomocí kmitočtového dělení](https://upload.wikimedia.org/wikipedia/commons/f/f1/Frequenzmultiplex001.svg) *Schutzbänder = ochranné pásmo*
## Prostorově
* na základě fyzického oddělení (v prostoru); není potřeba časového nebo frekvenčního multiplexu
* signály jsou přenášeny nezávisle ve vlastních fyz. cestách → minimální interference mezi jednotlivými kanály
* používá MIMO technologii *(Multiple Input, Multiple Output)* - více antén pro příjem/přenos signálů současně
* schopnost přenosu dat z různých zdrojů do různých cílů
## Vlnovou délkou
* používá se v optické komunikaci
* datový tok je rozdělen do několika vlnových délek (každá délka představuje jeden komunikační kanál)
* možnost přenosu více nezávislých dat. toků na jednom optickém vlákně (obousměrně)
* různé signály používají různé frekvence
* Wavelength Division Multiplexing *(WDM)*
	* muliplexer ve vysílači pro spojení signálů dohromady; demutiplexer v přijímači pro následné rozdělení
	* první WDM umělo kombinovat pouze dva signály; dnes až 160 signálů
	* umožňují rozšiřovat kapacitu sítě bez nutnosti pokládání dalších opt. vláken
	* Dense WDM *(DWDM)*
		* vlnové délky přiřazeny s velmi malými mezerami
		* umožňuje přenos velkého množství dat
	* Coarse WDM *(CWDM)*
		* vlnové délky přiřazeny se širšími mezerami
		* obvykle pro menší množství kanálů na jednom vláknu