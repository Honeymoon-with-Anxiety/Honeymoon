#technicke_vybaveni_pocitacu 
* vložené systémy
	* jakékoliv zařízení ovládané počítačem
	* změna funkce zařízení se provede změnou programu (HEX) → ISP (in system programming)
	* proč je vložený systém výhodné řešení? - rychlejší návrh a levnější realizace
	* nevýhoda je omezená rychlost procesoru
	* jednoúčelový počítač kde je řídicí systém zcela zabudován do ovládaného zařízení
	* na rozdíl od univerzálních počítačů jsou vložené systémy určené pro předem definované činnosti
* analýza
	* rozkládání na funkční části (každá část se může dál rozkládat)
	* rozbor dané události nebo jevu z hlediska příčin a důsledků jejich jednotlivých prvků a taktéž jejich vstupů a výstupů
	* postup od abstraktního ke konkrétnímu
	* důvod analýzy
		* lepší porozumění složitých systémů, jevů nebo problémů
		* identifikování příčiny problémů a hledání efektivních řešení
		* zlepšování systémů a procesů
* syntéza
	* proces spojování jednotlivých části, prvků nebo myšlenek dohromady, za účelem vytvořit něco nového
	* jak simulovat zadání zařízení z částí, které už "mám" → prototyp
		* optimalizace prototypu
			* integrace → snížení ceny
			* velikost
			* možnosti dalšího vývoje v dalších projektech
	* proč je syntéza důležitá?
		* umožňuje vytvářet nové a inovativní produkty
		* spojováním různých řešení lze nalézt optimální řešení komplexních problémů
		* umožňuje vytvářet nové teorie a modely
# Upgrade vloženého systému
* při nesprávném provedení může dojít ke ztrátě dat nebo poškození zařízení
* upgrade často závisí na podpoře výrobce
* některé upgrade mohou vyžadovat speciální znalosti a nástroje
* před provedením jakéhokoli upgrade si pečlivě prostudovat dokumentaci výrobce; pokud si nejsem jist, obrátit se na odborníka
* někdy lze upgrade otestovat v kontrolovaném prostředí
* postup upgradu softwaru
	1) příprava
		* zálohování dat
		* zjištění informací o zařízení - potřebujeme správný balíček pro specifický model zařízení
		* nástroje a vybavení - počítač, USB disk, internetové připojení
	2) stáhnutí balíčku
		* stáhnutí z oficiálních zdrojů
		* kontrola za pomocí kontrolního součtu
	3) instalace balíčku - postup podle manuálu
	4) ověření
		* funkčnosti - zda zařízení funguje správně a všechny nové funkce jsou dostupné
		* bezpečnosti - základní bezpečnostní sken
* kdy upgradovat
	* pokud potřebuji nové funkce, které nejsou v současné verzi dostupné, nebo chci využívat nové technologie a standardy
	* pokud zařízení trpí častými poruchami nebo nestabilitou
	* pokud chci zlepšit zabezpečení zařízení
* upgrade hardwaru bývá obtížný, někdy i nemožný protože vše se nachází na desce plošných obvodů - absolutně přečíst datasheet
# Modularita vloženého systému
* rozdělení systému na menší funkční části - moduly
* moduly mají jasně definované rozhraní a provádí specifické funkce
* proč rozdělovat vložené systémy do modulů
	* rozdělení systému na moduly zvyšuje srozumitelnost a usnadňuje jak návrh, tak i údržbu
	* dobře navržené moduly mohou být použity v různých projektech, což šetří čas a zdroje
	* jednotlivé moduly lze snadněji testovat a ověřovat, což zvyšuje kvalitu kódu
	* různé týmy mohou pracovat na různých modulech současně, což urychluje vývoj
	* modulární systémy se snadněji přizpůsobují změnám požadavků
