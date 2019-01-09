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
#include <vector>
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
     string *name = new (nothrow) string("");
     //date of hire in unix time
     int *hireDate = new (nothrow) int(0);
     //years since hire
     int *yearsSinceHire = new (nothrow) int(0);
     //toy assigned (see lookup table)
     int *toyAssigned = new (nothrow) int(0);
     //number of toys made
     int *toysMade = new (nothrow) int(0);
     //percent progress (0-100)
     int *progress = new (nothrow) int(0);

public:
     //init User
     User (string *nameInput, int *hireDateInput, int *yearsSinceHire, int *numberOfToysMade) {
          *name = *nameInput;

          *hireDate = *hireDateInput;

          *yearsSinceHire = getYearsSince(hireDate);

          *toyAssigned = 0

          *toysMade = *numberOfToysMade;
     }
     int getNumberOfToysMade () {
          return *toysMade;
     }
     void assignToysMade (int *numberOfToysMade){
          *toysMade = *numberOfToysMade;
     }
     int toyAssignedToElf (){
          return *toyAssigned;
     }
     ~User(){
          delete name;
          delete hireDate;
          delete yearsSinceHire;
          delete toyAssigned;
          delete toysMade;
          delete progress;
     }
     //get name
     //string *getName() {
     //     return *name;
     //}

};


class Child {
private:
     //name of child
     string *name = new (nothrow) string("");
     //birthday
     int *birthday = new (nothrow) int(0);
     //age
     int *age = new (nothrow) int(0);
     //gender
     bool *gender = new (nothrow) int(0);
     //home address
     string *homeAddress = new (nothrow) string("");
     //number of siblings
     int *numberOfSiblings = new (nothrow) int(0);
     //cookie rating
     int *cookieRating = new (nothrow) int(0);
     //niceness rating
     int *nicenessRating = new (nothrow) int(0);
     //toy assinged
     int *toyAssigned = new (nothrow) int(0);

public:
     //constructor
     Child (string *nameInput, int *birthdayInput, bool *genderInput, string *homeAddressInput, int *numberOfSiblingsInput) {

          *name = *nameInput;
          *birthday = *birthdayInput;
          *age = getYearsSince(*birthday);
          *gender = *genderInput;
          *homeAddress = *homeAddressInput
          *numberOfSiblings = *numberOfSiblingsInput;
          *cookieRating = 0;
          *NicenessRating = 50;
          *toyAssigned = 0;
     }
     int assignToy(){
          return *toyAssigned;
     }
     int changeHomeAddress(){
          return *homeAddress;
     }
     int siblingNumber(){
          return *numberOfSiblings;
     }
     int setCookieRating(){
          return *cookieRating;
     }
     int setNicenessRating(){
          return *nicenessRating;
     }

     ~Child(){
          delete name;
          delete birthday;
          delete age;
          delete gender;
          delete homeAddress;
          delete numberOfSiblings;
          delete cookieRating;
          delete nicenessRating;
          delete toyAssigned;
     }

};


//general utility funtions
size_t generateHash(string *username, string *password) {
     hash<string> hash_fn;
     return  hash_fn(*username+*password);
}

int getYearsSince(int dateInUnixTime) {

     int secondsSinceEpoch = (int)time(0);
     return (secondsSinceEpoch - dateInUnixTime)/(60*60*24*365.25);

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


void setupConsole() {
     //setup console inorder to handle mouse clicks
     HANDLE input_handle;
     input_handle = GetStdHandle(STD_INPUT_HANDLE);
     SetConsoleMode(input_handle, ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_INSERT_MODE | ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);

     setScreenPosAndSize();

}

void error(int errorCode) {

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

               //User tempUser(name, hireDate, toyAssigned, numberOfToysMade);

               //users.push_back(tempUser);

               //delete tempUser();

          }

          usersFile->close();

     }
     //end load all users


     //load children
     ifstream *childrensFile = new ifstream;
     childrensFile->open("children.txt");

     int *numberOfChildren = new int;

     //string *name = new string();
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

               //Child tempChild(name, birthday, gender, homeAddress, numberOfSiblings);

               //children.push_back(tempChild);

               //delete tempChild();
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

