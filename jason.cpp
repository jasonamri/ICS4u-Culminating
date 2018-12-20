
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

size_t generateHash(string *username, string *password) {
     hash<string> hash_fn;
     return  hash_fn(*username+*password);
}



int main()
{
     //string /***/username= /*new (nothrow) string (*/"Santa"/*)*/;
     //string /***/password= /*new (nothrow) string (*/"hi"/*)*/;

     string *username = new string("mrsclaus");
     string *password = new string("cookies");


     cout<<generateHash(username, password);


     //cout<<login();



     //setup console inorder to handle mouse clicks
/*     HANDLE input_handle;
     input_handle = GetStdHandle(STD_INPUT_HANDLE);
     SetConsoleMode(input_handle, ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_INSERT_MODE | ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);


     setScreenPosAndSize();


*/


     //int *permission = new int;
     //*permission = login();


     //size_t *hash = new size_t(generateHash(username, password));
     //cout<<compareHash(hash, username2, password2);

     //animations2();

     //while (true)
     //cout<<clicked(100, 150, 200, 250)<<"\n"<<mouseInput().x<<" "<<mouseInput().y<<"\n";

     _getch();
     return EXIT_SUCCESS;
}
