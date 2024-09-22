#technicke_vybaveni_pocitacu 
* ovlivňuje výkon procesoru
* umožňuje paralelní zpracování sad instrukcí
* klasifikace procesorů
	* podle architektury
		* RISC
			* skromný soubor instrukcí = delší zdroj
			* jedna instrukce - jedna operace
			* levnější
			* např. ARM
		* CISC
			* rozsáhlý soubor instrukcí = kratší zdroj
			* instrukce jsou složité; dokážou provádět mnoho operací
			* dražší
			* např. x86
	* podle počtu jader
		* jednojádrové
		* vícejádrové
	* účel použití
		* běžné - široké spektrum užití
		* specializované - pro specifický účel; např: pro GPU, NPU *(síťová komnunikace)*
	* podle taktovací frekvence
	* podle výrobní technologie
		* velikost tranzistorů
		* méně nanometrů = víc tranzistorů = větší výkon 😃
	* podle spotřeby energie
	* podle [[MO3 Počítačové architektury číslicových strojů|architektury paměti]]
# Výkon procesoru
* ovlivněn taktem - kolik operací procesor provede za jednu sekundu; v Hz
* počet jader - umožňuje paralelní zpracování více úloh současně bez potřeby přetaktování
* architektura - jak složité instrukce jsou
* cache paměť - velikost a efektivní správa cache ovlivňuje rychlost přístupu k datům
# Programátorský model procesoru
* práce na úrovni nízkého prog. jazyka
* abstraktní pohled na procesor umožňující psát software bez nutnosti znalosti architektury procesoru
* instrukční soubor definuje instrukce které procesor dokáže provádět
* registr je malá, rychlá paměť umístěná přímo na čipu procesoru; kolik registrů má takový procesor, jejich uspořádání a pojmenování
* nativní datové typy procesoru (8-bitový Byte; 16-bitový Word; atd.)
* procesor má mnoho režimů
	* uživatelský - limituje přístup k některým registrům a instrukcím
	* jádra - přístup ke všemu
* model popisuje, jak postupovat při [[M10 Základní cyklus počítače#Výjimečné stavy při běhu CPU|výjimečný stavech]]
* jak pracovat se zásobníkem
* popisuje jak jsou adresy paměti generovány, jak k nim procesor přistupuje a jak jsou dlouhé
* může zahrnovat speciální instrukce nebo adresovací schémata pro komunikaci s periférií
* zahrnuje jak pracovat s více jádry procesoru
# Kompatibilita na úrovni strojového kódu
* schopnost spustit stejný zdrojový kód na vícero architekturách
* pokud dva procesory mají stejný instrukční soubor, může být stejný kód spuštěn na obou procesorech
* kompatibilita nemusí být plně zachována mezi procesory s odlišnou architekturou → nemusí mít stejný počet jader nebo podporovat zpracování ve vláknech
# Evoluce instrukční sady
* první generace se zaměřovala na jednoduché instrukce a zvýšení taktu procesoru
* s potřebou většího výkonu se začaly vyrábět vícejádrové RISC procesory
* vyvynuta pokročilejší technologie pipelinů
* přidány instrukce pro šifrování
* snaha vytvoření otevřené RISC architektury (RISC-V)
# Vliv jader procesoru
## na software
* správně navržený software může zpracovávat instrukce o mnoho rychleji díky paralelnímu zpracování
* databáze mohou využívat více jader k vyhledávání, třídění a filtrování
* vícejádrové procesory mají různé energetické profily a mohou dynamicky měnit počet aktivních jader v závislosti na aktuálních potřebách
## na hardware
* architektura čipu musí umět pracovat s vícero jádry včetně sdílení paměti, atd.
* je lepší minimalizovat latenci přístupu k paměti
* procesory mohou generovat více tepla
* každé jádro má vlastní sadu registrů a frontu instrukcí
# Jednočip
* elektronické zařízení integrující všechny nezbytné funkce a komponenty na jediný čip
* integrace všech klíčových prvků na jeden čip vede k fyzickému zmenšení a menší komplexitě; užitečné ve spotřební a mobilní elektronice
* může vést ke snížení nákladu a spotřebě
* vývoj s jednočipem je jednodušší protože vývojáři pracují již s uceleným kouskem namísto s několika komponentami
# Kombinačni logika
* minimalizace složitosti instrukční sady a optimalizace provádění jednoduchých operací
* implementuje jednoduché operace, jako jsou aritmetické operace, logické operace a porovnávání
* každý stupeň pipelingu potřebuje vlastní kombinační logiku
* řídí tok instrukcí; provádí dekódování instrukcí a rozhoduje, která operace bude provedena v daném okamžiku; řeší otázky jako skoky (branching) a volání procedur
# Paměťové prvky
* ukládání a přístup k datům v procesoru
* registry
	* malé a velmi rychlé paměťové prvky přímo vestavěné v jádrech procesoru
	* slouží k ukládání proměnných nebo mezivýsledků během vykonávání instrukcí
	* RISC architektura obvykle obsahuje omezený počet registrů
* cache
	* slouží k ukládání často používaných dat a instrukcí
	* snadno dostupné pro procesor
* RAM
	* slouží k ukládání programů a dat, která nejsou momentálně využívána procesorem
	* přístup prostřednictvím adresového a datového busu
* buffer - slouží k dočasnému ukládání dat (např. při přenosu mezi různými částmi procesoru nebo mezi procesorem a periferními zařízeními) ^buffer
* instrukční cache - ukládá často používané instrukce programu
* datová cache - ukládá často používaná data
* paměťově mapované registry - speciální registry, jejichž hodnoty mohou ovlivňovat chování periferních zařízení nebo konfiguraci procesoru
* registry ukazatelů - slouží k uchování adres v paměti, které jsou používány při práci s daty nebo skoky v programu
# Synchronní stroj
* všechny operace v procesoru jsou řízeny hodinovým signálem; každá část obvodu provádí svou činnost v přesně definovaný čas
* snadnější synchronizace mezi různými částmi procesoru a periferními zařízeními
* hardware může být relativně jednoduchý a efektivní
* instrukce jsou prováděny v přesně stanovených taktových cyklech, které odpovídají hranám hodinového signálu
* chování synchronních strojů je předvídatelné a opakovatelné → snadnější návrh a analýza digitálních obvodů
# Popis obrázku
![](https://www.alrj.org/images/riscv/Pipeline_summary.png)
Instrukce uložená v `Memory` je načtena podle ukazatele Program Counteru *(`PC`)*. Načtená instrukce je následně do tabulky registru *(`Register File`)* a dekódována pro zjištění typu instrukce *(např. Aritmeticko-logická)*. Po zjištění typu instrukce, pokud je aritmeticko-logická, je instrukce přesunuta do Aritmeticko-logické jednotky *(`ALU`)* kde je vykonána instrukce, výsledek je přesunut do paměti. Výsledek uložený paměti může být odeslán jako konečný výsledek nebo se vrátní zpět na začátek pro další zpracování. Instrukce typu Přístup k paměti a Skoky jsou spouštěny specializovanou jednotkou pipeliny.