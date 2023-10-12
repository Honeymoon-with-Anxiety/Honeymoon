#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    /*
    int pocetRadku = 0;

    cout << "Zadejte pocet radku: ";
    cin >> pocetRadku;
    ofstream soubor ("cisla.txt");
    if(soubor.is_open()){
        for(int i = 0; i < pocetRadku; i++) soubor << i << endl;
    soubor.close();
    } else cout << "Soubor se nepodarilo otevrit!";

    string str, firstFileLoc, toFileLoc;
    cout << "Zadejte cestu puvodniho souboru: ";
    cin >> firstFileLoc;
    cout << "Zadejte cestu noveho souboru: ";
    cin >> toFileLoc;
    ifstream souborA(firstFileLoc);
    ofstream souborB(toFileLoc);
    if (souborA.is_open() && souborB.is_open())
    {
        while (getline(souborA, str))
        {
            souborB << str << endl;
        }
        souborA.close();
        souborB.close();
        cout << "Soubor zkopirovan";
    }
    else
        cout << "Soubory se nepodarilo otevrit!";

    // cout << "Hello World!";
    */
   

    ifstream soubor("cisla.txt");
    int inA, inB;
    if (soubor.is_open())
    {
        soubor >> inA;
        soubor >> inB;
        cout << "A: " << inA << " B: " << inB << "\nsoucet: " << inA + inB;
        soubor.close();
    }

    return 0;
}