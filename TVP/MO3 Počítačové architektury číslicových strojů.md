#technicke_vybaveni_pocitacu
* rozlišujeme dvě základní architektury
* moderní procesory spojují obě architektury; uvnitř procesoru Harvardská; zvenku von Neumannova
# Von Neumannova architektura
* označuje jednoduché schéma počítače používající jednu sběrnici
* jméno architektura získala po přednášce matematika Johna von Neumanna
* architektura popisuje počítač se společnou pamětí pro instrukce i data tudíž zpracování je sekvenční
* procesor se skládá z řídící jednotky a výkonné ALU; řídící zpracovává instrukce v paměti; výkonná jednotka následně operuje s daty podle instrukcí. vstup a výstup dat mají na starosti vstupní a výstupní jednotky
* rychlost zpracování instrukcí je dnes výrazně rychlejší než rychlost komunikace s pamětí. tuto nevýhodu částečně řeší mezipaměť (potřebná data a instrukce se do ní načítají rychleji, než jsou při zpracování potřeba)
* dnes je používána např. v kalkulačkách
![Von Neumannova architektura](https://upload.wikimedia.org/wikipedia/commons/thumb/a/a1/Von_Neumann_Architecture_CZ.svg/220px-Von_Neumann_Architecture_CZ.svg.png)
# Harvardská architektura
* odděluje fyzický paměť programu a jejich spojovací obvody
* název pochází z prvního počítače využívající tuto architekturu [[MO1 Motivace vzniku počítače#Nultá generace|Harvard Mark I]]; instrukce byly uloženy na děrované pásce a data na elektromechanických deskách
* CPU může současně číst instrukci z programové paměti a přistupovat do paměti dat
* používá se ve specializovaných procesorech, obvykle v audio/video technice
## Paměť
* není třeba mít paměť stejných parametrů a vlastností
* dvojí paměť umožňuje paralelní přístup k oběma pamětím => vyšší rychlost zpracování
* umístění programu do ROM paměti může zvýšit bezpečnost systému (program nelze modifikovat)
## Rychlost
* rychlost procesorů se několikanásobně zvětšila o proti rychlosti hlavní paměti → tendence zredukovat počet přístupů do hl. paměti.
* za vyšší cenu procesor může být mnohem rychlejší
* paměť cache (vyrovnávací) je velmi rychlá; je jí méně než hl. paměti; velikost cache je jeden z hlavních aspektů určování rychlosti procesoru
# Sekvenční obvody
* nezávisí na okamžité hodnotě vstupních signálů ale i na pořadí minulých vstupů
* jsou schopny uchovávat stav (obsahují paměť); je potřeba sledovat kromě vstupních proměnných i vnitřní proměnné
* dělíme na synchronní a asynchronní
	* u asynchronních se změna vstupu promítne ihned do stavu obvodu
	* u synchronních je zaveden synchronizační signál (hodiny); změna vstupu se promítne do obvodu až při pulzu hodinového signálu
* paměťová část je tvořena kombinačním obvodem - bistabilní klopný obvod; jeho úkol je uchovat informaci na vstupu i poté, co informace na vstupu již není
# Kombinační obvody
* výstup závisí na okamžité kombinaci vstupů
* nemají žádnou paměť
* závislost výstupní funkce je popsána pravdivostní tabulkou nebo pomocí logických výrazů
* pro realizaci je možné využít
	* pevné paměti
	* základní logické členy (NAND; AND, NOR, OR, atd.)
# Bezpečnost
* obor zabývající se ochranou počítačových systémů a sítí před neoprávněným přístupem, krádeží nebo poškozením hardwaru, softwaru. Hlavním cílem je zajistit spolehlivost, integritu a soukromí údajů systému.
* ochrana se dá shrnou třemi kroky:
	1) prevence - ochrana před hrozbami
	2) detekce - odhalení neoprávněných činností a slabých míst v systému
	3) náprava - odstranění slabých míst v systému
* bezpečnost zahrnuje
	* omezení fyzického přístupu k počítači a jeho zařízení, ochrana před neoprávněným manipulování
	* umožnit přístup jen oprávněným osobám vyškoleným pro práci s počítačem a daty
	* ochrana informací před krádeží, nelegální tvorbou kopií
	* použití hardwarových zařízení vynucující bezpečnostní opatření
	* využití mechanismů OS vynucující chování programů v souladu s počítačovou bezpečností
	* omezení množství programům, kterým je nutné důvěřovat
	* využití záznamů o změnách v programech a systémech
	* využití zabezpečení operačního systému
	* využití šifrování při komunikaci, práci s údaji a jejich přenosu
	* využití bezpečného ukládání a zálohování
	* plánování reakce na incident
# Synchronizace
## vnějších signálů
* proces, jenž má za úkol uspořádání signálů nebo časových značek pro komunikaci mezi různými zařízeními, systémy nebo procesy
* dosahuje se pomocí různých technik a zařízení, jako jsou atomové hodiny, GPS, synchronizační protokoly a speciální hardware
* základním prvkem pro správnou funkci moderních technologií a zařízení
## na úrovni procesů
* klíčový koncept v oblasti operačních systémů a paralelního programování
* mechanismy a techniky sloužící k řízení činnosti různých procesů (nebo vláken) v počítačovém systému
* cílem je zajistit efektivitu a bezpečnost procesů
* základní techniky synchronizace:
	* Race Conditions - nastávají, když více procesů má přístup ke sdíleným zdrojům (například paměti) a snaží se je upravovat současně; může vést k nepředvídatelným chybám v datech
	* Mutual Exclusion - základní synchronizační umožňující procesům získat exkluzivní přístup k sdíleným zdrojům; jen jeden proces může mít mutex v daný okamžik, což eliminuje konflikty.
# Systémy s více jádry
* jsou integrované obvody se dvěma nebo více CPU jednotkami zvané jádro
* řídí se stejně jako systémy s jedním jádrem, až na fakt, že vícejádrové systémy mohou spouštět procesy v jednotlivých jádrech → zvýšení rychlosti
* podpora více jader je závislá na programu a operačním systému
* pokud není software napsán s podporou více jader, program je nebude používat