#technicke_vybaveni_pocitacu 
* schopnost procesoru přerušit právě vykonávaný program a začít vykonávat jiný program
* začalo se implementovat do procesorů z důvodu obsluhy periferii
* procesor je rychlejší než ostatní hw → kdyby se zabýval pouze obsluhou, nebyl by využit a většinu času by jen čekal na hw
* volání dvěma způsoby
	* software - při dekódování instrukce `int`
	* hardware - vnějším okolím
# Rozdělení podle původu
* hardwarové
	* vyvolána fyzickými událostmi; signály přicházející z hw zařízení (klávesnice, myš...)
	* periferní zařízení - generována např.: sériovými porty, USB zařízeními, zvukovými či grafickými kartami
	* časovač - používána k periodickým úkolům jako je spouštění přerušení v pravidelných intervalech
	* I/O - vyvolané v případě dokončení čtení/zápisu z/do zařízení, chybě čtení/zápisu...
* software
	* generována operačním systémem nebo aplikacemi
	* použita k signalizaci událostí (chyby, výjimky...)
	* výjimky - vyvolány nějakým abnormálním stavem běhu programu (dělení nulou, přetečení, přístup k neplatné paměti...)
	* systémová volání
# Řadič přerušení
* el. obvod vyřizující přicházející přerušení podle priority kterou řídí
* priorita
	* pevná
	* rotující - procesor střídavě zpracovává různá přerušení podle jejich prioritní úrovně; vyvážení zátěže mezi zdroji přerušení
	* kaskádovitá - vyšší úroveň přerušení může přerušit zpracování nižší úrovně
* monitoruje [[M15 Přerušení CPU#Rozdělení podle původu|různé zdroje]] přerušení a registruje je
* stará se o správné přepnutí kontextu a uchovává stav běžícího programu
* po identifikaci a určení priority přerušení obslouží
* po obsloužení navrátí řízení zpět původnímu běžícímu programu
# Maskování a priorita
* maskování
	* proces umožňující ignorovat určitá přerušení - procesor nezaregistruje příchozí signál
	* užitečný pro řízení zpracování přerušení a prioritizaci událostí
	* využíván z důvodu synchronizace a zabránění nežádoucím interferencím mezi různými částmi systému
	* prostředky
		* globální - úplné zakázání všech přerušení
		* na úrovni přerušení - specifická pro jednotlivá přerušení
		* dle priority
		* programovatelné časy - doba, po kterou jsou přerušení maskována
	* hardwarové
		* obvod přímo v procesoru
		* umožňuje nastavit masku pro každý jednotlivý typ či skupinu přerušení
		* procesor nevyvolá obslužnou rutinu a nevykoná žádné akce spojené s přerušením
	* softwarové
		* pomocí instrukcí v procesoru nebo operačního systému
		* využívané v určitých situacích, jako je kritická sekce kódu
* priorita
	* rychlá reakce na událost, která je důležitá pro správné fungování systému
	* která maskování mají přednost při
		* maskování
		* obsluze
	* podle typu přerušení - SW nebo HW
	* při přerušení se mohou měnit priority v závoslosti na podmínkách a požadavcích systému
# Postup při vzniku a obsluha
![Schéma obsluhy hardwarového přerušení](https://upload.wikimedia.org/wikipedia/commons/3/3a/Obsluha_preruseni.gif)
* vznik
	1) generování signálu - periferní zařízení (senzory, komunikační rozhraní...) generujíc signál oznamující událost vyžadující pozornost CPU
	2) zápis do registru přerušení - procesor identifikuje zdroj přerušení a zapíše jeho identifikátor do registru
	3) zmrazení běžícího kódu - procesor pozastaví běžící kód a uloží jeho kontext do paměti pro pozdější obnovení
	4) přepnutí do režimu obsluhy
