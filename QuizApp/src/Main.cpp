#include <iostream>
#include <windows.h>
#include <fmt/core.h>

#include "QuizApp.h"

int main()
{
	try
	{
		QuizApp app;
		fmt::println("App started");
		app.Run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "An error occurred: " << e.what() << "\n";
		return -1;
	}
	return 0;
}