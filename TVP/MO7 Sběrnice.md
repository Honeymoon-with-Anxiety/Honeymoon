#technicke_vybaveni_pocitacu
* skupina signálových vodičů
* představuje komunikační cestu pro různé komponenty systému k výměně dat a informací
* účel zajistit přenos dat a řídicích povelů mezi dvěma a více elektronickými zařízeními
* přenos se řídí stanoveným protokolem
* po mechanické stránce vybavena konektory uzpůsobenými pro připojení modulů
* sloužila k propojení jednotlivých částí (procesoru, paměti a vstupně/výstupních zařízení)
* nahrazuje dvoubodovými spoji (příkladem je „sběrnice“ PCI-Express)
* "Sběrnice je kanál nebo cesta, která umožňuje přenos dat mezi různými komponenty v systému."
* mohou být propojeny s mechanismy DMA *(Direct Memory Access)* umožňující přímý přístup periferním zařízením k paměti bez účasti procesoru
# Univerzální a Specializovaná sběrnice
* univerzální
	* navrženy  aby byly obecně použitelné pro různé typy komponent v počítači
	* podporují různé typy zařízení (grafické karty, síťové karty, zvukové karty atd.)
	* lze je rozšířit rozšiřující kartou/modulem
* specializovaná
	* navrženy pro konkrétní účel nebo typ komponenty
	* slouží pro určitý typ zařízení nebo úlohu
	* obvykle jednodušší a přímočařejší
	* optimalizována pro efektivní specifických přenos dat pro daný typ zařízení
	* nemusí být rozšířitelné
# Standardy
* ISA - pasivní; šířka 8 nebo 16 bitů; přenosová rychlost < 8 MB/s
* PCI - „inteligentní“ sběrnice; šířka 32 nebo 64 bitů; přenosová rychlost < 130 MB/s (260 MB/s)
* AGP - pro připojení grafického rozhraní (karty) k systému; přenosová rychlost 260 MB/s – 2 GB/s
* PCI-X - zpětně kompatibilní rozšíření sběrnice PCI
* PCI-Expres - nová sériová implementace sběrnice PCI
* USB - 2 datové vodiče + 2 napájecí vodiče 5 V/500 mA; verze 1.1 přenosová rychlost ~1,43 MB/s, 2.0 přenosová rychlost ~57 MB/s, 3.0 přenosová rychlost ~572 MB/s
* FireWire - sériová sběrnice; široké použití; 50 MB/s
* RS-485 - sériová průmyslová sběrnice; někdy jako proudová smyčka (rozhraní používané pro přenos informací v prostředích s vysokou hladinou rušení); do prostor s vysokým elektromagnetickým rušením
* I²C - rychlost < 100 kb/s; adresace 128 zařízení; komunikace a řízení v elektronických zařízení
* Thunderbolt - kombinuje PCIe a DisplayPort do dvou sériových signálů v jednom kabelu společně se stejnosměrným nápájením; lze obsloužit až šest zařízení
# Organizace sběrnic
* struktura, ve které je sběrnice v počítačovém systému nebo elektronickém zařízení uspořádána do hierarchického uspořádání
* organizace umožňuje efektivní přenos informací mezi různými úrovněmi systému a periférii
* usnadňuje přidávání nebo odstraňování periferních zařízení bez výrazného ovlivnění celkové struktury systému
* Centrální
	* nachází se na nejvyšší úrovni hierarchie a slouží k propojení hlavních komponent, jako jsou procesor, hlavní paměť a hlavní řadič
	* často širokopásmová a umožňuje rychlý přenos dat mezi klíčovými částmi systému
	* zajišťuje koordinaci mezi procesorem a hlavní pamětí, a umožňuje přenos instrukcí a dat
* Systémová
	* propojení centrální sběrnice s periferními zařízeními, jako jsou grafické karty, síťové karty, a další
	* optimalizována pro specifické potřeby připojených periferních zařízení
	* rozšiřuje možnosti propojení systému s různými typy periferních zařízení a umožňuje jejich vzájemnou komunikaci
* Lokální
	* na úrovni jednotlivých periferních zařízení nebo skupin zařízení
	* přizpůsobena specifickým potřebám připojených komponent a optimalizována pro přenos dat v dané lokalitě
	* propojení periferních zařízení, která jsou vzájemně úzce propojena nebo mají specifické požadavky na přenos dat
