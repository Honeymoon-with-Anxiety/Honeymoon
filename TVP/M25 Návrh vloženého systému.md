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
* skládá se z části
	* proporcionální
		* reaguje na aktuální odchylku mezi požadovanou hodnotou a skutečnou hodnotou
		* prostý zesilovač
	* integrační - zohledňuje kumulativní odchylku v čase; eliminuje statickou chybu
	* derivační - reaguje na rychlost změny odchylky
* řadí se před řízenou soustavu
* nejdříve realizovány pomocí pneumatických; později elektronických obvodů
* postup procesu regulátoru
	* čidlo měří aktuální hodnotu řízené veličiny
	* naměřená hodnota se porovná s požadovanou hodnotou a vypočítá se odchylka
	* PID regulátor vypočítá řídicí signál na základě proporcionální, integrální a derivační složky
	* řídicí signál je aplikován na aktuátor, který ovlivňuje řízený proces
	* změna stavu procesu se projeví na výstupu čidla, což vede k novému výpočtu chybového signálu
* matematický popis $$u(t) = K_p * e(t) + K_i * ∫e(t)dt + K_d * (de(t)/dt)$$ kde
	* $u(t)$ - řídicí signál
	* $K_p$ - proporcionální konstanta
	* $K_i$ - integrační konstanta
	* $K_d$ - derivační konstanta
	* $e(t)$ - odchylka
* výhody
	* lze použít pro širokou škálu aplikací
	* je robustní
	* mnoho mikroprocesorů a mikrokontrolérů má integrované funkce pro implementaci PID regulátoru
* nevýhody
	* nastavení parametrů $K_p$, $K_i$ a $K_d$ může být náročné a vyžaduje určitou zkušenost
	* pro vysoce nelineární systémy může být potřeba použít složitější metody řízení
* využití
	* udržování konstantní teploty v průmyslových procesech, domácích spotřebičích
	* řízení otáček motorů v elektrických nářadí, průmyslových robotech
	* regulace tlaku v pneumatických systémech
![Regulátor PID v regulační smyčce](https://upload.wikimedia.org/wikipedia/commons/4/40/Pid-feedback-nct-int-correct.png)
# Účel
## analogové sekce
* při návrhu analogové sekce je důležité zvážit požadavky na přesnost, rychlost, spotřebu energie
* převod fyzikálních veličin na elektrické signály
	* senzory - měří fyzikální veličiny; výsledkem měření je obvykle analogový signál (napětí nebo proud) úměrný měřené veličině
	* převodníky - analogové signály ze senzorů jsou často převedeny na digitální hodnotu pomocí ADC, aby je mohl zpracovat mikroprocesor
* generování analogových signálů
	* DAC - převádí digitální hodnoty z mikroprocesoru na analogové signály, které mohou být použity k řízení externích zařízení
	* generátory signálů - produkují analogové signály (např.: sinusové, obdélníkové, trojúhelníkové); pro různé účely
* zpracování analogových signálů
	* zesílení
	* filtrace
	* srovnání - porovnávání analogových signálů s referenční hodnotou
* typické komponenty
	* operační zesilovače - univerzální analogové obvody pro zesilování, sčítání, odčítání, integraci a diferenciaci
	* komparátory - porovnávají dva analogové signály a generují digitální výstup
	* analogový multiplexor
	* filtry
	* ADC, DAC
## digitální sekce
* zpracovává informace, rozhoduje a řídí ostatní komponenty systému
* pracuje s diskrétními hodnotami (obvykle 0 a 1)
* zpracování dat
	* provádí aritmetické a logické operace nad daty získanými z analogové části nebo uloženými v paměti
	* na základě zpracovaných dat vydává příkazy pro ovládání ostatních částí systému
	* zajišťuje komunikaci s jinými zařízeními nebo s uživatelem
* uchovává programové kódy, data a konfigurační parametry systému
* zajišťuje přesné časování a synchronizaci různých procesů v systému
* komponenty
	* mikroprocesor nebo mikrokontrolér
	* paměť ROM/RAM
	* vstupně-výstupní porty
	* periférie
# Napájení
* zdroje napájení
	* baterie - primární, sekundární
	* síťové adaptéry
	* energetické zdroje - solární články, palivové články
* návrh napájecího systému
	* napětí - každý čip a obvod v systému má své specifické požadavky na napájecí napětí
	* proud - maximální odběr proudu určuje kapacitu zdroje a dimenzování vodičů
	* stabilita - napájení musí být stabilní, aby se předešlo poruchám a nesprávné funkci systému
	* rušení - napájecí zdroj by neměl vytvářet rušení, které by mohlo ovlivnit ostatní části systému
	* bezpečnost - napájecí systém musí být navržen tak, aby byl bezpečný pro uživatele i zařízení
* ochrana napájecího systému - pojistky, diody
* požadavky pro napájení vloženého systému
	* nízká spotřeba
	* široký rozsah vstupního napětí
	* ochrana citlivých obvodů před rušením a zemními smyčkami
	* ochrana proti přepólování
