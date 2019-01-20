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
#include <chrono> //helps with time
#include <windows.h> //allows built in windows functions and data types
#include <windef.h>
#include <direct.h>
#include <iomanip>
#include <map> //allows for lookup table
#include <thread> //allows for multithreading
using namespace std;


//****CONSTANTS****
//screen width and high
#define SCREENSIZEWIDTH 1080
#define SCREENSIZEHEIGHT 720

//when we have 0/0 toys made, is it 100% done or 0% done?
#define PROGRESSATZERO "100"

//number of toys available to be made
#define NUMOFTOYS 13

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
    { 10, "Pyjamas" },
    { 11, "1 piece of coal" },
    { 12, "2 pieces of coal" },
    { 13, "3 pieces of coal" }
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
         //save input into private variables

        *username = *_username;

        *name = *nameInput;
        //removes newline character, which may be artifact of text file
        name->erase(std::remove(name->begin(), name->end(), '\n'), name->end());

        *hireDate = *hireDateInput;

        *toyAssigned = *_toyAssigned;

        *toysMade = *numberOfToysMade;
    }

    //functions to return private variable values
    int getToysMade () {
        return *toysMade;
    }
    int getToyAssignedToElf () {
        return *toyAssigned;
    }
    string getName () {
        return *name;
    }
    string getUsername () {
        return *username;
    }
    int getHireDate () {
        return *hireDate;
    }
    int getYearsSinceHire () {
        return getYearsSince(hireDate);
    }
    string getHireDateReadable() {
        time_t t = *hireDate;
        struct tm *tm = localtime(&t);
        char date[20];
        strftime(date, sizeof(date), "%b %d %Y", tm);
        return (string)date;
    }

    //functions to update private variable values
    void setToysMade (int *numberOfToysMade) {
        *toysMade = *numberOfToysMade;
    }
    void setToyAssignedToElf (int *_toyAssigned) {
        *toyAssigned = *_toyAssigned;
    }

    //function to set name of the user to zzz so that it can be sorted to the end of the array, then deleted
    void forceEnd() {
        *name = "zzz";
    }

    //decontructor
    ~User() {
        //free memory
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
         //save input into private variables

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

    //functions to return private variable values
    int getAssignedToy() {
        return *toyAssigned;
    }
    string getHomeAddress() {
        return *homeAddress;
    }
    int getSiblingNumber() {
        return *numberOfSiblings;
    }
    int getCookieRating() {
        return *cookieRating;
    }
    int getNicenessRating() {
        return *nicenessRating;
    }
    string getName() {
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

    //functions to update private variable values
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
        if (*_toyAssigned > NUMOFTOYS) {
            *_toyAssigned = NUMOFTOYS;
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
    ~Child() {
        //free memory
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

/*purpose: generate hash from password with username as salt
arugments: pointer to a username string and a password string
returns:
*/
size_t generateHash(string *username, string *password) {
    hash<string> hash_fn;
    return hash_fn(*username+*password);
}

/*purpose: gets the position of the cursor
arugments: none
returns: point variable with x and y coord of the mouse cursor
*/
POINT mouseInput () {
    //intialize and get the cursor position
    POINT coord;
    GetCursorPos(&coord);

    //define return variable
    POINT output;

    //limit coordinates to screen size
    if (coord.x > SCREENSIZEWIDTH || coord.y > SCREENSIZEHEIGHT|| coord.y<0||coord.x<0) {
        output.x=-1;
        output.y=-1;
    } else {
        output=coord;
    }

    //return point variable with x and y coord of the mouse cursor
    return output;
}

/*purpose: checks if the mouse is clicking
arugments: none!
returns: boolean, true if first mouse button is down, false otherwise
*/
bool cursorDown() {
    //use windows function GetKeyState to check left mouse button
    return ((GetKeyState(VK_LBUTTON) & 0x100) != 0);
}

/*purpose: checks if user is clicking within a certain box
arugments: x and y top left corner and bottom right corner of a box in which the user will click
returns: boolean, true if user is clicking in that box, false otherwise
*/
bool clicked(int xMin, int yMin, int xMax, int yMax) {
    //get the current position of the mouse
    POINT * mouse = new POINT;
    *mouse = mouseInput();

    //check if the mouse is within the box and clicked, return true if it is
    return (mouse->x>xMin && mouse->x<xMax && mouse->y>yMin && mouse->y<yMax && cursorDown());

}

/*purpose: freeze the program a certain amount of time
arugments: time in milliseconds
returns: nothing!
*/
void delay(long unsigned int millis) {
    //start timer
    clock_t start = clock();
    //check if time has elasped, wait until it has
    while ((start + ((float)(millis / 1000) * CLOCKS_PER_SEC)) > (unsigned)clock());
}

/*purpose: obscures the password and displays it's prompt
arugments: the prompt to display and a boolean indicating whether to show the asterisks
returns: the password entered
*/
string getpass(string prompt, bool show_asterisk) {
    //shortform for character codes
     const char BACKSPACE=8;
     const char RETURN=13;

     //pointer to inputted password
     string *password = new (nothrow) string;
     //variable to track each character
     unsigned char ch=0;

     //output the prompt
     cout << prompt;

     //as long as the user doesn't hit enter
     while((ch=getch())!=RETURN)
     {
         //handle backspaces by removing asterisks
          if(ch==BACKSPACE)
          {
              //backspace the asterisks if the password has been typed
               if(password->length()!=0) {
                    if(show_asterisk)
                    cout <<"\b \b";
                    password->resize(password->length()-1);
               }
          }
          else if(ch==0 || ch==224) // handle escape sequences
          {
               getch(); // ignore non printable chars
               continue;
          }
          else
          {
              //add the character to the password string, then print an asterisk
               *password+=ch;
               if(show_asterisk)
               cout <<'*';
          }
     }
     //print enter once the user presses enter
     cout <<endl;

     //return string with the password
     return *password;
}

/*purpose: calculate the number of years since a date
arugments: date in seconds since unix epoch
returns: returns an integer number of years
*/
int getYearsSince(int *dateInUnixTime) {
    //get the current time
    int secondsSinceEpoch = (int)time(0);

    //find the difference between the current time and the provided, divide by the number of seconds in a year, return value
    return (secondsSinceEpoch - *dateInUnixTime)/(60*60*24*365.25);
}

/*purpose: adjust window size
arugments: none!
returns: nothing!
*/
void setScreenPosAndSize () {
    //get handle for the current window
    HWND consoleWindow = GetConsoleWindow();
    //use handle to change the window's position and size
    SetWindowPos(consoleWindow, HWND_TOP, -7, -30, SCREENSIZEWIDTH, SCREENSIZEHEIGHT, SWP_NOZORDER);
}

/*purpose: change the color of the screen
arugments: foreground and background colours from 1 to 15 (hex)
returns: nothing!
*/
void changeColor(int foreground, int background) {
    //uses windows functions to change the consoles text to a new colour
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), foreground + background * 16);
}

/*purpose: setups console for mouse input by disabling some settings
arugments: nothing!
returns: nothing!
*/
void setupConsole() {
    //get screen handler
    HANDLE input_handle;
    input_handle = GetStdHandle(STD_INPUT_HANDLE);

    //update screen settings
    SetConsoleMode(input_handle, ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_INSERT_MODE | ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);

    //change screen size and position
    setScreenPosAndSize();

}

/*purpose: opens a new terminal with the help screen executable
arugments: none.
returns: nothing.
*/
void spawnHelpScreen() {
    //start a new console and run the help.exe
    system("start; help.exe");
}

/*purpose: checks for the cntrl key and launches the help screen
arugments: pointer to a boolean, true to run, false to exit and stop running at the end of the program
returns: nothing!
*/
void helpWatcher(bool *helpBool) {
    //as long as we can run
    while (*helpBool) {
        //if ctrl is down
        if (GetKeyState(VK_CONTROL)<0) {
            //open the help screen
            spawnHelpScreen();
            //wait until we are back in this window, and we have let go of ctrl before respawning
            while (GetKeyState(VK_CONTROL) < 0 || !(GetConsoleWindow()==GetForegroundWindow())) {
                delay(10);
            }
        }
        //delay to prevent watchdog
        delay(10);
    }
}

/*purpose: converts human readable time to unix time
arugments:  date in YYYY/MM/DD as a string
returns:  unix time on success, -1 on fail
*/
int dateAsUnix(string * dateString) {

    //time variables
    time_t rawTime, currentTime;
    struct tm * timeinfo;
    struct tm * timeinfoCurrent;

    //pointers to the year, month and day, as integers and strings
    int *year = new (nothrow) int (0);
    int *month = new (nothrow) int (0);
    int *day = new (nothrow) int (0);
    //seperate into YYYY, MM, and DD
    string *yearString = new string(dateString->substr(0,4));
    string *monthString = new string(dateString->substr(5, 2));
    string *dayString = new string(dateString->substr(8, 2));

    //convert strings to integer
    *year = stoi(*yearString);
    *month = stoi(*monthString);
    *day = stoi(*dayString);

    //find the current year for error trapping
    time(&currentTime);
    int *currentYear = new int((localtime(&currentTime)->tm_year + 1900));

    //check if the date is in the future, or too far in the past
    if (*year<1970 || *year>*currentYear) {
        //returns error code, since date it invalid
        return -1;

    //todo: error trap better
    } else {
        //open a time variable, and set the year, month, day
        time ( &rawTime );
        timeinfo = localtime ( &rawTime );
        timeinfo->tm_year = *year - 1900;
        timeinfo->tm_mon = *month - 1;
        timeinfo->tm_mday = *day;
        timeinfo->tm_sec = 0;
        timeinfo->tm_min = 0;
        timeinfo->tm_hour = 12;

        //returns the unix time or -1 if it fails to make the time
        return mktime(timeinfo);
    }

    //free memory
    delete timeinfo;
    delete timeinfoCurrent;
    delete year;
    delete month;
    delete day;
    delete yearString;
    delete monthString;
    delete dayString;
    delete currentYear;

}

/*purpose: recalculate the number of toys made and needed based on the children and users data points
arugments: Users Array, Child Array, number of Users, the number of children, users username, and the number of toys
returns: nothing!
*/
void updateToys(Child * children[MAXCHILDREN], int * numberOfChildren, User * users[MAXUSERS], int *numberOfUsers, int (*toys)[NUMOFTOYS][2]) {

    //reset the toys counters
    for (int i = 0; i < NUMOFTOYS; i++) {
        (*toys)[i][0]=0;
        (*toys)[i][1]=0;
    }


    //update the number of toys made based on how many each elf has made
    for (int i = 0; i<*numberOfUsers; i++) {
        (*toys)[users[i]->getToyAssignedToElf()-1][0] += users[i]->getToysMade();
    }

    //update the number of toys needed based the number of children assigned each toys
    for (int i = 0; i<*numberOfChildren; i++) {
        (*toys)[children[i]->getAssignedToy()-1][1]++;
    }

}

/*purpose: determine a child's toy based on niceness, gender, and age
arguments: pointers to the child's niceness, their gender, and their age
returns: integer representing the toy
*/
int toyChooser(int nicenessRating, int age) {

    if (nicenessRating < 5) {
        //returns the worst gift
        return NUMOFTOYS;
    } else if (nicenessRating < 10) {
        //returns the 2nd worst gift
        return NUMOFTOYS-1;
    } else if (nicenessRating < 15) {
        //returns the 3rd worst gift
        return NUMOFTOYS-2;
    } else {
        //maps the children to each toy based on age
        return roundf(((float)(age+1)*(NUMOFTOYS-3))/(float)(18.0));
    }

}

/*purpose: sort the children alphabetically
arugments: Child Array, the number of children
returns: nothing!
*/
void sortChildren(Child * children[MAXCHILDREN], int * numberOfChildren) {

    //selection sort the children by name
    int i(0), j(0);
    int pos(0);

    string min;

    for (i = 0; i < *numberOfChildren - 1; i++)
    {

        min = children[i]->getName(); // the first element is min value
        pos = i;


        for (j = i + 1; j < *numberOfChildren; j++) // finding smaller value that Min
        {
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

/*purpose: sort the users alphabetically
arugments: Users Array, the number of users
returns: nothing!
*/
void sortUsers(User * users[MAXCHILDREN], int * numberOfUsers) {
    //insertion sort the users
    int i,j,tmp;
    for (i = 1; i < *numberOfUsers; i++) {
        j = i;
        // cout<<users[j - 1]->getName()<<" "<<
        while (j > 0 && users[j - 1]->getName() > users[j]->getName()) {
            swap(users[j-1], users[j]);
        }
    }

}

/*purpose: check if a user already exists
arugments: pointer to the username to search for
returns: boolean, true if user exists, false if not
*/
bool userExists(string *username) {
    //open the text file
    ifstream *loginFile = new ifstream;
    loginFile->open("login.txt");

    //pointers to variables
    //username from text file
    string *usernameToTest = new (nothrow) string;
    //boolean if the user has been found
    bool *usernameFound = new bool(false);
    //hash from text file
    size_t *hashToTest = new size_t;
    //permission level from text file
    int *permissionLevel = new int;


    //check if login file open
    if (loginFile->is_open()) {

        //read line by line
        while (!loginFile->eof()) {

            //read into variables
            *loginFile >> *usernameToTest;
            *loginFile >> *hashToTest;
            *loginFile >> *permissionLevel;

            //check if username is found
            if (*username==*usernameToTest) {
                *usernameFound=true;
                break;
            }
        }

        //close the file
        loginFile->close();

        //return true if the user was found, false otherwise
        if (*usernameFound == true) {
            //user exists
            return 1;

        } else {
            return 0;
        }

    }

    //free memory
    delete loginFile;
    delete usernameToTest;
    delete usernameFound;
    delete hashToTest;
    delete permissionLevel;
}

//purpose: validates credentials against text file
//arguments: pointer to username inputted as string, pointer to password entered as string
//returns permission level on success, 0 on fail
int loginHandler(string *username, string *password) {

    //open file
    ifstream *loginFile = new ifstream;
    loginFile->open("login.txt");

    //boolean if the user has been found
    bool *usernameFound = new bool(false);

    //username from text file
    string *usernameToTest = new string;
    //hash from text file
    size_t *hashToTest = new size_t;
    //permission level from text file
    int *permissionLevel = new int;

    //check if login file open
    if (loginFile->is_open()) {

        //read line by line
        while (!loginFile->eof()) {

            //read into variables
            *loginFile>> *usernameToTest;
            *loginFile>> *hashToTest;
            *loginFile>> *permissionLevel;

            //check if username is found, then break loop
            if (*username==*usernameToTest) {
                *usernameFound=true;
                break;
            }
        }

        //close file
        loginFile->close();

        if (*usernameFound != true) {
            //user doesn't exist, return error
            return 0;
        } else {
            //if password matches, return the permission level
            if (generateHash(username, password)==*hashToTest) {
                return *permissionLevel;
            } else {
                //incorrect password, return error
                return 0;
            }
        }

        //can't open file, return error
    } else {

        return 0;
    }

    //free memory
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
    //open users file
    ifstream fin;
    fin.open("users.txt");

    //make sure file is open, return error if not
    if(fin.fail()) {
        // throw error here
        //cout<<"Error loading user files? Is it in the right spot?";
        return -1;
    }

    //variables to read into
    string *username = new string;
    string *name = new string;
    int *hireDate = new int;
    int *toyAssigned = new int;
    int *numberOfToysMade = new int;


    //check if file is open
    if (fin.is_open()) {

        //read line by line
        while (!fin.eof())
        {
            //read into variables
            fin>> *username;
            getline(fin, *name, '$');
            fin>> *hireDate;
            fin>> *toyAssigned;
            fin>> *numberOfToysMade;

            //add new user
            users[*numberOfUsers] = new(nothrow) User(username, name, hireDate, toyAssigned, numberOfToysMade);

            //increment number of users
            *numberOfUsers = (*numberOfUsers + 1);

        }
        //close the file
        fin.close();
    }

    //free memory
    delete username;
    delete hireDate;
    delete name;
    delete toyAssigned;
    delete numberOfToysMade;


    //open children file
    fin.open("children.txt");

    //make sure file is open, return error if not
    if(fin.fail()) {
        // throw error here
        //cout<<"Error loading children files? Is it in the right spot?";
        return -2;
    }

    //variables to read into
    string *nameChild = new (nothrow) string;
    string *homeAddress = new (nothrow) string;
    int *birthday = new (nothrow) int;
    int *gender = new (nothrow) int;
    bool *genderBool = new (nothrow) bool;
    int *numberOfSiblings = new (nothrow) int;
    int *cookieRating = new (nothrow) int;
    int *nicenessRating = new (nothrow) int;
    int *toyAssignedChild = new (nothrow) int;

    //check if file is open
    if (fin.is_open()) {

        //read line by line
        while (!fin.eof() )
        {
            //read into variables
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

            //convert gender from binary int to bool
            *genderBool = (bool)(*gender);

            //add the new child
            children[*numberOfChildren] = new (nothrow) Child(nameChild,birthday,genderBool,homeAddress,numberOfSiblings, cookieRating, nicenessRating, toyAssignedChild);

            //increment the number of children
            *numberOfChildren = (*numberOfChildren + 1);



        }
        //close file
        fin.close();
    }

    //free memory
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

    //make sure file is open, return error if not
    if(fin.fail()) {
        // throw error here
        //cout<<"Error loading toys files? Is it in the right spot?";
        return -3;
    }

    //variables to read into
    int *needed = new int;
    int *made = new int;

    //check if file is open
    if (fin.is_open()) {
        //read each toy
        for (int i = 0; i < NUMOFTOYS; i++) {

            //read into variables
            fin >> *made;
            fin >> *needed;

            //update array
            (*toys)[i][0]=*made;
            (*toys)[i][1]=*needed;
        }
        //close file
        fin.close();
    }

    //free memory
    delete needed;
    delete made;

    //return success
    return 1;

}

/*purpose: update the files
arugments: users array, number of users pointer, children array, number of children pointer, toys array
returns: 1 on success, 0 on fail
*/
int saveFiles(User * users[MAXUSERS], int *numberOfUsers, Child * children[MAXCHILDREN], int * numberOfChildren, int (*toys)[NUMOFTOYS][2]) {

    //make sure everything is perfect before saving
    sortUsers(users, numberOfUsers);
    sortChildren(children, numberOfChildren);
    updateToys(children, numberOfChildren, users, numberOfUsers, toys);

    //open users file for writing
    ofstream fin;
    fin.open("users.txt");

    //check if file is open
    if (fin.is_open()) {

        //for each user
        for (int i =0; i< *numberOfUsers; i++) {
            //output everything to the text file
            if (i != 0) {
                fin<<"\n";
            }
            fin << users[i]->getUsername()<<"\n";
            fin << users[i]->getName()<<"$\n";
            fin << users[i]->getHireDate()<<"\n";
            fin << users[i]->getToyAssignedToElf()<<"\n";
            fin << users[i]->getToysMade();
        }
        //close the file
        fin.close();
    }

    //open children file for writing
    fin.open("children.txt");

    //check if file is open
    if (fin.is_open()) {
        //for each child
        for (int i = 0; i < *numberOfChildren; i++) {
            //output everything to the text file
            if (i != 0) {
                fin << "\n";
            }
            fin << children[i]->getName()<<"$\n";
            fin << children[i]->getBirthdayUnix()<<"\n";
            fin << children[i]->getGenderBool()<<"\n";
            fin << children[i]->getHomeAddress()<<"$\n";
            fin << children[i]->getSiblingNumber()<<"\n";
            fin << children[i]->getCookieRating()<<"\n";
            fin << children[i]->getNicenessRating()<<"\n";
            fin << children[i]->getAssignedToy();
        }
        //close the file
        fin.close();
    }


    //open toys file for writing
    fin.open("toys.txt");

    //check is file is open
    if (fin.is_open()) {
        //for each toy
        for (int i = 0; i < NUMOFTOYS; i++) {
            //write to the file
            if (i != 0) {
                fin << "\n";
            }
            fin << (*toys)[i][0]<<"\n";
            fin << (*toys)[i][1];

        }
        //close the file
        fin.close();
    }

    //return success
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


/*purpose: view a child's contents and edit each one as required
arugments: children array, number of children
returns: nothing!
*/
void editChild(Child *children[MAXCHILDREN], int *index) {

    //clear screen
    system("cls");

    //pointer to user selection
    int *selection = new (nothrow) int(0);

    //each of the variables to edit
    int * numberOfSiblings = new (nothrow) int;
    string * address = new (nothrow) string;
    int * cookieRating = new (nothrow) int;
    int * nicenessRating = new (nothrow) int;


    do {
        system("cls");
        //print all the child's details
        cout<<"Selected Child Name: "<<children[*index]->getName()<<"\n";
        cout<<"Birthday: "<<children[*index]->getBirthdayReadable()<<"\n";
        cout<<"Age: "<<children[*index]->getAge()<<"\n";
        cout<<"Gender: "<<children[*index]->getGenderReadable()<<"\n";
        cout<<"Address: "<<children[*index]->getHomeAddress()<<"\n";
        cout<<"# of siblings: "<<children[*index]->getSiblingNumber()<<"\n";
        cout<<"Cookie Rating (1-15): \t\t"<<children[*index]->getCookieRating()<<"\n";
        cout<<"Niceness Rating (0-100): \t"<<children[*index]->getNicenessRating()<<"\n";
        cout<<"Assigned Toy: "<<toysMap.at(children[*index]->getAssignedToy())<<"\n\n";

        //provide options to edit
        cout<<"1. Edit address\n";
        cout<<"2. Edit number of siblings\n";
        cout<<"3. Edit cookie rating\n";
        cout<<"4. Edit niceness rating\n";
        cout<<"5. Exit\n";
        cout<<"Make a selection -->";

        cin>>*selection;

        //error trap the input
        if (*selection > 5 || *selection < 1) {
            cout<<"Invalid selection. Must be between 1 and 5. Press any key to try again.";
            _getch();
        }

        //error trap the input
    } while (*selection > 5 || *selection < 1);



    system("cls");
    //edit each of the variables by getting the new value and pushing it to the child class, also error trap
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

    //free memory
    delete selection;
    delete nicenessRating;
    delete cookieRating;
    delete numberOfSiblings;
    delete address;
}

/*purpose: view each child and quickly edit the niceness ratings
arugments: children array, number of children
returns: nothing!
*/
void viewChild(Child *children[MAXCHILDREN], int *numberOfChildren) {
    //sort the children
    sortChildren(children, numberOfChildren);

    //pointer to the selections
    int *input = new int(7);
    int *selection = new int (0);
    //pointer to temp niceness rating
    int *nicenessRating = new int;



    do {
        //print each child and their niceness ratings, invert the colors for the selected child
        system("cls");
        cout<<"Enter to view/edit child details, up/down to select child, left/right to change niceness rating, esc to exit\n\n";
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


        //get user input
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
            //check if the user wants to exit, then exit, otherwise, edit the child
            if (*selection == *numberOfChildren) {
                *input = 6;
            } else {
                editChild(children, selection);
            }
            break;
        case 1:
            //change the selected child
            if (*selection>0) {
                *selection = *selection -1;
            }
            break;
        case 2:
            //change the niceness rating down
            *nicenessRating = children[*selection]->getNicenessRating();
            *nicenessRating = *nicenessRating - 1;
            children[*selection]->setNicenessRating(nicenessRating);
            break;
        case 3:
            //change the niceness rating up
            *nicenessRating = children[*selection]->getNicenessRating();
            *nicenessRating = *nicenessRating + 1;
            children[*selection]->setNicenessRating(nicenessRating);
            break;
        case 4:
            //change the selected child
            if (*selection<*numberOfChildren) {
                *selection = *selection +1;
            }
            break;
        }


        //loop until the user wants to exit by pressing exit
    } while (*input != 6);


    //free memory
    delete selection;
    delete input;
    delete nicenessRating;

    //clear the screen
    system("cls");

}


/*purpose: view each child's address and quickly edit their cookie ratings
arugments: children array, number of children
returns: nothing!
*/
void christmasMode(Child *children[MAXCHILDREN], int *numberOfChildren) {
    //sort the children
    sortChildren(children, numberOfChildren);

    //pointer to the selections
    int *input = new int(7);
    int *selection = new int (0);
    //pointer to temp cookie rating
    int *cookieRating = new int;



    do {
        //print each child, their address and siblings, and their cookie ratings, invert the colors for the selected child
        system("cls");
        cout<<"Up/down to select child, left/right to change cookie rating, esc to exit\n\nName:\t\tCookie Rating:\t\t# of Siblings:\t\tHome address:\n";
        for (int i=0; i<*numberOfChildren; i++) {
            //todo: formating of names by length
            if (*selection == i) {
                changeColor(15, 4);
            }
            cout<<children[i]->getName()<<"\t\t"<<children[i]->getCookieRating()<<"\t\t\t"<<children[i]->getSiblingNumber()<<"\t\t\t"<<children[i]->getHomeAddress()<<"\n";
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


        //get user input
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
            //check if the user wants to exit, then exit, otherwise, edit the child
            if (*selection == *numberOfChildren) {
                *input = 6;
            }
            break;
        case 1:
            //change the selected child
            if (*selection>0) {
                *selection = *selection -1;
            }
            break;
        case 2:
            //change the niceness rating down
            *cookieRating = children[*selection]->getCookieRating();
            *cookieRating = *cookieRating - 1;
            children[*selection]->setCookieRating(cookieRating);
            break;
        case 3:
            //change the niceness rating up
            *cookieRating = children[*selection]->getCookieRating();
            *cookieRating = *cookieRating + 1;
            children[*selection]->setCookieRating(cookieRating);
            break;
        case 4:
            //change the selected child
            if (*selection<*numberOfChildren) {
                *selection = *selection +1;
            }
            break;
        }


        //loop until the user wants to exit by pressing exit
    } while (*input != 6);


    //free memory
    delete selection;
    delete input;
    delete cookieRating;

    //clear the screen
    system("cls");

}

/*purpose: add a new child
arugments: children array, number of children
returns: nothing!
*/
void addChild(Child * children[MAXCHILDREN], int * numberOfChildren) {
    //pointers to variables for all of the children's settings
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

    //clear the screen
    system("cls");

    //get the name input
    cout << "Please Input the Name of the Child...> ";
    fflush(stdin);
    getline(cin, *childName);

    //get the birthday input and error trap
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


    //get the gender and error trap
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



    //convert the user input to the gender boolean
    if (*childGender == "M") {
        *genderBool = true;
    } else {
        *genderBool = false;
    }

    //get the home address
    cout << "Please Input the Home Address of the Child --> ";
    getline(cin, *childHomeAddress);

    //get the number of siblings and error trap
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

    //don't get toys assigned, not needed
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

    //add the new child
    children[*numberOfChildren] = new (nothrow) Child(childName,childBirthday,genderBool,childHomeAddress,childNumberOfSiblings, cookieRating, nicenessRating, toyAssigned);

    //increment the number of children
    *numberOfChildren = (*numberOfChildren + 1);

    //user message
    cout<<"Successfully added! Press any key to return to menu.";
    _getch();
    system("cls");

    //free memory
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

/*purpose: assign a gift to a child
arugments: children array, number of children
returns: nothing!
*/
void assignGift(Child * children[MAXCHILDREN], int * numberOfChildren) {
    //pointers to the user's selection
    int *input = new int(7);
    int *selection = new int (0);
    //pointer to the new toy to be assiggned
    int *toyAssigned = new int;

    do {

        system("cls");

        cout<<"Enter to auto assign, up/down to select child, left/right to change toy, esc to exit\n\n";

        //print all children and invert the colour of the selected child or exit
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


        //get arrow keys input
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
            //exit if the user has selected exit, otherwise, random assign the toy
            if (*selection == *numberOfChildren) {
                *input = 6;
            } else {
                *toyAssigned = toyChooser(children[*selection]->getNicenessRating(), children[*selection]->getAge());
                children[*selection]->setAssignedToy(toyAssigned);
                system("cls");
                cout<<"Successfully auto assigned toy, press any key to continue.";
                _getch();
            }
            break;
        case 1:
        //change selection
            if (*selection>0) {
                *selection = *selection -1;
            }
            break;
        case 2:
        //change the assigned toy
            *toyAssigned = children[*selection]->getAssignedToy();
            *toyAssigned = *toyAssigned - 1;
            children[*selection]->setAssignedToy(toyAssigned);
            break;
        case 3:
        //change the assigned toy
            *toyAssigned = children[*selection]->getAssignedToy();
            *toyAssigned = *toyAssigned + 1;
            children[*selection]->setAssignedToy(toyAssigned);
            break;
        case 4:
        //change selection
            if (*selection<*numberOfChildren) {
                *selection = *selection +1;
            }
            break;
        }


        //loop until the user wants to exit
    } while (*input != 6);


    //free memory
    delete selection;
    delete input;
    delete toyAssigned;

    //clear the screen
    system("cls");
}

/*purpose: assign gift to all children or all unassigned children
arugments: children array, number of children
returns: nothing!
*/
void assignAllGifts(Child * children[MAXCHILDREN], int * numberOfChildren) {
    //pointers to the user selection and their confirmation
    int * selection = new (nothrow) int(0);
    string * confirmation = new (nothrow) string;

    //display menu and get user selection, and error trap
    do {
        system("cls");

        cout<<"1. Auto assign gifts to all children\n";
        cout<<"2. Auto assign gifts to unassigned children\n";
        cout<<"3. Cancel\n";
        cout<<"--> ";

        cin>>*selection;

        if (*selection > 3 || *selection < 1) {
            cout<<"Invalid input! Must be between 0 and 3.\nPress any key to try again.";
            _getch();
        }

    } while (*selection > 3 || *selection < 1);


    //if they want to reassign all children
    if (*selection == 1) {
        //get a confirmation and error trap
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

        //reassign all children randomly
        if (*confirmation == "Y") {
            for (int i=0; i<*numberOfChildren; i++) {
                int * toyAssigned = new (nothrow) int (toyChooser(children[i]->getNicenessRating(), children[i]->getAge()));
                children[i]->setAssignedToy(toyAssigned);
                delete toyAssigned;
            }
            system("cls");
            cout<<"Done assigning toys. Press any key to return.";
            _getch();
        }
    } else if (*selection == 2) {
        //reassign all unassigned children
        for (int i=0; i<*numberOfChildren; i++) {
            if (children[i]->getAssignedToy()==0) {
                int * toyAssigned = new (nothrow) int (toyChooser(children[i]->getNicenessRating(), children[i]->getAge()));
                children[i]->setAssignedToy(toyAssigned);
                delete toyAssigned;
            }
        }
        system("cls");
        cout<<"Done assigning toys. Press any key to return.";
        _getch();
    }

    //free memory
    delete selection;
    delete confirmation;


}

/*purpose: delete children 18+
arugments: children array, number of children
returns: nothing!
*/
void purgeChildren(Child * children[MAXCHILDREN], int * numberOfChildren) {

    //pointer to the confirmation
    string * confirmation = new (nothrow) string;
    //track the number of removed children
    int * numberOfRemovedChildren = new (nothrow) int(0);

    //get confirmation and error trap
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

    //if they confirm
    if (*confirmation == "Y") {
        //for each child
        for (int i=0; i<*numberOfChildren; i++) {
            //if the child is 18
            if (children[i]->getAge() >= 18) {
                //force the child to the end of the error
                children[i]->forceEnd();
                //increment the number of children
                *numberOfRemovedChildren = *numberOfRemovedChildren +1;
            }
        }

        //sort the children alphabetically, push deleted children to the end
        sortChildren(children, numberOfChildren);

        //remove all deleted children
        for (int i=*numberOfChildren-1; i>=(*numberOfChildren-*numberOfRemovedChildren); i--) {
            delete children[i];
        }

        //update the number of children
        *numberOfChildren = *numberOfChildren - *numberOfRemovedChildren;
    }

    //free memory
    delete confirmation;
    delete numberOfRemovedChildren;

    //user message
    cout<<"Successfully purged children! Press any key to return.";
    _getch();

}

/*purpose: clean workshop menu for each elf, lets them update toys made
arugments: user array, number of users, and toys array
returns: nothing!
*/
void workshopMenu(User *users[MAXUSERS], int *numberOfUsers, int (*toys)[NUMOFTOYS][2], string *username) {

    //get the user number from the username
     int *userNumber = new (nothrow) int(-1);
    for (int i = 0; i<*numberOfUsers; i++) {
        if (users[i]->getUsername() == *username) {
            *userNumber = i;
        }
    }

    //set the user to the first elf is using an admin account (and username can't be found)
    if (*userNumber == -1) {
        *userNumber = 0;
        system("cls");
        cout<<"Not logged in as Elf! Using "<<users[*userNumber]->getName()<<" to test.\nPress any key to continue.";
        _getch();
    }

    //get the current toy assigned to the elf
    int *toyAssigned = new (nothrow) int(users[*userNumber]->getToyAssignedToElf() -1);

    //pointers to the number of toys made and the arrow key input
    int *input = new (nothrow) int;
    int *toysMade = new (nothrow) int;

    do {
        //show menu
        system("cls");
        cout << " _    _            _        _                  ___  ___" << endl;
        cout << "| |  | |          | |      | |                 |  \\/  |                 " << endl;
        cout << "| |  | | ___  _ __| | _____| |__   ___  _ __   | .  . | ___ _ __  _   _ " << endl;
        cout << "| |/\\| |/ _ \\| \'__| |/ / __| \'_ \\ / _ \\| \'_ \\  | |\\/| |/ _ \\ \'_ \\| | | |" << endl;
        cout << "\\  /\\  / (_) | |  |   <\\__ \\ | | | (_) | |_) | | |  | |  __/ | | | |_| |" << endl;
        cout << " \\/  \\/ \\___/|_|  |_|\\_\\___/_| |_|\\___/| .__/  \\_|  |_/\\___|_| |_|\\__,_|" << endl;
        cout << "                                       | |                              " << endl;
        cout << "                                       |_|                              " << endl;
        //show the name, toy assigned, number made, total needed, and progress
        cout<<"Hi "<<users[*userNumber]->getName()<<"!\n";
        cout<<"You have been assigned: "<< toysMap.at(*toyAssigned +1)<<"\n";
        cout<<"You have made: \t\t"<< users[*userNumber]->getToysMade()<<"\n";
        cout<<"Total made: \t\t"<< (*toys)[*toyAssigned][0]<<"\n";
        cout<<"Total needed: \t\t"<< (*toys)[*toyAssigned][1]<<"\n";

        //make sure we don't divide by zero
        if ((*toys)[*toyAssigned][1]==0) {
            //print a number if dividing by zero
            cout<<"Percent progress: \t"<< PROGRESSATZERO <<"%\n\n";
        } else {
            //print the percentage progress
            cout<<"Percent progress: \t"<< (int)((float)((float)(*toys)[*toyAssigned][0]/(float)(*toys)[*toyAssigned][1])*100)<<"%\n\n";
        }

        //use the arrow keys to navigate message
        cout<<"Use arrow keys to increase number of toys made. Use enter or esc to exit.";

        //get user input
        *input = arrowKeys(true);

        //if the user press the up or down key, change the number of toys made for the user and the toys array, as long as it's within bounds
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

        //loop until the user exits
    } while (*input != 0 && *input != 6);

    //free memory
    delete userNumber;
    delete toyAssigned;
    delete input;
    delete toysMade;

}

/*purpose: give santa a general overview of the progress of all the toys
arugments: toys array
returns: nothing!
*/
void workshopProgress(int (*toys)[NUMOFTOYS][2]) {
    //clear the screen
    system("cls");

    //for each toy
    for (int i = 0; i < NUMOFTOYS-3; i++) {

        //output the toy
        cout<< toysMap.at(i +1)<<": \t";

        //spacing
        if (i==5 || i== 7 || i==8) {
            cout<<"\t";
        }

        //output the number of toys made and needed
        cout<<(*toys)[i][0]<<"/"<<(*toys)[i][1]<<"\tor ";

        //check for dividing by zero
        if ((*toys)[i][1]==0) {
            //output a number when dividing by zero
            cout<<PROGRESSATZERO<<"%\n";
        } else {
            //output the percentage progress
            cout<< (int)((float)((float)(*toys)[i][0]/(float)(*toys)[i][1])*100)<<"%\n";
        }
    }

    //user message
    cout<<"\nPress any key to return to menu.";
    _getch();

}

/*purpose: change a users password
arugments: username
returns: nothing!
*/
void changePassword(string *username) {
     //initializing variables
    string *password = new (nothrow) string;
    string *passwordConfirm = new (nothrow) string;

    do {
         system("cls"); //clearing screen
         *password = getpass("Please enter the new password --> ", true); //password masking
         *passwordConfirm = getpass("Confirm the new password --> ", true); //password masking

         if(*passwordConfirm == *password) {
              cout <<"Passwords Match. Saved"<<endl;
         } else {
              cout <<"Passwords Do not Match. Please Try again"<<endl;
              _getch(); //holding screen
         }

    } while (*password != *passwordConfirm); //error trap


    ifstream *loginFile = new (nothrow) ifstream;
    loginFile->open("login.txt"); // open login files

    ofstream *outputFile = new (nothrow) ofstream;
    outputFile->open("loginTemp.txt"); //open the output files


    bool *usernameFound = new (nothrow) bool(false);

    string *usernameToTest = new (nothrow) string("");
    size_t *hashToTest = new (nothrow) size_t;
    int *permissionLevel = new (nothrow) int;

    //open login file
    if (loginFile->is_open()) {

        while (!loginFile->eof()) { //looping to the end of file

            if (*usernameToTest != "") {
                *outputFile<<"\n"; //outputting a new line in the output file
            }

            *loginFile>>*usernameToTest;
            *outputFile<<*usernameToTest<<"\n";
            *loginFile>> *hashToTest;

            if (*username==*usernameToTest) {
                *usernameFound=true; //marks if the username has been found
                *outputFile << generateHash(username, password) <<"\n"; //generating the password hash
            } else {
                *outputFile << *hashToTest<<"\n";
            }

            //outputting the permission level
            *loginFile >> *permissionLevel;
            *outputFile << *permissionLevel;
        }

        //closing the file
        loginFile->close();
        outputFile->close();
        //removing the text files
        remove("login.txt");
        rename("loginTemp.txt", "login.txt");



        if (*usernameFound != true) { //checking if the username was found or not
            //user doesn't exist
            cout<<"Failed to find user. Press any key to return.";
            _getch(); //holding the screen
        } else {
            cout<<"Successfully updated password. Press any key to return.";
            _getch(); //holding the screen
        }

        //can't open file
    } else {
        cout<<"Couldn't open file. Press any key to return.";
        _getch(); //holding the screen
    }

    //deleting pointers
    delete loginFile;
    delete outputFile;
    delete usernameFound;
    delete usernameToTest;
    delete hashToTest;
    delete permissionLevel;
    delete password;
    delete passwordConfirm;
}

/*purpose: to assign toys to elves
arugments: users array, number of users
returns: nothing!
*/
void elfToy(User *users[MAXUSERS], int *numberOfUsers) {


    sortUsers(users, numberOfUsers); //opening the sort users function

    //initializing variables
    int *selection = new int (0);
    int *input = new (nothrow) int(7);



    do {
        system("cls"); //clearing the screen

        cout<<"Select Elf, then press enter. (Press esc to go back)\n\n";

        for (int i=0; i<*numberOfUsers; i++) {
            //todo: formating of names by length
            if (*selection == i) {
                changeColor(15, 4); //changing the color of the text
            }
            cout<<users[i]->getName()<<"\t\t\t\t\t"<<toysMap.at(users[i]->getToyAssignedToElf())<<"\n"; //opening the toy map

            ;
            if (*selection == i) {
                changeColor(4, 15); //changing the color of the text
            }
        }

        *input = arrowKeys(true); //getting arrowkey input
        switch (*input) { //checking the users input
        case 1:
            if (*selection>0) {
                *selection = *selection -1;
            }
            break;
        case 4:
            if (*selection<*numberOfUsers-1) {
                *selection = *selection +1;
            }
            break;
        }


    } while (*input != 6 && *input != 0);

    if (*input == 0) {

        int *elfToyAssign = new (nothrow) int(0);

        do {
            system("cls"); //clearing screen
            //ASCII art and options
            cout << "\n\n\n\n\t\t\t\t" << " .----------------.  .----------------.  .----------------.  .----------------. " << endl;
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
            for (int i = 1; i <= NUMOFTOYS-3; i++) {
                cout << "\t\t\t\t" << "\t\t\t\t" << i <<". "<<toysMap.at(i) << endl;
            }
            cout << "\t\t\t\t" << "\t\t\t\t" << ">";
            cin >> *elfToyAssign; //user input
            if (*elfToyAssign < 1 || *elfToyAssign > NUMOFTOYS-3) //error trap
            {
                cout << "Error! Your Selection Must be Within 1 & " << NUMOFTOYS-3 << endl;
                _getch(); //holding screen
            }

            system("cls"); //clear screen

        } while(*elfToyAssign < 1 || *elfToyAssign > NUMOFTOYS-3); //repeat while error no longer occurs

        int *toysMade = new (nothrow) int(0);

        users[*selection]->setToyAssignedToElf(elfToyAssign); //set the toy assigned to the elf
        users[*selection]->setToysMade(toysMade); //reset toys made counter


        //deleting pointers
        delete elfToyAssign;
        delete toysMade;

    }

    //deleting pointers
    delete selection;
    delete input;

}

/*purpose: adding an elf to the text files
arugments: user array, number of users
returns:none
*/
void addElf(User * users[MAXUSERS], int *numberOfUsers) {

    //initializing variables
    string *username = new (nothrow) string;
    string *name = new (nothrow) string;
    int *hireDate = new (nothrow) int;
    int *toyAssigned = new (nothrow) int(1);
    int *numberOfToysMade = new (nothrow) int(0);
    string *password = new (nothrow) string;
    string *passwordConfirm  = new (nothrow) string;
    string *hireDateInput = new (nothrow) string;
    bool *error = new (nothrow) bool;


    system("cls");  //clearing screen

    cout << "Please Input the Name of the Elf...> ";
    fflush(stdin); //flushing standard input
    getline(cin, *name); //user input

    do {
        cout << "Please Input the Hire Date of the Elf (YYYY/MM/DD)...> ";
        getline(cin, *hireDateInput); //user input

        *error = false; //resetting the error function

        //error trap
        if (hireDateInput->length()!=10) {
            *error = true; //error

        } else {
            for (int i = 0; i<10; i++) {
                if (i == 4 || i == 7) {
                    if (hireDateInput->at(i)!='/') {
                        *error = true; //error
                    }
                } else {
                    if (!isdigit(hireDateInput->at(i))) {
                        *error = true; //error
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

    } while (*error == true); //do while there are errors


    do {
        system("cls"); //clearing screen
        cout << "Please Input the Username for the Elf...> ";
        cin>> *username; //user input

        if (userExists(username)) {
            cout<<"Username already exists! Please try again!\nPress any key.";
            _getch(); //holding screen
        }

    } while (userExists(username));

   do {
        system("cls"); //clearing the screen
        *password = getpass("Please enter the Elfs password --> ", true); //masking the password
        *passwordConfirm = getpass("Confirm the Elf's password --> ", true); //masking the password

        if(*passwordConfirm == *password) {
             cout <<"Passwords Match. Initialized"<<endl;
        } else {
             cout <<"Passwords Do not Match. Please Try again"<<endl;
             _getch(); //holding screen
        }

   } while (*password != *passwordConfirm);

//string *_username, string *nameInput, int *hireDateInput, int *_toyAssigned, int *numberOfToysMade)


    users[*numberOfUsers] = new (nothrow) User(username,name,hireDate,toyAssigned,numberOfToysMade);

    *numberOfUsers = (*numberOfUsers + 1);

    //opening files
    ofstream loginFile;
    loginFile.open("login.txt", ios::app);

    loginFile<<"\n"<<*username<<"\n";
    loginFile<<generateHash(username, password)<<"\n"; //generating a password hash
    loginFile<<"1";

    //deleting pointers
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
    _getch(); //holding screen
    system("cls"); //clearing the screen


}
/*purpose: to remove an elf from the text files
arugments: user array, number of users
returns:none
*/
void fireElf(User * users[MAXUSERS], int *numberOfUsers) {
    //initializing variables
    string * confirmation = new (nothrow) string;
    //int * numberOfRemovedUsers = new (nothrow) int(0);

    int *selection = new int (0);
    int *input = new (nothrow) int(7);



    do {
        system("cls"); //clearing screen

        cout<<"Select Elf to terminate, then press enter. (Press esc to go back)\n\n";

        for (int i=0; i<*numberOfUsers; i++) {
            if (*selection == i) {
                changeColor(15, 4); //changing the color of the text
            }
            cout<<users[i]->getName()<<"\n"; //getting the name if the user

            if (*selection == i) {
                changeColor(4, 15); //changing the color of the text
            }
        }

        *input = arrowKeys(true); //getting arrow key input
        switch (*input) { //checking user input
        case 1:
            if (*selection>0) {
                *selection = *selection -1;
            }
            break;
        case 4:
            if (*selection<*numberOfUsers-1) {
                *selection = *selection +1;
            }
            break;
        }


    } while (*input != 6 && *input != 0); //looping while the user has not hit the escape key or the enter key

    if (*input == 0) {

        do
        {
            system("cls"); //clearing screen
            cout << "Are you sure you want to terminate "<<users[*selection]->getName()<<" (Y or N) --> ";
            fflush(stdin); //flushing the standard input
            getline(cin, *confirmation); //getting the user input

            for (int i = 0; i < confirmation->length(); i++) {
                confirmation->at(i)=toupper(confirmation->at(i)); //making the user input upper case
            }

            if (*confirmation != "Y" && *confirmation != "N")
            { //error trap

                cout << "Error! Invalid input. ";
                _getch(); //holding the screen
                system("cls"); //clearing the screen
            }

        } while (*confirmation != "Y" && *confirmation != "N"); //looping while the input is not yes or no

        if (*confirmation == "Y") {

            string * username = new (nothrow) string;
            *username = users[*selection]->getUsername(); //getting the users username

            //remove creds from login file
            ifstream *loginFile = new ifstream;
            loginFile->open("login.txt"); //opening the login file

            ofstream *outputFile = new ofstream;
            outputFile->open("loginTemp.txt"); //opening the output file

            string *usernameToTest = new string("");
            size_t *hashToTest = new size_t;
            int *permissionLevel = new int;


            while (!loginFile->eof()) { //looping to the end of the file

                if (*usernameToTest != "" && *usernameToTest != *username) {
                    *outputFile<<"\n"; //outputting a new line into the text file
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

            //closing the text files
            loginFile->close();
            outputFile->close();

            //removing the files from the program
            remove("login.txt");
            rename("loginTemp.txt", "login.txt");


            //force the user to be sorted to the end of the array
            users[*selection]->forceEnd();
            //sort the user to the end of the array
            sortUsers(users, numberOfUsers);
            //delete the user
            delete users[*numberOfUsers-1];
            //decrease the number of users
            *numberOfUsers = *numberOfUsers - 1;


            cout<<"Successfully removed elf! Press any key to return.";
            _getch(); //holding the screen



        }

        //deleting pointers
        delete confirmation;



    }

    //deleting the pointers
    delete selection;
    delete input;




}


/*purpose: view each elf and their details
arugments: user array, number of users
returns: nothing!
*/
void viewElves(User * users[MAXUSERS], int *numberOfUsers) {

    sortUsers(users, numberOfUsers); //opening the sort users function

    //pointer to the selections
    int *input = new int(7);
    int *selection = new int (0);



    do {
        //print each elf, invert the colors for the selected elf
        system("cls");
        cout<<"Enter to view elf details, up/down to select elf, esc to exit\n\n";
        for (int i=0; i<*numberOfUsers; i++) {
            //todo: formating of names by length
            if (*selection == i) {
                changeColor(15, 4);
            }
            cout<<users[i]->getName()<<"\n";
            if (*selection == i) {
                changeColor(4, 15);
            }
        }

        if (*selection == *numberOfUsers) {
            changeColor(15, 4);
        }
        cout<<"Exit\n";
        if (*selection == *numberOfUsers) {
            changeColor(4, 15);
        }


        //get user input
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
            //check if the user wants to exit, then exit, otherwise, edit the child
            if (*selection == *numberOfUsers) {
                *input = 6;
            } else {
                system("cls");
                //print all the elf's details
                cout<<"Selected Elf's Name: "<<users[*selection]->getName()<<"\n";
                cout<<"Hire date: "<<users[*selection]->getHireDateReadable()<<"\n";
                cout<<"Year since hire: "<<users[*selection]->getYearsSinceHire()<<"\n";
                cout<<"Assigned Toy: "<<toysMap.at(users[*selection]->getToyAssignedToElf())<<"\n\n";

                cout<<"Press any key to return.";

                _getch();
                system("cls");
            }
            break;
        case 1:
            //change the selected child
            if (*selection>0) {
                *selection = *selection -1;
            }
            break;
        case 4:
            //change the selected child
            if (*selection<*numberOfUsers) {
                *selection = *selection +1;
            }
            break;
        }


        //loop until the user wants to exit by pressing exit
    } while (*input != 6);


    //free memory
    delete selection;
    delete input;

    //clear the screen
    system("cls");

}


/*purpose:To reset an elfs password
arugments: user array, number of users
returns: none
*/
void resetElfPassword(User * users[MAXUSERS], int *numberOfUsers) {
    //initializing the variables
    int *selection = new int (0);
    int *input = new (nothrow) int(7);



    do {
        system("cls"); //clearing the screen

        cout<<"Select Elf to reset password, then press enter. (Press esc to go back)\n\n";

        for (int i=0; i<*numberOfUsers; i++) {
            if (*selection == i) {
                changeColor(15, 4); //changing the color of the text
            }
            cout<<users[i]->getName()<<"\n"; //outputting the name of the user


            if (*selection == i) {
                changeColor(4, 15); //changing the color of the text
            }
        }

        *input = arrowKeys(true); //collecting input from the arrow keys
        switch (*input) { //checking the users input
        case 1:
            if (*selection>0) {
                *selection = *selection -1;
            }
            break;
        case 4:
            if (*selection<*numberOfUsers-1) {
                *selection = *selection +1;
            }
            break;
        }


    } while (*input != 6 && *input != 0); //looping while the user has not clicked escape or enter

    if (*input == 0) {
        string * username = new (nothrow) string;
        *username = users[*selection]->getUsername(); //collecting the users username


        changePassword(username); //opening the change password function

    }

    //deleting pointers
    delete selection;
    delete input;

}

/*purpose:Resets the cookie rating and niceness rating of a child
arugments: child array, number of children
returns:none
*/
void resetRatings(Child * children[MAXCHILDREN], int * numberOfChildren) {
    //Initialize the variables
    string * confirmation = new (nothrow) string;
    int * nicenessRating = new (nothrow) int(50);
    int * cookieRating = new (nothrow) int(1);
    int * toyAssigned = new (nothrow) int(0);

    //todo: reset toy assigned as well

    do
    {
        system("cls"); //clear screen
        cout << "Are you sure you want to reset cookie and niceness ratings as well as toys? (Y or N) --> ";
        fflush(stdin); //Flushing the Standard Input
        getline(cin, *confirmation); //Getting the users confirmation

        for (int i = 0; i < confirmation->length(); i++) {
            confirmation->at(i)=toupper(confirmation->at(i)); //Putting the confirmation to upper case
        }

        if (*confirmation != "Y" && *confirmation != "N") //Checking if input is yes or no
        {

            cout << "Error! Invalid input. "; //displaying error message
            _getch(); //holding screen
            system("cls"); //clearing screen
        }

    } while (*confirmation != "Y" && *confirmation != "N"); //repeating until either yes or no is inputted.

    if (*confirmation == "Y") { //resetting all ratings
        for (int i=0; i<*numberOfChildren; i++) {
            children[i]->setNicenessRating(nicenessRating);
            children[i]->setCookieRating(cookieRating);
            children[i]->setAssignedToy(toyAssigned);
        }
    }

    //deleting pointers
    delete nicenessRating;
    delete cookieRating;
    delete confirmation;
    delete toyAssigned;

}





//****MENU FUNCTIONS****

/*purpose:Opening the menu for the Elf User
arugments: Users Array, Child Array, number of Users, the number of children, users username, and the number of toys
returns: none
*/
void menuElf(User * users[MAXUSERS], int *numberOfUsers, Child * children[MAXCHILDREN], int * numberOfChildren, int (*toys)[NUMOFTOYS][2], string *username) {
  //Initializing variables
    int *selectionelf = new (nothrow) int(0);
    bool *error = new (nothrow) bool;

    while (*selectionelf != 7) { //Running the program whilst the user does not wish to exit

        do { //starting a do while loop
            *error = false;  //initializing the error variable as false
            system("cls"); //clearing the screen
            cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl; //centering the menu in the screen
            //ASCII Art for Elf screen and displaying options
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
            cin >> *selectionelf;//inputting users selection
            if (*selectionelf < 1 || *selectionelf > 7) //error trap
            {
                cout << "Error! Your Selection Must be Within 1 & 7" << endl;
                *error = true;
                _getch();
                system("cls");
            }
        } while(*error == true); //looping if error occurs

        switch(*selectionelf) //checking what the user selected
        { //opening each function relating to the users selection
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
    //delete pointers
    delete selectionelf;
    delete error;

}

/*purpose: Opening the menu for Santa
arugments: Users Array, Child Array, number of Users, the number of children, users username, and the number of toys
returns: none
*/
void menuSanta(User * users[MAXUSERS], int *numberOfUsers, Child * children[MAXCHILDREN], int * numberOfChildren, int (*toys)[NUMOFTOYS][2], string *username) {
    //Initializing variables
    int *selectionsanta = new (nothrow) int(0);
    bool *error = new (nothrow) bool;

    while (*selectionsanta != 12) { //Running the program whilst the user does not wish to exit

        do { //starting a do while loop
            *error = false; //initializing the error variable as false
            system("cls"); //clearing the screen
            cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl; //centering the menu in the screen
            //ASCII Art for Santa screen and displaying options
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
            cout << "\t\t\t" << "\t\t\t\t9. Christmas Eve mode" << endl;
            cout << "\t\t\t" << "\t\t\t\t10. Change Password" << endl;
            cout << "\t\t\t" << "\t\t\t\t11. Help" << endl;
            cout << "\t\t\t" << "\t\t\t\t12. Exit" << endl;
            cout << "\t\t\t" << "\t\t\t\t" << ">";
            cin >> *selectionsanta;  //inputting users selection
            if (*selectionsanta < 1 || *selectionsanta > 12) //error trap
            {
                cout << "Error! Your Selection Must be Within 1 & 11" << endl;
                *error = true;
                _getch();
                system("cls");
            }
        } while(*error == true); //looping if error occurs



        switch(*selectionsanta) //checking what the user selected
        { //opening each function relating to the users selection
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
            christmasMode(children, numberOfChildren);
            break;
        case 10:
            changePassword(username);
            break;
        case 11:
            spawnHelpScreen();
            break;
        }

    }

   //deleting pointers
    delete selectionsanta;
    delete error;

}

/*purpose: Opening the menu for Mrs Claus
arugments: Users Array, Child Array, number of Users, the number of children, users username, and the number of toys
returns: none
*/
void menuMrsClaus(User * users[MAXUSERS], int *numberOfUsers, Child * children[MAXCHILDREN], int * numberOfChildren, int (*toys)[NUMOFTOYS][2], string *username) {
     //Initializing variables
    int *selectionmrsclaus = new (nothrow) int(0);
    bool *error = new (nothrow) bool;

    while (*selectionmrsclaus != 7) { //Running the program whilst the user does not wish to exit

        do { //starting a do while loop
            *error = false; //initializing the error variable as false
            system("cls"); //clearing the screen
            cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl; //centering the menu in the screen
            //ASCII Art for mrs claus screen and displaying options
            cout << "\t\t\t\t" << "  __  __               _____ _                   __  __                  " << endl;
            cout << "\t\t\t\t" << " |  \\/  |             / ____| |                 |  \\/  |                 " << endl;
            cout << "\t\t\t\t" << " | \\  / |_ __ ___    | |    | | __ _ _   _ ___  | \\  / | ___ _ __  _   _ " << endl;
            cout << "\t\t\t\t" << " | |\\/| | \'__/ __|   | |    | |/ _` | | | / __| | |\\/| |/ _ \\ \'_ \\| | | |" << endl;
            cout << "\t\t\t\t" << " | |  | | |  \\__ \\_  | |____| | (_| | |_| \\__ \\ | |  | |  __/ | | | |_| |" << endl;
            cout << "\t\t\t\t" << " |_|  |_|_|  |___(_)  \\_____|_|\\__,_|\\__,_|___/ |_|  |_|\\___|_| |_|\\__,_|" << endl;
            cout << "\t\t\t" << "\t\t\t\t1. Add Elf" << endl;
            cout << "\t\t\t" << "\t\t\t\t2. Fire Elf" << endl;
            cout << "\t\t\t" << "\t\t\t\t3. View Elves" << endl;
            cout << "\t\t\t" << "\t\t\t\t4. Reset Elf Password" << endl;
            cout << "\t\t\t" << "\t\t\t\t5. Change Personal Password" << endl;
            cout << "\t\t\t" << "\t\t\t\t6. Help" << endl;
            cout << "\t\t\t" << "\t\t\t\t7. Exit" << endl;
            cout << "\t\t\t" << "\t\t\t\t" << ">";
            cin >> *selectionmrsclaus; //inputting users selection
            if (*selectionmrsclaus < 1 || *selectionmrsclaus > 7) //error trap
            {
                cout << "Error! Your Selection Must be Within 1 & 7" << endl;
                *error = true; //Error Code 46 means Error = true
                _getch();
                system("cls");
            }
        } while(*error == true); //looping if error occurs
        switch(*selectionmrsclaus) //checking what the user selected
        {//Opening each function relating to the users selection
        case 1:
            addElf(users, numberOfUsers);
            break;
        case 2:
            fireElf(users, numberOfUsers);
            break;
        case 3:
            viewElves(users, numberOfUsers);
            break;
        case 4:
            resetElfPassword(users, numberOfUsers);
            break;
        case 5:
            changePassword(username);
            break;
        case 6:
            spawnHelpScreen();
            break;
        }

    }

    //deleting pointers
    delete selectionmrsclaus;
    delete error;
}

/*purpose: Opening the menu for the Admin User
arugments: Users Array, Child Array, number of Users, the number of children, users username, and the number of toys
returns: none
*/
void menuAdmin(User * users[MAXUSERS], int *numberOfUsers, Child * children[MAXCHILDREN], int * numberOfChildren, int (*toys)[NUMOFTOYS][2], string *username) {
    //Initializing variables
    int *selectionadmin = new (nothrow) int(0);
    bool *error = new (nothrow) bool;

    while (*selectionadmin != 6) { //Running the program whilst the user does not wish to exit

        do { //starting a do while loop
            *error = false; //initializing the error variable as false
            system("cls"); //clearing the screen
            cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl; //centering the menu in the screen
            //ASCII Art for admin screen and displaying options
            cout << "\t\t\t\t\t" << "    ___       __          _     " << endl;
            cout << "\t\t\t\t\t" << "   /   | ____/ /___ ___  (_)___ " << endl;
            cout << "\t\t\t\t\t" << "  / /| |/ __  / __ `__ \\/ / __ \\" << endl;
            cout << "\t\t\t\t\t" << " / ___ / /_/ / / / / / / / / / /" << endl;
            cout << "\t\t\t\t\t" << "/_/  |_\\__,_/_/ /_/ /_/_/_/ /_/ " << endl;
            cout << "\t\t\t" << "\t\t\t\t1. Enter Elf Menu" << endl; //
            cout << "\t\t\t" << "\t\t\t\t2. Enter Santa Menu" << endl;
            cout << "\t\t\t" << "\t\t\t\t3. Enter Mrs Claus Menu" << endl;
            cout << "\t\t\t" << "\t\t\t\t4. Reset children" << endl;
            cout << "\t\t\t" << "\t\t\t\t5. Help" << endl;
            cout << "\t\t\t" << "\t\t\t\t6. Exit" << endl;
            cout << "\t\t\t" << "\t\t\t\t" << ">";
            cin >> *selectionadmin; //inputting users selection
            if (*selectionadmin < 1 || *selectionadmin > 6) //error trap
            {
                cout << "Error! Your Selection Must be Within 1 & 6" << endl;
                *error = true;
                _getch();
                system("cls");
            }
       } while(*error == true); //looping if error occurs
        switch(*selectionadmin) //checking what the user selected
        { //Opening each function relating to the users selection
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

    //deleting pointers
    delete selectionadmin;
    delete error;
}


 /****LOGIN SCREEN****/
int login(string *username) {
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
        cout << "\t\t\t\t\t\t" << "Enter username: ";
        getline(cin, *username);
        cout << "\t\t\t\t\t\t";
        *password = getpass("Enter Password: ", true);

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

 /****WELCOME SCREEN****/
void welcomeScreen() {
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
 /****EXIT SCREEN****/
void exitScreen() {
    //todo
    system("cls");

    welcomeScreen();
    cout<<"\n\n\n\n\n\t\t\t\t\t\t\tPress any key to exit";
}

//****MAIN FUNCTION****
int main() {


    //setupConsole();
    system("color F4");
    setScreenPosAndSize();

    srand((unsigned int)time(NULL));

    bool * helpBool = new (nothrow) bool(true);
    thread helpWatcherThread(helpWatcher, helpBool);


    int *permission = new (nothrow) int(0);
    string *username = new(nothrow) string;

    welcomeScreen();
    cout<<"\n\n\n\n\n\t\t\t\t\t\t\tPress any key to continue";
    _getch();
    system("cls");

    system("color F4");

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
    //delete[] users;
    //delete[] children;
    delete toys;
    delete numberOfUsers;
    delete numberOfChildren;
    delete helpBool;
    delete permission;
    delete username;


    return EXIT_SUCCESS;
}


/****CODE SNIPPETS****/

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
