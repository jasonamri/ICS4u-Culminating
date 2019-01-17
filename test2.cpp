//2018-12-13 - 2019-01-21
//Culminating Task - SANNTA
//Jason Amri & Jacob Van G


//****LIBRARIES****
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


//****CONSTANTS****
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





//****CLASSES****

//prototype for get year since function. this is the only function called by a class, so it must be declared above the classes
int getYearsSince(int *dateInUnixTime);

class User {
private:
     //name of elf
     string *name = new (nothrow) string("");
     //username of elf
     string *username = new (nothrow) string("");
     //date of hire in unix time
     int *hireDate = new (nothrow) int(0);
     //years since hire
     //calculatable value: int *yearsSinceHire = new (nothrow) int(0);
     //toy assigned (see lookup table)
     int *toyAssigned = new (nothrow) int(0);
     //number of toys made
     int *toysMade = new (nothrow) int(0);
     //percent progress (0-100)
     //calculatable value: int *progress = new (nothrow) int(0);

public:
     //init User
     User (string *_username, string *nameInput, int *hireDateInput, int *_toyAssigned, int *numberOfToysMade) {
          *username = *_username;

          *name = *nameInput;
          name->erase(std::remove(name->begin(), name->end(), '\n'), name->end());

          *hireDate = *hireDateInput;

          //calculatable value: *yearsSinceHire = getYearsSince(hireDate);

          //*username = *_username;

          *toyAssigned = *_toyAssigned;

          *toysMade = *numberOfToysMade;
     }
     int getToysMade () {
          return *toysMade;
     }
     void setToysMade (int *numberOfToysMade){
          *toysMade = *numberOfToysMade;
     }
     int getToyAssignedToElf (){
          return *toyAssigned;
     }
     string getName (){
          return *name;
     }
     string getUsername (){
          return *username;
     }
     void setToyAssignedToElf (int *_toyAssigned){
          *toyAssigned = *_toyAssigned;
     }


     ~User(){
          delete username;
          delete name;
          delete hireDate;
          //delete yearsSinceHire;
          delete toyAssigned;
          delete toysMade;
          //delete progress;
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
     //dont save calculatable value: int *age = new (nothrow) int(0);
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
          name->erase(std::remove(name->begin(), name->end(), '\n'), name->end());


          *birthday = *birthdayInput;
          //dont save calculatable value: *age = getYearsSince(birthday);
          *homeAddress = *homeAddressInput;
          homeAddress->erase(std::remove(homeAddress->begin(), homeAddress->end(), '\n'), homeAddress->end());
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
          return *name;
     }
     int getBirthdayUnix() {
          return *birthday;
     }
     string getBirthdayReadable() {
          time_t t = *birthday;
          struct tm *tm = localtime(&t);
          char date[20];
          strftime(date, sizeof(date), "%b %d %Y", tm);
          return (string)date;
     }
     int getAge() {
          return getYearsSince(birthday);
     }
     bool getGenderBool() {
          return *gender;
     }
     string getGenderReadable() {
          if (*gender == true) {
               return "Male";
          } else {
               return "Female";
          }
     }

     void setCookieRating(int *_cookieRating) {
          if (*_cookieRating > 15) {
               *_cookieRating = 15;
          } else if (*_cookieRating < 1) {
               *_cookieRating = 1;
          }

          *cookieRating = *_cookieRating;
     }
     void setNicenessRating(int *nicenessInput) {
          if (*nicenessInput > 100) {
               *nicenessInput = 100;
          } else if (*nicenessInput < 0) {
               *nicenessInput = 0;
          }

          *nicenessRating = *nicenessInput;
     }
     void setHomeAddress(string *_homeAddress) {
          *homeAddress = *_homeAddress;
     }
     void setNumberOfSiblings(int *_numberOfSiblings) {
          if (*_numberOfSiblings < 0) {
               *_numberOfSiblings = 0;
          }

          *numberOfSiblings = *_numberOfSiblings;
     }

     void setAssignedToy(int *_toyAssigned) {
          if (*_toyAssigned > 10) {
               *_toyAssigned = 10;
          } else if (*_toyAssigned < 0) {
               *_toyAssigned = 0;
          }

          *toyAssigned = *_toyAssigned;
     }

     void forceEnd() {
          *name = "zzz";
     }

     void show() {
          cout<<"\nName: "<<*name<<"\nBirthday"<<*birthday;
     }


