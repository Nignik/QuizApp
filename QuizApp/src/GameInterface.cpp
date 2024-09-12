#include "GameInterface.h"

#include <iostream>
#include <windows.h>


namespace GI
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	void DisplayQuestion(const std::string& question)
	{
		SetConsoleTextAttribute(hConsole, 11);
		std::cout << question << std::endl;
		SetConsoleTextAttribute(hConsole, 15);
	}

	void DisplayResult(const std::string& correctAnswer, const bool correct)
	{
		if (correct)
		{
			SetConsoleTextAttribute(hConsole, 10);
			std::cout << "Correct: ";
			SetConsoleTextAttribute(hConsole, 14);
			std::cout << correctAnswer << "\n\n";
			SetConsoleTextAttribute(hConsole, 15);
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 12);
			std::cout << "Incorrect: ";
			SetConsoleTextAttribute(hConsole, 14);
			std::cout << correctAnswer << "\n\n";
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

