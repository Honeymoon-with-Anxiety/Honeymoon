---
tags:
  - technicke_vybaveni_pocitacu
---
* přenos zdigitalizovaného analogového signálu pomocí přenosového média
* zahrnuje *vysílání* a *příjem*
* datová komunikace zahrnuje i přípravu k odeslání, řízení přenosu a procesy navazující na příjem
* způsoby přenosu: opticky, mechanicky, bezdrátově
	* různé přenosové trasy, včetně vodičů, optických vláken a bezdrátových spojů, poskytují rozmanité možnosti pro přenos informací
	* výběr vhodné trasy závisí na specifických požadavcích systému a dostupných technologiích.
# Vzorkovací teorém
* "K dosažení přesné rekonstrukce spojitého signálu s omezeným frekvenčním rozsahem z jeho vzorků je potřeba, aby vzorkovací frekvence přesáhla dvojnásobek frekvence nejvyšší harmonické složky vzorkovaného signálu."
* v praxi se vzorkovací volí dvakrát větší plus rezerva
# Šířka pásma
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
* 