#include<iostream>

using namespace std;

string vypisTabulku(){
    string retStr = "";
    for(int i = 0; i < 256; i++) {retStr += char(i);}
    return retStr;
}

string vypisTabulku(int inA){
    string retStr = "";
    int pocet = 0;
    for(int i = 0; i < 256; i++){
            retStr+=char(i);
            pocet++;
            if(pocet == inA) {retStr += "\n"; pocet = 0;}
    }
    return retStr;
}

void otocString(string inA){
    string retStr = "";
    for(int i = inA.length(); i >= 0; i--){
        retStr += inA[i];
    }
    cout << retStr << endl;
}

int main()
{
    //cout << vypisTabulku(4) << endl;
    otocString("Ahoj");
    return 0;
}