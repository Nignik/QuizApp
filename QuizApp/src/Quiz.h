#pragma once

#include <random>
#include <vector>
#include <string>
#include <functional>
#include "CardTypes.h"

class Quiz
{
public:
	Quiz(std::vector<QuizCard> deck, std::function<void(std::vector<QuizCard>&)> shuffleFunction);

	[[nodiscard]] std::string& GetCurrentQuestion() const;
	[[nodiscard]] std::string& GetCurrentAnswer() const;

	void NextCard();
	void ShuffleDeck();
	void Swap();

private:
	std::function<void(std::vector<QuizCard>&)> m_Shuffle;

	std::vector<QuizCard> m_Deck;
	std::vector<QuizCard>::iterator m_CurrentCard;
};