     ~Child(){
          delete name;
          delete birthday;
          //delete age;
          delete gender;
          delete homeAddress;
          delete numberOfSiblings;
          delete cookieRating;
          delete nicenessRating;
          delete toyAssigned;
     }

};




//****UTILITY FUNCTIONS****

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

void delay(long unsigned int millis){
	//start timer
	clock_t start = clock();
	//check is time has elasped
	while ((start + ((float)(millis / 1000) * CLOCKS_PER_SEC)) > (unsigned)clock());
}

int getYearsSince(int *dateInUnixTime) {
     int secondsSinceEpoch = (int)time(0);
     return (secondsSinceEpoch - *dateInUnixTime)/(60*60*24*365.25);
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



     int i(0), j(0);
     int pos(0);

    string min;

    for (i = 0; i < *numberOfChildren - 1; i++)
    {
         cout<<"newloop"<<i<<"\n";
        min = children[i]->getName(); // the first element is Min value
        pos = i;


        for (j = i + 1; j < *numberOfChildren; j++) // finding smaller value that Min
        {

              cout<<"compare"<<j<<"\n";
             if (children[j]->getName() < min)
             {
                   cout<<"yes"<<j<<"\n";
                 min = children[j]->getName();
                 pos = j;
             }
        }
        //not used
        //Child temp = *children[i]; // swap selected element and Min value
        //*children[i] = *children[pos];
        //*children[pos] = temp;
        swap(children[i], children[pos]);
    }



/*     int i(0), j(0), temp(0);
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
   }*/
}


//todo sort users
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



/* NOTES
login.txt
#of users
(username
hash
permissionLevel) x # of users


jason:admin
jacob:password
santa:santa
mrsclaus:cookies
elf1:hohoho


permission level
1: elf
2: ms. claus
3: mr. claus
4: admin

*/


//****CORE FUNCTIONS****

//arguments: pointer to username inputted as string, pointer to password entered as string
//returns permission level on success, 0 on fail
int loginHandler(string *username, string *password) {

     ifstream *loginFile = new ifstream;
     loginFile->open("login.txt");

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

     //todo delete pointers


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

     string *username = new string;
     string *name = new string;
     int *hireDate = new int;
     int *toyAssigned = new int;
     int *numberOfToysMade = new int;


     //open user file
     if (fin.is_open()) {

          while (!fin.eof())
          {
               fin>> *username;
               getline(fin, *name, '$');
               fin>> *hireDate;
               fin>> *toyAssigned;
               fin>> *numberOfToysMade;
//cout<<"hi";
               users[*numberOfUsers] = new(nothrow) User(username, name, hireDate, toyAssigned, numberOfToysMade);
//cout<<"hey";
               *numberOfUsers = (*numberOfUsers + 1);

          }
          fin.close();
     }

     delete username;
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
               //fin.ignore(120,'\n');
               //fin.seekg(1, ios::cur);
               getline(fin, *nameChild, '$');
               //cout<<*nameChild<<nameChild->length()<<"\n";
               //_getch();
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




//Purpose: arrow key handler
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

     //cout<<*index;
     //_getch();
     system("cls");

     int *selection = new (nothrow) int(0);



     int * numberOfSiblings = new (nothrow) int;
     string * address = new (nothrow) string;
     int * cookieRating = new (nothrow) int;
     int * nicenessRating = new (nothrow) int;

     /*
     delete name;
     delete birthday;
     delete age;
     delete gender;
     delete homeAddress;
     delete numberOfSiblings;
     delete cookieRating;
     delete nicenessRating;
     delete toyAssigned;


     */

     //cout<<children[1]->getName();

     //todo: error trap selection
     cout<<"Selected Child Name: "<<children[*index]->getName()<<"\n";
     cout<<"Birthday: "<<children[*index]->getBirthdayReadable()<<"\n";
     cout<<"Age: "<<children[*index]->getAge()<<"\n";
     cout<<"Gender: "<<children[*index]->getGenderReadable()<<"\n";
     cout<<"Address: "<<children[*index]->getHomeAddress()<<"\n";
     cout<<"# of siblings: "<<children[*index]->getSiblingNumber()<<"\n";
     cout<<"Cookie Rating (1-15): \t\t"<<children[*index]->getCookieRating()<<"\n";
     cout<<"Niceness Rating (0-100): \t"<<children[*index]->getNicenessRating()<<"\n";
     cout<<"Assigned Toy: "<<toysMap.at(children[*index]->getAssignedToy())<<"\n\n";


     cout<<"1. Edit address\n";
     cout<<"2. Edit number of siblings\n";
     cout<<"3. Edit cookie rating\n";
     cout<<"4. Edit niceness rating\n";
     cout<<"5. Exit\n";
     cout<<"Make a selection -->";

     cin>>*selection;

     system("cls");
     switch(*selection) {
          case 1:

               cout<<"Enter new home address --> ";
               fflush(stdin);
               getline(cin, *address);
               children[*index]->setHomeAddress(address);

               cout<<"Successfully changed home address. Press any key to return.";
               _getch();
               break;
          case 2:

               cout<<"Enter new number of siblings --> ";
               fflush(stdin);
               cin>>*numberOfSiblings;

               while(*numberOfSiblings < 0) {
                    //todo: error trap
               }

               children[*index]->setNumberOfSiblings(numberOfSiblings);
               cout<<"Successfully changed number of siblings. Press any key to return.";
               _getch();
               break;
          case 3:

               cout<<"Enter new cookie rating --> ";
               fflush(stdin);
               cin>> *cookieRating;

               while (*cookieRating > 15 || *cookieRating < 1) {
                    //todo errortrap
               }

               children[*index]->setCookieRating(cookieRating);
               cout<<"Successfully changed cookie rating. Press any key to return.";
               _getch();
               break;
          case 4:

               cout<<"Enter new niceness rating --> ";
               fflush(stdin);
               cin>> *nicenessRating;

               while(*cookieRating > 100 || *cookieRating < 0) {
                    //todo errortrap
               }

               children[*index]->setNicenessRating(nicenessRating);
               cout<<"Successfully changed niceness rating. Press any key to return.";
               _getch();
               break;
     }


     system("cls");

     delete index;
     delete nicenessRating;
     delete cookieRating;
     delete numberOfSiblings;
     delete address;
}

