#technicke_vybaveni_pocitacu
* přenos zdigitalizovaného analogového signálu pomocí přenosového média
* zahrnuje *vysílání* a *příjem*
* datová komunikace zahrnuje i přípravu k odeslání, řízení přenosu a procesy navazující na příjem
# [[MO4 Signály#Vzorkovací teorém|Vzorkovací teorém]]
* "K dosažení přesné rekonstrukce spojitého signálu s omezeným frekvenčním rozsahem z jeho vzorků je potřeba, aby vzorkovací frekvence přesáhla dvojnásobek frekvence nejvyšší harmonické složky vzorkovaného signálu."
* v praxi se vzorkovací volí dvakrát větší plus rezerva
# [[MO4 Signály#Šířka pásma|Šířka pásma]]
* rozdíl mezi nejvyšší a nejnižší frekvencí přenášeného signálu
* vyjádřeno v hertzech (Hz)
* v informatice se používá ve smyslu přenosové rychlosti
$$ B = f_{H}-f_{l}$$
# Šum
* nežádoucí signál zpravidla náhodné povahy; data bez významu
* nejčastější příčiny: vysoká frekvence, nízká energie
* vlnka je funkce používaná k rozkladu funkce nebo signálu vlnkovou transformací
* vlnková transformace umožňuje získat časově-frekvenční popis signálu; lze na ni nahlížet také jako na prostředek k rozkladu signálu na nezávislé stavební kameny
## Obraz
* například obraz z digitálních nebo filmových kamer, kde je k dispozici pouze jediná realizace snímku
* typy šumu
	* náhodný šum, také nezávislý šum (příkladem tohoto typu šumu je šum typu „sůl a pepř“)
	* Gaussův šum, také závislý šum, kde je každý pixel obrazu mírně pozměněn
