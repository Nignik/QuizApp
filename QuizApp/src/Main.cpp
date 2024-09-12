#include <iostream>
#include <windows.h>

#include "QuizApp.h"

int main()
{
	SetConsoleOutputCP(CP_UTF8);

	try
	{
		QuizApp app;
		std::cout << "App started" << '\n';
		app.Run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "An error occurred: " << e.what() << "\n";
		return -1;
	}
	return 0;
}