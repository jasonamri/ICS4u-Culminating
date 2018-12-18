//2018-12-13 - 2019-01-21
//Culminating Task

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
using namespace std;

map<int, string> toys = {
    { 1, "Teddy bear" },
    { 2, "Toy blocks" },
    { 3, "Rubber ducky" },
    { 4, "Firetruck" },
    { 5, "Hockey stick" },
    { 6, "Book" },
    { 7, "Toy car" },
    { 8, "Slime" },
    { 9, "Lego" },
    { 10, "Pyjamas" }
};

class User {
private:
     //name of elf
     string *name;
     //date of hire in unix time
     int *hireDate;
     //years since hire
     int *yearsSinceHire;
     //toy assigned (see lookup table)
     int *toyAssigned;
     //number of toys made
     int *toysMade;
     //percent progress (0-100)
     int *progress;

public:
     //init User
     User (string *name, int *hireDate) {

     }
     //get name
     //string *getName() {
     //     return *name;
     //}

};


int generateHash(string *username, string *password) {
     string s(*username+*password);
     hash<string> hash_fn;

     size_t hash = hash_fn(s);

     cout << hash << '\n'<<"hi";

     return 
}

bool compareHash(int *hash, string *password, string *username) {
     return generateHash(password, username) == *hash;
}

void password (){

  cout << "same hashes:\n" << boolalpha;
  cout << "nts1 and nts2: " << (ptr_hash(nts1)==ptr_hash(nts2)) << '\n';
  cout << "str1 and str2: " << (==str_hash(str2)) << '\n';
}*/

void mouseInput ()
{
     POINT coord;
     GetCursorPos(&coord);
     cout << coord.x << "," << coord.y << "\n";
}


void setScreenPosAndSize () {
     HWND consoleWindow = GetConsoleWindow();

	SetWindowPos(consoleWindow, HWND_TOP, -7, -30, 500, 500, SWP_NOZORDER);
}


void changeColor(int foreground, int background) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), foreground + background * 16);

}

int main()
{
     //string /***/username= /*new (nothrow) string (*/"Santa"/*)*/;
     //string /***/password= /*new (nothrow) string (*/"hi"/*)*/;

     string *username = new string("jason");
     string *password = new string("fu");

     //cout<<generateHash(username, password);

     changeColor(5, 6);
     generateHash(username, password);

     //animations2();

     //password();

     setScreenPosAndSize();

     mouseInput();

     _getch();
     return EXIT_SUCCESS;
}
