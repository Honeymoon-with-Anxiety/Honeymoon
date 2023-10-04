#include<iostream>

using namespace std;

string otoc(string inA){
    string str = "";
    for(int i = inA.length(); i >= 0; i--)
        str += inA[i];
    return str;
}

string naVelke(string inA){
    string str = "";
    for(int i = 0; i < inA.length(); i++){
        if(inA[i] >= 'a' && inA[i] <= 'z') str += char((int)inA[i]-32);
        else str+=inA[i];
    }
    return str;+
}

int main()
{
    cout << otoc(naVelke("Hello World!")) << endl;

    return 0;
}
