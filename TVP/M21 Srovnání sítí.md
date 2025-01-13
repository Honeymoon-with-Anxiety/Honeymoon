#technicke_vybaveni_pocitacu 
* sběrnicová topologie
	* spojení zprostředkovává jediné přenosové médium (sběrnice), ke kterému jsou připojeny všechny uzly sítě (koncová zařízení)
	* jakmile chtějí dva klienti na síti vysílat ve stejný okamžik vzniká kolize
	![Schéma sběrnicové topologie](https://upload.wikimedia.org/wikipedia/commons/4/4d/NetworkTopology-Bus.png)
# Porovnání Ethernetu a Token Ringu
## Princip funkce
* řešení kolize
	* Ethernet
		* každé zařízení může vysílat data
		* pokud dvě a více zařízení vyšlou data současně a dojde kolize, zařízení se pokusí vyslat data po náhodném zpoždění
	* Token Ring
		* v síti koluje speciální rám, který říká, kdo může posílat v danou chvíli data
		* po odeslání dat je token předán dál
* topologie
	* Ethernet je zapojen do [[M20 Základní síťový hardware#^9dcba9|hvězdicové topologie]]; dříve i sběrnicová
	* Token ring je zapojen logicky do kruhu; fyzicky do hvězdy (centrální [[M20 Základní síťový hardware#Hub|hub]] slouží pouze jako spoj mezi zařízeními)
* výhody
	* Ethernet
		* jednoduchost implementace
		* vysoká propustnost při nízkém zatížení
		* nízké náklady
	* Token ring
		* vyšší výkon při vysokém zatížení ve srovnání s Ethernetem
* nevýhody
	* Ethernet
		* možnost kolizí, které mohou snížit výkon při vysokém zatížení
		* obtížnější správa sítě
	* Token ring
		* složitější implementace
		* vyšší náklady
		* pokud selže jedno zařízení, může to ovlivnit celou síť
## Se zátěží
* Ethernet
	* nízké zatížení - vysoká propustnost; málo pravděpodobné že dojde ke kolizi
	* střední zatížení - s rostoucím zatížením se zvyšuje pravděpodobnost kolizí → snížení výkonu
	* vysoké zatížení - při velmi vysokém zatížení může dojít k tak častým kolizím že síť je prakticky nepoužitelná
* Token ring
	* nízké zatížení - při nízkém zatížení nižší propustnost → je nutné čekat na získání tokenu
	* střední zatížení - výkon se zvyšuje; token je neustále v oběhu a zařízení mohou rychle reagovat na jeho získání
	* vysoké zatížení: při velmi vysokém zatížení je udržen relativně stabilní výkon; kolize jsou vyloučeny díky tokenům
# WiFi
* skupina bezdrátových síťových protokolů
* pro místní síťové propojení zařízení a pro přístup k internetu (pomocí [[M20 Základní síťový hardware#Router|směrovače]])
* umožňují blízkým digitálním zařízením vyměňovat si data prostřednictvím rádiových vln
* Nově nainstalovaná domácí Wi-Fi síť v dubnu 2022 ![Nově nainstalovaná domácí Wi-Fi síť v dubnu 2022](https://upload.wikimedia.org/wikipedia/commons/b/bb/Home_wifi.jpg)
* různé verze WiFi používají různé rádiové technologie → různá rádiová pásma a maximální dosahy a rychlosti
* nejčastěji rádiová pásma 2,4 GHz (120 mm) ultra krátkých vln a 5 GHz (60 mm) superkrátkých vln; pásma jsou rozdělena do několika kanálů
* v rámci dosahu může na jednom kanálu vysílat vždy pouze jeden vysílač
* překážky
	* např.: zdi, sloupy, domácí spotřebiče
	* mohou výrazně snížit dosah
	* pomáhají minimalizovat rušení mezi různými sítěmi v přeplněném prostředí
* dosah přístupového bodu je ~20 metrů v interiéru; až 150 metrů ve venkovním prostředí
* zajišťuje komunikaci na [[M19 Standardizace v oblasti sítí#^61e86e|linkové vrstvě]] - přenáší zapouzdřené ethernetové packety
* SSID
	* řetězec až 32 ASCII znaků
	* rozlišuje jednotlivé sítě
	* v pravidelných intervalech vysílán jako broadcast
	* potenciální klienti si mohou zobrazit dostupné bezdrátové sítě, ke kterým je možné se připojit
* zabezpečení
	* kontrola [[M19 Standardizace v oblasti sítí#MAC|MAC adres]] - přípojný bod bezdrátové sítě má k dispozici seznam MAC adres klientů, kterým je dovoleno se připojit
	* zablokování vysílání SSID
	* WPA - klíče, které jsou často dynamicky bezpečným způsobem měněny; WPA2 přináší lepší šifrování klíčů
	* WPS - po stisknutí tlačítka na přístupovém bodě automaticky připojit bezdrátového klienta bez autentizace
# Bluetooth
* spadá do kategorie osobních počítačových sítí
* čtyři volby přenosové rychlosti mezi 2 Mb/s až 125 kbit/s; čím menší přenosová rychlost, tím větší dosah
* v Bluetooth 4.2 malé velikosti zpráv omezené na 31 bajtů; Bluetooth 5 umožňuje vysílání zpráv až o velikosti 255 bajtů
* pracuje v pásmu 2,4 GHz (stejném jako Wi-Fi); během jedné sekundy je provedeno 1600 skoků (přeladění) mezi 79 frekvencemi s rozestupem 1 MHz - odolnost spojení vůči rušení na stejné frekvenci
* komunikace do vzdálenosti 1–100 m (ve volném prostoru)
* přenosová rychlost se pohybuje okolo 720 kbit/s (90 KiB/s)
* datové spoje
	* symetrické
	* asymetrické - přenosová rychlost při příjmu je vyšší než při odesílání
* jednotlivá zařízení jsou identifikována pomocí své adresy `BD_ADDR`(podobně, jako je MAC adresa u Ethernetu)
* jedna radiová stanice jako řídicí (master) může současně obsloužit až 7 podřízených (slave) zařízení; synchronizují se taktem řídicí stanice
* komunikace na linkové vrstvě i vyšší - každý typ připojitelného zařízení musí mít definován komunikační protokol
# Porovnání podle technologie IR, RF
* IR
	* člověkem neviditelné infračervené záření pro přenos dat
	* dosah několik metrů (přímočaře)
	* nízká přenosová rychlost ve srovnání s RF sítěmi
	* použití: dálkové ovládání televizorů, dálková komunikace mezi zařízeními v malé místnosti (např. počítač a tiskárna)
	* nízká cena zařízení
	* nízká interference od jiných zařízení
	* citlivost na okolní světlo
* RF
	* rádiové vlny pro přenos dat
	* dosah od několika metrů až po několik desítek metrů
	* použití: WiFi, Bluetooth, mobilní sítě...
	* lepší průniky signálů přes překážky
	* možnost interference od jiných zařízení pracujících na stejné frekvenci
* porovnání - závisí na konkrétních požadavcích aplikace
	* krátký dosah a nízká cena → IR technologie
	* větší dosah, vyšší přenosová rychlost, odolnost vůči překážkám → RF technologie
