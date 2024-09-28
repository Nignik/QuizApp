#include "FileSelector.h"

#include <imgui.h>

FileSelector::FileSelector(std::string&& defaultPath)
	: m_defaultPath(defaultPath),
	m_path(defaultPath)
{
}

void FileSelector::Render()
{
	if (ImGui::Begin("File Selector"))
	{
		if (ImGui::Button("<-"))
		{
			m_path = m_path.parent_path();
		}
		ImGui::SameLine();
		ImGui::Text("%s", m_path.c_str());

		for (const auto& entry : fs::directory_iterator(m_path))
		{
			const auto& path = entry.path();
			auto filename = path.filename().string();

			if (entry.is_directory())
			{
				if (ImGui::Button(filename.c_str()))
				{
					m_path = path;
				}
			}
			else if (entry.is_regular_file())
			{
				ImGui::Selectable(filename.c_str(), m_selectedFilePath == path);

				if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
				{
					m_selectedFilePath = path;
				}
			}
		}
	}
	ImGui::End();
}

fs::path FileSelector::GetSelectedFilePath()
{
	return m_selectedFilePath;
}

void FileSelector::ResetSelectedFilePath()
{
	m_selectedFilePath = "";
}