void viewChild(Child *children[MAXCHILDREN], int *numberOfChildren){

     sortChildren(children, numberOfChildren);


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
               cout<<children[i]->getName()<<"\t\t\t\t\t\t"<<children[i]->getNicenessRating()<<"\n";
               if (*selection == i) {
                    changeColor(4, 15);
               }
          }

          if (*selection == *numberOfChildren) {
               changeColor(15, 4);
          }
          cout<<"Exit\n";
          if (*selection == *numberOfChildren) {
               changeColor(4, 15);
          }



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
                    if (*selection == *numberOfChildren) {
                         *input = 6;
                    } else {
                         editChild(children, selection);
                    }
                    break;
               case 1:
                    if (*selection>0) {*selection = *selection -1;}
                    break;
               case 2:
                    *nicenessRating = children[*selection]->getNicenessRating();
                    *nicenessRating = *nicenessRating - 1;
                    children[*selection]->setNicenessRating(nicenessRating);
                    break;
               case 3:
                    *nicenessRating = children[*selection]->getNicenessRating();
                    *nicenessRating = *nicenessRating + 1;
                    children[*selection]->setNicenessRating(nicenessRating);
                    break;
               case 4:
                    if (*selection<*numberOfChildren) {*selection = *selection +1;}
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

void assignGift(Child * children[MAXCHILDREN], int * numberOfChildren){
     int *input = new int(7);
     int *selection = new int (0);
     int *toyAssigned = new int;

     do {

          system("cls");

          cout<<"Enter to auto assign, up/down to select child, left/right to change toy, esc to exit\n\n";

          for (int i=0; i<*numberOfChildren; i++) {
               //todo: formating of names by length
               if (*selection == i) {
                    changeColor(15, 4);
               }
               cout<<children[i]->getName()<<"\t\t\t\t\t\t"<<toysMap.at(children[i]->getAssignedToy())<<"\n";
               if (*selection == i) {
                    changeColor(4, 15);
               }
          }

          if (*selection == *numberOfChildren) {
               changeColor(15, 4);
          }
          cout<<"Exit\n";
          if (*selection == *numberOfChildren) {
               changeColor(4, 15);
          }



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
                    if (*selection == *numberOfChildren) {
                         *input = 6;
                    } else {
                         *toyAssigned = rand() % 10 + 1;
                         children[*selection]->setAssignedToy(toyAssigned);
                         system("cls");
                         cout<<"Successfully auto assigned toy, press any key to continue.";
                         _getch();
                    }
                    break;
               case 1:
                    if (*selection>0) {*selection = *selection -1;}
                    break;
               case 2:
                    *toyAssigned = children[*selection]->getAssignedToy();
                    *toyAssigned = *toyAssigned - 1;
                    children[*selection]->setAssignedToy(toyAssigned);
                    break;
               case 3:
                    *toyAssigned = children[*selection]->getAssignedToy();
                    *toyAssigned = *toyAssigned + 1;
                    children[*selection]->setAssignedToy(toyAssigned);
                    break;
               case 4:
                    if (*selection<*numberOfChildren) {*selection = *selection +1;}
                    break;
          }



     } while (*input != 6);



     delete selection;
     delete input;
     delete toyAssigned;


     system("cls");
}

