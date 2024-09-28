#pragma once

#include "GuiWindow.h"
#include "Game.h"


class QuizApp
{
public:
	QuizApp();
	~QuizApp();

	void Run();

	void ShowOptions();

private:
	GuiWindow m_guiWindow;
	std::shared_ptr<SharedResources> m_sharedResources;
	Game m_game;
	std::thread m_gameThread;

	std::thread m_inputThread;

	void HandleInput();
};