* obsluha
	* je asynchronní událost umožňující IO zařízením získat pozornost procesoru nezávisle na právě prováděné činnosti
	* obvykle součástí ovladačů zařízení, které se instalují do operačního systému, ale také součástí procesoru
	* příklad: čtení dat z disku
		1) když disk dostane za úkol přečíst určitá data, nemusí procesor čekat, až pomalé zařízení příslušná data připraví pro vyzvednutí (do vyrovnávací paměti zařízení)
		2) V okamžiku, kdy jsou data v zařízení připravena, vyvolá zařízení přerušení
		3) procesor dokončí právě prováděnou strojovou instrukci a pomocí tabulky přerušení je vyvolána obsluha přerušení pro zařízení, které o přerušení požádalo
		4) obsluha přerušení nejprve na vhodné místo v operační paměti uložit stav procesoru a jeho registry, aby přerušený proces po návratu nic nepoznal
		5) po uložení stavu procesoru a registrů, které obsluha přerušení bude používat, dojde k vlastní obsluze zařízení → data jsou z vyrovnávací paměti zařízení odebrána
		6) po provedení obsluhy zařízení je obnoven stav procesoru a procesor pokračuje ve vykonávání programu v místě, kde došlo k přerušení
# Konfigurace
* identifikace - určení události nebo signálu který má být zachycen jako přerušení (dokončení IO operací, přerušení časovačem, signály od periferních zařízení)
* přiřazení priority - nastaveno podle důležitosti a časových požadavků
* nastavení obslužných rutin - vytvoření ob. rutin pro každý typ přerušení *(obslužná rutina je kód spuštěný po vyvolání přerušení)*
* nastavení vektorů přerušení - definování adres nebo indexů obslužných rutin v přerušovací vektorové tabulce
* testování a ladění - ověření správné konfigurace a funkcionality pro zjištění správné obsluhy a minimalizaci chyby
# Použití přerušení
## pro externí periférie
* často využíváno k zachycení příchozích dat z UART portu *(sběrnice pro asynchronní sériový přenos)* nebo k oznámení dokončení přenosu dat
* reakce na signály vyvolané senzorem
* vyvolané časovačem každou periodu nebo po uplynutí určitého času; užité např. pro generování periodických signálů
* při interakci s uživatelem prostřednictvím tlačítek, myši nebo jiném způsobu inputu zachycuje stisknutí tlačítka, podržení, puštění...
## pro integrované periférie
* ADC - přerušení vyvolané při dokončení převodu, chybě převodu
* časovače - přerušení s určitou periodou nebo po dosažení určité hodnoty; využívá se k řízení časových událostí, generování periodických signálů nebo měření času mezi událostmi
* sběrnice - detekce adresy zařízení, dokončení přenosu dat, přetečení bufferu nebo detekce chyby v komunikaci
# Víceúlohové operační systémy
* plánování úloh pomocí priority; určuje který proces má právo být spuštěn nebo pokračovat
* detekce systémových událostí jako je vypršení časovače, příjem síťového paketu, dokončení IO operace nebo pohybu myši a psaní na klávesnici či jiné řízení vstupu
# Fronta procesů
* řízení a plánování běžících procesů na základě kritérií a algoritmů
* obvykle ve formě seznamu seřazené podle nějakého kritéria (podle priority, času příchodu či stavu)
* uchovává informace o stavu (běží, připraven, čeká, ...) každého procesu
* užit k synchronizaci a koordinaci částí systému; např. nutné čekání na dokončení operace
# Čítač, přepínání
* čítač
	* inkrementuje se nebo dekrementuje se
	* když čítač dosáhne určité hodnoty nebo přeteče
	* periodické přerušení - generace přerušení s periodou odpovídající časovému intervalu; využívané pro časová měření a periodické operace
	* přerušení po dosažení určité hodnoty
	* obslužní rutina může například vynulovat čítač, nastavit novou max hodnotu
	* často využito v časovačích
* přepínání
	* přepínání mezi různými úrovněmi a typ přerušení v reakci na události v systému; změna kontextu z běžícího procesu na obsluhu přerušení
	* pokud je proces právě obsluhován a vyžaduje delší dobu zpracování, může být vyvoláno další přerušení s vyšší prioritou nebo kratší dobou zpracování
	* v rámci obsluhy jednoho přerušení může dojít k vyvolání dalšího přerušení
	* když dojde k přerušení, tato událost je zaregistrována a současný proces se pozastaví
	* aktuální stav běžícího procesu je uložen do registru a  je vyvolaná obsluha
	* po obsloužení operační systém obnoví kontext původního běžícího procesu nebo vybere jiný proces k provedení