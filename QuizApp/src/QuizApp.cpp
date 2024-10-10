#include "FilesHandler.h"

#include "QuizApp.h"

#include <iostream>
#include <queue>

#include "Game.h"
#include "SharedResources.h"

QuizApp::QuizApp()
	: m_sharedResources(std::make_shared<SharedResources>()),
	m_game(m_sharedResources),
	m_inputThread(&QuizApp::HandleInput, this)
{
}

QuizApp::~QuizApp()
{
	if (m_gameThread.joinable())
		m_gameThread.join();

	if (m_inputThread.joinable())
		m_inputThread.join();
}

void QuizApp::Run()
{
	while (!m_guiWindow.ShouldQuit())
	{
		if (m_guiWindow.GetSelectedFilePath() != "")
		{
			if (m_gameThread.joinable())
			{
				m_game.End();
				m_gameThread.join();
			}

			m_game.Init(extractCards(getCsvFile(m_guiWindow.GetSelectedFilePath())));
			m_gameThread = std::thread(&Game::Play, &m_game);
			m_guiWindow.ResetSelectedFilePath();

			m_guiWindow.ResetOptions();
			ShowOptions();
		}

		m_guiWindow.RenderFrame();
	}
}

void QuizApp::ShowOptions()
{
	m_guiWindow.AddCheckbox("Swap questions with answers", std::bind(&Game::Swap, &m_game));
	m_guiWindow.AddCheckbox("Enable case sensitivity", std::bind(&Game::ChangeCaseSensitivity, &m_game));
	m_guiWindow.AddIntInput({ "Repeat question", std::bind(&Game::UseMultiplyShuffle, &m_game, std::placeholders::_1), 1 });
}

void QuizApp::HandleInput()
{
	while (!m_guiWindow.ShouldQuit())
	{
		std::wstring input;
		std::getline(std::wcin, input);

		m_sharedResources->SetInput(input);
	}
}


