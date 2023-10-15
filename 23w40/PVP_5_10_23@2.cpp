#include <iostream>

using namespace std;

void sudaCisla(int inA[])
{
    int soucetCisel = 0;

    for (int i = 0; i < sizeof(inA) / sizeof(int); i++) if (inA[i] % 2 == 0) soucetCisel += inA[i];
    cout << "Soucet sudych cisel je: " << soucetCisel << endl;
}

int main()
{
    int radaCisel[] = {0, 3, 5, 8, 65, 124};

    sudaCisla(radaCisel);
    return 0;
}