* typy
	* hardware
		* rozdělení systému podle funkčních celků (např. vstup, zpracování, výstup)
		* rozdělení systému podle fyzických komponent (např. senzory, aktuátory, procesor)
	* software - rozdělení softwaru na samostatné funkce nebo knihovny
* příklady modularity
	* podle senzorů - každý senzor (např. teplotní) může být implementován jako samostatný modul
	* podle aktuátoru
	* podle komunikačního protokolu
* výhody
	* zrychlení vývoje - paralelní vývoj modulů
	* snížení nákladů - moduly můžu využít v jiných projektech
	* zvýšení spolehlivosti
	* flexibilita
* návrh
	* jasně definovat rozhraní - jak budou moduly mezi sebou komunikovat
	* minimalizovat závislost na jiné moduly
# Syntéza vloženého systému
* fáze syntézy
	1) analýza požadavků
		* jasné vymezení toho, co má systém dělat
		* určení omezení, jako je výkon, spotřeba energie, velikost, cena atd.
		* určení, jaké informace systém přijímá a jaké produkuje
		* definování požadavků na odolnost vůči chybám a poruchám
	2) návrh architektury
		* výběr vhodného procesoru, pamětí, senzorů, aktuátorů...
		* rozhodnutí o použitém operačním systému (pokud je použit), programovacím jazyku a struktuře softwaru
		* stanovení způsobů komunikace mezi jednotlivými komponentami systému
	3) implementace
		* programování
		* nastavení hardwarových komponent podle požadavků systému
		* spojení všech komponent do funkčního celku
	4) testování
		* testování jednotlivých modulů softwaru
		* testování interakce mezi jednotlivými moduly
		* testování celého systému za různých podmínek
	5) optimalizace
		* zvýšení výkonu
		* snížení spotřeby energie
		* implementace mechanismů pro detekci a opravu chyb
	6) nasazení
		* umístění do cílového prostředí
		* finální konfigurace
* nástroje pro syntézu
	* IDE pro psaní kódu, ladění a testování
	* nástroje pro simulaci chování systému před jeho fyzickou realizací
	* nástroje pro emulaci hardwarových komponent
* na co dávat pozor při syntéze vloženého systému
	* vestavěné systémy mají často omezenou výpočetní kapacitu, paměť a energii
	* mnohé vestavěné systémy musí reagovat na události v reálném čase
	* vestavěné systémy musí být velmi spolehlivé, protože jejich selhání může mít vážné následky
	* některé vestavěné systémy vyžadují vysokou úroveň zabezpečení
# Části vloženého systému
* základní části
	* mikroprocesor/mikrokontrolér
		* načítá a vykonává instrukce programu
		* zpracovává data ze senzorů
		* řídí aktuátory
		* komunikuje s ostatními zařízeními
	* paměť
		* ukládá instrukce programu, které mikroprocesor vykonává a data, se kterými mikroprocesor pracuje
		* ROM - permanentní paměť, obsahuje základní program a konfiguraci
		* RAM - dočasná paměť, slouží pro ukládání dat během běhu programu
	* I/O zařízení
		* převádějí fyzikální veličiny na elektrické signály a naopak
		* vyměňují data s jinými systémy
		* senzory - měří fyzikální veličiny
		* aktuátory - ovládají fyzikální procesy
		* komunikační rozhraní - komunikace s jinými zařízeními
	* napájecí zdroj
		* zajišťuje stabilní napájení systému
		* baterie, síťový adaptér
	* obvodová deska
		* mechanicky upevňuje komponenty
		* vytváří elektrické spoje mezi jednotlivými komponentami
		* spojuje všechny komponenty systému a zajišťuje jejich vzájemnou komunikaci
* doplňkové části
	* RTC baterie - napájí RTC obvod uchovávající přesný čas a datum, i když je systém vypnutý
	* Watchdog timer - sleduje správné fungování systému a v případě poruchy (zacyklení) provede restart
	* krystalový oscilátor - generuje přesný časový signál pro mikroprocesor
