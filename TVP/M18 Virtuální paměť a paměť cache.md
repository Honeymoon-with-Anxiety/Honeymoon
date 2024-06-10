* virtuální paměť
	* technika dovolující programům využívat více paměti než je jí fyzické
	* koncept vytváří iluzi velkého, spojitého adresového prostoru pro každou běžící aplikaci
	* paging
		* virt. pam. prostor je rozdělen na malé bloky nazývané stránky (pages)
		* RAM je rozdělena do bloků stejné velikosti jako v prostoru - rámce
		* když program potřebuje přístup k určité stránce, OS zjistí, zda je tato stránka již načtena do rámce; pokud není, dojde k výpadku stránky (page fault) a OS načte potřebnou stránku z diskového úložiště do volného rámce ve fyzické paměti
	* segmentace
		* virtuální paměť může být také rozdělena do segmentů různé velikosti odpovídající logickým částem programu (kód, data a zásobník)
		* segmenty mohou být umístěny kdekoli v adresním prostoru
		* segmenty mohou růst nebo se zmenšovat podle potřeby
	* page tables
		* OS používá tabulky stránek k mapování virtuálních adres na fyzické adresy
		* tabulka stránek obsahuje záznamy určující kde je každá stránka virtuální paměti uložena ve fyzické paměti
		* když procesor potřebuje přístup k určité virtuální adrese, nejprve zkontroluje tabulku stránek, aby zjistil odpovídající fyzickou adresu
	* swapování - pokud není dostatek fyzické paměti pro všechny aktuálně běžící procesy, operační systém může přenést některé stránky z fyzické paměti na disk do swapovacího prostoru
	* každý proces má svůj vlastní virtuální adresní prostor - vyšší bezpečnost a stabilita systému
	* ochrana paměti mezi procesy - jeden proces nemůže narušit paměť jiného procesu
* cache
	* rychlá paměť, která slouží k dočasnému ukládání často používaných dat nebo instrukcí
	* umístěna mezi procesorem a hlavní pamětí (RAM)
	* cílem je zrychlit výkon systému tím, že sníží dobu potřebnou k přístupu k datům
	* multilevel cache
		* v moderních procesorech
		* každá úroveň má různé charakteristiky (rychlost, velikost)
		* určena k optimalizaci přístupu k datům na různé úrovni hierarchie paměti
# Logické souvislosti s cache
* logické souvislosti určují, jaká data by měla být uložena v cache a jak by měla být spravována
* princip prostorové lokalizace (Spatial Locality)
	* pokud byl přístup k určité adrese v paměti, je vysoká pravděpodobnost, že blízké adresy budou také přístupné brzy
	* cache často ukládá bloky paměti (například několik po sobě jdoucích adres) namísto jednotlivých adres
* princip časové lokalizace (Temporal Locality)
	* pokud byla nedávno přístupná určitá paměťová adresa, je vysoká pravděpodobnost, že k ní bude znovu přístup v blízké budoucnosti
	* cache uchovává nedávno přístupná data, aby mohla být rychleji dostupná při opakovaných přístupech
* hierarchie paměti
	* různé úrovně paměti mají různé rychlosti a velikosti
	* nejrychlejší a nejmenší paměť je umístěna nejblíže procesoru (L1 cache); pomalejší a větší paměť je dále (RAM, pevný disk)
* algoritmy pro správu cache
	* určují, která data budou uložena a která budou odstraněna, když je cache plná
	* algoritmy využívají logické strategie pro maximalizaci cache hit rate
	* LRU (Least Recently Used) - nahrazuje nejméně nedávno použitá data
	* FIFO (First In, First Out) - nahrazuje data v pořadí, v jakém byla do cache uložena
	* LFU (Least Frequently Used) - nahrazuje data, která byla nejméně často přístupována; kombinace časové a prostorové lokalizace
* přednačítání (Prefetching) - cache může předem načíst data, která ještě nebyla požadována, ale jsou pravděpodobně potřebná v blízké budoucnosti
# Konzistence dat v cache
* nesmí dojít k situacím, kdy jsou stará nebo neplatná data používána místo aktuálních dat
* write strategy
	* trategie zápisu určují, jakým způsobem jsou data zapisována
	* write-through
		* data jsou zapisována do cache a zároveň okamžitě do RAM
		* vysoký úroveň konzistence; pomalejší
	* write-back
		* data jsou zapisována pouze do cache a do RAM jsou zapsána až tehdy, když jsou z cache odstraněna
		* rychlejší; složitější správa pamětí
* coherence protocols (Protokoly pro zajištění konzistence)
	* v systémech s více cache
	* MESI Protocol (Modified, Exclusive, Shared, Invalid)
		* každá cache line (řádek) může být ve čtyřech stavech: Modified (M), Exclusive (E), Shared (S), Invalid (I)
		* pokud je jedna cache line v modifikovaném stavu, žádná jiná cache nemá kopii této cache line ve stavu exclusive nebo shared
	* MOESI Protocol (Modified, Owner, Exclusive, Shared, Invalid) - rozšiřuje MESI protokol o stav Owner (O)
	* dragon protocol\
		* v multiprocesorových systémech
		* v situacích, kdy více procesorů sdílí stejné paměťové adresy
* synchronizace a invalidace
	* invalidate on write - při zápisu do cache jsou ostatní kopie dané cache line invalidovány; žádná jiná cache nemůže používat zastaralá data
	* update on write - při zápisu do cache jsou aktualizovány i ostatní kopie dané cache line; všechny cache mají aktuální data
* atomic operations
	* zejména v systémech s více procesory nebo jádry
	* zajišťují, že při čtení a zápisu dat nedochází k nekonzistentním stavům
* konzistenční protokoly v multiprocesorových systémech
	* snooping-based protocols - každá cache monitoruje (snoops) sběrnici pro zjištění operací, které mohou ovlivnit její vlastní kopie dat
	* directory-based protocols - používá centrální nebo distribuovaný adresář, který sleduje, která cache má kopii které paměťové adresy a spravuje aktualizace a invalidace dat
# Vyřazování a aktualizace cache
* h
# Adresa na sběrnici
* h
## Vznik fyzické adresy
* 