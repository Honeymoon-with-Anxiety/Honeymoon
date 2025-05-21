//for(n = 1; n <= 4; n++) {
//	let citatel = n + 2;
//	let jmenovatel = n + 1;
//	let zlomek = citatel/jmenovatel;
//	console.log("a" + n + " = " + zlomek);
//}

function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}
async function main(){
for(n = 1; true; n++) {
	let citatel = n + 2;
	let jmenovatel = n + 1;
	let zlomek = citatel/jmenovatel;
	console.log("a" + n + " = " + citatel+"/"+jmenovatel);
	await sleep(1000);
}
}

main();
