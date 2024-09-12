#pragma once

#include <string>

namespace GI
{
	void DisplayQuestion(const std::string& question);
	void DisplayResult(const std::string& correctAnswer, const bool correct = true);
	void ClearConsole();
}