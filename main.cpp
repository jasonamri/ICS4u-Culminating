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
#include <graphics.h>
#include <direct.h>
using namespace std;

void animations () {
     int x,y,i;
	int g=DETECT,d;
       initgraph(&g,&d,"\tc\bgi");
       cleardevice();
       x=getmaxx()/2;
       y=getmaxy()/2;
       settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
       setbkcolor(rand());
       setcolor(4);
       outtextxy(30,100,"Press");
       outtextxy(30,130,"any");
       outtextxy(30,160,"key");
       outtextxy(30,190, "to");
       outtextxy(30,220,"Quit");
       while (!kbhit())
       {
       setcolor(rand());
       for (int i=0;i<50;i++)
       circle(x,y,i );
       setcolor(rand());
       for (int j=70;j<120;j++)
       circle(x,y,j);
       setcolor(rand());
       for (int k=140;k<190;k++)
       circle(x,y,k);
       setcolor(rand());
       for (int l=210;l<230;l++)
       circle(x,y,l);
       delay(200);
       }
       getch();
       closegraph();
}

void animation2() {
     int gd = DETECT, gm;
   int x = 320, y = 240, radius;

   initgraph(&gd, &gm, "C:\\TC\\BGI");

   for ( radius = 25; radius <= 125 ; radius = radius + 20)
      circle(x, y, radius);

   getch();
   closegraph();
}

void mouseInput ()
{
     POINT coord;
     GetCursorPos(&coord);
     cout << coord.x << "," << coord.y << "\n";
}


void setScreenPosAndSize () {
     HWND consoleWindow = GetConsoleWindow();

	SetWindowPos(consoleWindow, HWND_TOP, -7, -30, 500, 500, SWP_NOZORDER);
}


void changeColor(int foreground, int background) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), foreground + background * 16);

}

int main()
{
     changeColor(5, 6);

     animations2();

     setScreenPosAndSize();

     mouseInput();

     _getch();
     return EXIT_SUCCESS;
}
