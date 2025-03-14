#include <windows.h>

#include "GameInterface.h"

#include <iostream>
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/xchar.h>

namespace GI
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	void DisplayQuestion(const std::wstring& question)
	{
		SetConsoleTextAttribute(hConsole, 11);
		fmt::println(L"{}", question);
		SetConsoleTextAttribute(hConsole, 15);
	}

	void DisplayResult(const std::wstring& correctAnswer, const bool correct)
	{
		if (correct)
		{
			SetConsoleTextAttribute(hConsole, 10);
			fmt::print("Correct: ");
			SetConsoleTextAttribute(hConsole, 14);
			fmt::print(L"{} \n\n", correctAnswer);
			SetConsoleTextAttribute(hConsole, 15);
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 12);
			fmt::print("Incorrect: ");
			SetConsoleTextAttribute(hConsole, 14);
			fmt::print(L"{}\n\n", correctAnswer);
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

