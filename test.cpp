#include <algorithm>
#include <chrono>
#include <conio.h>
#include <cstdlib>
#include <ctype.h>
#include <direct.h>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <math.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <thread>
#include <time.h>
#include <unordered_set>
#include <vector>
#include <windef.h>
#include <windows.h>

using namespace std;

void delay(long unsigned int millis)
{
    //start timer
    clock_t start = clock();
    //check is time has elasped
    while ((start + ((float)(millis / 1000) * CLOCKS_PER_SEC)) > (unsigned)clock());
}

size_t generateHash(string *username, string *password) {
    hash<string> hash_fn;
    return hash_fn(*username+*password);
}

int main()
{
//    thread helpWatcherThread(helpWatcher);
//    helpWatcherThread.detach();

    string* username = new string("mrsclaus");
    string* password = new string("cookies");

    cout<<generateHash(username, password);


    cout << "\t\t\t\t\t\t"
         << "Enter username: ";
    getline(cin, *username);
    cout << "hi";
    cout << "\t\t\t\t\t\t"
         << "Enter password: ";
    getline(cin, *password);

    while (1) {
        cout << "\t\t\t\t\t\t"
             << "Enter username: ";
        getline(cin, *username);
        cout << "\t\t\t\t\t\t"
             << "Enter password: ";
        getline(cin, *password);
    }

    return 0;
}