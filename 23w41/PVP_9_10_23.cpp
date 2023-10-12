#include <iostream>

using namespace std;

int inA, inMax = 0;

int main()
{
    // cout << "Hello World!";
    do
    {
        cout << "Zadejte cislo: ";
        cin >> inA;
        if (inA > inMax)
            inMax = inA;
    } while (inA != 0);
    cout << "Nejvetsi cislo: " << inMax << endl;
    return 0;
}