#pragma once
#include <Windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include <time.h>

// Developed by Alejandro Caro
// https://stackoverflow.com/a/75297939/8486034
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// Developed by Microsoft
// https://learn.microsoft.com/en-us/windows/console/clearing-the-screen
void cls(HANDLE hConsole)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	SMALL_RECT scrollRect;
	COORD scrollTarget;
	CHAR_INFO fill;

	// Get the number of character cells in the current buffer.
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		return;
	}

	// Scroll the rectangle of the entire buffer.
	scrollRect.Left = 0;
	scrollRect.Top = 0;
	scrollRect.Right = csbi.dwSize.X;
	scrollRect.Bottom = csbi.dwSize.Y;

	// Scroll it upwards off the top of the buffer with a magnitude of the entire height.
	scrollTarget.X = 0;
	scrollTarget.Y = (SHORT)(0 - csbi.dwSize.Y);

	// Fill with empty spaces with the buffer's default text attribute.
	fill.Char.UnicodeChar = TEXT(' ');
	fill.Attributes = csbi.wAttributes;

	// Do the scroll
	ScrollConsoleScreenBuffer(hConsole, &scrollRect, NULL, scrollTarget, &fill);

	// Move the cursor to the top left corner too.
	csbi.dwCursorPosition.X = 0;
	csbi.dwCursorPosition.Y = 0;

	SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}

// Developed by Yacsha
void clrscr() {

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	cls(hStdout);
}

// Developed by Yacsha
// Generates a random from 0 to randomMax
int random(int randomMax) {
	return rand() % (randomMax +1);
}

// Developed by Yacsha
// Start the seed to generate random numbers. Used with the random function
void randomize() {
	srand((unsigned int)time(0));
}

// Developed by Alejandro Caro
// https://stackoverflow.com/a/75297939/8486034
int wherex(){
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.X;
}

// Developed by Alejandro Caro
// https://stackoverflow.com/a/75297939/8486034
int wherey(){
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.Y;
}

// Developed by vegaseat
// https://www.daniweb.com/programming/software-development/code/216345/add-a-little-color-to-your-console-text
void textcolor(int color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color); // Console font color
}

// Developed by helloacm
// https://helloacm.com/modern-getch-implementation-on-windows-cc/
char cgetch() {

	DWORD mode, cc;
	HANDLE h = GetStdHandle(STD_INPUT_HANDLE);

	if (h == NULL) {
		return 0; // console not found
	}

	GetConsoleMode(h, &mode);
	SetConsoleMode(h, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));
	TCHAR c = 0;
	ReadConsole(h, &c, 1, &cc, NULL);
	SetConsoleMode(h, mode);
	return c;
}

// Developed by CodeMonkey
// https://cboard.cprogramming.com/cplusplus-programming/13937-kbhit-portability.html
bool ckbhit(){

	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD ip;//Holds keyboard event data
	DWORD dwResult;

	ReadConsoleInput(hIn, &ip, 1, &dwResult);
	if (ip.EventType == KEY_EVENT)
		return true;

	return false;
}