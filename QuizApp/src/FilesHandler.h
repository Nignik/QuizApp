#pragma once

#include <windows.h>
#include <string>
#include "CsvHandler.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <imgui.h>

#include "CardTypes.h"

namespace fs = std::filesystem;

inline std::ifstream getCsvFile(const std::string& filePath)
{
	std::ifstream file(filePath);

	if (!file)
	{
		std::cerr << "Incorrect filename" << "\nTry again." << std::endl;
	}

	return file;
}

inline std::vector<QuizCard> extractCards(std::ifstream file)
{
	std::vector<QuizCard> cards;
	for (auto& row : CSVRange(file))
	{
		cards.emplace_back(std::string(row[0]), std::string(row[1]));
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
		std::cerr << "Filesystem error: " << e.what() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "General error: " << e.what() << std::endl;
	}

	return files;
}