# Parametry sběrnice
* "Parametry jsou klíčové charakteristiky, které definují vlastnosti a schopnosti"
* Šířka sběrnice
	* určuje kolik bitů může být přeneseno najednou mezi různými částmi systému za jednu přenosovou operaci nebo hodinový cyklus
	* např 32bitová sběrnice umožňuje přenos 32 bitů najednou
	* širší sběrnice obvykle umožňují rychlejší přenos dat, protože mohou přenášet více bitů najednou
	* klíčové při přenosu dat mezi procesorem a pamětí
	* paralelní sběrnice přenášejí více bitů současně (například 8, 16, 32 nebo 64 bitů)
	* seriálová sběrnice přenáší bity postupně po jednom
	* širší sběrnice mohou vyžadovat více fyzických vodičů - větší nároky na fyzický design systému
	* přenos více bitů naráz může vyžadovat více energie
	* standardní šířky: 8 bitů *(byte)*, 16 bitů *(word)*, 32 bitů *(double word)* nebo 64 bitů
	* výběr šířky sběrnice závisí na konkrétních požadavcích aplikace a vyvážení mezi rychlostí
* Frekvence sběrnice
	* určuje frekvenci přenosu dat na sběrnici (cykly)
	* měřená v hertz *(Hz)* nebo megahertz *(MHz)*
	* každý cyklus umožňuje přenos dalšího bitu nebo skupiny bitů
	* frekvence synchronní sběrnice je synchronizována s hodinovým signálem systému; cykly sběrnice jsou synchronizovány s hodinovými pulsy
	* frekvence asynchronní sběrnice není synchronizována s hodinovým signálem systému
	* při zvyšování frekvence sběrnice je třeba brát v úvahu fyzikální omezení, jako jsou signálové ztráty, elektromagnetické rušení atd.
	* standardní frekvence: 100 MHz, 200 MHz nebo 400 MHz, v moderních systémech může být ještě vyšší
	* měla by být koordinována s dalšími částmi systému, jako jsou procesory, paměť a další periferní zařízení
	* vyšší frekvence obvykle vyžadují více elektrické energie, což může být důležité při návrhu systémů s nízkým příkonem
	* u mobilních zařízeních mohou být omezeny pro prodloužení výdrže baterie
* Šířka pásma sběrnice
	* celková kapacita sběrnice k přenosu dat za jednotku času
	* kombinace šířky sběrnice s frekvencí sběrnice
	* měří se v jednotkách bitů za sekundu *(bps)* nebo výsledné hodnoty mohou být vyjádřeny v kilobitech za sekundu *(kbps)*, megabitech za sekundu *(Mbps)* nebo gigabitech za sekundu *(Gbps)*
	* šířka se vypočítá násobením šířky sběrnice *(v bitech)* a frekvence sběrnice *(v Hz)* $$Šířka\ pásma=Šířka\ sběrnice * Frekvence\ sběrnice$$
	* fyzikální omezení, elektromagnetické rušení a další faktory mohou omezit dosažitelnou šířku pásma
	* klíčové optimalizovat šířku pásma sběrnice tak, aby byla vhodná pro konkrétní požadavky aplikace
* Latence sběrnice
	* "Latence je v označení pro dobu uplynulou mezi akcí a reakcí"
	* doba, která uplyne od okamžiku, kdy je zahájen přenos dat na sběrnici, až po okamžik, kdy jsou data efektivně doručena na místo určení
	* přispěvatelé
		* synchronizace s hodinovým signálem a další časovací faktory mohou přispívat k latenci
		* fyzická délka sběrnice může ovlivnit dobu, kterou signál potřebuje k cestě od jednoho konce sběrnice ke druhému
		* zpracování dat na straně zařízení, které zahajuje přenos, může způsobit další latenci
	* typy
		* Access - čas mezi požadavkem na přístup k datům a skutečným zahájením přenosu
		* Transfer - doba potřebná k přenosu dat samotných po zahájení přenosu
		* Network - latence internetového připojení
	* latence sběrnice se měří v mikrosekundách *(μs)* nebo nanosekundách *(ns)*, a to v závislosti na rychlosti a technologii sběrnice
	* pro dosažení nižší latence je možné provádět optimalizace, jako je zkrácení fyzické délky sběrnice a optimalizace algoritmů přenosu atd.
* Protokol sběrnice
	* pravidla a postupy, které určují, jak probíhá komunikace mezi různými zařízeními připojenými ke sběrnici
	* definují jak jsou data reprezentována a organizována; strukturu datových rámců, pořadí bajtů, kontrolní součty nebo kódy pro detekci chyb
	* určují jak jsou adresována zařízení na sběrnici
	* mohou obsahovat mechanismy pro řízení toku dat; zabraňují přetečení nebo ztrátě dat
	* specifikují, zda na sběrnici existuje hlavní zařízení *(master)*, které řídí komunikaci, nebo zda jsou všechna zařízení rovnocenná *(peer-to-peer)*
	* mohou obsahovat specifikace pro fyzickou vrstvu, jako je například drátové nebo bezdrátové rozhraní, elektrické napětí
	* stanovují pravidla pro zajištění bezpečné komunikace
	* některé podporují možnost připojovat a odpojovat zařízení ze sběrnice za chodu *(hot-swapping)*
