#technicke_vybaveni_pocitacu
# Informace
* obecně: údaj o dění v reálném světě
* v informatice: řetězec znaků, které lze vysílat, přijímat, uchovávat a zpracovávat
# Číselné soustavy
* číselná soustava je způsob reprezentace čísel. zápis čísla v dané soustavě je daná posloupností symbolů - číslic.
* rozlišujeme spoustu soustav; mezi základní patří dvojková (binární), osmičková (oktální), desítková (decimální) a šestnáctková (hexadecimální).

| Dec | Bin  | Hex | 
| --- | ---- | --- |
| 0   | 0000 | 0   |
| 1   | 0001 | 1   |
| 2   | 0010 | 2   |
| 3   | 0011 | 3   |
| 4   | 0100 | 4   |
| 5   | 0101 | 5   |
| 6   | 0110 | 6   |
| 7   | 0111 | 7   |
| 8   | 1000 | 8   |
| 9   | 1001 | 9   |
| 10  | 1010 | A   |
| 11  | 1011 | B   |
| 12  | 1100 | C   |
| 13  | 1101 | D   |
| 14  | 1110 | E   |
| 15  | 1111 | F   |

## Binární
* dvojková soutstava je soustava, která používá jen dvě číslice (0; 1).
* každá číslice odpovídá *n*-té mocnině čísla 2, kde *n* je pozice dané číslice v zapsaném čísle - binární číslo
* tato soustava se používá ve všech dnešních počítačích z důvodu jednoduchého rozdělení dvou stavů elektrického obvodu (vypnuto; zapnuto) či pravdivost

| binární číslo        | 1   | 1   | 0   | 1   | 0   | 1   | 1   | 0   |     |
| -------------------- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| pozice číslice       | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0   |     |
| mocniny čísla dvě    | 2^7 | 2^6 | 2^5 | 2^4 | 2^3 | 2^2 | 2^1 | 2^0 |     |
| hodnoty mocnin       | 128 | 64  | 32  | 16  | 8   | 4   | 2   | 1   |     |
| krát binární číslice | × 1 | × 1 | × 0 | × 1 | × 0 | × 1 | × 1 | × 0 |     |
| výsledky součinu     | 128 | 64  | 0   | 16  | 0   | 4   | 2   | 0   |     |
 
 * pro převod z dvojkové soustavy do desítkové si jednotlivé číslice umocníme podle pozice číslice. pokud číslice je rovna 1 přičteme do celkového výsledku její poziční mocninu; pokud číslice je rovna 0 číslici přeskočíme. podle této logiky zjistíme, že `11010110` se rovná `214`.
	 **1  1**  0  **1**  0 **1  1**  0
	 128  64  x  16  x  4  2 
	 128 + 64 + 16 + 4 + 2 = 214
## Ternární
* používá tři symboly: `0`, `1` a `2` nebo `-1`, `0`, `1`
* číslice se nazývá `trit`

| 10  | 2    | 3   |
| --- | ---- | --- |
| 1   | 1    | 1   |
| 2   | 10   | 2   |
| 3   | 11   | 10  |
| 4   | 100  | 11  |
| 5   | 101  | 12  |
| 6   | 110  | 20  |
| 7   | 111  | 21  |
| 8   | 1000 | 22  |
| 9   | 1001 | 100 |
| 10  | 1010 | 101 |
## Decimální
* tato soustava používá 10 číslic (0-9). tato soustava je nejrozšířenější na světě. umožňuje přesný zápis libovolných celých čísel, záporných čísel (začínají znakem "mínus" `-`). pomocí desetiné čárky/tečky lze zapsat libovolné reálné číslo.
## Hexadecimální
* soustava s 16 číslicemi (0-9, A-F), kde v desítkové soustavě číslo `10` je nahrazeno písmenem v šestnáctkové `A`, atd...
* převod z hex do dec: $$ 3F7 = 
(3*16^2) + (15*16^1) + (7*16^0) = 1015
$$
* hexadecimální soustava se používá např pro adresy v operační paměti počítače.
* z konstrukčního hlediska počítače pracují v dvojkové soustavě, ale mnohaciferná čísla se špatně čtou, proto se čísla a kódy převádí do šestnáctkové (případně osmičkové). v prog. jazyce C se před hexadec. číslo píše předpona `0x` (např. `0xAB`), v Assembly se pro změnu píše předpona `$` (např. `$AB`).

