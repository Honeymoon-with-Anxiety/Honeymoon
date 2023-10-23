// ConsoleSerial.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Serial.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
		unsigned char alpha=1;
		int nBytesRead = 0;

		CSerial serial;

		if (serial.Open(1, 9600))
		{
			cout<<"\nSerial port opened successfully.";
			while (1)
			{
				cout<<"\n Enter the character to send 0 to quit: ";
				cin>>alpha;
				if(alpha == 48 ) //leaving the nonsense
				{
					if(serial.Close()) break;
					else cout<<"\nCouldn't close the port!";
				}
				serial.WriteCommByte(alpha);

				nBytesRead = serial.ReadData(&alpha, 1);
				if (nBytesRead==1) cout<<"\n Received: "<< alpha;
				else cout<< "\nRead "<< nBytesRead <<" bytes!";		
			}
		}
		else
		cout<<"Failed to open the port!";
	return 0;
}

