#include<iostream>

using namespace std;

int main()
{
    /*
    int pocetRadku;

    cout << "Kolik radku chcete vypsat? ";
    cin << pocetRadku;
    for(int i = 1; i <= pocetRadku; i++){
        cout << i << ".\n";
    }
 ---
    int f;

    cout << "Vyberte cislo pro faktorial faktorialu: ";
    cin >> f;
    float fac = 1;

    for(int i = f; int > 1; i--){
        fac *= i; // fac = fac * i
    }
    cout << "Vysledek: " << fac;

    string inStr;
    cout << "Napiste slovo: ";
    cout << "Prvni znak slova: " << inStr[0] << endl;

   string inJmeno, outJmeno;
   cout << "Napiste sve jmeno: ";
   cin >> inJmeno;

    for(int i = inJmeno.length()-1; i >= 0; i--){
        outJmeno += inJmeno[i];
    }
    cout << "Jmeno obracene: " << outJmeno; 
    */

   for(int i = 32; i < 255; i++){
    cout << char(i) << " ";
   }

    return 0;
}
