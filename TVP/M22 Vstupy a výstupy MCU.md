#technicke_vybaveni_pocitacu 
* o signálech více [M04](obsidian://open?vault=E3A&file=TVP%2FMO4%20Sign%C3%A1ly)
# Vstupně výstupní pin
* univerzální kontakt na obvodu sloužící jak pro vstup, tak pro výstup signálu (čte i odesílá el. signál)
* digitální piny - pracují s diskrétními hodnotami reprezentovanými jako log. 0 a log. 1; hodnoty jsou definovány konkrétním napěťovým rozsahem
* analogové piny - mohou nabývat spojitého rozsahu hodnot napětí v určitém intervalu; měření fyzikálních veličin
## Charakteristika
* impedance
	* vstupní - určuje jaký proud poteče do pinu při připojení určitého napětí; vysoká impedance → pin odebere velmi malý proud
	* výstupní - jak se výstupní napětí změní při připojení zátěže; nízká impedance → výstupní napětí se příliš nezmění
* napěťový rozsah
	* logické úrovně - každý pin má definovaný rozsah napětí odpovídající log. 0 a 1
	* max a min napětí - pin má také maximální a minimální napětí
* maximální proud - každý pin má omezený max proud, který může protékat
* doba přechodu - čas, který pin potřebuje k přechodu z jednoho stavu do druhého
## Druhy
* sériové - pro sériovou komunikaci; data jsou přenášena po jednom bitu po jediném vodiči
* paralelní - přenos většího množství dat současně po více vodičích
* TTL - používají napěťové úrovně kompatibilní s tranzistor-tranzistorovou logikou
* CMOS - používají napěťové úrovně kompatibilní s komplementárními metal-oxid-polovodičovými obvody
* open-collector/open-drain - výstup pinu je spojen se zemí přes tranzistor; používá se pro připojení více výstupů k jedné zátěži
* třístavový - výstup může být ve třech stavech: `high`, `low` nebo `high-impedance` (odpojeno)
* s pull-up/pull-down rezistorem - mají vnitřní rezistor, který udržuje pin v log. 0/1, pokud není připojen žádný externí signál
* interrupt piny - vyvolávají přerušení procesoru při změně stavu
# Konfigurace pinů
* liší se v závislosti na použitém mikrokontroléru a programovacím jazyku
* přímým zápisem do speciálních registrů mikrokontroléru; často v nízkoúrovňovém programování
* konfigurace pomocí funkcí a tříd poskytovaných knihovnami
* obecné kroky
	1) výběr pinu
	2) nastavení směru
	3) další parametry
		* hodnota vnitřního pull-up rezistoru
		* přerušení
		* ...
* konfigurace v ATmega16 (v `Reset` obsluze)

```assembly
clr ZeroReg ;vycisteni nuloveho registru
ldi	TmpReg, 0xFF ;nastaveni hodnoty 255 do pracovniho registru
out	DDRA, TmpReg ;nastaveni smeru portu A
out	PortA, ZeroReg ;nastaveni prazdne hodnoty vystupu portu A
```

## Připojení na periférii
* napěťové úrovně na pinech musí odpovídat napěťovým úrovním periférie; je potřeba použít úrovňové převodníky
* je třeba hlídat maximální proudy
* zjistit zda periférie pracuje s pozitivní nebo negativní logikou
* všechny zapojené součástky musí mít společný referenční bod (zem)
* senzory
	* digitální (tlačítka, spínače, optické senzory) - na digitální pin
	* analogové (potenciometry, teplotní čidla) - na analogový pin
* aktuátory *(opak senzoru)*
	* LED diody - přes předřadný odpor k digitálnímu pinu
	* motory - přes tranzistory nebo motorové ovladače k digitálním pinům
	* relé - přes tranzistory nebo k digitálním pinům
* LCD displeje - přes řadič displeje k několika digitálním pinům
* před připojením jakékoliv periférie si pečlivě prostudovat její datasheet
# Techniky přizpůsobení vstupního a výstupního signálu
* MCU často vyžaduje přizpůsobení signálu aby odpovídal požadavkům
* děliče napětí
	* ke snížení napětí přicházejícího na pin MCU
	* dva odpory spojené v sérii
* filtry
	* odfiltrují nežádoucí frekvenční složky ze signálu
	* odfiltrování šumu, stabilizace signálu
	* typy
		* RC filtr - kombinuje rezistor a kondenzátor pro vytvoření jednoduchého filtru
		* LC filtr - kombinuje cívku a kondenzátor pro vytvoření filtru s vyšší kvalitou
		* aktivní - používají operační zesilovače pro realizaci složitějších filtrů
* zesilovače
	* zvýší amplitudu slabého signálu
	* zesílení signálů z nízkoohmových senzorů
	* typy
		* operační - univerzální zesilovače pro různé aplikace
		* speciální
* úrovňové převodníky
	* převádějí logické úrovně mezi různými napěťovými standardy (např. 3.3V a 5V)
	* připojení zařízení s různými napájecími napětími
* ochranné obvody
	* chrání pin MCU před přetížením, přepětím a elektrostatickým výbojem
	* diody, tranzistory, varistory
* [ADC](obsidian://open?vault=E3A&file=TVP%2FMO4%20Sign%C3%A1ly%23AD)
* [DAC](obsidian://open?vault=E3A&file=TVP%2FMO4%20Sign%C3%A1ly%23DA)
# Druhy vstupního a výstupního signálu
* podle typu
	* analogové - spojitá hodnota v určitém rozsahu; nejčastěji reprezentuje fyzikální veličiny
	* digitální - diskrétní hodnoty
* podle frekvence
	* nízkofrekvenční - pod několika kHz
	* středofrekvenční - několik kHz až MHz
	* vysokofrekvenční - nad několik MHz
* podle tvaru
	* sinusový
	* obdelníkový
	* pilový
	* pulzní
	* šum
* podle amplitudy
	* malé - pro citlivé zařízení
	* velké - pro ovládání výkonových zařízení
* fáze - časový posun mezi signály o stejné frekvenci
* šířka pásma - rozsah frekvencí obsažených v signálu
# Typické externí periférie
* senzory
* AD/DA převodníky
* Aktuátory
	* motory
	* LED
	* relé
* zobrazovací prvky
	* LCD displeje
	* LED displeje
* zvukové prvky
	* reproduktory
	* bzučáky
* komunikační prvky
	* UART - jednoduchá sériová komunikace
	* I2C - sériová sběrnice pro připojení více zařízení
	* SPI - sériová sběrnice pro vysokorychlostní komunikaci
	* Ethernet
	* [[M21 Srovnání sítí#WiFi|Wi-Fi]]
	* [[M21 Srovnání sítí#Bluetooth|Bluetooth]] přijímač a vysílač
* paměti
	* EEPROM
	* FLASH
* časovače
* přerušovače
