// PWM laborka helper
// by Písek Pískovec

// Program pro výpočet modulující frekvence, vzorku;
// následně výsledky budou ukládány do tabulky vhodné k vložení do ASM zdroje

let jedenVzorek = 360/120;

console.log(`.db 0, 0`);
console.log(`.db 0, 0`);
console.log(`.db 0, 0`);

for(let i = 0; i < 126; i += (2 * jedenVzorek)){
  console.log(`.db ` + i + `, ` + (i + jedenVzorek));
}

console.log(`.db 126, 126`);
console.log(`.db 126, 126`);
console.log(`.db 126, 126`);

for(let i = 123; i > 0; i -= (2 * jedenVzorek)){
  console.log(`.db ` + i + `, ` + (i - jedenVzorek));
}
