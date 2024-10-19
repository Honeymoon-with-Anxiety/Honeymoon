#technicke_vybaveni_pocitacu 
* na co dávat pozor při návrhu
	* definice požadavků
		* Jaké úlohy má systém vykonávat? Jaké vstupy a výstupy potřebuje? Jaká je požadovaná rychlost a přesnost?
		* Jak jsme omezení hmotností, velikostí, spotřebou? Jaké jsou okolní podmínky?
		* Jaké bezpečnostní opatření je třeba přijmout?
	* výběr hardware
		* jaký procesor je nejvhodnější?
		* jaký typ a velikost paměti je potřeba?
		* jaké periférie potřebuji pro realizaci požadovaných funkcí?
		* jak budu systém napájet?
	* vývoj software
		* nechám běžet software na holém hardware nebo použiji operační systém?
		* jaký programovací jazyk použiji?
		* jaké metody testování použiji?
	* design systému
		* jakou architekturu použiji?
		* bude systém rozdělen do modulů?
	* optimalizace
	* jaké certifikace budou potřeba pro daný systém? - při komerčním použití
* jak postupovat při míchání analogových a digitálních součástí
	* analogové části zpracovávají signály ze skutečného světa
	* digitální části provádějí výpočty a řídí systém
	* analogové a digitální části by měly být od sebe co nejvíce izolovány aby se zabránilo vzájemnému rušení
	* každá část by měla mít vlastní zdroj napájení aby se zabránilo šumu a rušení
	* vybírat převodníky s vhodným rozlišením a rychlostí převodu; správně převodníky zkalibrovat
	* pomocí osciloskopu vizualizovat analogové signály pro kontrolu
	* při návrhu multimetrem hlídat hodnoty napětí a proudu
	* pečlivě prostudovat datasheety
	* správně uzemnit obvody
* jak zvážit volbu procesoru
	* definice požadavků
		* jaké výpočetní nároky systém bude mít?
		* bude provádět složité výpočty nebo jen jednoduché úkoly?
		* kolik RAM bude systém potřebovat?
		* jaké periférie bude procesor ovládat?
		* jaká je maximální povolená spotřeba energie?
		* je nutné aby systém reagoval v reálném čase?
		* jaké jsou provozní podmínky?
	* výběr architektury
		* RISC nebo CISC?
			* RISC - energeticky úspornější, jednodušší na programování
			* CISC - větší výkon
		* kolik jader?
		* velikost cache paměti
	* periférie
		* zkontrolovat, zda procesor již obsahuje potřebné periférie - snížení externích součástek a nákladů
	* je dostupná široká škála vývojových nástrojů pro daný procesor?
	* cena a dostupnost
	* velikost
	* spotřeba energie v různých režimech
# Zpětnovazební systém
* výstup systému je srovnáván s požadovanou hodnotou; rozdíl mezi nimi (chyba) je použit k úpravě vstupu systému tak, aby se výstup přiblížil k požadované hodnotě
* důvody
	* umožňuje dosáhnout vysoké přesnosti a opakovatelnosti výsledků
	* zvyšuje stabilitu systému a jeho odolnost vůči rušivým vlivům
	* umožňuje systému adaptovat se na změny v prostředí nebo požadavcích
* výhody
	* vysoká přesnost
	* stabilita - systém je odolnější vůči rušivým vlivům
	* adaptabilita
	* optimalizace výkonu systému pro dosažení požadovaných výsledků
* nevýhody
	* složitost
	* při nesprávném návrhu může dojít ke kmitání nebo nestabilitě systému
* funkční princip
	* měření
	* srovnání
	* řízení
	* akce
	* zpětná vazba (zopakování předešlých 4 bodů)

![Kladná zpětná vazba](https://upload.wikimedia.org/wikipedia/commons/3/36/Feedback_positive.png)

## Části zpětnovazebního systému
* čidlo - měří fyzikální veličinu relevantní pro řízený proces; převádí měřenou fyzikální veličinu na elektrický signál, který může být zpracován elektrickým obvodem
* srovnávač
	* porovnává aktuální hodnotu měřené veličiny (výstup čidla) s požadovanou hodnotou (referencí)
	* vytváří chybový signál reprezentující rozdíl mezi aktuální hodnotou a referencí
	* může být realizován pomocí analogového nebo digitálního obvodu
* řídící člen
	* na základě chybového signálu vypočítá potřebnou korekci a generuje řídící signál
	* realizace pomocí mikroprocesoru, mikrokontroléru nebo specializovaného obvodu
* aktuátor - převádí řídící signál na fyzickou akci
# PID regulátor
# Účel
## analogové sekce
## digitální sekce
# Napájení
