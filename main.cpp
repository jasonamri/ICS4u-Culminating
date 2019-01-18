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
#include <thread>
using namespace std;


//****CONSTANTS****
//screen width and high
#define SCREENSIZEWIDTH 1080
#define SCREENSIZEHEIGHT 720

//when we have 0/0 toys made, is it 100% done or 0% done?
#define PROGRESSATZERO "100"

//number of toys available to be made
#define NUMOFTOYS 10

//maximum ammount of memory to allocate for the users and childre
#define MAXCHILDREN 100
#define MAXUSERS 50

//lookup table, matches toy number with toy name
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

//class for users a.k.a. elf
class User {
private:
     //name of elf
     string *name = new (nothrow) string("");
     //username of elf
     string *username = new (nothrow) string("");
     //date of hire in unix epoch time
     int *hireDate = new (nothrow) int(0);
     //toy assigned (see lookup table)
     int *toyAssigned = new (nothrow) int(0);
     //number of toys made
     int *toysMade = new (nothrow) int(0);

public:
     //purpose: initalize User
     //arguments: username, name, date of hire (since epoch), toy assigned to elf, number of toys the elf has made so far
     //returns: nothing!
     User (string *_username, string *nameInput, int *hireDateInput, int *_toyAssigned, int *numberOfToysMade) {
          *username = *_username;

          *name = *nameInput;
          //removes newline character, which may be artifact of text file
          name->erase(std::remove(name->begin(), name->end(), '\n'), name->end());

          *hireDate = *hireDateInput;

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
     int getHireDate (){
          return *hireDate;
     }
     void setToyAssignedToElf (int *_toyAssigned){
          *toyAssigned = *_toyAssigned;
     }
     //function to set name of the user to zzz so that it can be sorted to the end of the array, then deleted
     void forceEnd() {
          *name = "zzz";
     }
     //decontructor
     ~User(){
          delete username;
          delete name;
          delete hireDate;
          delete toyAssigned;
          delete toysMade;
     }
};

class Child {
private:
     //name of child
     string *name = new (nothrow) string;
     //birthday
     int *birthday = new (nothrow) int(0);
     //age
     //we dont save calculatable value: int *age = new (nothrow) int(0);
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
     //purpose: initalize User
     //arguments: name of child, birthday (since epoch), gender (true=male, false=female), home address, number of siblings, cookie rating (1-15), niceness rating (0-100), and the toy assigned to the child (0-10, 0 is Unassigned, see lookup table)
     //returns: nothing!
     Child (string *nameInput, int *birthdayInput, bool *genderInput, string *homeAddressInput, int *numberOfSiblingsInput, int *_cookieRating, int *_nicenessRating, int *_toyAssignedChild) {
          *gender = *genderInput;

          *name = *nameInput;
          //removes newline character, which may be artifact of text file
          name->erase(std::remove(name->begin(), name->end(), '\n'), name->end());

          *birthday = *birthdayInput;

          //dont save calculatable value: *age = getYearsSince(birthday);

          *homeAddress = *homeAddressInput;
          //removes newline character, which may be artifact of text file
          homeAddress->erase(std::remove(homeAddress->begin(), homeAddress->end(), '\n'), homeAddress->end());

          *numberOfSiblings = *numberOfSiblingsInput;

          *cookieRating = *_cookieRating;

          *nicenessRating = *_nicenessRating;

          *toyAssigned = *_toyAssignedChild;
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
     //convert birthday from unix time to human readable date
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
     //returns user readable gender as a string
     string getGenderReadable() {
          if (*gender == true) {
               return "Male";
          } else {
               return "Female";
          }
     }
     //error traps, then sets the cookie rating
     void setCookieRating(int *_cookieRating) {
          if (*_cookieRating > 15) {
               *_cookieRating = 15;
          } else if (*_cookieRating < 1) {
               *_cookieRating = 1;
          }

          *cookieRating = *_cookieRating;
     }
     //error traps, then sets the niceness rating
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
     //error traps, then sets the number of siblings
     void setNumberOfSiblings(int *_numberOfSiblings) {
          if (*_numberOfSiblings < 0) {
               *_numberOfSiblings = 0;
          }

          *numberOfSiblings = *_numberOfSiblings;
     }
     //error traps, then sets the assigned toy
     void setAssignedToy(int *_toyAssigned) {
          if (*_toyAssigned > 10) {
               *_toyAssigned = 10;
          } else if (*_toyAssigned < 0) {
               *_toyAssigned = 0;
          }

          *toyAssigned = *_toyAssigned;
     }
     //function to set name of the user to zzz so that it can be sorted to the end of the array, then deleted
     void forceEnd() {
          *name = "zzz";
     }
     //function for debugging
     void show() {
          cout<<"\nName: "<<*name<<"\nBirthday"<<*birthday;
     }

     //deconstructor
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

/*purpose:
arugments:
returns:
*/
size_t generateHash(string *username, string *password) {
     hash<string> hash_fn;
     return  hash_fn(*username+*password);
}

/*purpose:
arugments:
returns:
*/
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

/*purpose:
arugments:
returns:
*/
bool cursorDown() {
     return ((GetKeyState(VK_LBUTTON) & 0x100) != 0);
}

/*purpose:
arugments:
returns:
*/
bool clicked(int xMin, int yMin, int xMax, int yMax) {
     POINT * mouse = new POINT;
     *mouse = mouseInput();
     return (mouse->x>xMin && mouse->x<xMax && mouse->y>yMin && mouse->y<yMax && cursorDown());

}

/*purpose:
arugments:
returns:
*/
void delay(long unsigned int millis){
	//start timer
	clock_t start = clock();
	//check is time has elasped
	while ((start + ((float)(millis / 1000) * CLOCKS_PER_SEC)) > (unsigned)clock());
}

/*purpose:
arugments:
returns:
*/
int getYearsSince(int *dateInUnixTime) {
     int secondsSinceEpoch = (int)time(0);
     return (secondsSinceEpoch - *dateInUnixTime)/(60*60*24*365.25);
}

/*purpose:
arugments:
returns:
*/
void setScreenPosAndSize () {
     HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, HWND_TOP, -7, -30, 1080, 720, SWP_NOZORDER);
}

/*purpose:
arugments:
returns:
*/
void changeColor(int foreground, int background) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), foreground + background * 16);
}

