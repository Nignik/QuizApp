#include "UserInterface.h"

namespace fs = std::filesystem;

namespace UI
{
	void RenderFileSelector(const std::string& title, std::string& currentPath, std::string& selectedFile)
	{
		if (ImGui::Begin(title.c_str()))
		{
			if (ImGui::Button("<-"))
			{
				currentPath = fs::path(currentPath).parent_path().string();
			}
			ImGui::SameLine();
			ImGui::Text("%s", currentPath.c_str());

			for (const auto& entry : fs::directory_iterator(currentPath))
			{
				const auto& path = entry.path();
				auto filenameString = path.filename().string();

				if (entry.is_directory())
				{
					if (ImGui::Button(filenameString.c_str()))
					{
						currentPath = path.string();
					}
				}
				else if (entry.is_regular_file())
				{
					ImGui::Selectable(filenameString.c_str(), selectedFile == path.string());

					if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
					{
						selectedFile = path.string();
					}
				}
			}
		}
		ImGui::End();
	}

	void RenderSwapButton(std::function<void()>& swapFunction)
	{
		if (ImGui::Button("Swap questions with answers"))
		{
			swapFunction();
		}
	}
}


