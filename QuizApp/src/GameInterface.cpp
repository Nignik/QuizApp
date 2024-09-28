#include <windows.h>

#include "GameInterface.h"

#include <iostream>


namespace GI
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	void DisplayQuestion(const std::wstring& question)
	{
		SetConsoleTextAttribute(hConsole, 11);
		std::wcout << question << std::endl;
		SetConsoleTextAttribute(hConsole, 15);
	}

	void DisplayResult(const std::wstring& correctAnswer, const bool correct)
	{
		if (correct)
		{
			SetConsoleTextAttribute(hConsole, 10);
			std::wcout << "Correct: ";
			SetConsoleTextAttribute(hConsole, 14);
			std::wcout << correctAnswer << "\n\n";
			SetConsoleTextAttribute(hConsole, 15);
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 12);
			std::wcout << "Incorrect: ";
			SetConsoleTextAttribute(hConsole, 14);
			std::wcout << correctAnswer << "\n\n";
			SetConsoleTextAttribute(hConsole, 15);
		}
	}

	void ClearConsole()
	{
		constexpr COORD topLeft = { 0, 0 };
		DWORD written;
		CONSOLE_SCREEN_BUFFER_INFO info;

		if (!GetConsoleScreenBufferInfo(hConsole, &info))
		{
			std::cerr << "Something went wrong with clearing the console!!!" << std::endl;
		}
		const DWORD cells = info.dwSize.X * info.dwSize.Y;

		FillConsoleOutputCharacter(hConsole, ' ', cells, topLeft, &written);
		FillConsoleOutputAttribute(hConsole, info.wAttributes, cells, topLeft, &written);
		SetConsoleCursorPosition(hConsole, topLeft);
	}
}

