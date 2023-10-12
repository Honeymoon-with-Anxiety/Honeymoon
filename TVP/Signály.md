# Signál
* signál je smluvené znamení určená pro přenos [[Informace ve výpočetní technice|informace]]
* má různé formy (krátký zvuk, mluvené slovo, rozsvícení kontrolky) i účely (gesta vojenského velitele, televizní signál)
* může nést informace o události, povelu, zahájení činnosti, výstraze
* obsahuje malé množství informací - zachycuje okamžitý stav/událost
* důležité je doručení včas, proto se signál přenáší v zvláštním kanálu
## analogový
* může být sluch, chuť, čich, zrak, hmat; mozek dává orgánům příkazy a přijímá od nich analogové signály
* v elektronice je založen na přenosu el. energie; určitá napětí odpovídají frekvenci a amplitudě (zvuk, barva, jas, atd.; jsou analogické el. napětí)
* je spojený a může mít nekonečno hodnot v průběhu času
* má určitý fyzický rozsah, ve kterém se pohybuje
* citlivější na rušení, malé změny v hodnotách může mít vliv na kvalitu a přesnost informace
## digitální
* reprezentuje data ve formě diskrétních (signály nejsou spojený) hodnot
* jsou kódovány nulou nebo jedničkou (bity)
* pro velký přenos informací se signály spojují do bloků (bajty)
* běžně používány v elektronice, komunikacích, počítačových systémech
* obvykle mnohem odolnější vůči rušení než analogové signály
* jsou snadno reprodukovány, ukládány a zpracovávány pomocí digitálních zařízení, jako jsou počítače
# Převodník
## AD
* součástka určená k převodu analogového signálu do digitálního
* účel je zpracování analog. signálu na počítačích
* v digitální podobě lze signály přenášet bez ztrát informací; u analog. s každou kopií dochází ke ztrátě kvality
* převod se skládá ze dvou fází: vzorkování a kvantování
* rozlišení určuje, do kolika diskrétních úrovní může signál být rozdělen; vyšší rozlišení znamená, že převodník může zaznamenat více detailů, ale vyžaduje více bitů pro jeden vzorek.
### Vzorkování
* úsek digi. signálu se dá nekonečně zvětšovat, jenže to zabírá paměť počítače
* musíme se omezit na nezbytně nutné množství vzorků, které budeme dále zpracovávat
* vzorkování se provádí rozdělením vodorovné osy signálu na rovnoměrné úseky a z každého úseku odebereme vzorek
* ztratíme mnoho detailů; dostáváme množinu diskrétních bodů s intervalem odpovídajícím použité vzorkovací frekvenci
![Ukázka spojitého signálu se zvětšeným detailem](https://upload.wikimedia.org/wikipedia/commons/f/f8/Spojit%C3%BD-detail.png)
* chyba vzorkování může být horší pokud se v původním analog. signálu vyskytuje vyšší frekvence než je polovina vzorkovací frekvence, dojde k nenávratnému zkreslení kvůli jevu zvaný aliasing
* Aliasingu se dá zabránit jedině filtrem (dolní propust) zařazeným před převodníkem. Ten nedovolí vyšším frekvencím vstoupit do převodníku.
### Kvantování
* zařízení dále zpracovávající digi. signál umí vyjádřit čísla jen s omezenou přesností, je třeba upravit navzorkované hodnoty i na svislé ose.
* je třeba rozdělit prostor kolem jednotlivých hodnot na toleranční pásy (jeden takový pás je naznačen kolem nuly)
* kterémukoliv vzorku, který padne do tolerančního pásu, je přiřazena daná hodnota
* kvantové hodnoty se ve většině případů liší od skutečných navzorkovaných hodnot
* velikost kvantizační chyby je vzdálenost mezi kvantovanými a původními navzorkovanými body (velikost se pohybuje v intervalu +1/2 až -1/2 kvantizační úrovně)
## DA
* součástka určená k převodu digitálního signálu na signál analogový
* používá se všude tam, kde je třeba z digitálního signálu udělat zpět analogový (CD přehrávače, MP3 přehrávače, zvukové karty počítače, digitálním telefonu)
* rekonstrukce signálu - převod digitálních dat na spojitý analogový signál
# Vzorkovací teorém
* "K dosažení přesné rekonstrukce spojitého signálu s omezeným frekvenčním rozsahem z jeho vzorků je potřeba, aby vzorkovací frekvence přesáhla dvojnásobek frekvence nejvyšší harmonické složky vzorkovaného signálu."
* v praxi se vzorkovací volí dvakrát větší plus rezerva
# Šířka pásma
* rozdíl mezi nejvyšší a nejnižší frekvencí přenášeného signálu
* vyjádřeno v hertzech (Hz)
* v informatice se používá ve smyslu přenosové rychlosti
$$ B = f_{H}-f_{l}$$
# Pásmo
## základní
* signály, jejichž frekvenční pásmo začíná blízko frekvence 0 Hz
* šířka pásma signálu je rovna nejvyšší frekvenci signálu 
* signál v základním pásu
	* je signál který obsahuje frekvence ležící v porovnání s nejvyšší frekvencí velmi blízko nuly
	* signály které mohou být popsány jako složení množství různých frekvencí
## přeložené
* určitý rozsah frekvencí v rámci celkového frekvenčního spektra signálu, který byl posunut nebo přemístěn z jeho původního frekvenčního umístění na jinou frekvenci
* frekvence: vztahuje se k posunu nebo změně frekvenčního rozsahu signálu
# Multiplex
## časový
* přenos více signálů jedním přenosovým médiem
* jednotlivé signály jsou odděleny krátkými časovými intervaly ("každý chvilku tahá pilku")(časové sloty)
* hl. problém je rozeznat kde časový slot pro konkrétní signál začíná a končí; řešením je přidat další slot s definovaným obsahem na začátek řady (synchronizační časový slot)
	* máme signály **A**, **B**, **C**, **D**; v časovém multiplexu budou vysílány v pořadí: ABCDABCDABCD...; s přidáním synch. slotu **S**ABCD**S**ABCD**S**ABCD...
## frekvenční
* přenos více signálů jedním společným širokopásmovým médiem, kde každý signál používá jinou část kmitočtového pásma; každý signál je spojen s určitou frekvencí, která slouží jako nosič
* multiplexor kombinuje jednotlivé signály do spojeného signálu