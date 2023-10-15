#include<iostream>

using namespace std;

int main()
{
    int inA;

    cout << "Je cislo sudy nebo lichy?\n"; //nadpis programu
    cout << "Zadejte cislo: ";
    cin >> inA;

    if (inA == 0) cout << "Cislo 0 je nula.\n";
    else if(inA%2 == 0) cout << "Cislo " << inA << " je sudy.\n";
    else cout << "Cislo " << inA << " je lichy.\n";

    for(int i=0; i<10; i++){
        inA++;
        cout << "Promena i se rovna: " << i;
    }
    
    return 0;
}
