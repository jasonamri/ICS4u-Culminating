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


#define NUMOFTOYS 10


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
	while ((start + ((float)(millis / 1000) * CLOCKS_PER_SEC)) > (unsigned)clock());
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


class Child {
private:
     //name of child
     string *name;
     //birthday
     int *birthday;
     //age
     int *age;
     //gender
     bool *gender;
     //home address
     string *homeAddress;
     //number of siblings
     int *numberOfSiblings;
     //cookie rating
     int *cookieRating;
     //niceness rating
     int *nicenessRating
     //toy assinged
     int *toyAssigned;

public:
     //constructor
     Child (string *name, int *birthday, bool *gender, string *homeAddress, int *numberOfSiblings) {

     }


}

size_t generateHash(string *username, string *password) {
     hash<string> hash_fn;
     return  hash_fn(*username+*password);
}




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

     //open login file
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
               //incorrect password
               return 0;
          }

     //can't open file
     } else {
          return -1;
     }


}

void workshopMenu() {
     //ascii art?


}



//elf
void elfMenu(){

int *selectionelf = new (nothrow) int(10);
/*in the workshop menu

add new child
view/edit child
update niceness rating

change password*/

cout << " .----------------.  .----------------.  .----------------.   .----------------.  .----------------.  .-----------------. .----------------. " << endl;
cout << "| |  _________   | || |   _____      | || |  _________   | | | | ____    ____ | || |  _________   | || | ____  _____  | || | _____  _____ | |" << endl;
cout << "| | |_   ___  |  | || |  |_   _|     | || | |_   ___  |  | | | ||_   \\  /   _|| || | |_   ___  |  | || ||_   \\|_   _| | || ||_   _||_   _|| |" << endl;
cout << "| |   |  _|  _   | || |    | |   _   | || |   |  _|      | | | |  | |\\  /| |  | || |   |  _|  _   | || |  | |\\ \\| |   | || |  | \'    \' |  | |" << endl;
cout << "| |   | |_  \\_|  | || |    | |       | || |   | |_  \\_|  | | | |  |   \\/   |  | || |   | |_  \\_|  | || |  |   \\ | |   | || |  | |    | |  | |" << endl;
cout << "| |  _| |___/ |  | || |   _| |__/ |  | || |  _| |_       | | | | _| |_\\/_| |_ | || |  _| |___/ |  | || | _| |_\   |_  | || |   \\ `--\' /   | |" << endl;
cout << "| | |_________|  | || |  |________|  | || | |_____|      | | | ||_____||_____|| || | |_________|  | || ||_____|\\____| | || |    `.__.\'    | |" << endl;
cout << "| |              | || |              | || |              | | | |              | || |              | || |              | || |              | |" << endl;
cout << "| \'--------------\' || \'--------------\' || \'--------------\' | | \'--------------\' || \'--------------\' || \'--------------\' || \'--------------\' |" << endl;
cout << " \'----------------\'  \'----------------\'  \'----------------\'   \'----------------\'  \'----------------\'  \'----------------\'  \'----------------\' " << endl;
cout << "\t\t\t\t";




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



adduser() {
     /*string *username = new string("santa");
     string *password = new string("santa");


     cout<<generateHash(username, password);*/
}

void setupConsole() {
     //setup console inorder to handle mouse clicks
     HANDLE input_handle;
     input_handle = GetStdHandle(STD_INPUT_HANDLE);
     SetConsoleMode(input_handle, ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_INSERT_MODE | ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);

     setScreenPosAndSize();

}

int loadFiles(vector<User> users, vector<Child> children, int toys[10][2]) {

     //load all users
     ifstream *usersFile = new ifstream;
     usersFile->open("users.txt");

     int *numberOfUsers = new int;

     string *name = new string;
     int *hireDate = new int;
     int *toyAssigned = new int;
     int *numberOfToysMade = new int;

     //open user file
     if (usersFile->is_open()) {
          *usersFile>> *numberOfUsers;

          for (int i = 0; i < *numberOfUsers; i++) {

               *usersFile >> *name;
               *usersFile >> *hireDate;
               *usersFile >> *toyAssigned;
               *usersFile >> *numberOfToysMade;

               User tempUser(name, hireDate, toysAssigned, numberOfToysMade);

               users.push_back(tempUser);

               delete tempUser();

          }

          usersFile->close();

     }
     //end load all users


     //load children
     ifstream *childrensFile = new ifstream;
     childrensFile->open("users.txt");

     int *numberOfUsers = new int;

     string *name = new string;
     int *birthday = new int;
     bool *gender = new bool;
     string *homeAddress = new string;
     int *numberOfSiblings = new int;

     //open user file
     if (childrensFile->is_open()) {
          *childrensFile>> *numberOfChildren;

          for (int i = 0; i < *numberOfChildren; i++) {

               *usersFile >> *name;
               *usersFile >> *birthday;
               *usersFile >> *gender;
               *usersFile >> *homeAddress;
               *usersFile >> *numberOfSiblings;

               Child tempChild(name, birthday, gender, homeAddress, numberOfSiblings);

               child.push_back(tempChild);

               delete tempChild();
          }
          childrensFile->close();
     }
     //end load children

     //load toys
     ifstream *toysFile = new ifstream;
     toysFile->open("toys.txt");

     int *needed = new int;
     int *made = new int;


     if (toysFile->is_open()) {

          for (int i = 0; i < NUMOFTOYS; i++) {

               *toysFile >> *needed;
               *toysFile >> *made;

               toys[i][0]=*needed;
               toys[i][1]=*made;
          }
          toysFile->close();
     }
     //end load toys

}

/*todo
add user function
classes for users and children

*/

void error() {

}

int main()
{

     setupConsole();


     welcome();


     //handle login
     int *permission = new int;

     string *username = new string;
     string *password = new string;

     cout<<"Enter username: ";
     cin>>*username;
     cout<<"Enter password: ";
     cin>>*password;


     *permission = login(username, password);

     while(*permission == 0) {
          //Todo: failed login try again
          *permission = login(username, password);
     }


     vector<User> users;
     vector<Child> children;
     int *toys = new int[10][2];

     loadFiles(users, children, toys);


/*
     permission level
     1: elf
     2: ms. claus
     3: mr. claus
     4: admin
*/
     switch(*permission) {
          case 1:
               elfMenu();
               break;
          case 2:
               mrsClausMenu();
               break;
          case 3:
               mrClausMenu();
               break;
          case 4:
               admin();
               break;
          default:
               error();
               break;
     }


     changeColor(5, 6);



     _getch();
     return EXIT_SUCCESS;
}


//code snippets
//animations2();

//while (true)
//cout<<clicked(100, 150, 200, 250)<<"\n"<<mouseInput().x<<" "<<mouseInput().y<<"\n";

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
