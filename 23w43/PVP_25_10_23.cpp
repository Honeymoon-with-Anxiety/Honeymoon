#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    int strA, strB, strC;

    cout << "Zadejte stranu A: ";
    cin >> strA;
    cout << "Zadejte stranu B: ";
    cin >> strB;
    cout << "Zadejte stranu C: ";
    cin >> strC;

    if (strA + strB > strC)
        cout << "Trojuhelnik lze sestrojit\n";
    else
        cout << "Trojuhelnik nelze sestrojit\n";
    if (strB + strC > strA)
        cout << "Trojuhelnik lze sestrojit\n";
    else
        cout << "Trojuhelnik nelze sestrojit\n";
    if (strA + strC > strB)
        cout << "Trojuhelnik lze sestrojit\n";
    else
        cout << "Trojuhelnik nelze sestrojit\n";

    //cout << "Hello World!";
    return 0;
}