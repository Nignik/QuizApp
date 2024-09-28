#include "GuiWindow.h"

#include <iostream>
#include <queue>

GuiWindow::GuiWindow()
{
}

void GuiWindow::RenderFrame()
{
	m_renderer.StartFrame();

	RenderOptions();
	RenderFileSelectors();

	m_renderer.RenderFrame();
}

bool GuiWindow::ShouldQuit()
{
	return !m_renderer.IsRunning();
}

void GuiWindow::ResetOptions()
{
	m_checkboxes.clear();
}

void GuiWindow::RenderFileSelectors()
{
	m_fileSelector.Render();
}

void GuiWindow::RenderOptions()
{
	ImGui::Begin("Options");
	for (auto& checkbox : m_checkboxes)
	{
		if (ImGui::Checkbox(checkbox.name.c_str(), &checkbox.val))
		{
			checkbox.func();
		}
	}
	ImGui::End();
}

void GuiWindow::AddCheckbox(Checkbox&& newCheckbox)
{
	m_checkboxes.push_back(newCheckbox);
}

void GuiWindow::AddCheckbox(std::string&& name, std::function<void()> func)
{
	m_checkboxes.emplace_back(name, func);
}

void GuiWindow::CreateSelector(FileSelector&& newFileSelector)
{
	m_fileSelector = std::move(newFileSelector);
}

void GuiWindow::CreateSelector(std::string&& defaultPath)
{
	m_fileSelector = FileSelector(std::move(defaultPath));
}

fs::path GuiWindow::GetSelectedFilePath()
{
	return m_fileSelector.GetSelectedFilePath();
}

void GuiWindow::ResetSelectedFilePath()
{
	m_fileSelector.ResetSelectedFilePath();
}