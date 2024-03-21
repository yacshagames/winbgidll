#pragma once
#include <Windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

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

void clrscr() {

	HANDLE hStdout;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	cls(hStdout);
}

// Genera un aleatorio desde 0 hasta nRangoMayor
int random(int nRangoMayor) {
	return rand() % (nRangoMayor+1);
}

bool RedirectConsoleIO()
{
	bool result = true;
	FILE* fp;

	// Redirect STDIN if the console has an input handle
	if (GetStdHandle(STD_INPUT_HANDLE) != INVALID_HANDLE_VALUE)
		if (freopen_s(&fp, "CONIN$", "r", stdin) != 0)
			result = false;
		else
			setvbuf(stdin, NULL, _IONBF, 0);

	// Redirect STDOUT if the console has an output handle
	if (GetStdHandle(STD_OUTPUT_HANDLE) != INVALID_HANDLE_VALUE)
		if (freopen_s(&fp, "CONOUT$", "w", stdout) != 0)
			result = false;
		else
			setvbuf(stdout, NULL, _IONBF, 0);

	// Redirect STDERR if the console has an error handle
	if (GetStdHandle(STD_ERROR_HANDLE) != INVALID_HANDLE_VALUE)
		if (freopen_s(&fp, "CONOUT$", "w", stderr) != 0)
			result = false;
		else
			setvbuf(stderr, NULL, _IONBF, 0);

	// Make C++ standard streams point to console as well.
	std::ios::sync_with_stdio(true);

	// Clear the error state for each of the C++ standard streams.
	std::wcout.clear();
	std::cout.clear();
	std::wcerr.clear();
	std::cerr.clear();
	std::wcin.clear();
	std::cin.clear();

	return result;
}

bool ReleaseConsole()
{
	bool result = true;
	FILE* fp;

	// Just to be safe, redirect standard IO to NUL before releasing.

	// Redirect STDIN to NUL
	if (freopen_s(&fp, "NUL:", "r", stdin) != 0)
		result = false;
	else
		setvbuf(stdin, NULL, _IONBF, 0);

	// Redirect STDOUT to NUL
	if (freopen_s(&fp, "NUL:", "w", stdout) != 0)
		result = false;
	else
		setvbuf(stdout, NULL, _IONBF, 0);

	// Redirect STDERR to NUL
	if (freopen_s(&fp, "NUL:", "w", stderr) != 0)
		result = false;
	else
		setvbuf(stderr, NULL, _IONBF, 0);

	// Detach from console
	if (!FreeConsole())
		result = false;

	return result;
}

void AdjustConsoleBuffer(int16_t minLength)
{
	// Set the screen buffer to be big enough to scroll some text
	CONSOLE_SCREEN_BUFFER_INFO conInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &conInfo);
	if (conInfo.dwSize.Y < minLength)
		conInfo.dwSize.Y = minLength;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), conInfo.dwSize);
}

bool CreateNewConsole(int16_t minLength)
{
	bool result = false;

	// Release any current console and redirect IO to NUL
	ReleaseConsole();

	// Attempt to create new console
	if (AllocConsole())
	{
		AdjustConsoleBuffer(minLength);
		result = RedirectConsoleIO();
	}

	return result;
}