# CPU
* umí vykonávat strojové instrukce (složen v program) a obsluhovat vstupy a výstupy.
* protože procesor, který by dokázal vykonat program psaný ve vyšším prog. jazyce, by byl až moc složitý, je kód překládán na strojový kód (ten umí např. přesouvat informaci z registru do registru).
* registry uchovávají data ze vstupů a mezivýsledky
* obsahuje aritmeticko-logickou jednotku (ALU) která s daty provádí aritmetické a logické operace.

# Záporná čísla
* V této soustavě pro záporná čísla využíváme dvojkový doplněk
* pro znegování čísla se invertují všechny bity (z 0 se stává 1; z 1 se stává 0) a k výsledku přičteme 1
* nevýhodou je asymetrický interval (<-8; 7>)
	* výpočet intervalu: $$ -\frac{2^n}{2};\frac{2^n}{2}-1 $$

# Ochrana dat
* kontrolní součet je informace předána spolu s původními daty, sloužící k ověření, zda při přenosu nedošlo k chybě. kontrolní součet je přesně určená operace provedená s původními daty, lze ji ověřit u příjemce. pokud nové vypočítaný kontrolní součet nesouhlasí s původním, znamená to, že došlo k poškození původní zprávy nebo kontrolního součtu.

# Pořadí bajtů
* (nebo *endianita*) způsob uložení čísel v operační paměti
* v jakém pořadí jsou v operační paměti uloženy jednotlivé řady čísel, které zabírají více než jeden bajt
## Little-endian
* na paměťové místo s nejnižší adresou se uloží *nejméně významný bajt (LSB)* a za něj se ukládají ostatní bajty až po *nejvíce významný bajt (MSB)*.
## Big-endian
* na paměťové místo s nejnižší adresou se uloží *nejvíce významný bajt* a za něj se ukládají ostatní bajty až po *nejméně významný bajt*.
## Middle-endian
* složitější způsob pro určení jednotlivých bajtů
* kombinace little-endianu a big-endianu

# Základní datové typy
## Logická hodnota
* nebo-li `boolean` se využívá v případech, kdy vlastnosti mohou mít jen dvě hodnoty → pravda nebo lež (`True || False`)
## Celé číslo
* nebo-li `integer`
* jazyky mohou ale nemusí rozlišovat číslo bez znaménka a se znaménkem.
* u většiny jazyků je číslo omezené intervalem a kódováno v [[MO2 Informace ve výpočetní technice#Záporná čísla|dvojkovém doplňku]].
## Zlomek
* nulu v registru posuneme dle potřeby doleva (logické posuny fungují jako násobění/dělení)
* cokoliv za nulou bude $\frac{1}{2^n}$ kde $n$ je pozice za nulou (indexujeme od `1`)
## Znak
* nebo-li `char`, ohraničuje se apostrofem ( ' )
* ve skutečnosti vyjádřena celým číslem
* znaky jsou kódovány v [UNICODE](https://cs.wikipedia.org/wiki/Unicode) nebo v [ASCII](https://cs.wikipedia.org/wiki/Anglick%C3%A1_abeceda) a jejím národním rozšířením
## Reálné číslo
* nebo-li `float` či `double`
* je číslo s plovoucí desetinnou čárkou, jako znak pro desetinnou čárku se používá ' . ' (*tečka*)
* je psáno v dvojkové soustavě $$ {celéčíslo} * 2^{exponent}$$ (exponent je také celé číslo)
* mnohá desetinná čísla nelze v tomto formátu přesně reprezentovat, proto se může stát, že se reálná čísla budou v počítači chovat jinak, než bychom čekali
## Textový řetězec
* nebo-li `string`, ohraničuje se uvozovkami ( " )
* slouží k uložení konečného řetězci znaků