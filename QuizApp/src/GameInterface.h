#pragma once

#include <string>

namespace GI
{
	void DisplayQuestion(const std::wstring& question);
	void DisplayResult(const std::wstring& correctAnswer, const bool correct = true);
	void ClearConsole();
}