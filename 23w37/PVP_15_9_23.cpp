#include <iostream>

using namespace std;

int main(){
    int inA;
    cout << "Vyberte cislo: ";
    cin >> inA;

    if(true) cout << "Cislo " << inA << " je prvocislo";
    else {cout << "Cislo " << inA << " neni prvocislo";}

    return 0;
}
    
int vypis_char(){
    for (int i = 32; i < 255; i += 4){
        cout << i << ": " << char(i) << "\t" << i+1 << ": " << char(i+1) << "\t" << i+2 << ": " << char(i+2) << "\t" << i+3 << ": " << char(i+3) << endl;
        }
}