int dateAsUnix(string dateString) {


     time_t rawtime;
     struct tm * timeinfo;
     int year, month, day;

     year = stoi(dateString.begin(), dateString.begin()+3);
     cout<<year;

     /*
     time ( &rawtime );
     timeinfo = localtime ( &rawtime );
     timeinfo->tm_year = year - 1900;
     timeinfo->tm_mon = month - 1;
     timeinfo->tm_mday = day;
*/


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


//core functions
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
void newChild() {
     string *name = new string;
     int *birthday = new int;
     bool *gender = new bool;
     string *homeAddress = new string;
     int *numberOfSiblings = new int;

     string *birthdayInput = new string;


     cout<<"Enter child's name: ";
     cin>>*name;
     cout<<"Enter child's birthday (YYYY/MM/DD): "
     cin>>*birthdayInput;

     bool *error = new bool(false);

     if (*birthdayInput.length()!=10) {
          *error = true;
     } else {
          for (int i = 0; i<10; i++) {
               if (i==4 || i== 7) {
                    if (birthdayInput.at(i)!='/') {
                         *error = true;
                    }
               } else {
                    if (!isdigit(birthdayInput.at(i))) {
                         *error = true;
                    }
               }
          }
     }


     *birthday =




     *usersFile >> *birthday;
     *usersFile >> *gender;
     *usersFile >> *homeAddress;
     *usersFile >> *numberOfSiblings;

     //Child tempChild(name, birthday, gender, homeAddress, numberOfSiblings);

     //children.push_back(tempChild);

     //delete tempChild();
}
void viewChild(){

}
void assignGift(){

}
void assignAllGifts(){

}
void purgeChildren(){

}
void elfToy(){

}
void changePassword(){

}
void workshopProgress(){

}
void addElf(){

}
void fireElf(){

}
void resetElfPassword(){

}
void changePersonalPassword(){

}
void modeJanuary(){

}
void resetDefault(){

}
void menuElf(){

     int *selectionelf = new (nothrow) int(0);
     int *error = new (nothrow) int (0);

do {
          *error = 0;
          cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
          cout << "\t\t\t" << "  _______  ___       _______      ___      ___   _______  _____  ___   ____  ____  " << endl;
          cout << "\t\t\t" << " /\"     \"||\"  |     /\"     \"|    |\"  \\    /\"  | /\"     \"|(\\\"   \\|\"  \\ (\"  _||_ \" | " << endl;
          cout << "\t\t\t" << "(: ______)||  |    (: ______)     \\   \\  //   |(: ______)|.\\\\   \\    ||   (  ) : | " << endl;
          cout << "\t\t\t" << " \\/    |  |:  |     \\/    |       /\\\\  \\/.    | \\/    |  |: \\.   \\\\  |(:  |  | . ) " << endl;
          cout << "\t\t\t" << " // ___)_  \\  |___  // ___)      |: \\.        | // ___)_ |.  \\    \\. | \\\\ \\__/ //  " << endl;
          cout << "\t\t\t" << "(:      \"|( \\_|:  \\(:  (         |.  \\    /:  |(:      \"||    \\    \\ | /\\\\ __ //\\  " << endl;
          cout << "\t\t\t" << " \\_______) \\_______)\\__/         |___|\\__/|___| \\_______) \\___|\\____\\)(__________) " << endl;
          cout << "\t\t\t" << "\t\t\t\t1. Add New Child" << endl;
          cout << "\t\t\t" << "\t\t\t\t2. View/Edit Child" << endl;
          cout << "\t\t\t" << "\t\t\t\t3. Update Niceness Rating" << endl;
          cout << "\t\t\t" << "\t\t\t\t4. Change Password" << endl;
          cout << "\t\t\t" << "\t\t\t\t" << ">";
          cin >> *selectionelf;
          if (*selectionelf < 1 || *selectionelf > 4)
          {
               cout << "Error! Your Selection Must be Within 1 & 4" << endl;
               *error = 46; //Error Code 46 means Error = true
               _getch();
               system("cls");
          }
     } while(*error == 46);

     switch(*selectionelf)
     {
     case 1:
          newChild();
          break;
     case 2:
          viewChild();
          break;
     case 3:
          viewChild();
          break;
     case 4:
          changePassword();
          break;
     }

     getch();

     delete selectionelf;
     delete error;

}
void menuSanta(){

     int *selectionsanta = new (nothrow) int(0);
     int *error = new (nothrow) int (0);

     do {
          *error = 0;
          cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
          cout << "\t\t\t" << " ,---.                    ,--.              ,--.   ,--." << endl;
          cout << "\t\t\t" << "\'   .-\'  ,--,--.,--,--, ,-\'  \'-. ,--,--.    |   `.\'   | ,---. ,--,--, ,--.,--." << endl;
          cout << "\t\t\t" << "`.  `-. \' ,-.  ||      \' -.  .-\'\' ,-.  |    |  |\'.\'|  || .-. :|      \\|  ||  |" << endl;
          cout << "\t\t\t" << ".-\'    |\\ \'-\'  ||  ||  |  |  |  \\ '-'  |    |  |   |  |\\   --.|  ||  |\'  \'\'  \'" << endl;
          cout << "\t\t\t" << " `-----\' `--`--\'`--\'\'--\'  `--\'   `--`--\'    `--\'   `--\' `----\'`--\'\'--\' `----\' " << endl;
          cout << "\t\t\t" << "\t\t\t\t1. Add New Child" << endl;
          cout << "\t\t\t" << "\t\t\t\t2. View/Edit Child" << endl;
          cout << "\t\t\t" << "\t\t\t\t3. Update Niceness Rating" << endl;
          cout << "\t\t\t" << "\t\t\t\t4. Auto Assign Gift" << endl;
          cout << "\t\t\t" << "\t\t\t\t5. Auto Assign Gift To All" << endl;
          cout << "\t\t\t" << "\t\t\t\t6. Purge 18+ Children" << endl;
          cout << "\t\t\t" << "\t\t\t\t7. Assign Toy to Elf" << endl;
          cout << "\t\t\t" << "\t\t\t\t8. Workshop Progress" << endl;
          cout << "\t\t\t" << "\t\t\t\t9. Change Password" << endl;
          cout << "\t\t\t" << "\t\t\t\t" << ">";
          cin >> *selectionsanta;
          if (*selectionsanta < 1 || *selectionsanta > 9)
          {
               cout << "Error! Your Selection Must be Within 1 & 9" << endl;
               *error = 46; //Error Code 46 means Error = true
               _getch();
               system("cls");
          }
     } while(*error == 46);
     switch(*selectionsanta)
     {
     case 1:
          newChild();
          break;
     case 2:
          viewChild();
          break;
     case 3:
          viewChild();
          break;
     case 4:
          assignGift();
          break;
     case 5:
          assignAllGifts();
          break;
     case 6:
          purgeChildren();
          break;
     case 7:
          elfToy();
          break;
     case 8:
          workshopProgress();
          break;
     case 9:
          changePassword();
          break;
     }

     _getch();
     delete selectionsanta;
     delete error;

}
void menuMrsClaus(){

     int *selectionmrsclaus = new (nothrow) int(0);
     int *error = new (nothrow) int (0);
     do {
          *error = 0;
          cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
          cout << "\t\t\t\t" << "  __  __               _____ _                   __  __                  " << endl;
          cout << "\t\t\t\t" << " |  \\/  |             / ____| |                 |  \\/  |                 " << endl;
          cout << "\t\t\t\t" << " | \\  / |_ __ ___    | |    | | __ _ _   _ ___  | \\  / | ___ _ __  _   _ " << endl;
          cout << "\t\t\t\t" << " | |\\/| | \'__/ __|   | |    | |/ _` | | | / __| | |\\/| |/ _ \\ \'_ \\| | | |" << endl;
          cout << "\t\t\t\t" << " | |  | | |  \\__ \\_  | |____| | (_| | |_| \\__ \\ | |  | |  __/ | | | |_| |" << endl;
          cout << "\t\t\t\t" << " |_|  |_|_|  |___(_)  \\_____|_|\\__,_|\\__,_|___/ |_|  |_|\\___|_| |_|\\__,_|" << endl;
          cout << "\t\t\t" << "\t\t\t\t1. Add Elf" << endl;
          cout << "\t\t\t" << "\t\t\t\t2. Fire Elf" << endl;
          cout << "\t\t\t" << "\t\t\t\t3. Reset Elf Password" << endl;
          cout << "\t\t\t" << "\t\t\t\t4. Change Personal Password" << endl;
          cout << "\t\t\t" << "\t\t\t\t" << ">";
          cin >> *selectionmrsclaus;
          if (*selectionmrsclaus < 1 || *selectionmrsclaus > 4)
          {
               cout << "Error! Your Selection Must be Within 1 & 4" << endl;
               *error = 46; //Error Code 46 means Error = true
               _getch();
               system("cls");
          }
     } while(*error == 46);
     switch(*selectionmrsclaus)
     {
     case 1:
          addElf();
          break;
     case 2:
          fireElf();
          break;
     case 3:
          resetElfPassword();
          break;
     case 4:
          changePersonalPassword();
          break;
     }

     _getch();
     delete selectionmrsclaus;
     delete error;
}
void menuAdmin(){
     /*reset to default
     january mode*/
     int *selectionadmin = new (nothrow) int(0);
     int *error = new (nothrow) int (0);
     do {
          *error = 0;
          cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;

          cout << "\t\t\t\t" << "    ___       __          _     " << endl;
          cout << "\t\t\t\t" << "   /   | ____/ /___ ___  (_)___ " << endl;
          cout << "\t\t\t\t" << "  / /| |/ __  / __ `__ \\/ / __ \\" << endl;
          cout << "\t\t\t\t" << " / ___ / /_/ / / / / / / / / / /" << endl;
          cout << "\t\t\t\t" << "/_/  |_\\__,_/_/ /_/ /_/_/_/ /_/ " << endl;
          cout << "\t\t\t" << "\t\t\t\t1. Enter Elf Menu" << endl;
          cout << "\t\t\t" << "\t\t\t\t2. Enter Santa Menu" << endl;
          cout << "\t\t\t" << "\t\t\t\t3. Enter Mrs Claus Menu" << endl;
          cout << "\t\t\t" << "\t\t\t\t4. January Mode" << endl;
          cout << "\t\t\t" << "\t\t\t\t5. Reset to Default" << endl;
          cout << "\t\t\t" << "\t\t\t\t" << ">";
          cin >> *selectionadmin;
          if (*selectionadmin < 1 || *selectionadmin > 5)
          {
               cout << "Error! Your Selection Must be Within 1 & 5" << endl;
               *error = 46; //Error Code 46 means Error = true
               _getch();
               system("cls");
          }
     } while(*error == 46);
     switch(*selectionadmin)
     {
     case 1:
          menuElf();
          break;
     case 2:
          menuSanta();
          break;
     case 3:
          menuMrsClaus();
          break;
     case 4:
          modeJanuary();
          break;
     case 5:
          resetDefault();
          break;
     }

     _getch();
     delete selectionadmin;
     delete error;
}



/*todo
classes for users and children

*/


//main function
int main(){

     setupConsole();


     //welcome();

     //cout<<getYearsSince(985323600);

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
               cout << "Error! The Passwod Entered is Incorect. Please Check Your Password or Contact your Administrator";
          *permission = login(username, password);
     }


     vector<User> users;
     vector<Child> children;
     //int *toys = new int(10)[2];

     int **toys;
     toys = new int*[NUMOFTOYS]; // dynamic array (size 5) of pointers to int`

     for (int i = 0; i < NUMOFTOYS; ++i) {
       toys[i] = new int[2];
       // each i-th pointer is now pointing to dynamic array (size 10)
       // of actual int values
     }


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
