#pragma once

#include <string>

struct QuizCard
{
	std::wstring question;
	std::wstring answer;

	QuizCard(std::wstring question, std::wstring answer) : question(std::move(question)), answer(std::move(answer)) {}
};