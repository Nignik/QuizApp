#pragma once

#include "FileSelector.h"

#include <memory>
#include <filesystem>
#include <functional>

#include "Renderer.h"

namespace fs = std::filesystem;

struct Checkbox
{
	std::string name;
	std::function<void()> func;

	bool val = false;
};

struct IntInput
{
	std::string name;
	std::function<void(int)> func;

	int val = 0;
};

class GuiWindow
{
public:
	GuiWindow();

	void RenderFrame();
	bool ShouldQuit();

	void ResetOptions();

	fs::path GetSelectedFilePath();
	void ResetSelectedFilePath();

	void AddCheckbox(Checkbox&& newCheckbox);
	void AddCheckbox(std::string&& name, std::function<void()> func);

	void AddIntInput(IntInput&& newIntInput);

	void CreateSelector(FileSelector&& newFileSelector);
	void CreateSelector(std::string&& defaultPath);

private:
	Renderer m_renderer;

	std::vector<IntInput> m_intInputs;
	std::vector<Checkbox> m_checkboxes;
	FileSelector m_fileSelector = FileSelector("C:/");

	std::shared_ptr<bool> x = std::make_shared<bool>(false), y = std::make_shared<bool>(false);

	void RenderFileSelectors();
	void RenderOptions();
};