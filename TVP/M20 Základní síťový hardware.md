#technicke_vybaveni_pocitacu 
* umožňují propojení počítačů, tiskáren, serverů a dalších zařízení do společné sítě; vzájemná komunikace a sdílení zdrojů
* při vybírání je důležité zvážit velikost sítě, potřebná rychlost, technologie zabezpečení a další funkce
* síťové rozhraní
	* v operačním systému; síťová karta, WiFi rozhraní nebo virtuální rozhraní
	* přijímá a vysílá v síti data (např. ethernetové packety)
	* síťové rozhraní není: repeater, hub, switche a bridge (nelze přímo jemu poslat nějaká data)
* síť s hvězdicovou topologií ^9dcba9
	* každý prvek je připojen pomocí kabelu k hubu
	* mezi dvěma stanicemi existuje jen jedna cesta
	![[TVP_22_9_24.png]]
* token ring
	* LAN technologie
	* principem je předávání vysílacího práva pomocí speciálního packetu (tzv. tokenu) mezi adaptéry, zapojenými do logického kruhu (fyzicky je síť v hvězdicovém zapojení)
	* centrální hub slouží pouze jako spoj pro uzly v sousedních ramenech hvězdy
	* původní rychlost byla 4 Mbit/s, později 16 Mbit/s, 100 Mbit/s a 1 Gbit/s
