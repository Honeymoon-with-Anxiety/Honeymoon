#include <iostream>
#include <fstream>

using namespace std;

ifstream inFile("/run/media/pisek/Společné/E3A/23w42/MIT_16_10_23.asm");
ofstream outFile("catgirl");
string strFile="", strSpace="";
int intSpace = 0;

int main()
{
    cout << "Kolik mezer pred radkem? ";
    cin >> intSpace;

    for(int i = 0; i < intSpace; i++) strSpace += " ";
    

    if(inFile.is_open() && outFile.is_open()){
        while (getline(inFile, strFile)){
            outFile << strSpace << strFile << endl;
        }
        inFile.close();
        outFile.close();
    } else cout << "Nelze otevrit soubor(y)!\n";


    //cout << "Hello World!";
    return 0;
}