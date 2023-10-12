#include <iostream>

using namespace std;

void pozice(string inA, bool liche = false)
{
    /*
    switch (sude)
    {
    case true:
        for(int i = 0; i < inA.length(); i++){
            if(i%2==0) cout << inA[i];
        }
        cout << endl;
        break;

    case false:
        for(int i = 0; i < inA.length(); i++){
            if(i%2!=0) cout << inA[i];
        }
        cout << endl;
        break;
    }
    */

    for (int i = liche; i < inA.length(); i = i + 2)
        cout << inA[i];
    cout << endl;
}

int suma(int inA[], bool liche = false)
{
    int s = 0;
    for (int i = liche; i < sizeof(inA) / sizeof(int); i = i + 2)
        s += inA[i];
    return s;
}

int main()
{
    pozice("Hello World!");
    pozice("Hello World!", true);
    int tArr[] = {1, 2, 3, 4, 5};
    cout << suma(tArr) << endl;
    cout << suma(tArr, true) << endl;
    return 0;
}
