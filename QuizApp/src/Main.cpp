#include <iostream>
#include <windows.h>
#include <fcntl.h>
#include <io.h>

#include "QuizApp.h"

int main()
{
	SetConsoleOutputCP(CP_UTF8);

	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stdin), _O_WTEXT);

	try
	{
		QuizApp app;
		std::wcout << "App started" << '\n';
		app.Run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "An error occurred: " << e.what() << "\n";
		return -1;
	}
	return 0;
}