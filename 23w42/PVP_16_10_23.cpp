#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream inFile("cisla.txt");
    int a, pocet = 0, soucet = 0;
    if (inFile.is_open())
    {
        while (inFile >> a)
        {
            pocet++;
            soucet += a;
        }
        cout << "V souboru je " << pocet << " cisel.\n";
        cout << "Soucet cisel je " << soucet << endl;
        cout << "Prumer cisel je " << (float)soucet/pocet << endl;
    }

    return 0;
}