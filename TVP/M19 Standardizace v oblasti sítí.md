#technicke_vybaveni_pocitacu 
* standardizace
	* proces sjednocování a zavádění norem
	* normy určují požadavky na: vlastnosti, rozměry, výkon, bezpečnost aj.
	* cílem je soulad a kompatibilita mezi prvky
	* sdílení mezi různými spotřebiteli → individuální návrh zařízení
	* standardy jsou vytvářeny různými organizacemi
		* mezinárodní organizace pro standardizaci (ISO) - vytváří mezinárodně uznávané normy pro širokou škálu oblastí
		* Evropský výbor pro normalizaci (CEN) - zpracovává evropské normy
		* národní normalizační orgány - každá země má svůj národní orgán, který se zabývá tvorbou a zaváděním národních norem
		* odborné asociace a konsorcia - např. IEEE (Institute of Electrical and Electronics Engineers) pro oblast elektrotechniky a informatiky
# Význam standardizace v oblasti sítí
* pro efektivní komunikaci
* interoperabilita - různé systémy a zařízení (např. počítače, smartphony, tiskárny) mohou vzájemně spolupracovat; vytváření komplexních sítí
* není potřeba vyvíjet nové protokoly pro každé zařízení
* usnadnění správy a údržby sítě
* globální dostupnost služeb a informací - k síti se lze připojit odkudkoliv
# NIC
* NIC (Network Information Center) nebo-li Síťové informační centrum
* organizace spravující a koordinující určité části internetu; jakýsi "úřad" pro internetové služby
* např. [CZ.NIC](https://www.nic.cz) pro ČR nebo mezinárodní ICANN 
* úkol NIC
	* přiřazování unikátní IP adresy pro každé zařízení
	* registrace domén, e-mailových adres
	* správa DNS - převádí názvy na číselné IP pro konkrétní oblast
	* správa SSL certifikátů
# ISO, OSI
* popisuje, jak funguje komunikace v sítích
* rozděluje složitý proces komunikace do jednotlivých, srozumitelnějších vrstev
* umožňuje odborníkům lépe porozumět a analyzovat fungování sítí
* poskytuje společný základ pro vývoj a implementaci síťových protokolů a technologií
* dnes bývá nahrazen modelem TCP/IP
* při odesílání packety na sebe ve vrstvách "nabalují" data; při přijímání zase "odbalují"
* vrstvy
	![Model ISO/OSI](https://upload.wikimedia.org/wikipedia/commons/4/4d/Rm-osi_parallel_cs.svg)
	1) fyzická (protokol: 10Base5)
		* zajišťuje přenos bitů po fyzickém médiu (sériová linka nebo Ethernet)
		* definuje elektrické a fyzikální vlastnosti zařízení (rozložení pinů, napěťové úrovně...)
		* efektivně rozkládá všechny zdroje mezi všechny uživatele
		* [moduluje](obsidian://open?vault=E3A&file=TVP%2FMO6%20P%C5%99enos%20informace%23Modulace)
	2) linková (protokol: Ethernet) ^61e86e
		* poskytuje spojení mezi dvěma sousedními systémy
		* uspořádává data z fyzické vrstvy do rámců (frames)
		* stará se o nastavení parametrů přenosu linky
		* oznamuje neopravitelné chyby
		* opatřuje rámce fyzickou adresou
		* poskytuje synchronizaci pro fyzickou vrstvu
	3) síťová (protokol: IP)
		* stará se o směrování v síti a síťové adresování
		* poskytuje spojení mezi systémy, které spolu nesousedí
		* umožňuje překlenout rozdílné vlastnosti technologií v přenosových sítích
		* poskytuje funkce k zajištění přenosu dat různé délky skrze jednu nebo několik propojených sítí
		* poskytuje směrovací funkce
		* reportuje o prolémech při přenosu dat
	4) transportní (protokol: spojově (TCP) a nespojově (UDP) orientované protokoly)
		* zajišťuje spolehlivý přenos dat mezi koncovými zařízeními
	5) relační (protokol: NetBIOS, RPC)
		* organizuje a synchronizuje dialog mezi spolupracujícími vrstvami obou systémů
		* řídí výměnu dat mezi nimi
		* vytváří a ukončuje relační spojení, synchronizuje je a obnovuje jejich spojení
		* přiřazuje synchronizační značky
	6) prezenční (protokol: MIME)
		* transformuje data do požadovaného tvaru aplikace (šifrování, konvertování, komprimace)
		* zabývá se jen strukturou dat, nikoliv významem
	7) aplikační (protokol: HTTP, FTP, DNS, BitTorrent, POP3, SMTP, SSH) - umožňuje aplikacím přístup ke komunikačnímu systému a umožňuje jejich spolupráci
