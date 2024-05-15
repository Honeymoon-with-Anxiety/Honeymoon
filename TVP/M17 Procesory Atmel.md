* jednočip → jádro + periferie jedoucí současně; "proč?"
![[TVP_2_5_24.png]]
200 ms = 200 000 us = 200 000 000 ns
Q: 10 MHz krystal jak dlouho trvá jedna instrukce
kolik taktů trvá jedna instrukce → je to v AVR instruction pdf → trvá 2 takty (0,0000002 s = 200 ns)

* <něco> obvody <něco> k <něco> MCU
	* reset obvod
	* xfal?
	* napájení
	* brown out circuit
	* ošetření vstupů

* reset obvod
* připojení externího oscylátoru
* ISP obvd
---
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
* 