* Délka sběrnice
	* fyzická délka trasy, po které probíhá komunikace mezi různými zařízeními připojenými ke sběrnici
	* s rostoucí délkou sběrnice může docházet k ztrátě signálu, což může ovlivnit stabilitu a integritu dat
	* různé sběrnice mohou mít různá omezení ohledně maximální délky sběrnice
	* vyšší přenosové rychlosti mohou být citlivé na délku sběrnice
	* používání diferenciálních sběrnic (způsob komunikace využívající rozdílu mezi dvěma signály) může pomoci snížit vliv elektromagnetického rušení a ztrát signálu, což může umožnit delší sběrnice
	* použití správné kabeláže může pomoci minimalizovat problémy spojené s délkou sběrnice
	* mohou být použity repeatery nebo zesilovače signálu
* Multiplexování
	* umožňuje sdílet jednu fyzickou sběrnici pro přenos dat mezi více zařízeními
	* Časové Multiplexování *(TDM)* - alokuje časové sloty různým zařízením na sběrnici; každé zařízení má přidělený časový interval pro přenos svých dat
	* Frekvenční Multiplexování *(FDM)* - alokuje různým zařízením různé frekvenční pásma na sběrnici; každé zařízení má svou vlastní frekvenci pro přenos dat
	* Kanálové Multiplexování - kombinuje aspekty TDM a FDM tím, že přiřazuje různým zařízením jak časové sloty, tak i frekvenční pásma na sběrnici
	* synchronní multiplexování vyžaduje synchronizaci mezi všemi zařízeními na sběrnici
	* sdílení sběrnice mezi více zařízeními může snížit náklady na infrastrukturu
	* může docházet ke zpoždění v přenosu dat, protože různá zařízení musí čekat na svůj časový nebo frekvenční slot
* [[MO7 Sběrnice#Standardy|Standardy]] a Kompatibilita
* Formát datového přenosu
	* struktura, organizace a způsob kódování dat
	* data jsou organizována do datových rámců; rámec obsahuje hlavičku (informace o adrese, délce dat, kontrolních součtech atd.) a tělo dat
	* mohou být organizována na úrovni bajtů (8 bitů) nebo na úrovni bitů
	* pokud je ke sběrnici připojeno více zařízení datový formát často zahrnuje cílovou adresu
	* začátek nebo konec datového rámce je značen speciálními bity nebo značky
	* definován je datový formát příslušným komunikačním protokolem
		* UART *(Universal Asynchronous Receiver/Transmitter)* - sériová komunikace s asynchronním přenosem dat
		* I²C *(Inter-Integrated Circuit)* - sériová komunikace mezi integrovanými obvody
		* Ethernet Frame - pro přenos dat v síťovém prostředí
* Podpora Hot-Swapping
	* schopnost připojovat nebo odpojovat zařízení k systému za chodu
	* USB
	* Thunderbolt
	* SATA
		* pro připojení interních pevných disků a dalších úložných zařízení v počítačích
		* hot-swapping zejména u serverů a systémů s podporou této funkce
	* ExpressCard - pro připojení periferních zařízení k notebookům
	* PCIe
* [[MO7 Sběrnice#Organizace sběrnic|Typy sběrnic]]
# Vliv čipové sady základní desky
* sady podporují různé generace a rychlosti sběrnic
* sada určuje, kolik a jaké typy slotů jsou na základní desce k dispozici
* sada musí být kompatibilní se standardy
# Dekodér adresy
* převod adresy uložené v binární podobě na aktivační signály
* navržen různými způsoby v závislosti na architektuře systému (kombinační logický obvod nebo sekvenciální obvod s pamětí)
* může demultiplexovat vstupní adresu na více bitů, což umožňuje přesnější volbu paměťové lokality
# Northbridge a Southbridge
* nebo-li systémový řadič
* jeden ze svou čipů na zk. desce
![Typické schéma počítače](https://upload.wikimedia.org/wikipedia/commons/5/51/Chipset_schematic.svg)
* existují čipy obsahující oba mosty najednou za cenu vyšší složitosti při výrobě
## Northbridge
* komunikace mezi CPU, pamětí RAM a PCIe sběrnicí
* spojení s jižním mostem
* některé obsahují integrované grafické karty
* můstek pouze s jedním nebo se dvěma typy procesorů a zpravidla pouze s jedním typem paměti RAM
* určuje rychlost, druh procesorů, jejich množství a druh paměti RAM
* schopen propojení s jedním nebo se dvěma různými jižními můstky
* urřuje jak dalece mohou být počítače taktovány
* obvykle vyžaduje samostatné aktivní chlazení
## Southbridge
* vstupně-výstupní řadič
* realizuje pomalejší funkce základní desky
* není přímo spojen s procesorem
* průmyslový standard pro komunikaci mezi severním a jižním můstkem neexistuje
* pro komunikaci mezi severním a jižním můstkem byla využívána sběrnice PCI
* může zahrnovat podporu pro Ethernet, RAID, USB, SATA, zvukovou kartu a FireWire