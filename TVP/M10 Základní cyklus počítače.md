#technicke_vybaveni_pocitacu 
* obvykle se nazývá "fetch-decode-[execute](https://www.youtube.com/watch?v=ESx_hy1n7HA) cycle"
* popisuje zk. kroky opakované při každé instrukci
* architektura RISC má omezený počet instrukcí na základní a jednoduché
1) čtení *(fetch)*
	* instrukce se načtou z paměti
	* adresa instrukce k provedení je uložena v registru Program Counter *(PC)*
	* instrukce se načte adresy z PC do Instruction Register *(IR)*
2) dekódování *(decode)*
	* načtená informace *(v IR)* obsahuje operační kód *(opcode)* a další informace
	* během dekódování jsou jednotlivé části instrukce identifikovány pro další zpracování
	* pomocí opcode je určeno, jakou operaci instrukce představuje
	* pokud instrukce potřebuje operandy, dekódování je identifikuje a připraví k použití
3) provedení *([execute](https://www.youtube.com/watch?v=ESx_hy1n7HA))*
	* vykonává operaci definovanou dekódovanou instrukcí (např.: aritmetické operace, logické operace, přesuny dat, skoky nebo další)
	* po provedení instrukce se aktualizují stavové registry obsahující informace o procesoru (např. přetečení)
	* výsledky operací jsou zapsány do registrů nebo do paměti
4) zásah do paměti
	* umožňuje procesoru přistoupit k paměti
	* adresa je buď předem určena nebo je vypočtena na základě aktuálních hodnot v registrech; adresa je následně odeslána na paměťovou sběrnici
	* hodnota z interních *([[#Pipeline registr|pipeline]])* registrů je zapsána na adresu
	* po zápisu se aktualizují stavové bity *(bity ovlivňující následující průběh programu)*
	* dojde k aktualizaci PC aby ukazovala na další instrukci v paměti
* aktualizace PC
	* PC může být automaticky inkrementován po provedení každé instrukce (např. instrukce programu jsou uloženy za sebou v paměti, po provedení instrukce se PC zvedne o jeden → ukazuje na další instrukci v paměti)
	* při skoku (`jump`) nebo větvení (`branch`) se hodnota PC mění na základě logické podmínce; pokud je podmínka splněna, PC ukazuje na adresu, kde má program pokračovat
	* při volání (`call`) se adresa následující instrukce (adresa návratu) uloží na zásobník a adresa PC je změněna ukazujíc na první instrukci podprogramu; po provedení podprogramu je (návratová) adresa další instrukce načtena ze zásobníku do PC
	* při přerušení je PC aktualizován na adresu uloženou při volání podprogramu
	* v případě výjimky je adresa PC změněna na adresu obslužné rutiny výjimky; po obsluze výjimky může být adresa PC změněna na pokračování běhu programu
# Výjimečné stavy při běhu CPU
* stavy které mohou vyžadovat speciální pozornost či manipulaci
* přerušení *(interrupt)*
	* přerušují běžný tok programu
	* vyžadují okamžitou pozornost procesoru
	* vyvolána externím zařízením, chybou programu nebo samotným programem úmyslně
	* pro obsluhu přerušení musí procesor přepnout kontext a reagovat na příslušné události
* výjimky *(exception)*
	* podobné přerušení
	* jedná se o chybový stav
	* vyžadují zvláštní opatření
	* procesor musí přepnout na obsluhu výjimky a přijmout opatření k řešení problému
	* např.: dělení nulou, přetečení při aritmetických operacích nebo přístup k neplatné paměti, broken pipeline
* přepínání kontextu *(context switch)*
	* nastává když běžící proces na CPU je pozastaven a CPU přepíná svůj kontext na jiný proces
	* informace (registry, program counter, adt.) pozastaveného procesu jsou uloženy do paměti
	* informace jsou následně aktualizovány aby odpovídaly novému procesu
* stav úspory energie *(halt)*
	* nastává když CPU přechází do režimu nízké spotřeby nebo je dočasně zastaven
	* neprovádí žádné instrukce a čeká na další pokyny
* bezpečnostní režim *(privileged mode)*
	* CPU má vyšší úroveň oprávnění než v normálním uživatelském režimu
	* má přístup k systémovým zdrojům (speciální registry, instrukce nebo přímý přístup k hardwaru)
* chyby přístupu do daměti *(memory access violations)*
	* program přistoupí k neplatné paměti nebo s ní provede nepovolenou operaci
	* např. pokus o čtení nebo zápis do neexistující adresy paměti
# Formát instrukce
* AVR používá specifický formát založený na RISC formátu
* instrukce v AVR arch. jsou 16bitové
* instrukce
	* typu R *(-egistr)*
		* pracuje s registry
		* provádí aritmetické nebo logické operace
		* `opcode | Rd | Rr`
			* `opcode` → identifikační číslo operace
			* `Rd` → cílový registr (a zároveň zdrojový)
			* `Rr` → zdrojový registr
	* typu I *(-mmediate)*
		* pracuje s konstantami
		* konstanty jsou uloženy přímo v instrukci
		* `opcode | Rd | K`
			* `K`  → konstanta
	* typu J *(-ump)*
		* pro řízení toku programu
		* `opcode | d`
			* `d` → adresa destinace skoku

![Instruction Format of RISC](https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Ftse2.mm.bing.net%2Fth%3Fid%3DOIP.IuwuxpM8SHz8ayVylTbtPwHaGO%26pid%3DApi&f=1&ipt=dceadc4fabacf92783c3696efdc116e935698c9284822c63c2f931e661793a29&ipo=images)
# Operační
## jednotka
* aritmetické a logické operace provádí odděleně od těch ostatních
* instrukce jsou navrženy aby byly jednoduché; vyžadují minimální počet cyklů pro provedení
* každá instrukce provádí pouze jednu konkrétní operaci
* maximalizuje paralelní zpracování; navrženy pro nezávislé vykonávání vedoucí k rychlejšímu výpočtu
* pracuje pouze s daty v registrech; pokud data nejsou v registru, zapíše je
* pevně definovaná šířka slova
## znak
* základní strojový kód říkající procesoru, jakou operaci má provést
* "*operátor*"
	* v kontextu programování se jedná o symbol či zkratku reprezentující operaci (např.: `ADD` - sčítání; `SUB` - odčítání; `AND` - logický AND; `OR` - logický OR; `MOV` - přesun dat; `JMP` - nepodmíněný skok)
	* operátory jsou následně převedeny do binární podoby
	* operátory závisí na konkrétním RISC procesoru
# Pipeline registr
* speciální druh registrů používaný pro pipelining
* pipelining - technika umožňující provádění několik fází instrukce současně
* každá fáze má svůj registr; slouží k uložení mezikroků
* broken pipeline - situace, kdy je normální tok instrukcí v pipeline přerušen nebo narušen; obvykle vyžaduje nějakou formu opravy nebo obnovení pipeline do normálního stavu
* má minimálně 17 bitů
# Řadič
* dekóduje instrukce z paměti
* připravuje interní obvody pro provedení instrukcí
* řídí takt procesoru; určuje prioritu provedení instrukce
* spravuje přístup čtení a zápisu do paměti
* řídí tok dat v datových cestách
* detekuje stav výjimek a přerušení; popřípadě dokáže vyřešit [[#Výjimečné stavy při běhu CPU|neobvyklé stavy]]
* provádí skoky a podmíněné instrukce
* zodpovídá za plynulý a synchronní pohyb instrukcí skrz pipeline
## Dekodér
* interpretuje instrukce z programové paměti a připravuje připravuje je k provedení
* čte instrukce a převádí je do procesorem čitelné formy
* identifikuje a připravuje operandy (např. načtení hodnot z registrů/paměti)
* počítá adresy pro skoky
* identifikuje výjimky
* dekóduje paralelně s pipeline a zajišťuje aby každá fáze proběhla správně
# Hazardy
* nežádoucí situace, které mohou nastat v průběhu vykonávání instrukcí
* mohou vést k nesprávným výsledkům nebo nekonzistentním stavům obvodu
* mohou vzniknout v důsledku asynchronních vlastností obvodů nebo specifických vlastností instrukční sady a způsobu, jakým jsou instrukce provedeny
* datové harazdy
	* nastávají, když existuje závislost mezi dvěma instrukcemi ohledně datového zápisu nebo čtení
	* Read-After-Write Hazard *(RAW)* - čtení instrukce následuje po zápisu do stejného umístění v paměti nebo registru
	* Write-After-Read Hazard *(WAR)* - zápis instrukce následuje po čtení ze stejného umístění
	* Write-After-Write Hazard *(WAW)* - dva zápisy následují po sobě do stejného umístění
* řídící hazardy
	* nastávají, když je rozhodování o tom, která instrukce má být provedena, ovlivněno předchozími výsledky nebo podmínkami
	* zahrnuje koky, podmíněné větve nebo jiné mechanismy řízení toku instrukcí
* strukturální hazardy
	* vznikají, když je fyzická struktura obvodu nebo zařízení nesprávně přizpůsobena prováděným operacím
	* např. nedostatkem hardwarových zdrojů, jako jsou registry, ALU