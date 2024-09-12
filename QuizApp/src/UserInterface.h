#pragma once

#include <string>
#include <functional>
#include "FilesHandler.h"

namespace UI
{
	void RenderFileSelector(const std::string& title, std::string& currentPath, std::string& selectedFile);
	void RenderSwapButton(std::function<void()>& swapFunction);
};