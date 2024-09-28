#pragma once

#include <mutex>
#include <condition_variable>
#include <queue>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

class SharedResources
{
public:
	std::mutex mtx;
	fs::path selectedFilePath;
	std::queue<std::wstring> userInputQueue;
	bool inputReady = false;

	void SetInput(const std::wstring& input)
	{
		std::lock_guard<std::mutex> lock(mtx);
		userInputQueue.push(input);
	}

	fs::path GetSelectedFilePath()
	{
		std::lock_guard<std::mutex> lock(mtx);
		return selectedFilePath;
	}

	bool IsInputAvailable()
	{
		std::lock_guard<std::mutex> lock(mtx);
		return !userInputQueue.empty();
	}

	std::wstring GetInputNonBlocking()
	{
		std::lock_guard<std::mutex> lock(mtx);
		if (userInputQueue.empty())
		{
			return L"";
		}
		std::wstring input = userInputQueue.front();
		userInputQueue.pop();
		return input;
	}
};