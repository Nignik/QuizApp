#pragma once

#include <string>

struct QuizCard
{
	std::string question;
	std::string answer;

	QuizCard(std::string question, std::string answer) : question(std::move(question)), answer(std::move(answer)) {}
};