---
tags:
  - technicke_vybaveni_pocitacu
---
* přenos zdigitalizovaného analogového signálu pomocí přenosového média
* zahrnuje *vysílání* a *příjem*
* datová komunikace zahrnuje i přípravu k odeslání, řízení přenosu a procesy navazující na příjem
* způsoby přenosu: opticky, mechanicky, bezdrátově
	* různé přenosové trasy, včetně vodičů, optických vláken a bezdrátových spojů, poskytují rozmanité možnosti pro přenos informací
	* výběr vhodné trasy závisí na specifických požadavcích systému a dostupných technologiích
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

