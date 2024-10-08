#pragma once

#include <mutex>
#include <condition_variable>

#include "Quiz.h"
#include "SharedResources.h"
#include "Shuffles.h"

class Game
{
public:
	Game(std::shared_ptr<SharedResources> sharedResources);

	void Init(const std::vector<QuizCard>& cards);
	void Play();
	void Swap();
	void ChangeCaseSensitivity();
	void UseMultiplyShuffle(int val);
	void End();

	void ProcessUserAnswer() const;

private:
	std::shared_ptr<SharedResources> m_SharedResources;

	std::unique_ptr<Quiz> m_Quiz;
	std::wstring m_UserAnswer;

	bool m_IsGameOn = false;
	bool m_IsCaseSensitive = false;
	bool m_InputReady = false;

	std::mutex m_Mutex;
	std::condition_variable m_CondVar;
	std::wstring m_UserInput;
};