void assignAllGifts(Child * children[MAXCHILDREN], int * numberOfChildren){

     int * selection = new (nothrow) int(0);
     string * confirmation = new (nothrow) string;

     system("cls");


     cout<<"1. Auto assign gifts to all children\n";
     cout<<"2. Auto assign gifts to unsigned children\n";
     cout<<"3. Cancel\n";

     //todo error trapping selection

     cin>>*selection;


     if (*selection == 1) {
          do
          {
               system("cls");
               cout << "Are you sure you want to reassign all children (Y or N) --> ";
               fflush(stdin);
               getline(cin, *confirmation);

               for (int i = 0; i < confirmation->length(); i++) {
                    confirmation->at(i)=toupper(confirmation->at(i));
               }

               if (*confirmation != "Y" && *confirmation != "N")
               {

                    cout << "Error! Invalid input. ";
                    _getch();
                    system("cls");
               }

          } while (*confirmation != "Y" && *confirmation != "N");

          if (*confirmation == "Y") {

               for (int i=0; i<*numberOfChildren; i++) {
                    int * toyAssigned = new (nothrow) int (rand() % 10 + 1);
                    children[i]->setAssignedToy(toyAssigned);
                    delete toyAssigned;
               }
               system("cls");
               cout<<"Done assigning toys. Press any key to return.";
               _getch();
          }
     } else if (*selection == 2) {
          for (int i=0; i<*numberOfChildren; i++) {
               if (children[i]->getAssignedToy()==0) {
                    int * toyAssigned = new (nothrow) int (rand() % 10 + 1);
                    children[i]->setAssignedToy(toyAssigned);
                    delete toyAssigned;
               }
          }
          system("cls");
          cout<<"Done assigning toys. Press any key to return.";
          _getch();
     }


delete selection;
delete confirmation;


}

void purgeChildren(Child * children[MAXCHILDREN], int * numberOfChildren){

     string * confirmation = new (nothrow) string;
     int * numberOfRemovedChildren = new (nothrow) int(0);

     do
     {
          cout << "Are you sure you want to purge all children 18+ (Y or N) --> ";
          fflush(stdin);
          getline(cin, *confirmation);

          for (int i = 0; i < confirmation->length(); i++) {
               confirmation->at(i)=toupper(confirmation->at(i));
          }

          if (*confirmation != "Y" && *confirmation != "N")
          {

               cout << "Error! Invalid input. ";
               _getch();
               system("cls");
          }

     } while (*confirmation != "Y" && *confirmation != "N");

     if (*confirmation == "Y") {

          for (int i=0; i<*numberOfChildren; i++) {
               if (children[i]->getAge() >= 18) {
                    children[i]->forceEnd();
                    *numberOfRemovedChildren = *numberOfRemovedChildren +1;
               }
          }

          sortChildren(children, numberOfChildren);

          for (int i=*numberOfChildren-1; i>=(*numberOfChildren-*numberOfRemovedChildren); i--) {
               delete children[i];
          }

          *numberOfChildren = *numberOfChildren - *numberOfRemovedChildren;
     }

     delete confirmation;

     cout<<"Successfully purged children! Press any key to return.";
     _getch();

}

