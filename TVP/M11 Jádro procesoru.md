#technicke_vybaveni_pocitacu 
* ovlivňuje výkon procesoru
* umožňuje paralelní zpracování sad instrukcí
![](https://www.alrj.org/images/riscv/Pipeline_summary.png)
* klasifikace procesorů
	* podle architektury
		* RISC
			* skromný soubor instrukcí
			* jedna instrukce - jedna operace
			* např. ARM
		* CISC
			* rozsáhlý soubor instrukcí
			* instrukce jsou složité; dokážou provádět mnoho operací
			* např. x86
	* podle počtu jader
		* jednojádrové
		* vícejádrové
	* účel použití
		* běžné - široké spektrum užití
		* specializované - pro specifický účel; např: pro GPU, NPU *(síťová komnunikace)*
	* podle taktovací frekvence
	* podle výrobní technologie
		* velikost tranzistorů
		* méně nanometrů = víc tranzistorů = větší výkon 😃
	* podle spotřeby energie
	* podle [[MO3 Počítačové architektury číslicových strojů|architektury paměti]]
# Výkon procesoru
* ovlivněn taktem - kolik operací procesor provede za jednu sekundu; v Hz
* počet jader - umožňuje paralelní zpracování více úloh současně
* architektura - jak složité instrukce jsou
* cache paměť - velikost a efektivní správa cache ovlivňuje rychlost přístupu k datům
# Programátorský model procesoru
* práce na úrovni nízkého prog. jazyka
* abstraktní pohled na procesor umožňující psát software bez nutnosti znalosti architektury procesoru
* instrukční soubor definuje instrukce které procesor dokáže provádět
* registr je malá, rychlá paměť umístěná přímo na čipu procesoru; kolik registrů má takový procesor, jejich uspořádání a pojmenování
* nativní datové typy procesoru (8-bitový Byte; 16-bitový Word; atd.)
* procesor má mnoho režimů
	* uživatelský - limituje přístup k některým registrům a instrukcím
	* jádra - přístup ke všemu
* model popisuje, jak postupovat při [[M10 Základní cyklus počítače#Výjimečné stavy při běhu CPU|výjimečný stavech]]
* jak pracovat se zásobníkem
* popisuje jak jsou adresy paměti generovány, jak k nim procesor přistupuje a jak jsou dlouhé
* může zahrnovat speciální instrukce nebo adresovací schémata pro komunikaci s periférií
* zahrnuje jak pracovat s více jádry procesoru
# Kompatibilita na úrovni strojového kódu
* schopnost spustit stejný zdrojový kód na vícero architekturách
* pokud dva procesory mají stejný instrukční soubor, může být stejný kód spuštěn na obou procesorech
* kompatibilita nemusí být plně zachována mezi procesory s odlišnou architekturou → nemusí mít stejný počet jader nebo podporovat zpracování ve vláknech
# Evoluce instrukční sady
* první generace se zaměřovala na jednoduché instrukce a zvýšení taktu procesoru
* s potřebou většího výkonu se začaly vyrábět vícejádrové RISC procesory
* vyvynuta pokročilejší technologie pipelinů
* přidány instrukce pro šifrování
* snaha vytvoření otevřené RISC architektury (RISC-V)
# Vliv jader procesoru
## na software
* 