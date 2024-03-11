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

# Konfigurace
* 
# Použití přerušení
## pro externí periférie
* 
## pro integrované periférie
* 
# Víceúlohové operační systémy
* 
# Fronta procesů
* 
# Vřeteno, čítač, přepínání
* 