void workshopMenu(User *users[MAXUSERS], int *numberOfUsers, int (*toys)[NUMOFTOYS][2], string *username) {
     //todo: ascii art?


     int *userNumber = new (nothrow) int;
     for (int i = 0; i<*numberOfUsers; i++) {
          if (users[i]->getUsername() == *username) {
               *userNumber = i;
          }
     }
     int *toyAssigned = new (nothrow) int(users[*userNumber]->getToyAssignedToElf() -1);

     int *input = new (nothrow) int;
     int *toysMade = new (nothrow) int;

     do {

          system("cls");
          cout<<"Hi "<<users[*userNumber]->getName()<<"\n";
          cout<<"You have been assigned: "<< toysMap.at(*toyAssigned +1)<<"\n";
          cout<<"You have made: "<< users[*userNumber]->getToysMade()<<"\n";
          cout<<"Total made: "<< (*toys)[*toyAssigned][0]<<"\n";
          cout<<"Total needed: "<< (*toys)[*toyAssigned][1]<<"\n";
          cout<<"Percent progress: "<< (int)((float)((float)(*toys)[*toyAssigned][0]/(float)(*toys)[*toyAssigned][1])*100)<<"%\n\n";

          cout<<"Use arrow keys to increase number of toys made. Use enter or esc to exit.";

          *input = arrowKeys(true);

          switch (*input) {
               case 1:
                    if ((*toys)[*toyAssigned][0] < (*toys)[*toyAssigned][1] && users[*userNumber]->getToysMade() < (*toys)[*toyAssigned][1]) {
                         (*toys)[*toyAssigned][0]++;
                         *toysMade = users[*userNumber]->getToysMade()+1;
                         users[*userNumber]->setToysMade(toysMade);
                    }
                    break;
               case 4:
                    if ((*toys)[*toyAssigned][0] > 0 && users[*userNumber]->getToysMade() > 0) {
                         (*toys)[*toyAssigned][0]--;
                         *toysMade = users[*userNumber]->getToysMade()-1;
                         users[*userNumber]->setToysMade(toysMade);
                    }
                    break;
          }


     } while (*input != 0 && *input != 6);


     delete userNumber;
     delete toyAssigned;
     delete input;
     delete toysMade;

}

void workshopProgress(int (*toys)[NUMOFTOYS][2]){

     system("cls");

     for (int i =0; i <NUMOFTOYS; i++) {
          cout<< toysMap.at(i +1)<<": "<<(*toys)[i][0]<<"/"<<(*toys)[i][1]<<" or "<< (int)((float)((float)(*toys)[i][0]/(float)(*toys)[i][1])*100)<<"%\n";
     }

     cout<<"\nPress any key to return to menu.";
     _getch();

}

void changePassword(string *username){

//todo obscure passwords
     string *password = new (nothrow) string;
     string *passwordConfirm = new (nothrow) string;

     do {
          system("cls");
          cout<<"Enter new password -->";
          cin>>*password;
          cout<<"Confirm new password -->";
          cin>>*passwordConfirm;

          if (*password != *passwordConfirm) {
               cout<<"Error! Password do not match! Press any key to try again.";
               _getch();
          }

     } while (*password != *passwordConfirm);


     ifstream *loginFile = new ifstream;
     loginFile->open("login.txt");

     ofstream *outputFile = new ofstream;
     outputFile->open("loginTemp.txt");


     bool *usernameFound = new bool(false);

     string *usernameToTest = new string("");
     size_t *hashToTest = new size_t;
     int *permissionLevel = new int;

     //open login file
     if (loginFile->is_open()) {

          while (!loginFile->eof()) {

               if (*usernameToTest != "") {
                    *outputFile<<"\n";
               }


               *loginFile>>*usernameToTest;
               *outputFile<<*usernameToTest<<"\n";
               *loginFile>> *hashToTest;

               if (*username==*usernameToTest) {
                    *usernameFound=true;
                    *outputFile << generateHash(username, password) <<"\n";
               } else {
                    *outputFile << *hashToTest<<"\n";
               }

               *loginFile >> *permissionLevel;
               *outputFile << *permissionLevel;
          }


          loginFile->close();
          outputFile->close();

          remove("login.txt");
          rename("loginTemp.txt", "login.txt");



          if (*usernameFound != true) {
               //user doesn't exist
               cout<<"Failed to find user. Press any key to return.";
               _getch();
          } else {
               cout<<"Successfully updated password. Press any key to return.";
               _getch();
          }

     //can't open file
     } else {
          cout<<"Couldn't open file. Press any key to return.";
          _getch();
     }


     //todo delete pointers
}

