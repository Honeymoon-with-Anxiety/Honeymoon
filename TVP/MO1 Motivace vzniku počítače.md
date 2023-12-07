#technicke_vybaveni_pocitacu
* algoritmus - přesný návod či postup, kterým lze vyřešit daný typ úlohy.
# Motivace
* zprvu pomoc se složitými výpočty, později kancelářské práce jako jsou textové dokumenty a tabulky
* zautomatizování neustále opakujících se prací - člověk při neustálé stejné činnosti chybuje
# První mechanické počítače
## Abakus
* jednoduché počítadlo s posuvnými kuličkami
* Vznikl před asi 5 000 lety v Babylonii jako deska s kamínky. Slovo abakus se skládá ze slova *abaq* nebo-li *prach*. Ve starověkém Řecku a Římě používali hliněnou desku do které vkládaly kamínky (*calculli*)
![Obrázek abakusu](https://upload.wikimedia.org/wikipedia/commons/thumb/8/8e/Noe_abacus.jpg/480px-Noe_abacus.jpg)
## Logaritmické tabulky a pravítko
* V roce 1614 byla objevena nová metoda násobení a dělení za pomoci sčítání a odčítání. Po objevení se v Anglii začali stavět první tabulky. 
* Po tabulkách přišli logaritmická pravítka, která se používala dalších 200 let (do 70. let 20. st.) ve školách a v technických oborech. Při práci s velkými čísly byla přesnost menší z důvodu zaokrouhlování. Skládalo se ze dvou pohyblivých částí. Součin bylo možno vypočítat součtem logaritmů čísel vyznačených na pravítku.
![Logaritmické pravítko](https://upload.wikimedia.org/wikipedia/commons/thumb/b/b8/Logaritmicke_pravitko.jpg/1920px-Logaritmicke_pravitko.jpg)
## Mechanické kalkulátory
* První mechanický kalkulátor vynalezen mezi 150 až 100 lety př. n. l. byl Mechanismus z Antikythéry sloužil pravděpodobně k výpočtu polohy Slunce, Měsíce a planet. Skládal se z třiceti a více ozubených koleček.
* Roku 1623 Schickard sestavil mechanický kalkulátor vyrobený z ozubených koleček z hodin. Uměl sčítat a odčítat šesticiferná čísla.
* Další počítací stroj byl vyroben [Pascalem](https://cs.wikipedia.org/wiki/Blaise_Pascal) roku 1642 který uměl také jen sčítat a odčítat.  Roku  cca 1820 vytvořil Thomas první mech. kalkulátor který uměl sčítat, odčítat, násobit a dělit. Byl také i sériově vyráběn.
* Většina kalkulátorů byla stavěna na desítkové soustavě, která se obtížně implementovala.
* Následovaly děrné štítky a tkalcovské stavy.
# První programovatelné stroje
* roku 1833 Charles Babbage předběhl svou dobu vývojem "Analytického stroje" který nemohl ve své době vyrobit. Analytický stroj se stal prvním univerzálním Turingovsky úplným počítačem *(lze napodobit jiné počítače bez nutnosti fyzicky upravit počítač)* . Jeho počítač měl pracovat s pevnou desetinnou čárkou a padesáti-místnými čísly. Měl mít "sklad" *(pamět)* a "mlýnici" *(procesor)*. Programy byly psané do děrných štitků.
![děrovaný papír pro řízení tkalcovského stavu](https://upload.wikimedia.org/wikipedia/commons/thumb/a/ae/Damast-Museum_Gro%C3%9Fsch%C3%B6nau_%2857%29.jpg/800px-Damast-Museum_Gro%C3%9Fsch%C3%B6nau_%2857%29.jpg)
# Nultá generace
* první počítače této generace ve většině případů již používala relé a pracovaly na kmitočtu +- 100 Hz. Díky druhé světové válce se tato oblast techniky výrazně posunula vpřed.
## Z1
* práce na konstrukci začala již roku 1934 a dokončena byla roku 1936. stroj pracoval v dvojkové soustavě a neuměl podmíněné skoky. programy se psaly na děrné pásky (nosičem byl kinofilm). celý elektromechanický stroj byl dokončen až roku 1938. byl velmi poruchový tudíž prakticky nepoužitelný. považován za první počítač.
## Z2, Z3
* po dokončení Z1 se německý inženýr Zuse vrhl na Z2 který měl 200 relé a mechanickou paměť ze Z1. 
* Následovala spolupráce Zuseho a Schreyre pro vytvoření ještě výkonnějšího počítače Z3. Z3 byl zničen při náletech v roce 1944
## ABC
* v říjnu 1939 sestavil americký profesor Atanasoff elektronický počítač ABC, který sloužil k řešení lineárních rovnic ve fyzice.
## Colossus
* Colossus MK1 byl zkonstruován roku 1943 Thomasem H. Flowers jako prototyp dešifrovacího počítače použit pro dešifrování textu strojem [Enigma](https://cs.wikipedia.org/wiki/Enigma). Používal vakuové elektronky.
* Colossus MK2 byl zkonstruován o rok později pro dešifraci zpráv zašifrované přístrojem Lorenz cipher.
## SAPO
* První počítač vyrobený v Československu. Název SAPO je zkratkou pro SAmočinný POčítač. Byl uveden do provozu roku 1957 a obsahoval 7 000 relé a 400 elektronek. Byl zvláštní ve dvou věcech: součástí každé instrukce bylo 5 adres (2 operandy, výsledek, adresy skoku v případě kladného a záporného výsledku) a měl 3 procesory, které pracovaly paralelně.
* O správnosti výsledku se hlasovalo. Výsledek z každého procesoru se porovnával, pokud se alespoň výsledek jednoho procesoru shodoval s výsledkem druhého procesoru výsledek byl prohlášen za správný; pokud se všechny tři výsledky neshodovaly, proces se opakoval.
* Tři roky po svém spuštění SAPO shořel. Z jiskřících releových kontaktů se vzňala loužička oleje, kterým se relé promazávala.
# První generace
* první generace již používala elektronky (relé jen v menší míře). Počítače byly vysoce poruchové, neefektivní a příliš nákladné. Neměli žádný operační systém ani progr. jazyky, programy se psaly na propojovací desky, později na děrné štítky a pásky. Byly vybaveny tiskárnou pro výtisk výsledku na děrný štítek. Za úspěch se považovalo ukončit výpočet bez poruchy počítače.
## ENIAC a MANIAC
* Roku 1944 na univerzitě v Pensylvánii uveden do provozu elektronický počítač EINAC. Na rozdíl od Z3 umožňoval vytvoření smyčky i podmíněné skoky a byl Turingovsky úplný. Prováděl až 5000 součtů za sekundu, ale byl energeticky velmi náročný, poruchový a jeho provoz byl drahý.
* MANIAC byl inspirován od ENIACu, sestaven roku 1945 a zprovozněn roku 1952. Byl využit k matematickým výpočtům popisující fyzikální děje a k vývoji jaderných bomb.
# Druhá generace
* druhá generace používá polovodičové součástky - tranzistory. To zapříčinilo zrychlení, zmenšení a spolehlivost počítače ale i snížení energetických nároků.
![Počítač UNIVAC](https://upload.wikimedia.org/wikipedia/commons/2/2f/Univac_I_Census_dedication.jpg)
## UNIVAC
* v roce 1951 prvním sériově vyráběným komerčním počítačem. Pátý vyrobený kus úspěšně předpověděl výsledky voleb.
## EPOS (1 a 2)
* Roku 1960 byl spuštěn EPOS 1. Pracoval v desítkové aritmetice, v kódu, který umožňoval automatickou opravu jedné chyby. V 60. a 70. letech se vyráběl i v mobilní verzi a byl vybaven operačním systémem, assemblerem a překladačem.
* EPOS 2 byl spuštěn dva roky po EPOS 1. Byl osazen tranzistory a konstruován do stavebnicové formy - pro každý typ využití se dal sestavit "optimální systém".
# Třetí generace
* Již používala integrované obvody. Začalo se objevovat multiprogramování - zatímvo jeden program čeká na dokončení I/O operace, je procesorem zpracovávána druhá úloha. Objevuje se také nový termín proces, první podpra multitaskingu. Krom velkých počítačů přes celou místnost (mainframe) se objevují první mini- a mikropočítače.
## IBM System 360
* Objevil se v různých výkonnostních modelech, od modelu 360/20 až po 360/90, a všechny mohly používat shodný software. mohly pracovat jak s pevnou, tak také proměnnou délkou operandů (dat). Vyráběli se v tisícových sérií, a byly obrovským pokrokem v komerčním využití.
## Cray
* tehdy nejvýkonnější počítač na světě Cray-1 (první superpočítač). S nástupem paralelních výpočtů Cray-1 ustoupil a firma v roce 1995 zkrachovala.
# Čtvrtá (dnešní) generace
* Charakterizuje ji mikroprocesory a osobní počítače. Zmenšil se procesor (dříve složený z několika obvodů), zvýšila se rychlost, spolehlivost a kapacita paměti, snížila se velikost a náklady. Začínají ustupovat mainframey a nahrazují je osobní stolní počítače (v roce 1981 uveden IBM PC) a laptopy. Ostatní výrobci začínají vyrábět počítače shodné konstrukce jako "IBM PC kompatibilní". Příchází éra GUI, DOSu (převážně MS-DOS), později MS Windows (zprvu postavené na DOSu, později na NT) a jiných operačních systému jako je *System 1-9*, později nahrazen*macOS*, Unix/BSD, GNU/Linux, BeOS/Haiku, OS/2.
![IBM PC 5150](https://upload.wikimedia.org/wikipedia/commons/thumb/6/69/IBM_PC_5150.jpg/220px-IBM_PC_5150.jpg)
# Budoucnost
* zatím se neví jakým směrem se vývoj bude ubírat.
* první komerční kvantový počítač IBM Q System One byl představen v lednu 2019.