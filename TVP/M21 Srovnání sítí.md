#technicke_vybaveni_pocitacu 
* sběrnicová topologie
	* spojení zprostředkovává jediné přenosové médium (sběrnice), ke kterému jsou připojeny všechny uzly sítě (koncová zařízení)
	* jakmile chtějí dva klienti na síti vysílat ve stejný okamžik vzniká kolize
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
# Bluetooth
# Porovnání podle technologie IR, RF