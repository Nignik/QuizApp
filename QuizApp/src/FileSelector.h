#pragma once

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

class FileSelector
{
public:
	FileSelector(std::string&& defaultPath);

	void Render();

	fs::path GetSelectedFilePath();
	void ResetSelectedFilePath();

private:
	fs::path m_defaultPath;
	fs::path m_path;
	fs::path m_selectedFilePath;
};