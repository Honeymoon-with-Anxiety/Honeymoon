#technicke_vybaveni_pocitacu 
* standardizace
	* proces sjednocování a zavádění norem
	* normy určují požadavky na: vlastnosti, rozměry, výkon, bezpečnost aj.
	* cílem je soulad a kompatibilita mezi prvky
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
* vrstvy
	![Model ISO/OSI](https://upload.wikimedia.org/wikipedia/commons/4/4d/Rm-osi_parallel_cs.svg)
	* fyzická (protokol: 10Base5)
		* zajišťuje přenos bitů po fyzickém médiu (sériová linka nebo Ethernet)
		* definuje elektrické a fyzikální vlastnosti zařízení (rozložení pinů, napěťové úrovně...)
		* efektivně rozkládá všechny zdroje mezi všechny uživatele
		* [moduluje](obsidian://open?vault=E3A&file=TVP%2FMO4%20Sign%C3%A1ly)
	* linková (protokol: Ethernet)
		* poskytuje spojení mezi dvěma sousedními systémy
		* uspořádává data z fyzické vrstvy do rámců (frames)
		* stará se o nastavení parametrů přenosu linky
		* oznamuje neopravitelné chyby
		* opatřuje rámce fyzickou adresou
		* poskytuje synchronizaci pro fyzickou vrstvu
	* síťová (protokol: IPv4)
		* stará se o směrování v síti a síťové adresování
		* poskytuje spojení mezi systémy, které spolu nesousedí
		* umožňuje překlenout rozdílné vlastnosti technologií v přenosových sítích
		* poskytuje funkce k zajištění přenosu dat různé délky skrze jednu nebo několik propojených sítí
		* poskytuje směrovací funkce
		* reportuje o prolémech při přenosu dat
	* transportní (protokol: spojově (TCP) a nespojově (UDP) orientované protokoly)
		* zajišťuje spolehlivý přenos dat mezi koncovými zařízeními
	* relační (protokol: NetBIOS, RPC)
		* organizuje a synchronizuje dialog mezi spolupracujícími vrstvami obou systémů
		* řídí výměnu dat mezi nimi
		* vytváří a ukončuje relační spojení, synchronizuje je a obnovuje jejich spojení
		* přiřazuje synchronizační značky
	* prezenční (protokol: MIME)
		* transformuje data do požadovaného tvaru aplikace (šifrování, konvertování, komprimace)
		* zabývá se jen strukturou dat, nikoliv významem
	* aplikační (protokol: HTTP, FTP, DNS, BitTorrent, POP3, SMTP, SSH) - umožňuje aplikacím přístup ke komunikačnímu systému a umožňuje jejich spolupráci
## Protokoly
* 10Base5 - historicky nejstarší verze Ethernetu; rychlost 10 Mbit/s; segmenty o max. délce 500 m a 100 počítačů 
* Ethernet - souhrn technologií pro LAN sítě
* IPv4 - protokol přepravující data bez záruky; poskytuje teoreticky $2^{32}$ možných adres (ve skutečnosti jich je méně)
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
## MAC
## IP
## Process ID
# DNS
# LAN, WAN, Intranet
## LAN
## WAN
## Intranet
# Strukturovaná kabeláž