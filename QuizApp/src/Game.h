#pragma once

#include <mutex>
#include <condition_variable>

#include "Quiz.h"
#include "SharedResources.h"

class Game
{
public:
	Game(SharedResources* sharedResources);
	void Init(const std::vector<QuizCard>& cards);
	void Play();
	void Swap();
	void End();
	void ProcessUserAnswer() const;

private:
	std::unique_ptr<SharedResources> m_SharedResources;

	std::unique_ptr<Quiz> m_Quiz;
	std::string m_UserAnswer;

	bool m_IsGameOn = false;
	bool m_InputReady = false;

	std::mutex m_Mutex;
	std::condition_variable m_CondVar;
	std::string m_UserInput;
};