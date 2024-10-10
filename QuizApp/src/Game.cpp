#include "Game.h"

#include <iostream>
#include "Shuffles.h"

#include "GameInterface.h"

Game::Game(std::shared_ptr<SharedResources> sharedResources) 
	: m_SharedResources(sharedResources)
{
}

void Game::Init(const std::vector<QuizCard>& cards)
{
	m_IsGameOn = true;

	auto shuffle = std::make_shared<MultiplyShuffle>(1);
	m_Quiz = std::make_unique<Quiz>(cards, shuffle);
}

void Game::Play()
{
	GI::DisplayQuestion(m_Quiz->GetCurrentQuestion());

	while (m_IsGameOn)
	{
		if (m_SharedResources->IsInputAvailable())
		{
			m_UserAnswer = m_SharedResources->GetInputNonBlocking();
			if (!m_UserAnswer.empty())
			{
				ProcessUserAnswer();

				m_Quiz->NextCard();
				GI::DisplayQuestion(m_Quiz->GetCurrentQuestion());
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		m_InputReady = false;
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::wcout << "Play stopped" << '\n';
	//GI::ClearConsole();
}

void Game::Swap()
{
	m_Quiz->Swap();
}

void Game::ChangeCaseSensitivity()
{
	m_IsCaseSensitive = !m_IsCaseSensitive;
}

void Game::UseMultiplyShuffle(int val)
{
	m_Quiz->SetShuffleClass(std::make_shared<MultiplyShuffle>(val));
}

void Game::End()
{
	m_IsGameOn = false;
}

void Game::ProcessUserAnswer() const
{
	auto userAnswer = m_UserAnswer;
	auto correctAnswer = m_Quiz->GetCurrentAnswer();
	if (!m_IsCaseSensitive)
	{
		std::transform(userAnswer.begin(), userAnswer.end(), userAnswer.begin(), tolower);
		std::transform(correctAnswer.begin(), correctAnswer.end(), correctAnswer.begin(), tolower);
	}
	if (userAnswer == correctAnswer)
	{
		GI::DisplayResult(m_Quiz->GetCurrentAnswer(), true);
	}
	else
	{
		GI::DisplayResult(m_Quiz->GetCurrentAnswer(), false);
	}
}