void elfToy(User *users[MAXUSERS], int *numberOfUsers){


     int *selection = new int (0);
     int *input = new (nothrow) int(7);



     do {
          system("cls");

          cout<<"Select Elf, then press enter. (Press esc to go back)\n\n";

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

     if (*input == 0) {

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

          delete elfToyAssign;

     }

     delete selection;
     delete input;

}


//finished up to here


void addElf(User * users[MAXUSERS], int *numberOfUsers){




}
void fireElf(){

}
void resetElfPassword(){

}


void modeJanuary(){

}
void resetDefault(){

}


void menuElf(User * users[MAXUSERS], int *numberOfUsers, Child * children[MAXCHILDREN], int * numberOfChildren, int (*toys)[NUMOFTOYS][2], string *username){

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
          cout << "\t\t\t" << "\t\t\t\t4. Workshop Menu" << endl;
          cout << "\t\t\t" << "\t\t\t\t5. Change Password" << endl;
          cout << "\t\t\t" << "\t\t\t\t6. Exit" << endl;
          cout << "\t\t\t" << "\t\t\t\t" << ">";
          cin >> *selectionelf;
          if (*selectionelf < 1 || *selectionelf > 6)
          {
               cout << "Error! Your Selection Must be Within 1 & 6" << endl;
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
          workshopMenu(users, numberOfUsers, toys, username);
          break;
     case 5:
          changePassword(username);
          break;
     }

     delete selectionelf;
     delete error;

}
void menuSanta(User * users[MAXUSERS], int *numberOfUsers, Child * children[MAXCHILDREN], int * numberOfChildren, int (*toys)[NUMOFTOYS][2], string *username){

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
               cout << "\t\t\t" << "\t\t\t\t4. Assign Gifts" << endl;
               cout << "\t\t\t" << "\t\t\t\t5. Auto Assign Gifts To All" << endl;
               cout << "\t\t\t" << "\t\t\t\t6. Purge 18+ Children" << endl;
               cout << "\t\t\t" << "\t\t\t\t7. View Elves/Assign Toy to Elf" << endl;
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
               assignGift(children, numberOfChildren);
               break;
          case 5:
               assignAllGifts(children, numberOfChildren);
               break;
          case 6:
               purgeChildren(children, numberOfChildren);
               break;
          case 7:
               elfToy(users, numberOfUsers); //works
               break;
          case 8:
               workshopProgress(toys);
               break;
          case 9:
               changePassword(username);
               break;
          }

     }


     delete selectionsanta;
     delete error;

}
void menuMrsClaus(User * users[MAXUSERS], int *numberOfUsers, Child * children[MAXCHILDREN], int * numberOfChildren, int (*toys)[NUMOFTOYS][2], string *username){

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
          changePassword(username);
          break;
     }

     _getch();
     delete selectionmrsclaus;
     delete error;
}
void menuAdmin(User * users[MAXUSERS], int *numberOfUsers, Child * children[MAXCHILDREN], int * numberOfChildren, int (*toys)[NUMOFTOYS][2], string *username){
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
          menuElf(users, numberOfUsers, children, numberOfChildren, toys, username);
          break;
     case 2:
          menuSanta(users, numberOfUsers, children, numberOfChildren, toys, username);
          break;
     case 3:
          menuMrsClaus(users, numberOfUsers, children, numberOfChildren, toys, username);
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
int login(string *username){
     int *permission = new int;

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

     delete password;
     delete error;

     return *permission;
}

//welcom screen
void welcomeScreen(){
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

void exitScreen() {
     //todo
}


//****MAIN FUNCTION****
int main(){

     //setupConsole();
     system("color F4");

     srand((unsigned int)time(NULL));
     //changeColor(12, 15);

     int *permission = new (nothrow) int(0);
     string *username = new(nothrow) string;


     //handle login
     *permission = login(username);

     //vector<User> users;
     //vector<Child> children;

     User *users[MAXUSERS];
     Child *children[MAXCHILDREN];


     //children.reserve(100);

     int toyArray [NUMOFTOYS][2];
     int (*toys)[NUMOFTOYS][2] = &toyArray;


     int *numberOfUsers = new (nothrow) int(0);
     int *numberOfChildren = new (nothrow) int(0);

//todo error codes
    loadFiles(users, numberOfUsers, children, numberOfChildren, toys);

     //viewChild(children, numberOfChildren);
    //cout<<(*toys)[3][0];



    //viewChild(children,numberOfChildren);

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
               menuElf(users, numberOfUsers, children, numberOfChildren, toys, username);
               break;
          case 2:
               menuMrsClaus(users, numberOfUsers, children, numberOfChildren, toys, username);
               break;
          case 3:
               menuSanta(users, numberOfUsers, children, numberOfChildren, toys, username);
               break;
          case 4:
               menuAdmin(users, numberOfUsers, children, numberOfChildren, toys, username);
               break;
          default:
               errorHandler(1567892435);
               break;
     }



//todo exit screen

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
