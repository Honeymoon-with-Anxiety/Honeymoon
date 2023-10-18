#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream inFile("txt.txt");
    char selChar = 'a';
    string line;
    int totChar = 0;

    cout << "Zadejte vstupni znak: ";
    cin >> selChar;

    while(inFile >> line){
        for(int i = 0; i < line.length(); i++){
            if(line[i] == selChar) totChar++;
        }
    }

    cout << "Pocet " << selChar << " v souboru: " << totChar << endl;
    //cout << "Hello World!";
    return 0;
}