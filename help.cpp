/*Culminating Task Main Function*/

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

//Purpose: change screen size and position
//arguments: none
//returns: nothing!
void setScreenPosAndSize () {
    HWND consoleWindow = GetConsoleWindow();
    SetWindowPos(consoleWindow, HWND_TOP, -7, -30, 1080, 720, SWP_NOZORDER);
}


int main(){

     system("COLOR F0");
     setScreenPosAndSize();

     int *selection = new (nothrow) int;
     bool *error = new (nothrow) bool;

     do {
          do {
               *error = false;
               system("cls");
               cout << endl << "\t\t\t\t\t" << "ooooo   ooooo           oooo             " << endl;
               cout << "\t\t\t\t\t" << "`888\'   `888\'           `888             " << endl;
               cout << "\t\t\t\t\t" << " 888     888   .ooooo.   888  oo.ooooo.  " << endl;
               cout << "\t\t\t\t\t" << " 888ooooo888  d88\' `88b  888   888\' `88b " << endl;
               cout << "\t\t\t\t\t" << " 888     888  888ooo888  888   888   888 " << endl;
               cout << "\t\t\t\t\t" << " 888     888  888    .o  888   888   888 " << endl;
               cout << "\t\t\t\t\t" << "o888o   o888o `Y8bod8P\' o888o  888bod8P\' " << endl;
               cout << "\t\t\t\t\t" << "                               888       " << endl;
               cout << "\t\t\t\t\t" << "                              o888o      " << endl << endl;
               cout << "\t\t\t" << "\t\t" << "Please Select a Function which you would like Help With" << endl << endl;
               cout << "\t\t\t" << "\t\t" << "1. Add New Child Function" << endl;
               cout << "\t\t\t" << "\t\t" << "2. View/Edit Child Function" << endl;
               cout << "\t\t\t" << "\t\t" << "3. Update Niceness Rating Function" << endl;
               cout << "\t\t\t" << "\t\t" << "4. Workshop Menu Function" << endl;
               cout << "\t\t\t" << "\t\t" << "5. Change Password Function" << endl;
               cout << "\t\t\t" << "\t\t" << "6. Add Elf Function" << endl;
               cout << "\t\t\t" << "\t\t" << "7. Fire Elf Function" << endl;
               cout << "\t\t\t" << "\t\t" << "8. Reset Elf Password Function" << endl;
               cout << "\t\t\t" << "\t\t" << "9. Change Personal Password Function" << endl;
               cout << "\t\t\t" << "\t\t" << "10. Assign Gifts Function" << endl;
               cout << "\t\t\t" << "\t\t" << "11. Auto Assign Gifts to All Function" << endl;
               cout << "\t\t\t" << "\t\t" << "12. Purge 18+ Children Function" << endl;
               cout << "\t\t\t" << "\t\t" << "13. View Elves/Assign Toy to Elf Function" << endl;
               cout << "\t\t\t" << "\t\t" << "14. Workshop Progress Function" << endl;
               cout << "\t\t\t" << "\t\t" << "15. Enter Elf Menu Function" << endl;
               cout << "\t\t\t" << "\t\t" << "16. Enter Santa Menu Function" << endl;
               cout << "\t\t\t" << "\t\t" << "17. Enter Mrs Claus Menu Function" << endl;
               cout << "\t\t\t" << "\t\t" << "18. Reset to Default Function" << endl;
               cout << "\t\t\t" << "\t\t" << "19. Exit Function" << endl;
               cout << "\t\t\t" << "\t\t" << "20. Arrow Keys Function" << endl;
               cout << "\t\t\t" << "\t\t" << ">";
               cin >> *selection;
							 cout << endl << endl << endl;
               if (*selection < 1 || *selection > 20)
               {
                    cout << "Error! Your Selection Must be Within 1 & 20" << endl;
                    *error = true; //Error Code 46 means Error = true
                    _getch();
                    system("cls");
               }
          } while(*error == true);

          switch(*selection)
          {
          case 1:
               cout << "The add new child function utilizes a very user friendly interface which quickly asks for the new childs name, birthday, gender, home address and siblings. Through the input of this information the child will then be saved into the program.";
               break;
          case 2:
               cout << "The view\\edit child function will open an interface which gives the user the ability to view the childs information and edit the home address, number of siblings, cookie rating and niceness rating of the child in a very easy manner.";
               break;
          case 3:
               cout << "The niceness rating function allows the user to easily change the niceness rating of a child in a very efficient manner. Through the utilization of this function the user can update the niceness of a child by simply pressing the left and right key and can navigate through different users with the up and down keys";
               break;
          case 4:
               cout << "The workshop menu function is where the elves will go to get their newly assigned toy, the last toy they made and the total amount of toys they have made, and the toys that are still needed. As well the user can use the arrow keys in order to increase their total number of toys made.";
               break;
          case 5:
               cout << "This is the function where the user has the ability to change their personal password. It will open up a screen which will ask them for their new password and confirm this password.";
               break;
          case 6:
               cout << "This function is where Mrs. Claus has the ability to add an elf. She will need to input a hire date, the elfs username and their password. This makes the adding process of an elf much more efficient.";
               break;
          case 7:
               cout << "This function is where Mrs. Claus removes a fired elf from the system thus allowing another to take their username or the toy they still need to create.";
               break;
          case 8:
               cout << "This function is responsible for the resetting of an elves password if they have forgotten their own and are unable to login to the program. ";
               break;
          case 9:
               cout << "This function is where Mrs. Claus is capable of changing her own password for her account.";
               break;
          case 10:
               cout << "This function randomly assigns gifts to each child. In addition it can be used to choose which gift each child is getting by Santa himself. Therefore allowing Santa to make sure that no two siblings get the same gift.";
               break;
          case 11:
               cout << "This function automatically assigns all gifts to all children with the press of one button.";
               break;
          case 12:
               cout << "This function automatically removes all children from the system who are over the age of 18.";
               break;
          case 13:
               cout << "This function allows Santa to see every elf under his dominion and modify which toys they are making to specialize the labour force.";
               break;
          case 14:
               cout << "This function allows Santa to see the total number of toys made and the total percent of toys made in total.";
               break;
          case 15:
               cout << "This function allows an admin to enter the elf menu";
               break;
          case 16:
               cout << "This function allows an admin to enter the Santa menu";
               break;
          case 17:
               cout << "This function allows an admin to enter the Mrs. Claus Menu";
               break;
          case 18:
               cout << "This function allows the admin to reset all of the childrens ratings back to their default values";
               break;
          case 19:
               cout << "This function allows the user to exit the program";
               break;
          case 20:
               cout << "The arrow keys are used to control a few parts of the function but also allow the escape key to be used to close the program.";
               break;
          }
					cout << endl << endl << "Press any key to continue or escape to leave the help screen...> ";

     } while(arrowKeys(true) != 6);

     delete selection;
     delete error;

}
