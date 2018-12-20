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

#define SCREENSIZEWIDTH 1080
#define SCREENSIZEHEIGHT 720


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

void delay(long unsigned int millis)
{
	//start timer
	clock_t start = clock();
	//check is time has elasped
	while ((start + ((float)(millis / 1000) * CLOCKS_PER_SEC)) > (unsigned)clock())
		;
}

/*
jason:admin
jacob:password
santa:santa
mrsclaus:cookies
elf1:hohoho
*/

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


size_t generateHash(string *username, string *password) {
     hash<string> hash_fn;
     return  hash_fn(*username+*password);
}


/*
bool compareHash(size_t *hash, string *password, string *username) {
    return generateHash(password, username) == *hash;
}*/
/*
void password (){

  cout << "same hashes:\n" << boolalpha;
  cout << "nts1 and nts2: " << (ptr_hash(nts1)==ptr_hash(nts2)) << '\n';
  cout << "str1 and str2: " << (==str_hash(str2)) << '\n';
}*/

POINT mouseInput ()
{
     POINT coord;
     GetCursorPos(&coord);

     POINT output;

     if (coord.x > SCREENSIZEWIDTH || coord.y > SCREENSIZEHEIGHT|| coord.y<0||coord.x<0) {
       output.x=-1;
       output.y=-1;
     } else {
       output=coord;
     }

     return output;
}

bool cursorDown() {
     return ((GetKeyState(VK_LBUTTON) & 0x100) != 0);
}

bool clicked(int xMin, int yMin, int xMax, int yMax) {
     POINT * mouse = new POINT;
     *mouse = mouseInput();
     return (mouse->x>xMin && mouse->x<xMax && mouse->y>yMin && mouse->y<yMax && cursorDown());

}

void setScreenPosAndSize () {
     HWND consoleWindow = GetConsoleWindow();
	   SetWindowPos(consoleWindow, HWND_TOP, -7, -30, 1080, 720, SWP_NOZORDER);
}


void changeColor(int foreground, int background) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), foreground + background * 16);
}





/*
login.txt
#of users
(username
hash
permissionLevel) x # of users


permission level
1: elf
2: ms. claus
3: mr. claus
4: admin

*/

int login(string *username, string *password) {

     ifstream *loginFile = new ifstream;
     loginFile->open("login.txt");

     int *numberOfUsers = new int;

     bool *usernameFound = new bool(false);

     string *usernameToTest = new string;
     size_t *hashToTest = new size_t;
     int *permissionLevel = new int;

     if (loginFile->is_open()) {
          *loginFile>> *numberOfUsers;

          for (int i = 0; i<*numberOfUsers; i++) {

               *loginFile>>*usernameToTest;
               *loginFile>> *hashToTest;
               *loginFile>> *permissionLevel;

               if (*username==*usernameToTest) {
                    *usernameFound=true;
                    break;
               }
          }


          loginFile->close();

          if (generateHash(username, password)==*hashToTest) {
               return *permissionLevel;
          } else {
               return 0;
          }


     } else {
          return -1;
     }


}






void menu1(){

in the workshop menu

add new child
view/edit child
update niceness rating

change password


}

santa() {

     workshop progress


     add new child
     view/edit child
     update niceness rating
     auto assign gift to child

     auto assign all gifts to all children
     purge list of children over 18

     assign toy to elf

     change password

}


ms claus() {

     add elf
     fire elf
     reset elf password

     change personal password

}


admin() {

     reset to default
     january mode


}



int main()
{


     welcome();


     int *permission = new int;

     string *username = new string;
     string *password = new string;

     cout<<"Enter username: ";
     cin>>*username;
     cout<<"Enter password: ";
     cin>>*password;


     *permission = login();

     while(*permission == 0) {



          *permission = login();
     }

     switch(*permission) {
          case 1:
               menu1();
               break;
     }


     string *username = new string("santa");
     string *password = new string("santa");


     cout<<generateHash(username, password);

     changeColor(5, 6);




     //setup console inorder to handle mouse clicks
     HANDLE input_handle;
     input_handle = GetStdHandle(STD_INPUT_HANDLE);
     SetConsoleMode(input_handle, ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_INSERT_MODE | ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);


     setScreenPosAndSize();










     //animations2();

     //while (true)
     //cout<<clicked(100, 150, 200, 250)<<"\n"<<mouseInput().x<<" "<<mouseInput().y<<"\n";

     _getch();
     return EXIT_SUCCESS;
}