# Síťová karta
* zařízení pro propojení počítačů v síti
* může být externí ve formě karty ([PCIe](obsidian://open?vault=E3A&file=TVP%2FMO7%20Sb%C4%9Brnice) sběrnice na zk. desce) nebo integrovaná; pro laptopy se dají připojit i přes USB
* každá karta má od výrobce určenou [[M19 Standardizace v oblasti sítí#MAC|MAC adresu]]
* obsahuje
	* specializovaný komunikační obvod - specializovaný komunikační procesor obsahující vše, co komunikace přes síť vyžaduje
	* ROM paměť (*BootROM*)
		* paměť má v sobě nahraný program který umožňuje připojení k LAN bez dodatečného komunikačního softwaru
		* umožňuje postavení bezdiskové stanice - veškerý software potřebný pro práci stáhne ze serveru
	* napěťový měnič z 5 V na 9 V potřebný pro některé druhy sítí
	* konektor pro připojení síťového kabelu
	* LED diody na indikaci aktivity sítě a přítomnosti signálu v síti
* rozdělení
	* serverové
		* víceportové
		* zvýšená datová propustnost
		* rozšířené možnosti komunikace
		* snížené zatížení procesoru
	* pro pracovní stanice
* parametry
	* typ média: kroucená dvojlinka, tenký/tlustý koaxiální kabel, bezdrátová komunikace, optické vlákno
	* typ sítě: Ethernet, Fast Ethernet, Arcnet, Token Ring, FDDI
	* rychlost: 4 Mbit/s, 10 Mbit/s, 16 Mbit/s, 100 Mbit/s, 1 Gbit/s, 10 Gbit/s
# Hub
* větví síť bez jakéhokoliv řízení do hvězdicové topologie (při zkolabování hubu zkolabuje celá síť)
* chová se jako opakovač - data, která přijdou na jeden z portů, jsou obnovena a odeslána na všechny ostatní porty; zpoždění 1 bit
* pracuje na 1. vrstvě [[M19 Standardizace v oblasti sítí#ISO, OSI|OSI modelu]]
* dnes u starších sítích → nahrazeno switchem
* podle LEDek je možné zjistit vadné spojení
* kvůli schopnosti detekce kolize
	* je počet hubů v síti omezen dle rychlosti
		* 10 Mbit/s - 5 segmentů (4 huby) mezi dvěma koncovými stanicemi
		* 100 Mbit/s - 3 segmenty (2 huby) mezi dvěma koncovými stanicemi
	* některé huby mají speciální port, který umožňuje jejich slučování, takže se navenek chovají jako jeden
# Switch
* propojuje zařízení nebo části jedné sítě hvězdicovou topologií; pracuje pouze v místní síti
* obsahuje menší i větší počet portů
* posílá síťový provoz jen do portů, do kterých je třeba
* způsoby přeposílání packetů
	* store and forward - packet z jednoho portu přijme; uloží si jej do [bufferu](obsidian://open?vault=E3A&file=TVP%2FM11%20J%C3%A1dro%20procesoru%23%5Ebuffer); prozkoumá hlavičky; odešle packet do příslušného portu
	* cut-through switching - k analýze hlaviček dochází, když dorazí začátek packetu; jakmile je destinace určena, začne se packet odesílat (nečeká se na celý packet)
	* fragment free - přeposlání packetu začne až po přijetí 64 bytů (pro detekci kolize); pro sítě kde je do switche připojen hub
	* adaptive switching - automatické přepínání mezi metodami cut-through switching a store and forward
* vrstva
	* základní switche - 2. vrstva OSI modelu
	* LAN switche - 3. vrstva pokud je rozhodnutí založeno na IP adrese; 4. vrstva pokud je rozhodováno podle IP adresy a síťového portu
# Router
* router spojuje dvě sítě a přenáší mezi nimi data
* na třetí vrstvě OSI modelu
* nejčastěji spojován s IP protokolem; lze použít i jiné protokoly
* jako router může být využít jakýkoliv počítač s podporou síťování; v menších sítí se často používají běžné osobní počítače; ve vysokorychlostních sítích se používají vysoce účelové počítače obvykle se speciálním hardwarem
* *"jednoruký" router* - používá jeden port a routuje packety mezi VLAN provozovanými na této zásuvce
* *"okrajový" router*/*gateway* - připojuje klienty k vnější síti (většinou Internet)
* *"vnitřní" router* - přenáší data mezi jinými routery
* *routovací tabulka* - obsahuje nejlepší cesty k jistým cílům
# Repeater
* přijímá poškozený signál a zesílený ho vyšle dále
* k zvýšení dosahu média bez ztráty kvality a obsahu signálu
* patří do první vrstvy OSI modelu (pracuje přímo s el. signálem)
* odstraňuje šum tím, že obnoví příchozí signál do původní digitální podoby a poté jej znovu převede do analogové podoby a vyšle ve správný čas
* u Ethernetu je jejich počet omezen z důvodu kolizních protokolů
* komunikace
	* bezdrátová
		* repeater se skládá z rádio přijímače, zesilovače, vysílače, izolátoru a dvou antén
		* vysílač generuje signál na odlišné frekvenci od signálu na vstupu; ochrana vstupu od zesíleného signálu; izolátor v tomto případě poskytuje dodatečnou ochranu
		* umisťují se na střechy vysokých budov, vrcholky kopců aj.
		* rádiový signál - k oddělení signálu v jejich frekvenčním rozsahu od jednoho přijímače ke druhému
		![bezdrátový opakovač](https://upload.wikimedia.org/wikipedia/commons/f/f1/Repeater-schema.svg)
	* optická
		* repeater je složen z fotobuňky (přijímač) a LEDky/IREDky (vysílač)
		* signál je převeden na elektronický a po zrestaurování zpět na optický, který je dále vysílán
		* pracují s mnohem menšími výkony, než bezdrátové; mnohem jednodušší a levnější
		* jejich výroba vyžaduje vyšší přesnost a kvalitu; z důvodu minimalizace šumu
# Bridge
* spojuje dvě části sítě na druhé vrstvě OSI modelu; pro vyšší vrstvy je most neviditelný
* odděluje provoz různých segmentů sítě a tím zmenšuje její zatížení
* v RAM si sám sestaví tabulku [[M19 Standardizace v oblasti sítí#MAC|MAC adres]] a portů
* leží-li příjemce ve stejném segmentu jako odesílatel, most packety do jiných částí sítě neodešle; v opačném případě je odešle do příslušného segmentu v nezměněném stavu (Unicast packety) nebo je propoustí bez omezení (Multicast, Broadcast)
* *transparent bridging*
	* mosty jsou neviditelné pro koncové stanice
	* zařízení na začátku vůbec neví, jak jsou jednotlivé stanice v síti rozloženy, a musí paket přijatý na jedné síti poslat do všech ostatních připojených sítí, protože ještě neví, kde se cílová stanice nachází; postupně se naučí, jak jsou stanice v síti rozloženy
* source route bridging
	* ve spojení s token ring sítěmi
	* každý packet musí kromě adresy odesílatele a příjemce obsahovat také posloupnost adres všech mostů, kterými musí paket projít
* snižuje velikost kolizní domény
* transparentní k protokolům z vyšších vrstev
* vyšší latence, než opakovače z důvodu čtení MAC adresy; dražší než opakovače
* bridging × routing
	* bridging a routing jsou podobná řízení toku dat, ale pracují pomocí různých metod
	* bridging se provádí na 2. vrstvě; routing na 3. vrstvě
	* most směruje packety podle jejich hardwarové MAC adresy; router se rozhoduje podle IP adresy uvnitř přenášeného datagramu
# Kabely
## Měděné
* vysoká rychlost a stabilita
* levnější než optika
* obtížněji napadnutelné než bezdrátové sítě
* délka kabelu je omezena (zejména u vyšších rychlostí přenosu)
* UTP
	* ze dvou nebo více párů měděných drátů zkroucených dohromady
	* kroucení snižuje elektromagnetické rušení
* STP
	* podobný jako UTP
	* každý pár drátů je navíc chráněn kovovým opletením - vyšší úroveň ochrany proti rušení
	* Coaxial - centrální vodič obklopený izolací a kovovým opletením
## Optické
* vysoká rychlost, dlouhý dosah a odolnost vůči rušení než u mědi
* přenášejí data ve formě světelných impulsů po tenkém skleněném nebo plastovém vlákně
* signál se v optickém vlákně tlumí mnohem méně než v měděném kabelu
* nejsou ovlivněny elektromagnetickým rušením
* vlákna jsou křehká a mohou se snadno poškodit
# Konektory
* fyzické propojení jednotlivých zařízení přenosovým médiem (nejčastěji kabel)
* každý typ kabelu vyžaduje specifický typ konektoru
* různé konektory podporují různé rychlosti přenosu dat
* některé prostředí (např. průmysl) vyžadují odolnější typy konektorů
* rozdíl v počtu pinů
## Typy
* RJ-45
	* konektor UTP a STP kabelů
	* název vychází z podobnosti s telefonními koncovkami (ty jsou však s moderními počítačovými síťovými kabely nekompatibilní)
	  ![Zapojení kabelů](TVP_23_9_24.png)
* SC
	* konektor pro optická vlákna
	* čtvercový tvar a jednoduchý západkový mechanismus
	* **\[Obrázek SC konektoru]**
* ST
	* konektor pro optická vlákna
	* kulatý tvar a používá bajonetový zámek pro zajištění
	* obecně považovány za robustnější než SC konektory
* LC
	* nejmenší typ konektorů pro optická vlákna
	* západkový mechanismus
	* liší se úhlem leštění koncovky optického vlákna
* FC
	* konektor pro optická vlákna
	* navrženo pro prostředí s vysokými vibracemi
	* kabel končí 2,5 mm kováním (Zinek nebo nerez)
	* špička je naleštěna do koule
* BNC
	* konektor pro koaxiální kabely
	* impedance 50 až 75 Ohmů
	* pro frekvence do 4 GHz; napětí do 500 voltů
