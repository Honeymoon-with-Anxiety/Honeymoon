#technicke_vybaveni_pocitacu 
* fyzická zařízení určená k ukládání programů nebo dat pro okamžitou nebo trvalou potřebu
* rozdělení fyzických zařízení
	* vnitřní - RAM
	* vnější - ukládání programů a dat
* vnitřní paměť uložená v vnější se nazývá "virtuální" paměť *(nebo swap)*

![[TVP_23_1_24.png]]
* energetické rozdělení
	* nezávislé *(nevolatilní)* - Flash (vnější i vnitřní), ROM/PROM/EPROM/EEPROM (pro uložení firmware)
	* závislé *(volatilní)* - vnitřní paměť DRAM a vyrovnávací (SRAM)
* paměťové médium popisuje vnější paměť jako je např.: magnetopáska, optický disk (CD/DVD)
# Operační paměť
* slouží k ukládání dat po dobu běhu programu
* přístup k op je rychlejší než přístup k vnější paměti
* procesor pomocí adresy vybírá požadovanou buňku
* paměť je spojena s procesorem pomocí rychlé sběrnice; mezi op a procesor se vkládá ještě [[M13 Paměť#Paměť cache|cache]]
* dnes realizována jako polovodičová paměť typu RAM; ztrácí informace při odpojení napájení; obsah paměti je třeba občerstvovat čtením všech řádků
* je spravován operačním systémem
* uchovává kód programů (kód procesů a jejich mezivýsledky), základní datové struktury kernelu, atd.
* Fyzický adresový prostor *(FAP)* paměti je souvislý prostor paměťových buněk určité velikosti (1, 2, 4 nebo 8 bytů); buňky jsou lineárně adresovány adresami pevné délky; velikost buňky je dána délkou adresy (adresa $n$ bytů; buněk $2^n$); celý FAP nemusí být vyplněn; některé bloky se mohou objevit vícekrát
* správa paměti
	* přidělení paměť. regionu na požádání procesu
	* uvolnění regionu na požádání procesu
	* udržení informace o obsažení adresového prostoru
	* zabránění přístupu procesu k paměti mimo jeho přidělený region
	* podpora střídavého běhu více procesů
* architektury
	* [[MO3 Počítačové architektury číslicových strojů#Von Neumannova architektura|Von Neumannova]]

  ![Schéma Von Neumannovy architektury](https://upload.wikimedia.org/wikipedia/commons/4/4a/Von_Neumannova_architektura_PC.svg)
	* [[MO3 Počítačové architektury číslicových strojů#Harvardská architektura|Harvardská]]

  ![Schéma Harvardské architektury PC](https://upload.wikimedia.org/wikipedia/commons/1/17/Harvardska_architektura.svg)
  * metody správy
	  * monolitická
		  * FAP je rozdělen na dva bloky
			  * jeden provádí rutiny kernelu a jeho datové struktury - "Kernel memory"
			  * druhý je přiřazen na požádání aplikacím - "Application memory"
		  * je-li paměť volná, je přidělena procesu celá bez ohledu na požadovanou velikost (nesmí přesáhnout velikost bloku); v obsazené paměti je požadavek zamítnut
	  * statické bloky
		  * paměť je rozdělena do několika bloků o pevné velikosti, které lze samostatně alokovat
		  * maximální počet procesů je omezen počtem bloků; proces může přesahovat jeden blok
		  * velikost bloku se liší podle využití
		  * ochranu zajišťuje limitní registr procesoru - v registru je uložena hodnota aktuálního paměťového regionu; hodnota lok. adresy se porovnává s hodnotou registru; pokud je hodnota větší je vyvolaná výjimka *(`proces se pokouší zapsat mimo region`)*
	  * dynamická
		  * paměť je rozdělena na bloky jejichž velikost se dynamicky upravuje dle požadavků procesů; před alokací prvního regionu tvoří paměť aplikačního prostoru jeden blok
		  * po uvolnění bloků je nutné provádět scelování volných bloků
		  * obsazení paměti je realizováno na počátku každého bloku jakousi hlavičku
		  * paměť je chráněna limitním registrem
# Paměť cache
* součást, která uchovává často používaná data a tím zrychluje přístup k nim
* od bufferu se liší tím, že data uchovává (buffer je jen přestupní bod)
* je tvořena rychlejší a dražší pamětí → menší velikost (než úložný prostor ke kterému zrychluje přístup)
* lze ji najít
	* hardwarově - v mikroprocesorech, pevných discích; tvořena paměťovými obvody
	* softwarově - v operační paměti; řízena jádrem OS; vytvořená programově
* vynalezena v 1. pol. 60. let 20. st.
* př.: cache webového prohlížeče uchovává objekty (obrázky aj.; neměnné) pro rychlejší načtení při otevření stránky - nestahují se znovu z internetu
  ## softwarová
* obvykle jako vyrovnávací paměť pro pomalé vnější paměti (pevný disk počítače)
* OS se snaží často používané informace ukládat do cache v co nejvýhodnějším pořadí
* je přidělena dynamicky - podle množství volné paměti a potřeb systému
* rizikem je nepředvídatelný výpadek napájení
	* stav datových souborů na disku není vždy aktuální a musí se synchronizovat s obsahem cache
	* proto OS vyžadují před vypnutím proces `shutdown` který korektně ukončí procesy systému a uloží obsah diskového cache do souborů na disku
	* před odpojením je důležité odmountovat vyměnitelná média jinak může dojít k poškození souborového systému
	* moderní systém se snaží problém eliminovat zapomocí žurnálů
  ## hardwarová
* v řídících jednotkách vyrovnává rozdíl mezi nepravidelným předáváním/přebíráním dat sběrnicí a pravidelným tokem dat do/z magnetických hlav
* obvod je tvořen z tranzistorů a její funkcí je vyrovnávat rozdílnou rychlost mezi procesorem a operační pamětí
* vyšší rychlostí lze dosáhnout použitím kvalitnějších tranzistorů a položením blíže k procesoru
# Paměť flash
* je energicky nezávislá a elektricky zapisovatelná
* organizována po blocích (1 blok = [?] bytů); každý blok lze programovat samostatně
* používá se jako paměť typu ROM např. pro uložení firmware
* lze ji znovu naprogramovat bez nutnosti vyjmutí čipu
* využívá se v přenosném datovém médiu (např.: SD karta, USB Flash disk, SSD disky)
* princip ukládání
	* data jsou ukládána v unipolárních tranzistorech (1 tranzistor = 1 bit *(SLC)* / 3+ bitů *(MLC)*); SLC nabízí větší rychlost a stabilitu, MLC naopak větší kapacitu a menší cenu
	* tranzistor obsahuje dvě hradla - ovládací *(CG)* a plovoucí *(FG)* izolované vrstvou oxidu; všechny elektrony na FG přivedené jsou zde „uvězněny“, tím je informace uchována
	* když jsou na FG elektrony, částečně ruší el. pole přicházející z CG, což modifikuje prahové napětí $U_t$ buňky
	* buňka je aktivována přivedením určitého elektrického napětí na CG, což ovlivňuje elektrický proud tranzistorem; tento proud proudí, nebo neproudí, což závisí na úrovni $U_t$ buňky, která je závislá na množství elektronů na hradle FG
	* přítomnost nebo nepřítomnost elektrického proudu je interpretována jako log.  `1` nebo `0`
  ![Struktura tranzistoru s plovoucím hradlem.](https://upload.wikimedia.org/wikipedia/commons/d/d3/FLASH_RAM-Cell.svg)
# EEPROM
* elektricky mazatelnou energeticky nezávislou paměť typu ROM-RAM
* typická životnost je 200 000 zápisů (ATmega16) (víc než flash); životnost dat je 20 let
* nevýhodou je vyšší složitost paměťové buňky → nižší hustota → vyšší cena
* využívá se jako úložiště dat, která se mění častěji než je životnost paměti flash (např. nastavení hlasitosti u TV)
* používá tranzistory vyrobené technologií MNOS; na řídící elektrodě je nanesena vrstva nitridu křemíku a pod ní je umístěna tenká vrstva oxidu křemičitého
* buňka paměti pracuje na principu vkládání elektrického náboje na přechod těchto dvou vrstev
# Paměťová buňka
## statická
* uchovává informaci v sobě uloženou po celou dobu, kdy jsou připojeny ke zdroji elektrického napájení
* má rychlý přístupový čas, což znamená, že data lze číst nebo zapisovat rychle
* používá bistabilní klopný obvod k uložení informace
## dynamická
* uchovává informaci v sobě uloženou i po odpojení zdroje elektrického napájení
* vyžaduje periodickou obnovu informace aby se zabránilo ztrátě dat
* používá malého náboje uloženého v kondenzátoru k uložení informace
* levnější na výrobu
# Klopné obvody
* elektronický obvod, který přechází mezi několika stavy
* ke změně mezi stavy dochází skokově
* skládají z hradel
* lze je použít jako např.: paměťové prvky, impulzní generátory, časovače nebo oscilátory
* astabilní
	* nemají žádný stabilní stav
	* obvody neustále oscilují mezi jedním a druhým stavem podle nastavené časové konstanty

  ![Realizace astabilního klopného obvodu z diskrétních součástek](https://upload.wikimedia.org/wikipedia/commons/6/6a/Transistor_Multivibrator.svg)
* monostabilní
	* jeden stabilní stav
	* sám se po určité době přepne zpět do stabilního stavu

  ![Realizace monostabilního klopného obvodu z diskrétních součástek](https://upload.wikimedia.org/wikipedia/commons/5/59/Transistor_Monostable.svg)
* bistabilní
	* dva stabilní stavy
	* mezi stavy lze přepínat pomocí signálů přivedených na vstupy
	* obvody se používají jako paměťové prvky

![Realizace bistabilního klopného obvodu typu RS z diskrétních součástek](https://upload.wikimedia.org/wikipedia/commons/9/98/Transistor_Bistable.svg)
* Schmittův
	* slouží k úpravě tvaru impulzů
	* základní vlastností je hystereze
	* výstup je závislý nejen na hodnotě vstupu, ale i na jeho původním stavu
	* hystereze zde zabraňuje vzniku zákmitů výstupního signálu v okolí střední úrovně spínání

![Realizace Schmittova klopného obvodu z diskrétních součástek](https://upload.wikimedia.org/wikipedia/commons/9/94/Schmitt_with_transistors.svg)
# Registry
  * 
# Latence
  * 
# Volatilita
  * 
# Přepisovatelnost
  * 
# Synchronní a asynchronní