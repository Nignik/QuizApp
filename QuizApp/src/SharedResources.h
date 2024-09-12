#pragma once
#include <mutex>
#include <condition_variable>
#include <queue>
#include <string>

class SharedResources
{
public:
	std::mutex mtx;
	std::queue<std::string> userInputQueue;
	bool inputReady = false;

	void SetInput(const std::string& input)
	{
		std::lock_guard<std::mutex> lock(mtx);
		userInputQueue.push(input);
	}

	// Check if input is available
	bool IsInputAvailable()
	{
		std::lock_guard<std::mutex> lock(mtx);
		return !userInputQueue.empty();
	}

	// Get input without waiting
	std::string GetInputNonBlocking()
	{
		std::lock_guard<std::mutex> lock(mtx);
		if (userInputQueue.empty())
		{
			return ""; // No input available
		}
		std::string input = userInputQueue.front();
		userInputQueue.pop();
		return input;
	}
};