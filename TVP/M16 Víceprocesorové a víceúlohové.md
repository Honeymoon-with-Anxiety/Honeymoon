#technicke_vybaveni_pocitacu 
# Paralelizace
* rozdělení úlohy na menší části, které jsou následně prováděny současně
* zvyšuje efektivitu a rychlost zpracování
* implementace na úrovni
	* hardwaru - [[M11 Jádro procesoru|vícejádrové procesory]]
	* softwaru - algoritmy
![Paralelizace](https://cs.stanford.edu/people/eroberts/courses/soco/projects/risc/pipelining/laundry2.gif)
## Důvody
* zkrácení doby zpracování - podprogramy jsou spouštěny současně, dosahující rychlejšího výsledku než sériové zprac. (viz [[M12 Pipeline CPU]])
* zjednodušení algoritmu - použito ke zjednodušení problému na menší části řešené samostatně
* lepší využití zdrojů - rozdělením práce se zabraňuje situace, kdy jeden procesor pracuje naplno a ostatní čekají
## Výhody a nedostatky
* výhody
	* rychlejší zpracování
	* zvládnutí více práce současně
	* snadnější rozšíření - přidáním stroji další procesor program poběží ještě rychleji
	* čistší kód *(v některých případech)* - snadnější řešení složitých úloh
* nevýhody
	* složitější kód a odhalování chyb v něm (+ větší riziko výskytu)
	* komunikace - podprogramy potřebují mezi sebou komunikovat; komunikace je zdrojem režie, předávání mezivýsledků aj.
	* nemožnost paralelizace - pokud vlákno musí čekat na výsledek druhé, pak nemusí být paralelizace nejoptimálnější řešení
# Multiprocessing
* počítačový koncept se schopností nezávisle provádět procesy současně za pomocí více procesorů
## symetrický
* všechny procesory jsou si rovnocenné
* mají přístup ke stejným zdrojům (paměť, IO zařízení)
* jsou stejného typu
* operační systém řídí a spravuje všechny procesory
* dají se jednoduše implementovat a rozšiřovat; rozšířitelnost je omezená
* určena pro širokou škálu využití
## nesymetrický
* 
# HW podpora pro systémy se souběžným zpracováním více úloh
* 
# Multitasking
* 
## preemptivní
* 
## nepreemptivní
* 