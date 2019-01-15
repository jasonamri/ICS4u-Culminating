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

#define MAXCHILDREN 100
#define MAXUSERS 50


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

void delay(long unsigned int millis){
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

int getYearsSince(int *dateInUnixTime) {

     int secondsSinceEpoch = (int)time(0);
     return (secondsSinceEpoch - *dateInUnixTime)/(60*60*24*365.25);

}

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

          *toyAssigned = 0;

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
     string getName() {
          return *name;
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
     string *name = new (nothrow) string;
     //birthday
     int *birthday = new (nothrow) int(0);
     //age
     int *age = new (nothrow) int(0);
     //gender
     bool *gender = new (nothrow) bool;
     //home address
     string *homeAddress = new (nothrow) string("");
     //number of siblings
     int *numberOfSiblings = new int(0);
     //cookie rating
     int *cookieRating = new (nothrow) int(0);
     //niceness rating
     int *nicenessRating = new (nothrow) int(0);
     //toy assinged
     int *toyAssigned = new (nothrow) int(0);

public:
     //constructor
     Child (string *nameInput, int *birthdayInput, bool *genderInput, string *homeAddressInput, int *numberOfSiblingsInput) {

          *gender = *genderInput;

          *name = *nameInput;

          *birthday = *birthdayInput;
          //*age = getYearsSince(birthday);
          //*gender = *genderInput;
          *homeAddress = *homeAddressInput;
          *numberOfSiblings = *numberOfSiblingsInput;

          //cout<<
          //*cookieRating = 0;
          //*nicenessRating = 50;
          //*toyAssigned = 0;
          //cout<<*numberOfSiblings;
     }

     int getAssignedToy(){
          return *toyAssigned;
     }
     string getHomeAddress(){
          return *homeAddress;
     }
     int getSiblingNumber(){
          return *numberOfSiblings;
     }
     int getCookieRating(){
          return *cookieRating;
     }
     int getNicenessRating(){
          return *nicenessRating;
     }
     string getName(){
          //cout << "hello";
          return *name;
     }
     void setNicenessRating(int *nicenessInput) {
          *nicenessRating = *nicenessInput;
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


//returns -1 if users file not found
//returns -2 if children file not found
//returns -3 if toys file not found
//returns 1 if successful

/*
int loadFiles(User * users, int *numberOfUsers, Child * children, int *numberOfChildren, int (*toys)[NUMOFTOYS][2]) {

     //load all users

     //end load all users


     ifstream fin;



     //children.reserve(100);

    fin.open("children.txt");

    if(fin.fail()) {
          // throw error here
          return -2;
    }

    string *nameChild = new (nothrow) string;
    string *homeAddress = new (nothrow) string;
    int *birthday = new (nothrow) int;
    int *gender = new (nothrow) int;
    bool *genderBool = new (nothrow) bool;
    int *numberOfSiblings = new (nothrow) int;
    int *cookieRating = new (nothrow) int;
    int *nicenessRating = new (nothrow) int;
    int *toyAssignedChild = new (nothrow) int;

    if (fin.is_open()) {

         while (!fin.eof() )
         {
               getline(fin, *nameChild, '$');
               //cout<<nameChild<<"\n";
               fin >> *birthday;
               //cout<<birthday<<"\n";
               fin >> *gender;
               //cout<<gender<<"\n";
               getline(fin, *homeAddress, '$');
               //cout<<homeAddress<<"\n";
               fin >> *numberOfSiblings;
               //cout<<numberOfSiblings<<"\n";
               fin >> *cookieRating;
               //cout<<cookieRating<<"\n";
               fin >> *nicenessRating;
               //cout<<nicenessRating<<"\n";
               fin >> *toyAssignedChild;
               //cout<<toyAssignedChild<<"\n";

               *genderBool = (bool)(*gender);

               children[*numberOfChildren] = new (nothrow) Child(nameChild,birthday,genderBool,homeAddress,numberOfSiblings);

               *numberOfChildren++;

              //cout<<"hillo"<<"i:"<<*name<<":i"<<*hireDate<<":i"<<*toyAssigned<<":i"<<*numberOfToysMade<<":i"<<"\n";

              //users.emplace_back(name, hireDate, toyAssigned, numberOfToysMade);

         }
         fin.close();
    }


    delete nameChild;
    delete birthday;
    delete gender;
    delete homeAddress;
    delete numberOfSiblings;
    delete toyAssignedChild;
    delete nicenessRating;
    delete cookieRating;

     //load toys
     fin.open("toys.txt");

     int *needed = new int;
     int *made = new int;

     if(fin.fail()) {
          // throw error here
          return -3;
    }

     if (fin.is_open()) {

          for (int i = 0; i < NUMOFTOYS; i++) {

               fin >> *needed;
               fin >> *made;

               (*toys)[i][0]=*needed;
               (*toys)[i][1]=*made;
          }
          fin.close();
     }
     //end load toys

     return 1;

}

*/

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


/*

ifstream fin;
fin.open("users.txt");

if(fin.fail()) {
     // throw error here
     return -1;

}

string *name = new string("");
int *hireDate = new int;
int *toyAssigned = new int;
int *numberOfToysMade = new int;


//open user file
if (fin.is_open()) {

     while (!fin.eof() )
     {
          fin>> *name;
          fin>> *hireDate;
          fin>> *toyAssigned;
          fin>> *numberOfToysMade;



          users[*numberOfUsers] = new(nothrow) User(name, hireDate, toyAssigned, numberOfToysMade);

          *numberOfUsers++;

          //cout<<"hillo"<<"i:"<<*name<<":i"<<*hireDate<<":i"<<*toyAssigned<<":i"<<*numberOfToysMade<<":i"<<"\n";

          //users.emplace_back(name, hireDate, toyAssigned, numberOfToysMade);

     }
     fin.close();
}

delete hireDate;
delete name;
delete toyAssigned;
delete numberOfToysMade;


*/


//main function
int main(){



     

     //load toys
     /*fin.open("toys.txt");

     int *needed = new int;
     int *made = new int;

     if(fin.fail()) {
          // throw error here
          cout<<"Error loading toys files? Is it in the right spot?";
    }

     if (fin.is_open()) {

          for (int i = 0; i < NUMOFTOYS; i++) {

               fin >> *needed;
               fin >> *made;

               (*toys)[i][0]=*needed;
               (*toys)[i][1]=*made;
          }
          fin.close();
     }



     cout<<toys[1][0];*/


     _getch();
     return EXIT_SUCCESS;
}


