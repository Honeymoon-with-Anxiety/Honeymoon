// PWM laborka helper
// by Písek Pískovec

// Program pro výpočet modulující frekvence, vzorku;
// následně výsledky budou ukládány do tabulky vhodné k vložení do ASM zdroje

const readline = require('node:readline');
const rl = readline.createInterface({
	input: process.stdin,
	output: process.stdout
});

let frekvenceKrystalu;
let deleniFrekvence;
let pocetVzorku;

rl.question("Zadejte frekvenci krystalu [def.: 14754600]: ", hz => {
  frekvenceKrystalu = hz ?? 14754600;
});

rl.question("Zadejte dělení frekvence (pre-scale) [def.: 0]: ", hz => {
  deleniFrekvence = hz ?? 0;
});

rl.question("Zadejte počet vzorků (v bitech) [def.: 8]: ", bits => {
  pocetVzorku = bits ?? 14754600;
	printParams();
});

function printParams(){
  rl.close();
  console.log("----");
  console.log("Parametry použité pro výpočet:");
  console.log("Frekvence krystalu: " + frekvenceKrystalu);
  console.log("Dělení frekvence: " + deleniFrekvence);
  console.log("Počet vzorků: " + pocetVzorku);
  console.log("----");
}
