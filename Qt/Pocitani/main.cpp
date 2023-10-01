#include<iostream>

using namespace std;

int main()
{
    int inA, inB, inC, inD; // C vysledek, D predpoklad
    
    cout << "Zadejte hodnotu A: ";
    cin >> inA;
    
    cout << "Zadejte hodnotu B: ";
    cin >> inB;

    cout << "Zadejte predpoklad vysledku: ";
    cin >> inD;

    inC = inA+inB;

    if (inD == inC) cout << "Priklad: " << inA << " + " << inB << " = " << inC << "(predpoklad " << inD << "byl spravny)";
    else cout << "Priklad: " << inA << " + " << inB << " = " << inC << "(predpoklad " << inD << "byl spatny)";

    return 0;
}