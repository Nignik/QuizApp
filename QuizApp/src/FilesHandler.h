#pragma once

#include <windows.h>

#include <string>
#include "CsvHandler.h"
#include <fstream>
#include <filesystem>
#include <iostream>

#include "QuizUtils.h"
#include "CardTypes.h"

namespace fs = std::filesystem;

inline std::ifstream getCsvFile(const std::string& filePath)
{
	std::ifstream file(filePath);

	if (!file)
	{
		std::wcerr << "Incorrect filename" << "\nTry again." << std::endl;
	}

	return file;
}
inline std::wifstream getCsvFile(const fs::path& filePath)
{
	std::wifstream file(filePath);
	//file.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));

	if (!file)
	{
		std::wcerr << "Incorrect filename" << "\nTry again." << std::endl;
	}

	return file;
}

inline std::vector<QuizCard> extractCards(std::wifstream file)
{
	std::vector<QuizCard> cards;
	for (auto& row : CSVRange(file))
	{
		std::wstring s1 = std::wstring(row[0]), s2 = std::wstring(row[1]);
		ltrim(s1); ltrim(s2);
		rtrim(s1); rtrim(s2);
		cards.emplace_back(s1, s2);
	}

	return cards;
}

inline std::vector<std::string> getFolderContent(const std::string& folderPath)
{
	std::vector<std::string> files;

	try
	{
		if (fs::is_directory(folderPath))
		{
			for (const auto& entry : fs::directory_iterator(folderPath))
			{
				files.push_back(entry.path().filename().string());
			}
		}
		else
		{
			std::cerr << "Error: Specified path is not a directory." << std::endl;
		}
	}
	catch (const fs::filesystem_error& e)
	{
		std::wcerr << "Filesystem error: " << e.what() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::wcerr << "General error: " << e.what() << std::endl;
	}

	return files;
}