## Protokoly
* 10Base5 - historicky nejstarší verze Ethernetu; rychlost 10 Mbit/s; segmenty o max. délce 500 m a 100 počítačů 
* Ethernet - souhrn technologií pro LAN sítě
* IP - protokol přepravující data bez záruky
* TCP - obousměrné připojení zařízení schopný rozeznávat data pro jednotlivé aplikace na jednom počítači
* UDP - protokol nedávající záruky na datagramy (obvykle pakety související se službami, které neposkytují záruky) - je *bez záruky doručení*
* NetBIOS - zpřístupnění síťových prostředků a služeb pomocí názvů počítačů
* RPC - protokol dovolující programu vykonat kód na jiném místě, než je umístěn volající program
* MIME - přenášení textů v různých kódováních, binární data a vícedílné zprávy kanály původně navrženými pouze pro přenos textových zpráv v kódování ASCII
* HTTP - určený pro komunikaci s WWW servery; přenos hypertextových dokumentů ve formátu HTML nebo XML
* FTP - protokol pro přenos souborů mezi počítači; download i upload souborů (pokud má uživatel na operaci práva); postaveno na architektuře klient-server
* BitTorrent - protokol pro přenos souborů; postaveno na architektuře klient-klient (P2P)
* POP3 - stahování e-mailových zpráv ze serveru na klienta
* SMTP - přenos e-mailů pomocí přímého spojení mezi odesílatelem a adresátem
* SSH - zabezpečený komunikační protokol vzdálené shelly
# MAC, IP a ProcessID
* MAC adresa pracuje na linkové vrstvě, IP na síťové
* ARP protokol spojuje MAC a IP adresy v rámci jedné sítě; když zařízení chce odeslat paket do jiného zařízení, musí nejprve zjistit jeho MAC adresu
* IP adresa identifikuje síťové rozhraní; PID identifikuje konkrétní proces, který komunikaci využívá
## MAC
* globálně unikátní adresa síťové karty
* přiřazena přímo při výrobě
* nazývána "fyzická adresa"
* ethernetová MAC adresa se skládá ze 48 bitů; šestice dvojciferných hexadecimálních čísel oddělených pomlčkami nebo dvojtečkou
* prvních 24 bitů je určeno výrobcem
* původně zamýšlená jako permanentní; většina moderního HW umožňuje SW změnu adresy
## IP
* protokol používající rodinu protokolů TCP/IP
* neposkytuje záruku na přenos dat
* zodpovědný za přenos paketů ze zdrojového zařízení do cílového přes jednu nebo více IP sítí
* paket se skládá z metadat a z uživatelských dat; posílají se po blocích a putují po síti nezávisle
* IPv4 adresa
	* používá 32bitové číslo; definovaná 4 oktety (synonym pro byte)
	* dělí se na 3 části - *číslo sítě*, *číslo podsítě* a *číslo síťového rozhraní*
	* existují vyhrazené adresy
		* `127.x.x.x` - localhost; `127.0.0.1` - loopback (posílání packetů sám sobě)
		* pouze pro adresování vnitřních sítí; na internetu se nemohou objevit (např.  `10.x.x.x`)
* IPv6 adresa
	* používá 128bitové číslo rozděleno do 8 skupin po čtyřech hexadecimálních číslicích
	* pro několik po sobě jdoucích nulových skupin lze napsat `::` - lze použít **jen jednou**
