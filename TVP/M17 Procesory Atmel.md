#technicke_vybaveni_pocitacu 
* ATmega16
	* 8-bitový procesor s vysokým výkonem a nízkou spotřebou energie
	* RISC architektura
		* 131 příkazů (většina na jeden hodinový tick)
		* 32 8bitových registrů pro běžné použití
		* propustnost až 16 MIPS (million operations per second) při 16 MHz
		* v čipu 2-cyklový násobič
	* Paměť
		* 16 kB Flash paměti s výdrží 10 000 přečtení/zápisů
		* volitelný oddíl zaváděcího kódu
		* 512 b EEPROM paměti s výdrží 100 000 přečtení/zápisů
		* 1 kB interní SRAM
	* JTAG interface
		* k programování Flashe, EEPROM a uzamykání bitů
		* data jsou přenášena sériově
			* TDI - Test Data In
			* TDO - Test Data Out
			* TCK - Test ClocK
			* TMS - Test Mode Select
			* TRST - Test ReSeT (volitelný)
		* rozsáhlá podpora debugování přímo na čipu
	* funkce periférií
		* dva 8-bitové časovače/čítače se samostatně nastavitelným škálováním a režimem porovnání
		* jeden 16-bitový časovač/čítač
		* reálný časový čítač s odděleným osciloskopem
		* 10-bitový [[MO4 Signály#AD|ADC převodník]]
		* Master/Slave SPI sériová sběrnice
		* programovatelný Watchdog (resetuje systém pokud se zacyklí) s odděleným on-chip oscilátorem
		* on-chip analogový komparátor
	* speciální funkce
		* Power-On Reset a Brown-Out detekce (dokáže zjistit problémy s napájením)
		* interní kalibrovaný RC oscilátor
		* externí a interní zdroje přerušení (tabulka?)
		* 6 režimů uspání
	* pracovní napětí
		* 2,7 - 5,5 V pro ATmega16L
		* 4,5 - 5,5 V pro ATmega16
	* rychlostní stupně
		* 0 - 8 MHz pro ATmega16L
		* 0 - 16 MHz pro ATmega16
	* odběr energie (při 1 MHz, 3 V, 25 °C pro ATmega16L)
		* Aktivní → 1,1 mA
		* Nečinný (Idle) → 0,35 mA
		* Vyplý → <1 µA
# Jednočip
* integrovaný obvod
* kombinace mikroprocesoru s perifériemi (paměť, IO porty, časovače aj.) → vše na jedné desce
* využito v embedded systémech
* hlavní komponenty
	* CPU - jádro
	* ROM - pro uložení firmwaru
	* RAM - dočasné uložení dat pro probíhající procesy
	* I/O porty - komunikace s externími perifériemi
	* časovače a čítače - měření času, [[MO5 Zpracování signálů pomocí CPU#DA převodník pomocí PWM|PWM]] signály a další časově závislé úkoly
	* [[MO4 Signály#AD|AD]]/[[MO4 Signály#DA|DA]] převodníky
	* UART *(Universal Asynchronous Receiver/Transmitter)* - sběrnice pro async. sériový přenos
	* [[MO7 Sběrnice#Standardy|SPI, I2C]], GPIO (univerzální vstup/výstup)
	* Watchdog Timer - periferie resetující systém při jeho zacyklení (k zacyklení může dojít chybou hardwaru nebo softwaru)
* používá RISC architekturu
* současný běh jádra s perifériemi
	* CPU může vykonávat instrukce programu, zatímco periferní zařízení pracují nezávisle
	* přerušení 
		* periférie generují přerušení informující CPU o dokončení nebo chybě (či jiná událost vyžadující pozornost CPU) operace
		* CPU může přerušit aktuální úkol, obsloužit přerušení a poté se vrátit k původnímu úkolu
	* DMA *(Direct Memory Access)* - periférie mají přímý přístup k paměti bez zatížení CPU
	* základní formy [[M16 Víceprocesorové a víceúlohové systémy#Multitasking|multitasking]]u
* důvody jednočipu
	* integrace různých periférii do kopmaktního těla
	* jednodušší návrh softwaru
	* navrženo s ohledem na nízkou spotřebu
	* vysoká škála použití
* ![[TVP_2_5_24.png]]
## Reset obvod (ATmega16)
* Power-on Reset - aktivace po prvním zapnutí mikrokontroleru
* External Reset - vyvolán když je `RESET` pin držen nízko alespoň 1.5 us; obvykle je pin připojen k uzemněnému tlačítku ![[TVP_7_6_24@1.png|]]
* Watchdog reset - pokud watchdog timer není obnoven během zvoleného časového intervalu vyvolá reset
* Brown-out - monitoruje napájecí napětí a resetuje mikrokontrolér pokud napětí klesne pod předdefinovanou úroveň
## Brown-out detektor
![[TVP_7_6_24@2.png]]
* R1 - pull-up rezistor připojený mezi napájecí napětí (VCC) a základnu tranzistoru T1; udržuje základnu tranzistoru na vysokém napětí, když není přítomno žádné rušení
* D1 - zenerova dioda stabilizuje napětí na základně tranzistoru T1; pokud napětí přesáhne určitý prah, dioda začne vést a stáhne základnu tranzistoru na nízkou úroveň
* T1 - tranzistor, jehož emitor je připojen k zemi a kolektor k RESET pinu mikrokontroléru přes rezistor R2
* R2 - rezistor omezuje proud tekoucí kolektorem tranzistoru při jeho sepnutí
* pokud napětí překročí určitou úroveň, Zenerova dioda aktivuje tranzistor, který stáhne `RESET` pin mikrokontroléru na nízkou úroveň a vyvolá reset
# Doba jedné instrukce
* jak dlouho trvá jedna instrukce když máme 10 MHz krystal?
	* z [[AVR_Instruction_set.pdf]] jsme zjistili, že jedna operace trvá `2 takty`
	* 10 MHz je 0,0000001 sekund (100 ns) (jeden takt) $$\frac{1}{10^{7}}= 0.0000001$$
	* tudíž jedna operace trvá 200 ns
# Připojení externího oscilátoru
* zapojení k procesoru
	* jeden vývod krystalu k pinu `XTAL1`
	* druhý vývod krystalu k pinu `XTAL2`
	* jeden kondenzátor (keramický; mezi 22 pF a 33 pF) mezi vývod krystalu (připojený k `XTAL1`) a zem (`GND`)
	* druhý kondenzátor mezi vývod krystalu (připojený k `XTAL2`) a zem (`GND`)
	![[TVP_7_6_24@3.png]]
* je nutné správně nastavit pojistky (definují zdroj taktovacího signálu a další konfigurační parametry mikrokontroléru)
# ISP obvod
* In-System Programming *(ISP)* je technika programování mikrokontrolérů přímo v cílovém zařízení, bez nutnosti vyjmutí MCU z PCB
* obvod využívá specifické piny mikrokontroléru, které jsou připojeny k programátoru, aby mohl být mikrokontrolér naprogramován nebo přeprogramován
* ISP piny pro ATmega16 - MISO, MOSI, SCK (Serial Clock), RESET, VCC, GND
![[TVP_7_6_24@4.png]]