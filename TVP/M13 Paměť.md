#technicke_vybaveni_pocitacu 
* fyzická zařízení určená k ukládání programů nebo dat pro okamžitou nebo trvalou potřebu
* rozdělení fyzických zařízení
	* vnitřní - RAM
	* vnější - ukládání programů a dat
* vnitřní paměť uložená v vnější se nazývá "virtuální" paměť *(nebo swap)*

![[TVP_23_1_24.png]]
* energetické rozdělení
	* nezávislé - Flash (vnější i vnitřní), ROM/PROM/EPROM/EEPROM (pro uložení firmware)
	* závislé - vnitřní paměť DRAM a vyrovnávací (SRAM)
* paměťové médium popisuje vnější paměť jako je např.: magnetopáska, optický disk (CD/DVD)
# Operační paměť
* slouží k ukládání dat po dobu běhu programu
* přístup k op je rychlejší než přístup k vnější paměti
* procesor pomocí adresy vybírá požadovanou buňku
* paměť je spojena s procesorem pomocí rychlé sběrnice; mezi op a procesor se vkládá ještě [[M13 Paměť#Paměť cache|cache]]
* dnes realizována jako polovodičová paměť typu RAM; ztrácí informace při odpojení napájení; obsah paměti je třeba občerstvovat čtením všech řádků
* je spravován operačním systémem
* uchovává kód programů (kód procesů a jejich mezivýsledky), základní datové struktury kernelu, atd.
* Fyzický adresový prostor *(FAP)* paměti je souvislý prostor paměťových buněk určité velikosti (1, 2, 4 nebo 8 bytů); buňky jsou lineárně adresovány adresami pevné délky; velikost buňky je dána délkou adresy (adresa $n$ bytů; buněk $2^n$); celý FAP nemusí být vyplněn; některé bloky se mohou objevit vícekrát; 
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
	* před odpojením je důležité odmountovat vyměnitelná média jinak může dojít k poškození souborového systému
	* moderní systém se snaží problém eliminovat zapomocí žurnálů
  ## hardwarová
* v řídících jednotkách vyrovnává rozdíl mezi nepravidelným předáváním/přebíráním dat sběrnicí a pravidelným tokem dat do/z magnetických hlav
* obvod je tvořen z tranzistorů a její funkcí je vyrovnávat rozdílnou rychlost mezi procesorem a operační pamětí
* vyšší rychlostí lze dosáhnout použitím kvalitnějších tranzistorů a položením blíže k procesoru
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
# Klopné obvody
* 
# Registry
  * 
# Latence
  * 
# Volatilita
  * 
# Přepisovatelnost
  * 
# Synchronní a asynchronní