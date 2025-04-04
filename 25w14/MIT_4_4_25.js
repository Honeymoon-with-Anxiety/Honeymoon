// PWM laborka helper
// by Písek Pískovec

// Program pro výpočet modulující frekvence, vzorku;
// následně výsledky budou ukládány do tabulky vhodné k vložení do ASM zdroje

let jedenVzorek = 360/120;

for(let i = jedenVzorek; i <= 360; i += (2 * jedenVzorek)){
  console.log(`.db ` + i + `, ` + (i + jedenVzorek));
}
