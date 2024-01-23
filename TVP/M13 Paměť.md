#technicke_vybaveni_pocitacu 
* fyzická zařízení určená k ukládání programů nebo dat pro okamžitou nebo trvalou potřebu
* rozdělení fyzických zařízení
	* vnitřní - RAM
	* vnější - ukládání programů a dat
* vnitřní paměť uložená v vnější se nazývá "virtuální" paměť *(nebo swap)*

![[TVP_23_1_24.png]]
* energetické rozdělení
	* nezávislé - Flash (vnější i vnitřní), ROM/PROM/EPROM/EEPROM (pro uložení firmware)
	* závislé - vnitřní paměť DRAM a vyrovnávaví (SRAM)
* paměťové médium popisuje vnější paměť jako je např.: magnetopáska, optický disk (CD/DVD)
# Operační paměť
* 
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
# Paměť flash
* 
# EEPROM
* 
# Paměťová buňka
## statická
* 
## dynamická
* 
# Přehled trhu
* 
# Výhody
* 