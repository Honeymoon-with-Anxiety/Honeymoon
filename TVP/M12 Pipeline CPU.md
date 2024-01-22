#technicke_vybaveni_pocitacu 
* využívá technologii pipeline k urychlení vykonávání instrukcí
* umožňuje provádění několika instrukcí najednou v různých fázích zpracování
* efektivnější využití zdrojů procesoru
* zkrácení doby potřebné k vykonání instrukcí
* má 4 fáze *(fetch, decode, [execute](https://www.youtube.com/watch?v=ESx_hy1n7HA), zásah do paměti)* - instrukce procházejí skrz tyto fáze postupně
* mohou se vyskytnout [[M10 Základní cyklus počítače#Hazardy|problémy]]
* je důležité zajistit předcházení konfliktům
# Schéma pipeline CPU
![Činnost mikroprocesoru, aneb jde to i bez trpaslíků](https://i.iinfo.cz/urs/pc_05_01-120648298004188.gif)
Popis jednotlivých [[M11 Jádro procesoru#Popis obrázku|komponent]] a [[M10 Základní cyklus počítače|fází]]
# Fáze
## plnění
* týká se způsobu jakým jsou instrukce vloženy do pipeliney a jak jim prochází
* fetch - instrukce jsou načteny z paměti do pipeliney
* decode - instrukce je přeložena na sérii mikroinstrukcí
## provozu
* [execute](https://www.youtube.com/watch?v=ESx_hy1n7HA) - procesor vykonává instrukce
* memory - jen pokud instrukce vyžaduje přístup k paměti (čtení/zápis)
* write back - výsledek instrukce je zaslán zpět do registru či paměti
## vyprazdňování
* vztahuje se k situacím, kdy je nutné náhlé přerušení nebo zastavení běhu pipeline (např. změna toku instrukcí) nebo po dokončení instrukcí
* detekce skoku - pokud je podmínka splněna, instrukce v pipeline (načteny, nedokončeny) jsou "zahozeny"
* může způsobit zpoždění
* zahození instrukcí
	* zajišťuje, že neproběhnou neplatné operace
	* pipeline je zaplněna nulami
* aktualizace stavu procesoru - procesor je aktualizován na novou hodnotu PC na základě skoku nebo větvení; nové instrukce jsou načteny z nové pozice v programu
* zahájení nového provozu (plnění → provoz)
# Dekompozice systému
* 
## Vliv na výkon
* 
# Konflikty
## skokové
### vznik
* 
### řešení
* 
## datové
### vznik
* 
### řešení
* 
# Vliv na výkon
* 