## Process ID
* číslo, pod kterým je v jádře operačního systému jednoznačně evidován proces
# DNS server
* převádí název domény na IP adresu (nebo opačně)
* databáze je členěna do několika větví
	![Struktura](https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Ftse1.mm.bing.net%2Fth%3Fid%3DOIP.EhPVIkqr7ccO_VnKNRNkdgHaHa%26pid%3DApi&f=1&ipt=ca605c3d2a5e9a8a47a15e47900995753a5a233388b7ba25673e66ec62608bb9&ipo=images) 
* autoritativní server
	* trvale ukládá záznamy k dané doméně
	* obvykle min. 2 servery - primární a sekundární
	* obvykle provozovány registrátorem domény nebo poskytovatelem webhostingu
* rekurzivní
	* obracejí se na něj klienti (počítač, mobil aj.)
	* server pro ně získá záznam z autoritativních serverů; po stanovenou dobu (TimeToLive) je má uložené v cache
	* obvykle se používá DHCP protokol
# LAN, WAN, Intranet
## LAN
* lokální síť; uvnitř místností, budov nebo malých areálů; na vlastní náklady majitelů propojených počítačů
* obvykle vysoké přenosové rychlosti
* použito ke sdílení prostředků; propojení síťového prostoru, dálkový tisk, sdílení připojení k internetu
* složení
	* aktivní prvky → podílejí se aktivně na komunikaci (switch, router, síťová karta)
	* pasivní prvky → prvky nevyžadující napájení (propojovací kabel, konektory, někdy i hub)
## WAN
* rozlehlá síť; síť překračuje hranice města, regionu, státu; nejznámější Internet
* využito pro spojování LAN sítí mezi sebou nebo s Internetem
* většina WAN budována pro společnosti - jsou soukromé
* pro přenos a adresaci používají rodinu protokolů TCP/IP
## Intranet
* používá stejné technologie jako internet; je pouze lokální (LAN)
* označuje interní webové stránky ale i rozsáhlejší infrastrukturu (interní komunikace aj.)
* obvykle chráněny před externím přístupem sítí, bránou a firewallem ale i přihlášením uživatele osobním heslem
* [příklad](file:///home/pisek/Projekty/E4A/intranet/index.php) domovské stránky intranetu
# Strukturovaná kabeláž
* k propojení uživatelů v rámci sítě
* z metalických nebo optických prvků
* podporuje přenos digitálních i analogových signálů
* instaluje se na místa, kde nejsou momentálně potřeba
* očekává se od nich dlouhá životnost
* patch panely - k připojení jednotlivých uživatelů do aktivních zařízení
* zásuvky
* konektory
	* pro připojení kabelů k patch panelům a zásuvkám
	* RJ-45
		* 8pinový; pro zakončení UTP
		* UTP - nestíněný pro kroucené páry
		* FTP - stíněný pro kroucené páry; lepší ochrana proti rušení
		* STP - stínění kolem každého jednotlivého páru
		![RJ-45](https://encrypted-tbn2.gstatic.com/images?q=tbn:ANd9GcSl0Na-UHoQDfuvr-Lo2szVPBdLh90s-rkSCwmWjFRQ8k3LCsLEwPzm_1mlW2U_)
	* SC, ST, LC - optické konektory pro zakončení optických vláken
	* BNC - koaxiální konektor; ve starších sítích nebo připojení antén
* kabely
	* kroucené páry (UTP) - datové kabely se čtyřmi kroucenými páry
		![datové kabely se čtyřmi kroucenými páry](https://eshop.mtlcable.cz/strukturovana-kabelaz_ispt84.jpg)
	* optické - pro přenos dat na velké vzdálenosti; v prostředí s vysokým elektromag. rušením
	* kategorie
		* Cat3 - telefonní sítě
		* Cat5e - standardní kabel
		* Cat6 - vyšší přenosová rychlost; pro náročnější prostředí
		* Cat6A/Cat7 - velmi vysoké přenosové rychlosti; pro náročnější prostředí
* rozvaděče - centrální místo; zde se sbíhají všechny kabely v budově
