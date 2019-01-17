#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include <functional>
#include <string>
#include <stdio.h>
#include <ctype.h>
#include <fstream>
#include <sstream>
#include <math.h>
#include <chrono>
#include <windows.h>
#include <windef.h>
#include <direct.h>
#include <iomanip>
#include <unordered_set>
#include <map>
#include <vector>
#include <thread>

using namespace std;



void delay(long unsigned int millis){
	//start timer
	clock_t start = clock();
	//check is time has elasped
	while ((start + ((float)(millis / 1000) * CLOCKS_PER_SEC)) > (unsigned)clock());
}





int main()
{
  thread helpWatcherThread(helpWatcher);
  helpWatcherThread.detach();

  string *username = new string;
  string *password = new string;

  cout<< "\t\t\t\t\t\t" << "Enter username: ";
 getline(cin, *username);
 cout<<"hi";
 cout<< "\t\t\t\t\t\t" << "Enter password: ";
 getline(cin, *password);


  while(1) {  cout<< "\t\t\t\t\t\t" << "Enter username: ";
   getline(cin, *username);
   cout<< "\t\t\t\t\t\t" << "Enter password: ";
   getline(cin, *password);};

  return 0;
}