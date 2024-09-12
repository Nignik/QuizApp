#include "Quiz.h"

Quiz::Quiz(std::vector<QuizCard> deck, std::function<void(std::vector<QuizCard>&)> shuffleFunction) :
	m_Shuffle(std::move(shuffleFunction)), m_Deck(std::move(deck))
{
	ShuffleDeck();
	m_CurrentCard = m_Deck.begin();
}

std::string& Quiz::GetCurrentQuestion() const
{
	return m_CurrentCard->question;
}

std::string& Quiz::GetCurrentAnswer() const
{
	return m_CurrentCard->answer;
}

void Quiz::NextCard()
{
	++m_CurrentCard;

	if (m_CurrentCard == m_Deck.end())
	{
		ShuffleDeck();
		m_CurrentCard = m_Deck.begin();
	}
}

void Quiz::ShuffleDeck()
{
	m_Shuffle(m_Deck);
}

void Quiz::Swap()
{
	std::vector<QuizCard> oldDeck = m_Deck;
	std::vector<QuizCard> newDeck;
	for (auto& card : oldDeck)
	{
		newDeck.push_back(QuizCard(card.answer, card.question));
	}

	m_Deck = newDeck;
	m_CurrentCard = m_Deck.begin();
}

