//*********************************
//	Main for lab 13 
//	Description:
//		this program takes a text file
//		and sends it line by line to the MCU
//		over RS232. The program should test
//		the circular buffer on the MCU side 
//		in combination with software handshaking  
//***********************************

#include "stdafx.h"
#include "Serial.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

bool try_send_line(	CSerial& port, 
					string& line,
					ofstream& PCreceived, bool& gotX);



int main(int argc, char* argv[])
{
	char comm_byte = START_TRANS;
	string lineout, linein;
	ifstream PCwrote("TestFile.txt");		//outgoing file
	ofstream PCreceived("TestFileEcho.txt");//incoming from MCU

	CSerial serial;
	bool gotX_off = false;
	unsigned int attempted_num = 0;

	if(!serial.Open(1,9600)) 
	{
		cout<<"Failed to open the port! \nTerminating the program...";
	}
	else
	{
		while(getline(PCwrote, lineout))
		{
			//sending and reattempting a line here
			while(!try_send_line(serial,lineout,PCreceived,gotX_off))
			{
				PCreceived<<"\n					waiting for XON from MCU...\n";
				attempted_num++;
			}
				
			lineout="";
			PCreceived<<"\n					PC completed sending a line ";
			PCreceived<<"on "<<attempted_num<<" attempts\n";
			attempted_num=0;
		}

		//send end of transmission character
		comm_byte=END_TRANS;
		serial.WriteCommByte(comm_byte);
		comm_byte=START_TRANS;

		//don't stop reading until the 
		//end of transmission character
		while(comm_byte!=END_TRANS)
		{
			if(serial.ReadDataWaiting()) 
			{	serial.ReadData(&comm_byte,1);
				if((comm_byte!=START_TRANS)&&(comm_byte!=END_TRANS)) 
					PCreceived<< comm_byte;
			}
		}
		serial.Close();
	}

	return 0;
}//************************ end Main *********************** 


bool try_send_line(	CSerial& port, string& line,
					ofstream& fromMCU, bool& gotX_off)
{
	//returns false if it got X_OFF 
	//return true if it was able to send 
	//the whole line
	unsigned char alpha = ' ';
	int nBytesRead	= 0;

	for(size_t i=0; i<line.length(); i++)
	{
				//read anything pending and
				//check for Xoff from the MCU
				while(port.ReadDataWaiting()) //gotta read it and check
				{
					nBytesRead = port.ReadData(&alpha, 1);
					if (nBytesRead)//make sure again 
					{
						//check the XOFF
						if(alpha==ASCII_XOFF) 
						{
							gotX_off=true;
							fromMCU<<"\n	(X_off)\n";
							//adjust the string 
							string TmpString = line.substr(i,line.length());
							line = TmpString;
							return false;
						}
						else if(alpha==ASCII_XON) 
						{
								gotX_off=false;
								fromMCU<<"\n	(X_on)\n";
						}
						else fromMCU<< alpha;
						
					}//if nBytesRead not zero
				}//while something in the Queue
			
				//attempt the actual write
				if(gotX_off==false)
				{
					if(!port.WriteCommByte(line.at(i)))
					{//problem sending the byte
						fromMCU<<"\ntry_send_line: could not send the byte.";
						cout<<"\ntry_send_line: could not send the byte.";
					}
				}
				else//have to reattempt
				i--;	
	
	}//end for line length

	return true;
}