/*purpose:
arugments:
returns:
*/
void setupConsole() {
     //setup console inorder to handle mouse clicks
     HANDLE input_handle;
     input_handle = GetStdHandle(STD_INPUT_HANDLE);
     SetConsoleMode(input_handle, ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_INSERT_MODE | ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);

     setScreenPosAndSize();

}

/*purpose:
arugments:
returns:
*/
void spawnHelpScreen() {
     system("start; help.exe");
}

/*purpose:
arugments:
returns:
*/
void helpWatcher(bool *helpBool) {
     while (*helpBool) {
          if (GetKeyState(VK_CONTROL)<0) {
               spawnHelpScreen();
               while (GetKeyState(VK_CONTROL) < 0 || !(GetConsoleWindow()==GetForegroundWindow())) {delay(10);}
          }
          delay(10);
     }
}

/*purpose:
arugments:
returns:  unix time on success, -1 on fail
*/
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


    *year = stoi(*yearString);
     *month = stoi(*monthString);
     *day = stoi(*dayString);

     //find the current year for error trapping
     time(&currentTime);
     int *currentYear = new int((localtime(&currentTime)->tm_year + 1900));


     if (*year<1970 || *year>*currentYear) {
          //returns error code, since date it invalid
          return -1;

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

/*purpose:
arugments:
returns:
*/
void updateToys(Child * children[MAXCHILDREN], int * numberOfChildren, User * users[MAXUSERS], int *numberOfUsers, int (*toys)[NUMOFTOYS][2]) {

     for (int i = 0; i < NUMOFTOYS; i++) {
         (*toys)[i][0]=0;
         (*toys)[i][1]=0;
     }



     for (int i = 0; i<*numberOfUsers; i++) {
          (*toys)[users[i]->getToyAssignedToElf()-1][0] += users[i]->getToysMade();
     }

     for (int i = 0; i<*numberOfChildren; i++) {
          (*toys)[children[i]->getAssignedToy()-1][1]++;
     }

}

/*purpose:
arugments:
returns:
*/
void sortChildren(Child * children[MAXCHILDREN], int * numberOfChildren) {

     int i(0), j(0);
     int pos(0);

    string min;

    for (i = 0; i < *numberOfChildren - 1; i++)
    {
      //   cout<<"newloop"<<i<<"\n";
        min = children[i]->getName(); // the first element is Min value
        pos = i;


        for (j = i + 1; j < *numberOfChildren; j++) // finding smaller value that Min
        {

          //    cout<<"compare"<<j<<"\n";
             if (children[j]->getName() < min)
             {
          //         cout<<"yes"<<j<<"\n";
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
}

/*purpose:
arugments:
returns:
*/
void sortUsers(User * users[MAXCHILDREN], int * numberOfUsers) {

      int i,j,tmp;
      for (i = 1; i < *numberOfUsers; i++) {
           j = i;
          // cout<<users[j - 1]->getName()<<" "<<
           while (j > 0 && users[j - 1]->getName() > users[j]->getName()) {
                swap(users[j-1], users[j]);
           }
      }

}

/*purpose:
arugments:
returns:
*/
bool userExists(string *username) {
     ifstream *loginFile = new ifstream;
     loginFile->open("login.txt");

     string *usernameToTest = new (nothrow) string;
     bool *usernameFound = new bool(false);
     //string *usernameToTest = new string;
     size_t *hashToTest = new size_t;
     int *permissionLevel = new int;


     //open login file
     if (loginFile->is_open()) {

          while (!loginFile->eof()) {

               *loginFile >> *usernameToTest;
               *loginFile >> *hashToTest;
               *loginFile >> *permissionLevel;

               if (*username==*usernameToTest) {
                    *usernameFound=true;
                    break;
               }
          }


          loginFile->close();


          if (*usernameFound == true) {
               //user exists
               return 1;

          } else {
               return 0;
          }

     }
}

//purpose: validates credentials against text file
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

               *loginFile>> *usernameToTest;
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

     delete loginFile;
     delete usernameFound;
     delete usernameToTest;
     delete hashToTest;
     delete permissionLevel;


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

               users[*numberOfUsers] = new(nothrow) User(username, name, hireDate, toyAssigned, numberOfToysMade);
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

               children[*numberOfChildren] = new (nothrow) Child(nameChild,birthday,genderBool,homeAddress,numberOfSiblings, cookieRating, nicenessRating, toyAssignedChild);

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

              fin >> *made;
              fin >> *needed;

              (*toys)[i][0]=*made;
              (*toys)[i][1]=*needed;
         }
         fin.close();
    }

    return 1;

}

/*purpose:
arugments:
returns:
*/
int saveFiles(User * users[MAXUSERS], int *numberOfUsers, Child * children[MAXCHILDREN], int * numberOfChildren, int (*toys)[NUMOFTOYS][2]) {

     sortUsers(users, numberOfUsers);
     sortChildren(children, numberOfChildren);

     //load users
     ofstream fin;
     fin.open("users.txt");

     //open user file
     if (fin.is_open()) {

          for (int i =0; i< *numberOfUsers; i++) {

               if (i != 0) { fin<<"\n";}
               fin << users[i]->getUsername()<<"\n";
               fin << users[i]->getName()<<"$\n";
               fin << users[i]->getHireDate()<<"\n";
               fin << users[i]->getToyAssignedToElf()<<"\n";
               fin << users[i]->getToysMade();
          }

          fin.close();
     }


     fin.open("children.txt");

    //open user file
    if (fin.is_open()) {
         for (int i = 0; i < *numberOfChildren; i++) {

              if (i != 0) { fin << "\n";}
              fin << children[i]->getName()<<"$\n";
              fin << children[i]->getBirthdayUnix()<<"\n";
              fin << children[i]->getGenderBool()<<"\n";
              fin << children[i]->getHomeAddress()<<"$\n";
              fin << children[i]->getSiblingNumber()<<"\n";
              fin << children[i]->getCookieRating()<<"\n";
              fin << children[i]->getNicenessRating()<<"\n";
              fin << children[i]->getAssignedToy();
         }

         fin.close();
    }


    //load toys
    fin.open("toys.txt");

   //open user file
   if (fin.is_open()) {
        for (int i = 0; i < NUMOFTOYS; i++) {

            if (i != 0) { fin << "\n";}
            fin << (*toys)[i][0]<<"\n";
            fin << (*toys)[i][1];

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


/* NOTES
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


/*purpose:
arugments:
returns:
*/
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

     do {
          system("cls");
          cout<<"Selected Child Name: "<<children[*index]->getName()<<"\n";
          //cout<<"hi";
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

          if (*selection > 5 || *selection < 1) {
               cout<<"Invalid selection. Must be between 1 and 5. Press any key to try again.";
               _getch();
          }
     } while (*selection > 5 || *selection < 1);



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
               do {
                    cout<<"Enter new number of siblings --> ";
                    fflush(stdin);
                    cin>>*numberOfSiblings;

                    if (*numberOfSiblings < 0) {
                         system("cls");
                         cout<<"Invalid input. Must be greater than zero.\n";
                    }
               } while(*numberOfSiblings < 0);

               children[*index]->setNumberOfSiblings(numberOfSiblings);
               cout<<"Successfully changed number of siblings. Press any key to return.";
               _getch();
               break;
          case 3:
               do {
                    cout<<"Enter new cookie rating --> ";
                    fflush(stdin);
                    cin>> *cookieRating;

                    if (*cookieRating > 15 || *cookieRating < 1) {
                         system("cls");
                         cout<<"Invalid input. Must be between 1 and 15.\n";
                    }
               } while (*cookieRating > 15 || *cookieRating < 1);



               children[*index]->setCookieRating(cookieRating);
               cout<<"Successfully changed cookie rating. Press any key to return.";
               _getch();
               break;
          case 4:
               do {
                    cout<<"Enter new niceness rating --> ";
                    fflush(stdin);
                    cin>> *nicenessRating;

                    if (*nicenessRating > 100 || *nicenessRating < 0) {
                         system("cls");
                         cout<<"Invalid input. Must be between 0 and 100.\n";
                    }
               } while(*nicenessRating > 100 || *nicenessRating < 0);


               children[*index]->setNicenessRating(nicenessRating);
               cout<<"Successfully changed niceness rating. Press any key to return.";
               _getch();
               break;
     }


     system("cls");

     delete selection;
     delete nicenessRating;
     delete cookieRating;
     delete numberOfSiblings;
     delete address;
}

/*purpose:
arugments:
returns:
*/
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

/*purpose:
arugments:
returns:
*/
void addChild(Child * children[MAXCHILDREN], int * numberOfChildren){
     //CHILD child;
     string *childName = new (nothrow) string;
     int *childBirthday = new (nothrow) int(0);
     string *childBirthdayInput = new (nothrow) string;
     int *childAge = new (nothrow) int(0);
     string *childGender = new (nothrow) string;
     string *childHomeAddress = new (nothrow) string;
     int *childNumberOfSiblings = new (nothrow) int(0);
     int *toyAssigned = new (nothrow) int(0);
     int *nicenessRating = new (nothrow) int(50);
     int *cookieRating = new (nothrow) int(1);
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
               system("cls");
               cout<<"Invalid Date! Must be in the YYYY/MM/DD format, example: 2001/03/23\n";
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


     children[*numberOfChildren] = new (nothrow) Child(childName,childBirthday,genderBool,childHomeAddress,childNumberOfSiblings, cookieRating, nicenessRating, toyAssigned);

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
     delete toyAssigned;
     delete error;
     delete genderBool;
     delete nicenessRating;
     delete cookieRating;


}

/*purpose:
arugments:
returns:
*/
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

/*purpose:
arugments:
returns:
*/
void assignAllGifts(Child * children[MAXCHILDREN], int * numberOfChildren){

     int * selection = new (nothrow) int(0);
     string * confirmation = new (nothrow) string;

     do {
          system("cls");

          cout<<"1. Auto assign gifts to all children\n";
          cout<<"2. Auto assign gifts to unsigned children\n";
          cout<<"3. Cancel\n";
          cout<<"--> ";

          cin>>*selection;

          if (*selection > 3 || *selection < 1) {
               cout<<"Invalid input! Must be between 0 and 3.\nPress any key to try again.";
               _getch();
          }

     } while (*selection > 3 || *selection < 1);



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

/*purpose:
arugments:
returns:
*/
void purgeChildren(Child * children[MAXCHILDREN], int * numberOfChildren){

     string * confirmation = new (nothrow) string;
     int * numberOfRemovedChildren = new (nothrow) int(0);

     do
     {
          system("cls");
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

/*purpose:
arugments:
returns:
*/
void workshopMenu(User *users[MAXUSERS], int *numberOfUsers, int (*toys)[NUMOFTOYS][2], string *username) {
     //todo: ascii art?



     int *userNumber = new (nothrow) int(-1);
     for (int i = 0; i<*numberOfUsers; i++) {
          if (users[i]->getUsername() == *username) {
               *userNumber = i;
          }
     }

     if (*userNumber == -1) {
          *userNumber = 0;
          system("cls");
          cout<<"Not logged in as Elf! Using "<<users[*userNumber]->getName()<<" to test.\nPress any key to continue.";
          _getch();
     }
     //cout<<"hi";
     int *toyAssigned = new (nothrow) int(users[*userNumber]->getToyAssignedToElf() -1);

     int *input = new (nothrow) int;
     int *toysMade = new (nothrow) int;

     do {

          system("cls");
          cout<<"Hi "<<users[*userNumber]->getName()<<"!\n";
          cout<<"You have been assigned: "<< toysMap.at(*toyAssigned +1)<<"\n";
          cout<<"You have made: \t\t"<< users[*userNumber]->getToysMade()<<"\n";
          cout<<"Total made: \t\t"<< (*toys)[*toyAssigned][0]<<"\n";
          cout<<"Total needed: \t\t"<< (*toys)[*toyAssigned][1]<<"\n";

          if ((*toys)[*toyAssigned][1]==0) {
               cout<<"Percent progress: \t"<< PROGRESSATZERO <<"%\n\n";
          } else {
               cout<<"Percent progress: \t"<< (int)((float)((float)(*toys)[*toyAssigned][0]/(float)(*toys)[*toyAssigned][1])*100)<<"%\n\n";
          }

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

/*purpose:
arugments:
returns:
*/
void workshopProgress(int (*toys)[NUMOFTOYS][2]){

     system("cls");

     for (int i =0; i <NUMOFTOYS; i++) {

          cout<< toysMap.at(i +1)<<": \t";

          if (i==5 || i== 7 || i==8) {
               cout<<"\t";
          }

          cout<<(*toys)[i][0]<<"/"<<(*toys)[i][1]<<"\tor ";


          if ((*toys)[i][1]==0) {
               cout<<PROGRESSATZERO<<"%\n";
          } else {
               cout<< (int)((float)((float)(*toys)[i][0]/(float)(*toys)[i][1])*100)<<"%\n";
          }
     }

     cout<<"\nPress any key to return to menu.";
     _getch();

}

/*purpose:
arugments:
returns:
*/
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


     delete loginFile;
     delete outputFile;
     delete usernameFound;
     delete usernameToTest;
     delete hashToTest;
     delete permissionLevel;
     delete password;
     delete passwordConfirm;
}

/*purpose:
arugments:
returns:
*/
void elfToy(User *users[MAXUSERS], int *numberOfUsers){


     sortUsers(users, numberOfUsers);

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

/*purpose:
arugments:
returns:
*/
void addElf(User * users[MAXUSERS], int *numberOfUsers){


     string *username = new (nothrow) string;
     string *name = new (nothrow) string;
     int *hireDate = new (nothrow) int;
     int *toyAssigned = new (nothrow) int(1);
     int *numberOfToysMade = new (nothrow) int(0);
     string *password = new (nothrow) string;
     string *passwordConfirm  = new (nothrow) string;
     string *hireDateInput = new (nothrow) string;
     bool *error = new (nothrow) bool;


     system("cls");

     cout << "Please Input the Name of the Elf...> ";
     fflush(stdin);
     getline(cin, *name);

     do {
          cout << "Please Input the Hire Date of the Elf (YYYY/MM/DD)...> ";
          getline(cin, *hireDateInput);

          *error = false;

          if (hireDateInput->length()!=10) {
               *error = true;

          } else {
               for (int i = 0; i<10; i++) {
                    if (i == 4 || i == 7) {
                         if (hireDateInput->at(i)!='/') {
                              *error = true;
                         }
                    } else {
                         if (!isdigit(hireDateInput->at(i))) {
                              *error = true;
                         }
                    }
               }
          }

          if (!(*error)) {
               //cout<<"hi";
               *hireDate = dateAsUnix(hireDateInput);

               if (*hireDate == -1) {
                    *error = true;
               }
          }

          if (*error == true) {
               system("cls");
               cout<<"Invalid Date! Must be in the YYYY/MM/DD format, example: 2001/03/23\n";
          }

     } while (*error == true);


     do {
          system("cls");
          cout << "Please Input the Username for the Elf...> ";
          cin>> *username;

          if (userExists(username)) {
               cout<<"Username already exists! Please try again!\nPress any key.";
               _getch();
          }

     } while (userExists(username));

     do {
          system("cls");
          cout<<"Enter the Elf's password -->";
          cin>>*password;
          cout<<"Confirm the Elf's password -->";
          cin>>*passwordConfirm;

          if (*password != *passwordConfirm) {
               cout<<"Error! Password do not match! Press any key to try again.";
               _getch();
          }

     } while (*password != *passwordConfirm);

//string *_username, string *nameInput, int *hireDateInput, int *_toyAssigned, int *numberOfToysMade)


     users[*numberOfUsers] = new (nothrow) User(username,name,hireDate,toyAssigned,numberOfToysMade);

     *numberOfUsers = (*numberOfUsers + 1);

     ofstream loginFile;
     loginFile.open("login.txt", ios::app);

     loginFile<<"\n"<<*username<<"\n";
     loginFile<<generateHash(username, password)<<"\n";
     loginFile<<"1";


     delete username;
     delete name;
     delete hireDate;
     delete toyAssigned;
     delete numberOfToysMade;
     delete password;
     delete passwordConfirm;
     delete hireDateInput;
     delete error;

     cout<<"Successfully added! Press any key to return to menu.";
     _getch();
     system("cls");


}

/*purpose:
arugments:
returns:
*/
void fireElf(User * users[MAXUSERS], int *numberOfUsers){

     string * confirmation = new (nothrow) string;
     //int * numberOfRemovedUsers = new (nothrow) int(0);

     int *selection = new int (0);
     int *input = new (nothrow) int(7);



     do {
          system("cls");

          cout<<"Select Elf to terminate, then press enter. (Press esc to go back)\n\n";

          for (int i=0; i<*numberOfUsers; i++) {
               if (*selection == i) {
                    changeColor(15, 4);
               }
               cout<<users[i]->getName()<<"\n";

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

          do
          {
               system("cls");
               cout << "Are you sure you want to terminate "<<users[*selection]->getName()<<" (Y or N) --> ";
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

               string * username = new (nothrow) string;
               *username = users[*selection]->getUsername();

               //remove creds from login file
               ifstream *loginFile = new ifstream;
               loginFile->open("login.txt");

               ofstream *outputFile = new ofstream;
               outputFile->open("loginTemp.txt");

               string *usernameToTest = new string("");
               size_t *hashToTest = new size_t;
               int *permissionLevel = new int;

               while (!loginFile->eof()) {

                    if (*usernameToTest != "" && *usernameToTest != *username) {
                         *outputFile<<"\n";
                    }

                    *loginFile>>*usernameToTest;

                    if (*username!=*usernameToTest) {
                         *outputFile<<*usernameToTest<<"\n";
                         *loginFile>> *hashToTest;
                         *outputFile << *hashToTest<<"\n";
                         *loginFile >> *permissionLevel;
                         *outputFile << *permissionLevel;
                    } else {
                         //*outputFile<<*usernameToTest<<"\n";
                         *loginFile>> *hashToTest;
                         //*outputFile << *hashToTest<<"\n";
                         *loginFile >> *permissionLevel;
                         //*outputFile << *permissionLevel;
                    }
               }


               loginFile->close();
               outputFile->close();

               remove("login.txt");
               rename("loginTemp.txt", "login.txt");


               //force the user to be sorted to the end of the array
               users[*selection]->forceEnd();
               //sort the user to the end of the array
               sortUsers(users, numberOfUsers);
               //delete the user
               delete users[*numberOfUsers];
               //decrease the number of users
               *numberOfUsers = *numberOfUsers - 1;


               cout<<"Successfully removed elf! Press any key to return.";
               _getch();



          }

          delete confirmation;



     }


     delete selection;
     delete input;




}

/*purpose:
arugments:
returns:
*/
void resetElfPassword(User * users[MAXUSERS], int *numberOfUsers){

     int *selection = new int (0);
     int *input = new (nothrow) int(7);



     do {
          system("cls");

          cout<<"Select Elf to reset password, then press enter. (Press esc to go back)\n\n";

          for (int i=0; i<*numberOfUsers; i++) {
               if (*selection == i) {
                    changeColor(15, 4);
               }
               cout<<users[i]->getName()<<"\n";

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
          string * username = new (nothrow) string;
          *username = users[*selection]->getUsername();


          changePassword(username);

     }


     delete selection;
     delete input;

}

/*purpose:
arugments:
returns:
*/
void resetRatings(Child * children[MAXCHILDREN], int * numberOfChildren){

     string * confirmation = new (nothrow) string;
     int * nicenessRating = new (nothrow) int(50);
     int * cookieRating = new (nothrow) int(1);

     //todo: reset toy assigned as well

     do
     {
          system("cls");
          cout << "Are you sure you want to reset cookie and niceness ratings to zero? (Y or N) --> ";
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
               children[i]->setNicenessRating(nicenessRating);
               children[i]->setCookieRating(cookieRating);
          }
     }

     delete nicenessRating;
     delete cookieRating;
     delete confirmation;

}





//****MENU FUNCTIONS****

/*purpose:
arugments:
returns:
*/
void menuElf(User * users[MAXUSERS], int *numberOfUsers, Child * children[MAXCHILDREN], int * numberOfChildren, int (*toys)[NUMOFTOYS][2], string *username){

     int *selectionelf = new (nothrow) int(0);
     bool *error = new (nothrow) bool;

     while (*selectionelf != 7) {

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
               cout << "\t\t\t" << "\t\t\t\t6. Help" << endl;
               cout << "\t\t\t" << "\t\t\t\t7. Exit" << endl;
               cout << "\t\t\t" << "\t\t\t\t" << ">";
               cin >> *selectionelf;
               if (*selectionelf < 1 || *selectionelf > 7)
               {
                    cout << "Error! Your Selection Must be Within 1 & 7" << endl;
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
               updateToys(children, numberOfChildren, users, numberOfUsers, toys);
               workshopMenu(users, numberOfUsers, toys, username);
               break;
          case 5:
               changePassword(username);
               break;
          case 6:
               spawnHelpScreen();
               break;
          }

     }

     delete selectionelf;
     delete error;

}

/*purpose:
arugments:
returns:
*/
void menuSanta(User * users[MAXUSERS], int *numberOfUsers, Child * children[MAXCHILDREN], int * numberOfChildren, int (*toys)[NUMOFTOYS][2], string *username){

     int *selectionsanta = new (nothrow) int(0);
     bool *error = new (nothrow) bool;

     while (*selectionsanta != 11) {

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
               cout << "\t\t\t" << "\t\t\t\t10. Help" << endl;
               cout << "\t\t\t" << "\t\t\t\t11. Exit" << endl;
               cout << "\t\t\t" << "\t\t\t\t" << ">";
               cin >> *selectionsanta;
               if (*selectionsanta < 1 || *selectionsanta > 11)
               {
                    cout << "Error! Your Selection Must be Within 1 & 11" << endl;
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
               updateToys(children, numberOfChildren, users, numberOfUsers, toys);
               workshopProgress(toys);
               break;
          case 9:
               changePassword(username);
               break;
          case 10:
               spawnHelpScreen();
               break;
          }

     }


     delete selectionsanta;
     delete error;

}

/*purpose:
arugments:
returns:
*/
void menuMrsClaus(User * users[MAXUSERS], int *numberOfUsers, Child * children[MAXCHILDREN], int * numberOfChildren, int (*toys)[NUMOFTOYS][2], string *username){

     int *selectionmrsclaus = new (nothrow) int(0);
     bool *error = new (nothrow) bool;

     while (*selectionmrsclaus != 6) {

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
               cout << "\t\t\t" << "\t\t\t\t5. Help" << endl;
               cout << "\t\t\t" << "\t\t\t\t6. Exit" << endl;
               cout << "\t\t\t" << "\t\t\t\t" << ">";
               cin >> *selectionmrsclaus;
               if (*selectionmrsclaus < 1 || *selectionmrsclaus > 6)
               {
                    cout << "Error! Your Selection Must be Within 1 & 6" << endl;
                    *error = true; //Error Code 46 means Error = true
                    _getch();
                    system("cls");
               }
          } while(*error == true);
          switch(*selectionmrsclaus)
          {
          case 1:
               addElf(users, numberOfUsers);
               break;
          case 2:
               fireElf(users, numberOfUsers);
               break;
          case 3:
               resetElfPassword(users, numberOfUsers);
               break;
          case 4:
               changePassword(username);
               break;
          case 5:
               spawnHelpScreen();
               break;
          }

     }

     delete selectionmrsclaus;
     delete error;
}

/*purpose:
arugments:
returns:
*/
void menuAdmin(User * users[MAXUSERS], int *numberOfUsers, Child * children[MAXCHILDREN], int * numberOfChildren, int (*toys)[NUMOFTOYS][2], string *username){
     //reset to default
     //january mode
     int *selectionadmin = new (nothrow) int(0);
     bool *error = new (nothrow) bool;

     while (*selectionadmin != 6) {

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
               cout << "\t\t\t" << "\t\t\t\t4. Reset child ratings" << endl;
               cout << "\t\t\t" << "\t\t\t\t5. Help" << endl;
               cout << "\t\t\t" << "\t\t\t\t6. Exit" << endl;
               cout << "\t\t\t" << "\t\t\t\t" << ">";
               cin >> *selectionadmin;
               if (*selectionadmin < 1 || *selectionadmin > 6)
               {
                    cout << "Error! Your Selection Must be Within 1 & 6" << endl;
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
               resetRatings(children, numberOfChildren);
               break;
          case 5:
               spawnHelpScreen();
               break;
          }

     }


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
          //reset password

          //****INCASE OF LOCKOUT, UNCOMMENT TO RESET PASSWORDS
          //changePassword(username);

          *permission = loginHandler(username, password);

          if(*permission == 0) {
               cout << "Error! The Password Entered is Incorect. Please Check Your Password or Contact your Administrator";
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
     system("cls");

     welcomeScreen();
     cout<<"\n\n\n\n\n\t\t\t\t\t\t\tPress any key to exit";
}

//****MAIN FUNCTION****
int main(){


     //setupConsole();
     system("color F4");
     setScreenPosAndSize();

     srand((unsigned int)time(NULL));

     bool * helpBool = new (nothrow) bool(true);
     thread helpWatcherThread(helpWatcher, helpBool);


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


     if (loadFiles(users, numberOfUsers, children, numberOfChildren, toys) == 1) {

          /*permission level
               1: elf
               2: ms. claus
               3: mr. claus
               4: admin*/

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
          }

          saveFiles(users, numberOfUsers, children, numberOfChildren, toys);

          exitScreen();
          _getch();

     } else {
          cout<<"Error opening files, please make sure all files are in the same directory as the executable.\nPress any key to exit.";
          _getch();
     }


     //stop the help screen watcher thread
     *helpBool = false;
     helpWatcherThread.join();

     //delete main function and global pointers
     delete[] users;
     delete[] children;
     delete toys;
     delete numberOfUsers;
     delete numberOfChildren;
     delete helpBool;
     delete permission;
     delete username;


     return EXIT_SUCCESS;
}


//CODE SNIPPETS

/*
void addElf(User * users[MAXUSERS]){
     fstream userLogin;
     userLogin.open("login.txt", ios::app);
     string *elfName = new (nothrow) string;
     string *elfUsername = new (nothrow) string;
     string *elfHireDate = new (nothrow) string;
     int *elfYearsSinceHire = new (nothrow) int(0);
     int *elfProgress = new (nothrow) int(0);
     bool *error = new (nothrow) bool;
     string *elfPassword = new (nothrow) string;
     string *usernameToTest = new (nothrow) string;
     size_t *hashToTest = new (nothrow) size_t;
     int *permissionLevel = new (nothrow) int;
     char *letter = new (nothrow) char;
     bool *usernameFound = new (nothrow) bool(false);

     cout << "Please Input the Name of the Elf...> ";
     getline(cin, *elfName);
     do {
          cout << "Please Input the Hire Date of the Elf(YYYY/MM/DD)...> ";
          getline(cin, *elfHireDate);

          *error = false;

          if (elfHireDate->length()!=10) {
               *error = true;
          }
             else {
               for (int i = 0; i<10; i++) {
                    if (i==4 || i== 7) {
                         if (elfHireDate->at(i)!='/') {
                              *error = true;
                         }
                    } else {
                         if (!isdigit(elfHireDate->at(i))) {
                              *error = true;
                         }
                    }
               }
          }


          *elfYearsSinceHire = dateAsUnix(elfHireDate);

          if (*elfYearsSinceHire == -1) {
               *error = true;
          }

          if (*error == true) {
               //todo: error message
               system("cls");
               cout<<"Invalid Date Format!";
          }
     } while (*error == true);

     do {
          *error = false;
          cout << "Please Input the Elfs Username...> ";
          getline(cin, *elfUsername);

          if (userLogin.is_open()) {
               while (!userLogin.eof()){
                    userLogin >> *usernameToTest;
                    userLogin >> *hashToTest;
                    userLogin >> *permissionLevel;
                    if (*elfUsername==*usernameToTest) {
                         *usernameFound=true;
                         break;
                    }
               }
          }
          userLogin.close();

          if (*usernameFound = true) {
               *error = true;
               system("cls");
               cout << "Username not Available Please Try Again\n";
          }

     } while (*error = true);

     cout << "Please Input the Elfs Password...> ";


     while ((*letter=_getch()) != '\n')
     {
         elfPassword->push_back(*letter);
         _putch('*');
         _getch();
     }

     userLogin << elfUsername << endl;
     userLogin << generateHash(elfUsername, elfPassword) << endl;
     userLogin << "1" << endl;

     delete elfName;
     delete elfUsername;
     delete elfHireDate;
     delete elfYearsSinceHire;
     delete elfProgress;
     delete error;
     delete elfPassword;
     delete usernameToTest;
     delete hashToTest;
     delete permissionLevel;
     delete letter;
     delete usernameFound;

}*/

/*
void errorHandler(int errorCode) {
     cout << "Error Code " << errorCode << "Please Contact an Administrator to Address this Issue."<< endl;
     _getch();
     system("cls");
}*/


//animations2();

//while (true)
//cout<<clicked(100, 150, 200, 250)<<"\n"<<mouseInput().x<<" "<<mouseInput().y<<"\n";

/*
bool compareHash(size_t *hash, string *password, string *username) {
    return generateHash(password, username) == *hash;
}*/


//viewChild(children, numberOfChildren);
//cout<<(*toys)[3][0];

//viewChild(children,numberOfChildren);

//  cout<<children[2]->getNicenessRating();

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

               system("cls");

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

//string /***/username= /*new (nothrow) string (*/"Santa"/*)*/;
//string /***/password= /*new (nothrow) string (*/"hi"/*)*/;

/*   string *username = new string("jason");
string *password = new string("fu");
string *username2 = new string("jason");
string *password2 = new string("fu");*/

//cout<<generateHash(username, password);

//changeColor(5, 6);


//setup console inorder to handle mouse clicks
/*HANDLE input_handle;
input_handle = GetStdHandle(STD_INPUT_HANDLE);
SetConsoleMode(input_handle, ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_INSERT_MODE | ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);*/

//cout<<dateAsUnix("2001/03/23");

//welcome();

//int *permission = new int;
//*permission = login();


//size_t *hash = new size_t(generateHash(username, password));
//cout<<compareHash(hash, username2, password2);

//animations2();

//while (true)
//cout<<clicked(100, 150, 200, 250)<<"\n"<<mouseInput().x<<" "<<mouseInput().y<<"\n";

//setScreenPosAndSize();

//cout<<getYearsSince(985323600);

/*
login.txt
#of users
(username
hash) x # of users


*/

/*int login() {
     string *username = new string;
     string *password = new string;

     cout<<"Enter username: ";
     cin>>*username;
     cout<<"Enter password: ";
     cin>>*password;

     ifstream *loginFile= new ifstream;
     loginFile->open("login.txt");

     int *numberOfUsers = new int;

     bool *usernameFound = new bool(false);

     string *usernameToTest = new string;
     size_t *hashToTest = new size_t;
     int *permissionLevel = new int;

     if (loginFile.isopen()) {
          myfile>>*numberOfUsers;

          for (int i = 0; i<*numberOfUsers; i++) {

               myfile>>*usernameToTest;
               myfile >> *hashToTest
               myfile>>*permissionLevel
               if (*username==*usernameToTest) {
                    usernameFound=true;
                    break;
               }
          }


          myfile->close();

          if (generateHash(username, password)==*hashToTest) {
               return *permissionLevel;
          }


     } else {
          return -1;
     }


}*/

/*void password (){

  cout << "same hashes:\n" << boolalpha;
  cout << "nts1 and nts2: " << (ptr_hash(nts1)==ptr_hash(nts2)) << '\n';
  cout << "str1 and str2: " << (==str_hash(str2)) << '\n';
}*/

/*
void welcome(){
     double start(0);
     system("color F9");



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

     start = clock();
	while ((clock() - start) < 0.1 * CLOCKS_PER_SEC);
     system("color F1");
     system("cls");
     cout << endl;
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
     start = clock();
	while ((clock() - start) < 0.2 * CLOCKS_PER_SEC);
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
     start = clock();
	while ((clock() - start) < 0.3 * CLOCKS_PER_SEC);
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
     start = clock();
	while ((clock() - start) < 0.4 * CLOCKS_PER_SEC);
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
     start = clock();
	while ((clock() - start) < 0.5 * CLOCKS_PER_SEC);
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
     start = clock();
	while ((clock() - start) < 0.6 * CLOCKS_PER_SEC);
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
     start = clock();
	while ((clock() - start) < 0.7 * CLOCKS_PER_SEC);
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
     start = clock();
	while ((clock() - start) < 0.8 * CLOCKS_PER_SEC);
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
     start = clock();
	while ((clock() - start) < 0.9 * CLOCKS_PER_SEC);
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
     start = clock();
	while ((clock() - start) < 1.0 * CLOCKS_PER_SEC);
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
     start = clock();
	while ((clock() - start) < 1.1 * CLOCKS_PER_SEC);
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
     start = clock();
	while ((clock() - start) < 1.2 * CLOCKS_PER_SEC);
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
     start = clock();
     while ((clock() - start) < 1.3 * CLOCKS_PER_SEC);
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
     start = clock();
     while ((clock() - start) < 1.4 * CLOCKS_PER_SEC);
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
     start = clock();
     while ((clock() - start) < 1.5 * CLOCKS_PER_SEC);
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
     start = clock();
     while ((clock() - start) < 1.6 * CLOCKS_PER_SEC);
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
     start = clock();
     while ((clock() - start) < 1.7 * CLOCKS_PER_SEC);
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
     start = clock();
     while ((clock() - start) < 1.8 * CLOCKS_PER_SEC);
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
     start = clock();
     while ((clock() - start) < 1.9 * CLOCKS_PER_SEC);
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
     start = clock();
     while ((clock() - start) < 2.0 * CLOCKS_PER_SEC);
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
     start = clock();
     while ((clock() - start) < 2.1 * CLOCKS_PER_SEC);
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
     start = clock();
     while ((clock() - start) < 2.2 * CLOCKS_PER_SEC);
     system("color F1");
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
     start = clock();
     while ((clock() - start) < 2.3 * CLOCKS_PER_SEC);
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
     start = clock();
     while ((clock() - start) < 2.4 * CLOCKS_PER_SEC);
     system("color F1");
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
     start = clock();
     while ((clock() - start) < 2.5 * CLOCKS_PER_SEC);
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
     start = clock();
     while ((clock() - start) < 2.6 * CLOCKS_PER_SEC);
     system("color F1");
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
     start = clock();
     while ((clock() - start) < 2.7 * CLOCKS_PER_SEC);
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
     start = clock();
     while ((clock() - start) < 2.8 * CLOCKS_PER_SEC);
     system("color F1");
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
     start = clock();
     while ((clock() - start) < 2.9 * CLOCKS_PER_SEC);
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

}

*/
