#pragma once

#include <random>
#include <vector>
#include <string>
#include <functional>

#include "CardTypes.h"
#include "Shuffles.h"

class Quiz
{
public:
	Quiz(std::vector<QuizCard> deck, std::shared_ptr<ShuffleType> shuffleStrategy);

	[[nodiscard]] std::wstring& GetCurrentQuestion() const;
	[[nodiscard]] std::wstring& GetCurrentAnswer() const;

	void NextCard();
	void ShuffleDeck();
	void Swap();

	void SetShuffleClass(std::shared_ptr<ShuffleType> newStrategy);

private:
	std::shared_ptr<ShuffleType> m_shuffle;
	std::vector<QuizCard> m_deckArchetype;
	std::vector<QuizCard> m_deck;
	std::vector<QuizCard>::iterator m_currentCard;
};