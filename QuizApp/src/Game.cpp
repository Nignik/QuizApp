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

	std::function passFunction = shuffleRandom<QuizCard>;
	m_Quiz = std::make_unique<Quiz>(cards, passFunction);
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

void Game::End()
{
	m_IsGameOn = false;
}

void Game::ProcessUserAnswer() const
{
	if (m_UserAnswer == m_Quiz->GetCurrentAnswer())
	{
		GI::DisplayResult(m_Quiz->GetCurrentAnswer(), true);
	}
	else
	{
		GI::DisplayResult(m_Quiz->GetCurrentAnswer(), false);
	}
}