## Odstranění
* bez znalosti charakteristiky šumu nebo signálu není možné šum odstranit
* prahování vlnkových koeficientů
	* nejprve se spočítá diskrétní vlnková transformace signálu
	* pro prahování koeficientů je možno použít jakýkoli postup
	* nejčastěji se ale používá tvrdé (_hard_) či měkké (_soft_) prahování
		* při tvrdém se koeficienty menší než práh λ nahradí nulami
		
			 ${\displaystyle \rho _{\lambda }^{hard}(x)={\begin{cases}x\quad |x|\geq \lambda \\0\quad |x|<\lambda \end{cases}}}$
			 
		* u měkkého se navíc ostatní posunou o velikost prahu směrem k nule (to má za následek větší ztrátu energie signálu).
		
			${\displaystyle \rho _{\lambda }^{soft}(x)={\begin{cases}x-\lambda \quad &x\geq \lambda \\x+\lambda \quad &x\leq -\lambda \\0\quad &|x|<\lambda \end{cases}}}$
		* volba prahu závisí na použitých vlnkách i charakteru šumu a může být odlišná v různých měřítkách
		
	![Ukázka odstranění šumu ze signálu prahováním koeficientů vlnkové transformace](https://upload.wikimedia.org/wikipedia/commons/1/10/Wavelet_denoising.svg)
* metody odstranění šumu u obrazu
	* je třeba vhodně zvolit barevný model
	* lineární filtry
		* podle frekvenční charakteristiky šumu mají tyto lineární filtry často charakter dolní propusti
		* Gaussův filtr
			* tato metoda vede k rozmazání obrázku, což může být pro další zpracování obrazu problém (například pro detekci hran)j
			* je to efektivní technika k potlačení Gaussova šumu.
		* průměrování
			* hodnota každého pixelu je určena průměrem jeho a jeho nejbližších sousedů
			* vede k rozmazání obrazu
			* je efektní k potlačení Gaussova šumu
		* dolní propust
			* obecná dolní propust propustí jen nízké frekvence (šum je zpravidla vysokofrekvenční)
	* nelineární filtry
		* mediánový filtr
			* filtr vezme pro každý pixel obrazu jeho okolí; ze všech těch pixelů vybere medián, který se stává novou hodnotou zpracovávaného pixelu
		* prahování vlnkových koeficientů
# Modulace
* nelineární proces měnící charakter nosného signálu pomocí modulujícího signálu
* elektronika využívající modulaci: např rozhlasový a televizní přijímač, mobilní telefon, různé typy modemů, satelitní přijímače, atd.
* posílí signál (nesenou informaci), aby mohl být přenesen na delší vzdálenost
![Schematická značka modulátoru](https://upload.wikimedia.org/wikipedia/commons/9/93/Zna%C4%8Dka-Modul%C3%A1toru.png)
* rozdělení
	* spojité analogové
		* nosným signálem je signál s harmonickým průběhem v čase a modulačním signálem je analogový signál
		* libovolný harmonický signál je definován amplitudou (A), úhlovou frekvencí (ω) a fázovým posuvem (φ) $y = A * \sin{\omega t + \phi}$
		* podle toho, který z výše uvedených parametrů je ovlivňován modulačním signálem, jsou spojité modulace rozděleny na amplitudovou (AM), frekvenční (FM) nebo fázovou (PM)
	* spojité digitální
		* nosným signálem je signál s harmonickým průběhem, modulačním signálem je diskrétní (digitální) signál
		* pokud je modulačním signálem typický analogový signál nabývající nekonečného počtu hodnot, nabývá také výsledný fázor modulovaného signálu nekonečného množství hodnot
	* diskrétní
		* nosným signálem těchto modulací je signál s nespojitým průběhem často také nazývaný taktovací signál
		* modulace se rozděluje podle toho, jestli je modulační signál spojitý (nekvantovaný) nebo diskrétní (kvantovaný)
# Kódování
* převod informací z jednoho formátu nebo reprezentace do jiného
* chápeme jako přiřazování určitých řetězců znaků konkrétním zprávám, jež vycházejí ze zdroje
* znaky v řetězcích přitom tvoří jistou abecedu
* pokud mají všechny řetězce stejnou délku, pak za obor hodnot takového přiřazení stačí brát množinu, pokud se ale délka řetězců pro různé zprávy může lišit, bude obor hodnot takového přiřazení podmnožina množiny
* analogové kódování - převod kontinuálních hodnot do digitálního formátu
* digitální kódování - převod diskrétních hodnot (často binárních) na jiný formát
* používáme pro efektivnější přenos, ukládání nebo zpracování informací
# Parita
* základní význam: rovnost, rovnocennost, porovnatelnost hodnot
* paritní bit
	* redundantní (nadbytečný) bit přidaný k datovému slovu a obsahuje paritní informaci o počtu jedničkových bitů ve slově
	* je určen k jednoduché detekci chyby ve slově
	* hodnotu paritního bitu lze jednoduše vypočítat jako XOR mezi všemi datovými bity slova
	* lichá parita znamená lichý počet jedničkových bitů ve slově (i s paritním bitem); sudá parita sudý počet jedničkových bitů ve slově

| 7bitová data | 8 bitů včetně sudé parity | 8 bitů včetně liché parity |
| ------------ | ------------------------- | -------------------------- |
| 0000000      | 0000000**0**              | 0000000**1**               |
| 1010001      | 1010001**1**              | 1010001**0**               |
| 1101001      | 1101001**0**              | 1101001**1**               |
| 1111111      | 1111111**1**              | 1111111**0**               |

# Opravné kódy
* používány k detekci a opravě chyb, které mohou vzniknout během přenosu dat
* kódy s jednobitovou korekcí
	* Hammingovy kódy - mohou být použity pro posílání dat v situacích, kde je vysoce pravděpodobné vznik chyb, například v paměti počítače
* kódy s mnohobitovou korekcí
	* BCH *(Bose-Chaudhuri-Hocquenghem)* kódy - využívány v bezdrátových komunikačních systémech a digitální televizi
* Reed-Solomon kódy
	* schopny detekovat a opravit chyby v blokových datech
	* využívány v kódech pro CD, DVD, QR kódy a další
* Turbo kódy
	* založeny na kombinaci dvou nebo více kódů
	* používány ve 3G a 4G mobilních sítích a v jiných komunikačních systémech s vysokým datovým tokem
* Low-Density Parity-Check *(LDPC)* kódy - používané v bezdrátových komunikačních systémech a v komunikacích ve vesmíru
* Konvoluční kódy - používány v komunikačních systémech, kde jsou vyžadovány rychlé a efektivní metody detekce a korekce chyb (např. v bezdrátových sítích)

# Přenosová média
* způsoby přenosu: opticky, mechanicky, bezdrátově
	* různé přenosové trasy, včetně vodičů, optických vláken a bezdrátových spojů, poskytují rozmanité možnosti pro přenos informací
	* výběr vhodné trasy závisí na specifických požadavcích systému a dostupných technologiích
* prostředí, které může přenášet vlnění nebo jinou formu energie
* nejrozšířenější metalické kabely
* pomocí elektromagnetického vlnění (nejčastěji pomocí rádiových vln), je možné komunikovat volným prostorem i vzduchoprázdným prostředím
# Konektor
* elektrotechnická součástka
* zajišťuje zasunovací slaboproudé elektrické spojení vodičů a kabelů rozebíratelné (připojitelné a odpojitelné) opakovatelně bez nářadí
* jako svorka se označuje připojovací místo na elektrickém přístroji, kde je jednotlivý vodič připojován pomocí nástroje
* tělo konektoru
	* mech. část sestavená z plastových a kovových výlisků
	* zajišťuje mechanické spojení a izolační vlastnosti konektoru
* kontaktní prvky
	* zajišťují elektrické spojení
	* nejčastěji použitý tvar kontaktů je kolík kruhového průřezu
* alespoň jedna část upevněna na kabelu nebo výměnné jednotce; protikus může být také součástí kabelu, nebo je napevno namontovaný
* druhy
	* sériový port
		* nejrozšířenější u starších počítačů; dnes stále k nalezení
		* malá rychlost přenosu (115 KB/s)
		* obyčejný počítač obsahuje dva porty značené jako `COM1` a `COM2`
	* port PS/2
		* kulaté provedení
		* výhradně pro klávesnice a myš
		* nelze připojit klávesnici do portu na myš a naopak
	* konektor DIN
		* kulaté provedení
		* pro klávesnice jen u starších AT motherboardech
	* paralelní port
		* 25pinový
		* rychlý přenos
		* komunikace s perifériemi náročná
		* dnes pro připojení starých tiskáren a skenerů
	* Universal Serial Bus
		* rychlost 1,5 MB/s až 12 MB/s (USB 1.1), 480 MB/s (USB 2.0)
		* lze do něj zapojovat zařízení během chodu počítače
	* konektory zvukové karty
		* na standartních zvukových kartách jsou čtyři konektory
		* první pro reproduktory; druhý pro mikrofon; třetí pro vstup CD přehrávače; čtvrtý herní (gamepad, joystick)
		* občas se objeví pátý "Line-out" pro připojení zesilovače nebo Hi-Fi věže
	* BNC a RJ-45
		* na zadní straně síťových karet
		* připojení počítačů do sítě
	* IDE
		* připojení pevných disků, CD/DVD mechanik, disketových mechanik
		* směřuje do základní desky
	* High Definition Multimedia Interface
		* dokážou přenášet video, audio ale také jiné druhy signálu
		* schopný přenášet signál v digitálním formátu