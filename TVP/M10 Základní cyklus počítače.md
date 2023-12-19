#technicke_vybaveni_pocitacu 
* obvykle se nazývá "fetch-decode-[execute](https://www.youtube.com/watch?v=ESx_hy1n7HA) cycle"
* popisuje zk. kroky opakované při každé instrukci
1) čtení *(fetch)*
	* instrukce se načtou z paměti
	* adresa instrukce k provedení je uložena v registru Program Counter *(PC)*
	* instrukce se načte z adresy z PC do Instruction Register *(IR)*
	* dojde k aktualizaci PC aby ukazovala na další instrukci v paměti
2) dekódování *(decode)*
	* načtená informace *(v IR)* obsahuje operační kód *(opcode)* a další informace
	* během dekódování jsou jednotlivé části instrukce identifikovány pro další zpracování
	* pomocí opcode je určeno, jakou operaci instrukce představuje
	* pokud instrukce potřebuje operandy, dekódování je identifikuje a připraví k použití
3) provedení *([execute](https://www.youtube.com/watch?v=ESx_hy1n7HA))*
	* vykonává operaci definovanou dekódovanou instrukcí (např.: aritmetické operace, logické operace, přesuny dat, skoky nebo další)
	* po provedení instrukce se aktualizují stavové registry obsahující informace o procesoru (např. přetečení)
	* výsledky operací jsou zapsány do registrů nebo do paměti
* 