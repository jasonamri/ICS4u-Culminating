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


map<int, string> toysMap = {
    { 0, "Unassigned" },
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
     int getToyAssignedToElf (){
          return *toyAssigned;
     }
     string getName (){
          return *name;
     }
     void setToyAssignedToElf (int *_toyAssigned){
          *toyAssigned = *_toyAssigned;
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
          //todo//*age = getYearsSince(birthday);
          *homeAddress = *homeAddressInput;
          *numberOfSiblings = *numberOfSiblingsInput;
          *cookieRating = 0;
          *nicenessRating = 50;
          *toyAssigned = 0;

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
          if (*nicenessInput > 100) {
               *nicenessInput = 100;
          } else if (*nicenessInput < 0) {
               *nicenessInput = 0;
          }

          *nicenessRating = *nicenessInput;
     }
     void show() {
          cout<<"\nName: "<<*name<<"\nBirthday"<<*birthday;
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

POINT mouseInput (){
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

void errorHandler(int errorCode) {
     cout << "Error Code " << errorCode << "Please Contact an Administrator to Address this Issue."<< endl;
     _getch();
     system("cls");
}

//returns unix time on success
//returns -1 on fail
int dateAsUnix(string * dateString) {

     time_t rawTime, currentTime;
     struct tm * timeinfo;
     struct tm * timeinfoCurrent;
     int *year = new (nothrow) int (0);
     int *month = new (nothrow) int (0);
     int *day = new (nothrow) int (0);

     string *yearString = new string(dateString->substr(0,4));
     string *monthString = new string(dateString->substr(5, 2));
     string *dayString = new string(dateString->substr(8, 2));

//cout<<"year: "<<*yearString<<"mon: "<<*monthString<<"day: "<<*dayString;
//cout<<stoi(*yearString);

    *year = stoi(*yearString);
     *month = stoi(*monthString);
     *day = stoi(*dayString);
//cout<<"rexy";
     //find the current year for error trapping
     time(&currentTime);
     int *currentYear = new int((localtime(&currentTime)->tm_year + 1900));

//cout<<"hey";
     if (*year<1970 || *year>*currentYear) {
          //returns error code, since date it invalid
          return -1;
          //cout<<"hiii";
//todo: error trap better
     } else {
          time ( &rawTime );
          timeinfo = localtime ( &rawTime );
          timeinfo->tm_year = *year - 1900;
          timeinfo->tm_mon = *month - 1;
          timeinfo->tm_mday = *day;
          timeinfo->tm_sec = 0;
          timeinfo->tm_min = 0;
          timeinfo->tm_hour = 12;
//cout<<"hello";
          //returns -1 if failed, otherwise unix time

          //cout<<mktime(timeinfo);

          return mktime(timeinfo);
     }
}


void sortChildren(Child * children[MAXCHILDREN], int * numberOfChildren) {

     int i(0), j(0), temp(0);
     //cout<<"hi"<<children.size();
    for (i = 1; i < *numberOfChildren; i++)
    {

        j = i;
        cout<<"rolec1all\n";
        children[0]->show();
        cout<<children[1]->getName()<<"\n";
        cout<<children[2]->getName()<<"\n";
        cout<<children[3]->getName()<<"\n";
        cout<<children[4]->getName()<<"\n";

        while (j > 0 && children[j]->getName() < children[j - 1]->getName())
        {



             //cout<<"jason";
             Child tempChild = *children[j];
             //cout<<"rexy1";
             *children[j] = *children[j-1];
             //cout<<"rexy2";
             *children[j-1] = tempChild;
             //cout<<"rexy3";
             //cout<<i<<"-"<<j;



             cout<<"rolecall\n";
             cout<<children[0]->getName()<<"\n";
             cout<<children[1]->getName()<<"\n";
             cout<<children[2]->getName()<<"\n";
             cout<<children[3]->getName()<<"\n";
             cout<<children[4]->getName()<<"\n";

             j--;
        }
    }
}

/*
double selectionSort(int array[])
{
   int i(0), j(0), temp(0);
   int min(100), pos(0);



   for (i = 0; i < SIZE - 1; i++)
   {
       min = array[i]; // the first element is Min value
       pos = i;

       for (j = i + 1; j < SIZE; j++) // finding smaller value that Min
       {
           if (array[j] < min)
           {
               min = array[j];
               pos = j;
           }
       }
       temp = array[i]; // swap selected element and Min value
       array[i] = array[pos];
       array[pos] = temp;
   }


   return 0;
}*/

void sortUsers() {


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

//arguments: pointer to username inputted as string, pointer to password entered as string
int loginHandler(string *username, string *password) {

     ifstream *loginFile = new ifstream;
     loginFile->open("login.txt");

     int *numberOfUsers = new int;

     bool *usernameFound = new bool(false);

     string *usernameToTest = new string;
     size_t *hashToTest = new size_t;
     int *permissionLevel = new int;

     //open login file
     if (loginFile->is_open()) {

          while (!loginFile->eof()) {

               *loginFile>>*usernameToTest;
               *loginFile>> *hashToTest;
               *loginFile>> *permissionLevel;

               if (*username==*usernameToTest) {
                    *usernameFound=true;
                    break;
               }
          }


          loginFile->close();

          if (*usernameFound != true) {
               //user doesn't exist
               return 0;
          } else {
               if (generateHash(username, password)==*hashToTest) {
                    return *permissionLevel;
               } else {
                    //incorrect password
                    return 0;
               }
          }

     //can't open file
     } else {
          return 0;
     }


}






//purpose:
//   loads data from textfiles into arrays for use
//arugments:
//   users array, number of users pointer, children array, number of children pointer, toys array
//returns:
//   -1 if users file not found
//   -2 if children file not found
//   -3 if toys file not found
//   1 if successful
int loadFiles(User * users[MAXUSERS], int *numberOfUsers, Child * children[MAXCHILDREN], int * numberOfChildren, int (*toys)[NUMOFTOYS][2]) {
     //load users
     ifstream fin;
     fin.open("users.txt");

     if(fin.fail()) {
          // throw error here
          //cout<<"Error loading user files? Is it in the right spot?";
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

               *numberOfUsers = (*numberOfUsers + 1);

          }
          fin.close();
     }

     delete hireDate;
     delete name;
     delete toyAssigned;
     delete numberOfToysMade;


     //load children
     fin.open("children.txt");

    if(fin.fail()) {
          // throw error here
          //cout<<"Error loading children files? Is it in the right spot?";
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
               //getline(fin, *nameChild, '\n');
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

               //children[*numberOfChildren]->show();
               //_getch();

               *numberOfChildren = (*numberOfChildren + 1);

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

    if(fin.fail()) {
          // throw error here
          //cout<<"Error loading toys files? Is it in the right spot?";
          return -3;
    }

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

    return 1;

}







//elf
/*void newChild() {
     string *name = new string;
     int *birthday = new int;
     bool *gender = new bool;
     string *homeAddress = new string;
     int *numberOfSiblings = new int;

     string *birthdayInput = new string;
     string *genderInput = new string;

     cout<<"Enter Child's name: ";
     getline(cin, *name);


     bool *error = new (nothrow) bool;

     do {
          cout<<"Enter Child's birthday (YYYY/MM/DD): ";
          getline(cin, *birthdayInput);

          *error = false;

          if (birthdayInput->length()!=10) {
               *error = true;
          }
             else {
               for (int i = 0; i<10; i++) {
                    if (i==4 || i== 7) {
                         if (birthdayInput->at(i)!='/') {
                              *error = true;
                         }
                    } else {
                         if (!isdigit(birthdayInput->at(i))) {
                              *error = true;
                         }
                    }
               }
          }


          *birthday = dateAsUnix(birthdayInput);

          if (*birthday == -1) {
               *error = true;
          }

          if (*error == true) {
               //todo: error message
               system("cls");
               cout<<"Invalid Date Format!";
          }
     } while (*error == true);


     do {
          cout<<"Enter child's gender (male or female): ";
          getline(cin, *genderInput);


          //*genderInput.ToLower(*genderInput);

          for (int i = 0; i < genderInput->length(); i++) {
               genderInput->at(i)=tolower(genderInput->at(i));
          }



          if (*genderInput != "male" && *genderInput != "female")
          {
               *error = true;
               cout << "Error! The Gender you Inputted Does Not Exist. Please Enter a Real Gender of Male or Female. ";
               _getch();
               system("cls");
          }

     } while (*error == true);


     /**usersFile >> *birthday;
     *usersFile >> *gender;
     *usersFile >> *homeAddress;
     *usersFile >> *numberOfSiblings;*/

     //Child tempChild(name, birthday, gender, homeAddress, numberOfSiblings);

     //children.push_back(tempChild);

     //delete tempChild();
//}

void workshopMenu() {
     //ascii art?


}


//arrow key handler
//arguments: boolean indicating whether to wait for key press
//returns: int 0-6 for arrow key direction or enter key
//0: enter
//1: up
//2: left
//3: right
//4: down
//5: tab
//6: esc
int arrowKeys(bool wait) {
	//buffer variable
	int input = 0;

	//wait for enter or arrowKey if requested by function arguments
	if (wait) {
		//wait until the correct input is recieved
		while (input != 224 && input != 13 && input != 9 && input !=27) {
			input = _getch();
			//printf("%d", input);
		}
	} else {
		input = _getch();
	}

	//return value based on input
	if (input == 13) {
		//return 0 for enter
		return 0;
	} else if (input == 9) {
		//return 5 for tab
		return 5;
	}
	else if (input == 27) {
		//return 6 for esc
		return 6;
	}
	else {
		//return 1-4 for directions and 7 for error
		switch (_getch()) {
		case 72:
			return 1;
			break;
		case 75:
			return 2;
			break;
		case 77:
			return 3;
			break;
		case 80:
			return 4;
			break;
		default:
			return 7;
			break;
		}
	}
}


//callled by view child to edit detailed atributes
void editChild(Child *children[MAXCHILDREN], int *index) {


     system("cls");


     /*todo: be able to change:
     address
     siblings
     cookie rating
     niceness rating
     */

     cout<<children[*index]->getName();

     _getch();
     system("cls");
}

void viewChild(Child *children[MAXCHILDREN], int *numberOfChildren){

     int *input = new int(7);
     int *selection = new int (0);
     int *nicenessRating = new int;

     do {

          system("cls");
          for (int i=0; i<*numberOfChildren; i++) {
               //todo: formating of names by length
               if (*selection == i) {
                    changeColor(15, 4);
               }
               cout<<children[i]->getName()<<"\t\t\t\t\t\t"<<children[i]->getNicenessRating();
               if (*selection == i) {
                    changeColor(4, 15);
               }
          }

          *nicenessRating = children[*selection]->getNicenessRating();

          *input = arrowKeys(true);

          //0: enter
          //1: up
          //2: left
          //3: right
          //4: down
          //5: tab
          //6: esc

          switch (*input) {
               case 0:
                    editChild(children, selection);
                    break;
               case 1:
                    if (*selection>0) {*selection = *selection -1;}
                    break;
               case 2:
                    *nicenessRating = *nicenessRating - 1;
                    children[*selection]->setNicenessRating(nicenessRating);
                    break;
               case 3:
                    *nicenessRating = *nicenessRating + 1;
                    children[*selection]->setNicenessRating(nicenessRating);
                    break;
               case 4:
                    if (*selection<*numberOfChildren-1) {*selection = *selection +1;}
                    break;
          }


     } while (*input != 6);



     delete selection;
     delete input;
     delete nicenessRating;


     system("cls");

}


void addChild(Child * children[MAXCHILDREN], int * numberOfChildren){
     //CHILD child;
     string *childName = new (nothrow) string;
     int *childBirthday = new (nothrow) int(0);
     string *childBirthdayInput = new (nothrow) string;
     int *childAge = new (nothrow) int(0);
     string *childGender = new (nothrow) string;
     string *childHomeAddress = new (nothrow) string;
     int *childNumberOfSiblings = new (nothrow) int(0);
     int *childToyAssigned = new (nothrow) int(0);
     bool *error = new (nothrow) bool;
     bool *genderBool = new (nothrow) bool;

     system("cls");

     cout << "Please Input the Name of the Child...> ";
     fflush(stdin);
     getline(cin, *childName);

     do {
          cout << "Please Input the Birthday of the Child(YYYY/MM/DD)...> ";
          getline(cin, *childBirthdayInput);

          *error = false;

          if (childBirthdayInput->length()!=10) {
               *error = true;

          } else {
               for (int i = 0; i<10; i++) {
                    if (i == 4 || i == 7) {
                         if (childBirthdayInput->at(i)!='/') {
                              *error = true;
                         }
                    } else {
                         if (!isdigit(childBirthdayInput->at(i))) {
                              *error = true;
                         }
                    }
               }
          }

          if (!(*error)) {
               //cout<<"hi";
               *childBirthday = dateAsUnix(childBirthdayInput);

               if (*childBirthday == -1) {
                    *error = true;
               }
          }

          if (*error == true) {
               //todo: error message
               system("cls");
               cout<<"Invalid Date!\n";
          }

     } while (*error == true);



     do
     {
          *error = false;

          cout << "Please Input the Gender of the Child(M/F) --> ";
          getline(cin, *childGender);

          for (int i = 0; i < childGender->length(); i++) {
               childGender->at(i)=toupper(childGender->at(i));
          }

          if (*childGender != "M" && *childGender != "F")
          {
               *error = true;
               cout << "Error! The Gender you Inputted Does Not Exist. Please Enter a Gender of Male or Female. ";
               _getch();
               system("cls");
          }

     } while (*error == true);




     if (*childGender == "M") {
          *genderBool = true;
     } else {
          *genderBool = false;
     }

     cout << "Please Input the Home Address of the Child --> ";
     getline(cin, *childHomeAddress);


     do
     {
          *error = false;

          cout << "Please Input the Number of Siblings the Child has --> ";
          cin >> *childNumberOfSiblings;

          if (*childNumberOfSiblings < 0)
          {
               *error = true;
               cout << "Error! Can't have negative siblings!";
               _getch();
               system("cls");
          }

     } while (*error == true);


     /*do {
          *error = false;
          cout << "Please Input the Toy that was Assigned to the Child(1-10)";
          cin >> *childToyAssigned;
          if (*childToyAssigned < 1 || *childToyAssigned > 10)
          {
               *error = true;
               system("cls");
               _getch();
          }
     } while(*error == true);*/


     children[*numberOfChildren] = new (nothrow) Child(childName,childBirthday,genderBool,childHomeAddress,childNumberOfSiblings);

     *numberOfChildren = (*numberOfChildren + 1);

     cout<<"Successfully added! Press any key to return to menu.";
     _getch();
     system("cls");

     delete childName;
     delete childBirthday;
     delete childBirthdayInput;
     delete childAge;
     delete childGender;
     delete childHomeAddress;
     delete childNumberOfSiblings;
     delete childToyAssigned;
     delete error;
     delete genderBool;


}


void assignGift(){

}
void assignAllGifts(){

}
void purgeChildren(){

}
void elfToy(User *users[MAXUSERS], int *numberOfUsers){


     int *selection = new int (0);
     int *input = new (nothrow) int(7);

     cout<<"Select Elf, then press enter. (Press esc to go back)\n\n";

     do {
          system("cls");
          for (int i=0; i<*numberOfUsers; i++) {
               //todo: formating of names by length
               if (*selection == i) {
                    changeColor(15, 4);
               }
               cout<<users[i]->getName()<<"\t\t\t\t\t"<<toysMap.at(users[i]->getToyAssignedToElf())<<"\n";

               ;
               if (*selection == i) {
                    changeColor(4, 15);
               }
          }

          *input = arrowKeys(true);
          switch (*input) {
               case 1:
                    if (*selection>0) {*selection = *selection -1;}
                    break;
               case 4:
                    if (*selection<*numberOfUsers-1) {*selection = *selection +1;}
                    break;
          }


     } while (*input != 6 && *input != 0);


     int *elfToyAssign = new (nothrow) int(0);

     do {
          system("cls");
          cout << "\t\t\t\t" << " .----------------.  .----------------.  .----------------.  .----------------. " << endl;
          cout << "\t\t\t\t" << "| .--------------. || .--------------. || .--------------. || .--------------. |" << endl;
          cout << "\t\t\t\t" << "| |  _________   | || |     ____     | || |  ____  ____  | || |    _______   | |" << endl;
          cout << "\t\t\t\t" << "| | |  _   _  |  | || |   .\'    `.   | || | |_  _||_  _| | || |   /  ___  |  | |" << endl;
          cout << "\t\t\t\t" << "| | |_/ | | \\_|  | || |  /  .--.  \\  | || |   \\ \\  / /   | || |  |  (__ \\_|  | |" << endl;
          cout << "\t\t\t\t" << "| |     | |      | || |  | |    | |  | || |    \\ \\/ /    | || |   \'.___`-.   | |" << endl;
          cout << "\t\t\t\t" << "| |    _| |_     | || |  \\  `--\'  /  | || |    _|  |_    | || |  |`\\____) |  | |" << endl;
          cout << "\t\t\t\t" << "| |   |_____|    | || |   `.____.\'   | || |   |______|   | || |  |_______.\'  | |" << endl;
          cout << "\t\t\t\t" << "| |              | || |              | || |              | || |              | |" << endl;
          cout << "\t\t\t\t" << "| \'--------------\' || \'--------------\' || \'--------------\' || \'--------------\' |" << endl;
          cout << "\t\t\t\t" << " \'----------------\'  \'----------------\'  \'----------------\'  \'----------------\'" << endl;
          cout << "\t\t\t\t" << "\t\t\t\t" << "1. Teddy bear" << endl;
          cout << "\t\t\t\t" << "\t\t\t\t" << "2. Toy blocks" <<endl;
          cout << "\t\t\t\t" << "\t\t\t\t" << "3. Rubber ducky" <<endl;
          cout << "\t\t\t\t" << "\t\t\t\t" << "4. Firetruck" <<endl;
          cout << "\t\t\t\t" << "\t\t\t\t" << "5. Hockey stick" <<endl;
          cout << "\t\t\t\t" << "\t\t\t\t" << "6. Book" <<endl;
          cout << "\t\t\t\t" << "\t\t\t\t" << "7. Toy car" <<endl;
          cout << "\t\t\t\t" << "\t\t\t\t" << "8. Slime" <<endl;
          cout << "\t\t\t\t" << "\t\t\t\t" << "9. Lego" <<endl;
          cout << "\t\t\t\t" << "\t\t\t\t" << "10. Pyjamas" <<endl;
          cout << "\t\t\t\t" << "\t\t\t\t" << ">";
          cin >> *elfToyAssign;
          if (*elfToyAssign < 1 || *elfToyAssign > NUMOFTOYS)
          {
               cout << "Error! Your Selection Must be Within 1 & 10" << endl;
               _getch();
          }

          system("cls");

     } while(*elfToyAssign < 1 || *elfToyAssign > NUMOFTOYS);

     users[*selection]->setToyAssignedToElf(elfToyAssign);

     delete selection;
     delete elfToyAssign;
     delete input;

}
void changePassword(){

}
void workshopProgress(){

}
void addElf(User * users[MAXUSERS]){

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


void menuElf(User * users[MAXUSERS], int *numberOfUsers, Child * children[MAXCHILDREN], int * numberOfChildren, int (*toys)[NUMOFTOYS][2]){

     int *selectionelf = new (nothrow) int(0);
     bool *error = new (nothrow) bool;

     do {
          *error = false;
          system("cls");
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
               *error = true; //Error Code 46 means Error = true
               _getch();
               system("cls");
          }
     } while(*error == true);

     switch(*selectionelf)
     {
     case 1:
          addChild(children, numberOfChildren);
          break;
     case 2:
          viewChild(children, numberOfChildren);
          break;
     case 3:
          viewChild(children, numberOfChildren);
          break;
     case 4:
          changePassword();
          break;
     }

     getch();

     delete selectionelf;
     delete error;

}
void menuSanta(User * users[MAXUSERS], int *numberOfUsers, Child * children[MAXCHILDREN], int * numberOfChildren, int (*toys)[NUMOFTOYS][2]){

     int *selectionsanta = new (nothrow) int(0);
     bool *error = new (nothrow) bool;

     while (*selectionsanta != 10) {

          do {
               *error = false;
               system("cls");
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
               cout << "\t\t\t" << "\t\t\t\t10. Exit" << endl;
               cout << "\t\t\t" << "\t\t\t\t" << ">";
               cin >> *selectionsanta;
               if (*selectionsanta < 1 || *selectionsanta > 10)
               {
                    cout << "Error! Your Selection Must be Within 1 & 9" << endl;
                    *error = true; //Error Code 46 means Error = true
                    _getch();
                    system("cls");
               }
          } while(*error == true);



          switch(*selectionsanta)
          {
          case 1:
               addChild(children, numberOfChildren);
               break;
          case 2:
               viewChild(children, numberOfChildren);
               break;
          case 3:
               viewChild(children, numberOfChildren);
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
               elfToy(users, numberOfUsers); //works
               break;
          case 8:
               workshopProgress();
               break;
          case 9:
               changePassword();
               break;
          }

     }


     delete selectionsanta;
     delete error;

}
void menuMrsClaus(User * users[MAXUSERS], int *numberOfUsers, Child * children[MAXCHILDREN], int * numberOfChildren, int (*toys)[NUMOFTOYS][2]){

     int *selectionmrsclaus = new (nothrow) int(0);
     bool *error = new (nothrow) bool;
     do {
          *error = false;
          system("cls");
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
               *error = true; //Error Code 46 means Error = true
               _getch();
               system("cls");
          }
     } while(*error == true);
     switch(*selectionmrsclaus)
     {
     case 1:
          addElf(users);
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
void menuAdmin(User * users[MAXUSERS], int *numberOfUsers, Child * children[MAXCHILDREN], int * numberOfChildren, int (*toys)[NUMOFTOYS][2]){
     //reset to default
     //january mode
     int *selectionadmin = new (nothrow) int(0);
     bool *error = new (nothrow) bool;
     do {
          *error = false;
          system("cls");
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
               *error = true; //Error Code 46 means Error = true
               _getch();
               system("cls");
          }
     } while(*error == true);
     switch(*selectionadmin)
     {
     case 1:
          menuElf(users, numberOfUsers, children, numberOfChildren, toys);
          break;
     case 2:
          menuSanta(users, numberOfUsers, children, numberOfChildren, toys);
          break;
     case 3:
          menuMrsClaus(users, numberOfUsers, children, numberOfChildren, toys);
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


//Login Function
int login(){
     int *permission = new int;

     string *username = new string;
     string *password = new string;
     bool *error = new (nothrow) bool;

     do
     {
          *error = false;

          cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
          cout << "\t\t\t" << " _____                   ____             _____         ____________  _____    _____" << endl;
          cout << "\t\t\t" << "|\\    \\              ____\\_  \\__     _____\\    \\_      /            \\|\\    \\   \\    \\" << endl;
          cout << "\t\t\t" << " \\\\    \\            /     /     \\   /     /|     |    |\\___/\\  \\\\___/|\\\\    \\   |    |" << endl;
          cout << "\t\t\t" << "  \\\\    \\          /     /\\      | /     / /____/|     \\|____\\  \\___|/ \\\\    \\  |    |" << endl;
          cout << "\t\t\t" << "   \\|    | ______ |     |  |     ||     | |_____|/           |  |       \\|    \\ |    |" << endl;
          cout << "\t\t\t" << "    |    |/      \\|     |  |     ||     | |_________    __  /   / __     |     \\|    |" << endl;
          cout << "\t\t\t" << "    /            ||     | /     /||\\     \\|\\        \\  /  \\/   /_/  |   /     /\\      \\" << endl;
          cout << "\t\t\t" << "   /_____/\\_____/||\\     \\_____/ || \\_____\\|    |\\__/||____________/|  /_____/ /______/|" << endl;
          cout << "\t\t\t" << "  |      | |    ||| \\_____\\   | / | |     /____/| | |||           | / |      | |     | |" << endl;
          cout << "\t\t\t" << "  |______|/|____|/ \\ |    |___|/   \\|_____|     |\\|_|/|___________|/  |______|/|_____|/" << endl;
          cout << "\t\t\t" << "                    \\|____|               |____/                                         " << endl;
          cout<< "\t\t\t\t\t\t" << "Enter username: ";
          getline(cin, *username);
          cout<< "\t\t\t\t\t\t" << "Enter password: ";
          getline(cin, *password);


          *permission = loginHandler(username, password);

          if(*permission == 0) {
               cout << "Error! The Passwod Entered is Incorect. Please Check Your Password or Contact your Administrator";
               *error = true;
               _getch();
               system("cls");
               //*permission = login(username, password);
          }
     } while(*error == true);

     return *permission;
}
void welcome(){
     double start(0);
     system("color F9");


     delay(50);
     system("color F1");
     system("cls");


     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F1");
     system("cls");


     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F9");
     system("cls");


     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F1");
     system("cls");

     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F9");
     system("cls");

     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F1");
     system("cls");

     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F9");
     system("cls");


     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F1");
     system("cls");

     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F9");
     system("cls");

     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F1");
     system("cls");

     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F9");
     system("cls");


     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F1");
     system("cls");

     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F9");
     system("cls");

     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F1");
     system("cls");


     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F9");
     system("cls");


     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F1");
     system("cls");


     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F9");
     system("cls");


     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F1");
     system("cls");


     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F9");
     system("cls");


     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F1");
     system("cls");

     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F9");
     system("cls");

     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F1");
     system("cls");

     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F9");
     system("cls");
     cout << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F1");
     system("cls");
     cout << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F9");
     system("cls");
     cout << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F1");
     system("cls");
     cout << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F9");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F1");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F9");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F1");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F9");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F1");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F9");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F1");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F9");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F1");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F9");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F1");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F9");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F1");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F9");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F1");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     cout << "                             ()                             " << "\t\t" << "                     ()                             " << endl;
     delay(50);
     system("color F9");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     cout << "                             \\/                             " << "\t\t" << "                     \\/                            " << endl;
     delay(50);
     system("color F1");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     cout << "                            \\\\//                            " << "\t\t" << "                    \\\\//                          " << endl;
     delay(50);
     system("color F9");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     cout << "                           <<  >>                           " << "\t\t" << "                   <<  >>                           " << endl;
     delay(50);
     system("color F1");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     cout << "                        ()  //\\\\  ()                        " << "\t\t" << "                ()  //\\\\  ()                      " << endl;
     delay(50);
     system("color F9");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     cout << "              ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()             " << "\t\t" << "      ()`\"\"\"`   \\/   //   \\/   `\"\"\"\"`()    " << endl;
     delay(50);
     system("color F1");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;;
     cout << "                /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\                " << "\t\t" << "        /\'--\'/ \\\\// \\\\// \\\\// \\\'--\'\\    " << endl;
     delay(50);
     system("color F9");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;
     delay(50);
     system("color F1");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     cout << "                 //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\                 " << "\t\t" << "         //\"\"/\\\\\"\"//\\\"\"//\\\"\"//\\\"\"\\\\" << endl;
     delay(50);
     system("color F9");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     cout << "                  .--\\\\/--\\//--\\//--\\//--.                  " << "\t\t" << "          .--\\\\/--\\//--\\//--\\//--.             " << endl;
     delay(50);
     system("color F1");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     cout << "                     ////\\\\\\//\\\\///\\\\\\\\                     " << "\t\t" << "             ////\\\\\\//\\\\///\\\\\\\\            " << endl;
     delay(50);
     system("color F9");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     cout << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()          " << "\t\t" << "                 ()-= >>\\\\< <\\\\> >\\\\<< =-()           " << endl;
     delay(50);
     system("color F1");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     cout << "                    \\\\\\\\///\\\\//\\\\\\////                     " << "\t\t" << "             \\\\\\\\///\\\\//\\\\\\////            " << endl;
     delay(50);
     system("color F9");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     cout << "                 \'--/\\\\--//\\--//\\--/\\\\--\'                " << "\t\t" << "        \'--/\\\\--//\\--//\\--/\\\\--\'        " << endl;
     delay(50);
     system("color F1");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     cout << "                \\\\__\\\\/__\\//__\\//__\\\\/__//               " << "\t\t" << "       \\\\__\\\\/__\\//__\\//__\\\\/__//       " << endl;
     delay(50);
     system("color F9");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     cout << "                    \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./              " << "\t\t" << "      \\.--.\\ //\\\\ //\\\\ //\\\\ /.--./      " << endl;
     delay(50);
     system("color F1");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     cout << "            ()._____   /\\   \\\\   /\\   _____.()           " << "\t\t" << "   ()._____   /\\   \\\\   /\\   _____.()       " << endl;
     delay(50);
     system("color F9");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     cout << "                       ()  \\\\//  ()                      " << "\t\t" << "              ()  \\\\//  ()                    " << endl;
     delay(50);
     system("color F1");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     cout << "                          <<  >>                         " << "\t\t" << "                 <<  >>                         " << endl;
     delay(50);
     system("color F9");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     cout << "                           //\\\\                          " << "\t\t" << "                  //\\\\                        " << endl;
     delay(50);
     system("color F1");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     cout << "                            /\\                           " << "\t\t" << "                   /\\                          " << endl;
     delay(50);
     system("color F9");
     system("cls");
     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "                            ()                           " << "\t\t" << "                   ()                           " << endl;
     delay(50);
     system("color F1");
     system("cls");

     cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
     cout << "\t\t\t" << "  ______           _          ____  _____     ____  _____   _________        _" << endl;
     cout << "\t\t\t" << ".' ____ \\         / \\        |_   \\|_   _|   |_   \\|_   _| |  _   _  |      / \\" << endl;
     cout << "\t\t\t" << "| (___ \\_|       / _ \\         |   \\ | |       |   \\ | |   |_/ | | \\_|     / _ \\" << endl;
     cout << "\t\t\t" << " _.____`.       / ___ \\        | |\\ \\| |       | |\\ \\| |       | |        / ___ \\" << endl;
     cout << "\t\t\t" << "| \\____) | _  _/ /   \\ \\_  _  _| |_\\   |_  _  _| |_\\   |_  _  _| |_  _  _/ /   \\ \\_" << endl;
     cout << "\t\t\t" << " \\______.'(_)|____| |____|(_)|_____|\\____|(_)|_____|\\____|(_)|_____|(_)|____| |____|" << endl;

     delay(50);
     system("color F9");
     delay(50);
     system("color F1");
     delay(50);
     system("color F9");
     delay(50);
     system("color F1");
     delay(50);
     system("color F9");
     delay(50);
     system("color F1");
     delay(50);
     system("color F9");
     delay(50);
     system("color F1");
     delay(50);
     system("color F9");
     delay(50);
     system("color F1");
     delay(50);
     system("color F9");
     delay(50);
     system("color F1");
     delay(50);
     system("color F9");
     delay(50);
     system("color F1");
     delay(50);
     system("color F9");
     delay(50);
     system("color F1");
     delay(50);
     system("color F9");
     delay(50);
     system("color F1");
     delay(50);
     system("color F9");
     delay(50);
     system("color F1");
     delay(50);
     system("color F9");
     delay(50);
     system("color F1");
     delay(50);
     system("color F9");
     delay(50);
     system("color F1");
}
//main function
int main(){

     //setupConsole();
     system("color F4");
     //changeColor(12, 15);

     int *permission = new (nothrow) int(0);


     //cout<<getYearsSince(985323600);

     //handle login
     *permission = login();

     //vector<User> users;
     //vector<Child> children;

     User *users[MAXUSERS];
     Child *children[MAXCHILDREN];


     //children.reserve(100);

     int toyArray [NUMOFTOYS][2];
     int (*toys)[NUMOFTOYS][2] = &toyArray;


     int *numberOfUsers = new (nothrow) int(0);
     int *numberOfChildren = new (nothrow) int(0);


    loadFiles(users, numberOfUsers, children, numberOfChildren, toys);

    //cout<<(*toys)[3][0];



//    viewChild(children,numberOfChildren);

  //  cout<<children[2]->getNicenessRating();


/*
     permission level
     1: elf
     2: ms. claus
     3: mr. claus
     4: admin
*/
     system("cls");
     switch(*permission) {
          case 1:
               menuElf(users, numberOfUsers, children, numberOfChildren, toys);
               break;
          case 2:
               menuMrsClaus(users, numberOfUsers, children, numberOfChildren, toys);
               break;
          case 3:
               menuSanta(users, numberOfUsers, children, numberOfChildren, toys);
               break;
          case 4:
               menuAdmin(users, numberOfUsers, children, numberOfChildren, toys);
               break;
          default:
               errorHandler(1567892435);
               break;
     }





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
