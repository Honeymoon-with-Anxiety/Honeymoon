#technicke_vybaveni_pocitacu 
* tvorba umělých grafických objektů; úprava zobrazitelných a prostorových informací, nasnímaných z reálného světa
* grafická karta
	* vytváří grafický výstup na monitoru
	* grafický procesor (GPU) slouží pro rychlé a efektivní změny obsahu grafické paměti
	* karta se stará o grafický výstup na zobrazovací jednotku
	* pokud karta obsahuje VIVO (video-in a video-out) umožňuje analogový vstup videosignálu - ukládání videosouborů z videokamery, videopřehrávačů apod
	* součásti
		* GPU - obsahuje řadič paměti, unifikované shadery a další; zpracovává 3D geometrii na 2D obraz
		* Video RAM - počítačová paměť, kde jsou ukládány obrazové informace
		* firmware
		* RAMDAC - převodník digitálního signálu, se kterým pracuje grafická karta, na analogový, kterému rozumí zobrazovací zařízení
		* výstupy - VGA, HDMI, DVI, DisplayPort aj.
	* výrobci - AMD, NVIDIA, Intel (většinou integrované grafiky)
# Displej
* zařízení pro zobrazování informací jako je text nebo obraz v různé podobě
* v elektronických přístrojích slouží k zobrazování různých údajů
* používají se pro konstrukci terminálů
* split-flap display
	* první dálkově či automaticky ovládané displeje
	* byly tvořeny otočnými listy
	* na jednotlivých listech mohly být jednotlivé znaky i celá slova či víceslovné informace
	![Displej Pragotron z listových překlápěcích jednotek](https://upload.wikimedia.org/wikipedia/commons/5/5e/Beroun%2C_odjezdov%C3%A1_tabule%2C_detail.jpg)
* flip-dot display
	* body tvořené otočnými dvoupolohovými disky
	* ovládány elektromagneticky nebo servomotorky
	* v některých verzích osvíceny LED diodami
	* často závadou je nefunkčnost některých bodových disků či zpoždění při jejich otáčení
	![Čas zobrazený otočnými bodovými disky na silniční informační tabuli, s vadně natočenými body](https://upload.wikimedia.org/wikipedia/commons/e/ed/Ho%C5%99ej%C5%A1%C3%AD_n%C3%A1b%C5%99e%C5%BE%C3%AD%2C_za%C5%99%C3%ADzen%C3%AD_pro_provozn%C3%AD_informace%2C_%C4%8Das_20.06.jpg)
* digitron
	* první elektronické displeje bez mechanické části
	* text nebo číslice byly sestaveny z několika výbojek umístěny za sebou v jednom průhledném pouzdru; podle potřeby se jednotlivé výbojky rozsvěcovaly a vytvářely tak svítící čísla
	* nevýhodou byla relativně vysoká spotřeba, potřeba vysokého napětí a jednotlivé číslice byly v nestejné vzdálenosti od pozorovatele
	![Digitron, LED displej ze svítivých diod a VF displej](https://upload.wikimedia.org/wikipedia/commons/1/1e/Anzeigen%28Displays%29.jpg)
## LED
* aktivní zobrazovací zařízení
* hlavním aktivním prvkem jsou světelné diody pokrývající celou plochu obrazovky
* princip aditivního sčítání barev
	* každý jednotlivý plněbarevný bod obrazovky tvoří trojice LED diod (R, G, B)
	* při sledování velkoplošné LED obrazovky z určité vzdálenosti barevný svit všech tří LED splyne díky omezené rozlišovací schopnosti lidského oka
	* čím větší je rozteč mezi jednotlivými LED, tím větší je i minimální pozorovací vzdálenost
	![Detail LED obrazovky](https://upload.wikimedia.org/wikipedia/commons/f/fa/MK38527_LED_Display.jpg)
* stínítka jsou výstupky tvořící stříšku nad LED - zabraňuje dopadu slunečního záření; chrání před mechanickým poškozením
* černá barva podkladu obrazovky zajišťuje optimální podmínky pro maximální využití barevné škály a intenzity vyzařovaného světla
* rozdílnou intenzitou svitu jednotlivých LED lze docílit zobrazení až 68 miliard barev
* obrazová data jsou zpracovávána v počítači prostřednictvím řídící aplikace, která každé LED přiřazuje odlišnou intenzitu svitu
* informace je zasílána do řídící jednotky uvnitř samotné obrazovky
* výhody
	* dobře viditelné na přímém slunci
	- venkovní použití
## LCD
* tenké a ploché zobrazovací zařízení
* skládá se z omezeného (velikostí monitoru) počtu [barevných](https://youtu.be/jLew3Dd3IBA) nebo [monochromatických](https://youtu.be/eGQQWIbD-nM) pixelů seřazených před zdrojem světla nebo reflektorem
* vyžaduje poměrně malé množství elektrické energie
* obecné schéma LCD![Schéma LCD](TVP_13_10_24.png)
* [TN LCD](https://youtu.be/J6W1jYoa1HM)
* funkce řádkových LCD displejů
	* k zobrazování textu na několika řádcích
	* kalkulačky, hodinky, budíky, mikrovlnné trouby, audio přehrávače, měřící přístroje, Arduino a jiné mikrokontrolérové projekty
	* jsou obecně levnější než jiné typy displejů
	* mohou zobrazovat pouze text a jednoduché symboly
	* rozlišení těchto displejů je obvykle nízké
	* obvykle 16×2 znaků
# [Barva](https://youtu.be/srRI7yMjGz0)
* historie
	* první barevné fotografie byly černobílé s nanesenou barvou
	* Maxwell přišel s nápadem vyfotit objekt 3× pokaždé s odlišným filtrem; poté posvítit na fotografii barvou filtru a výsledek s míchat se zbytkem; první barevná fotografie touto metodou - Thomas Sutton
* míchání barev
	* subtractive
		* RYB prostor
		* využito v malířství
		* absorpce určitých vln z bílého světla a odraz zbylých
	* additive
		* RGB prostor
		* využito v zachycování světla a fotografování
		* skládání červené, zelené a modré k vytvoření nové barvy; složením všech tří barev vznikne bílá
* barevné prostory
	* CIE XYZ 1931
		* výsledek sledování reakce lidského oka na různé vlnové délky světla
		* dnes stále porovnáván s ostatními prostory
		* nepřesný ve světlosti ![Nepřesnosti](TVP_14_10_24@1.png)
	* CIE LUV (CIE 1976)
		* L - světlost; U - přechod ze zelené do červené; V - přechod z modré do žluté
		* používaný v designu osvětlení a v TV
	* CIE LAB
		* L - světlost; A - přechod ze zelené do červené; B - přechod z modré do žluté
		![Porovnání](TVP_14_10_24@2.jpg)
	* CIE LCH
		* L - světlost; C - chroma (jak moc barevný); H - hue (červená, žlutá, zelená...)
* pixel
	* rozdělen do 3 subpixelů - RGB
	* data jsou uchována v bitech (bit na subpixel)
		* 1 bit - $2 × 2 × 2 = 8$ barev (2 stavy subpixelu)
		* 2 bity - $4×4×4 = 64$ barev (4 stavy subpixelu)
		* 3 bity - $8×8×8 = 512$ barev (8 stavů subpixelu)
* reprezentace barevných prostorů na displeji
	* v 90. letech nejčastější prostor RGB
	* Rec. 709
		* podporuje ~70 % CIE XYZ 1931
		* určeno pro HDTV a HD monitory
		* jas byl optimalizován spíše pro televize než pro kanceláře
	* standard RGB (sRGB)
		* spolupráce mezi HP a Microsoftem
		* určeno pro kanceláře a web
		* hodnota gammy = 2.2
	* Adobe RGBCIE XYZ 1931
		* Rec. 709 a sRGB vypadali moc vybledle
		* výrazně rozšiřuje azurovou a zelenou oproti sRGB
		* pokrývá ~52 % okem viditelných barev
		* určeno pro tisk
	* DCI-P3
		* vytvořeno filmovými studii
		* má výraznější zelenou
		* pokrývá ~53 % CIE XYZ 1931 diagramu
		* oproti ostatním má teplejší bílou (středový bod; ostatní 6500 K, DCI-P3 6300 K)
	* Display P3 - úprava DCI-P3 Applem pro své displeje
	* Rec. 2020 - pokrývá ~75 % diagramu
	* Rec. 2100 (HDR)
	![Diagram barev](TVP_14_10_24@3.jpg)
# Řadič
* řídí a synchronizuje všechny části displeje
* řadič dostává od procesoru data, co se má na displeji zobrazit ve formě bitů, které představují jednotlivé pixely
* řadič ovládá jednotlivé pixely na displeji tak, aby vytvořily požadovaný obraz; určuje jak moc se má subpixel rozsvítit a v který čas
* další funkce: nastavení jasu, kontrastu, barevné teploty nebo automatické otáčení obrazu
* typy
	* TFT - pro řízení tenkovrstvých tranzistorových displejů; běžné v mobilních telefonech, tabletech a monitorech
	* OLED - řídí organické elektroluminiscenční displeje
	* STN - pro řízení super twist nematických displejů; levnější, nižší kontrast a pomalejší odezva
* parametry
	* rozlišení
	* frekvence snímání (FPS)
	* barevná hloubka - počet bitů, které se používají k reprezentaci barvy každého pixelu
	* rozhraní - přípojný konektor (dnes HDMI, DisplayPort, USB-C)
	* schopnost použít s dotykovým displejem
* konfigurace
	* základní - jas, kontrast, barevná teplota, ostrost
	* pokročilá - nastavení barev, gama křivky, redukce šumu, režimy obrazu
	* nastavení vstupu - výběr zdroje signálu, nastavení rozlišení a obnovovací frekvence
	* nastavení zvuku - pokud je řadič vybaven zvukovým výstupem, lze konfigurovat hlasitost a další zvukové parametry
	* tip - začít s výchozím nastavením; konfigurovat v tmavém prostředí; použít u toho testovací obraz
* komunikace
	* rozhraní
		* HDMI - přenos videa a zvuku ve vysoké kvalitě
		* DisplayPort - moderní digitální rozhraní podobné HDMI; vyšší šířka pásma
		* DVI (Digital Visual Interface) - starší digitální rozhraní široce používáno u počítačových monitorů
		* VGA (Video Graphics Array) - analogové rozhraní; stále se používá u starších zařízení; kvalita výrazně nižší
		* SPI - pro komunikaci s menšími displeji
		* I2C
	* proces
		1) zdrojové zařízení vytvoří digitální obraz a pošle jej přes zvolené rozhraní do řadiče obrazu
		2) řadič přijme data a dekóduje je
		3) řadič pošle signály na jednotlivé pixely displeje, aby se rozsvítily v požadované barvě a intenzitě
		4) řadič musí zajistit, aby všechny pixely byly osvětleny synchronně (aby obraz byl plynulý a bez blikání)
* podpůrné obvody
	* hlavní funkce - napájení, generování hodinového signálu, paměť, regulace jasu podsvícení, filtrace a potlačení elektromagnetického rušení, 
	* typické obvody
		* regulátory napětí
		* oscilátory - generují hodinový signál
		* paměť - k uchování nastavení, data obrazu a firmware
		* řadič podsvícení
		* ochranné diody - chrání obvody před přepětím a přebíjením
# Výpočet obrazu
* výpočet obrazu v grafických systémech zahrnuje matematické a algoritmické postupy pro transformaci digitálních dat do podoby vizuálního obsahu vhodného pro zobrazení na různých typech displejů
* modelování 3D scény
* stínování - definování vzhledu objektů pomocí světla, barev a textur
* texturování - detaily na povrchu 3D objektu
* transformace - převod 3D objektu na 2D plátno schopné se zobrazit na displeji
* rasterizace - převod 2D plátna na jednotlivé pixely
* renderování - výpočty barevných vlastností každého pixelu
