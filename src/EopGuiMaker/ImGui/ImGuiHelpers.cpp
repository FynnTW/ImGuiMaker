#include "gmpch.h"
#include "ImGuiHelpers.h"
#include "ImGuiFileDialog.h"
#include "Creator/Components/Components.h"

namespace EopGuiMaker {
	
	bool ADD_FONT_WINDOW = false;

	void FontManager()
	{
		ImGui::Begin("Font Manager");
		static std::string font_name = "Font";
		static float font_size = 16.0f;
		if (ADD_FONT_WINDOW)
		{
			ImGui::InputText("Font Name", &font_name);
			ImGui::InputFloat("Font Size", &font_size);
			if (ImGui::Button("Browse"))
			{
				IGFD::FileDialogConfig config;
				config.path = ".";
				ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".ttf", config);
			}
			// display
			if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) 
			{
			    if (ImGuiFileDialog::Instance()->IsOk()) { // action if OK
				    const std::string file_path_name = ImGuiFileDialog::Instance()->GetFilePathName();
				    const std::string file_path = ImGuiFileDialog::Instance()->GetCurrentPath();
				    const auto add_font = new AddFont();
					add_font->FontName = font_name;
					add_font->FontPath = file_path_name;
					add_font->FontSize = font_size;
					FONT_QUEUE.push_back(add_font);
			    }
			    ADD_FONT_WINDOW = false;
			    // close
			    ImGuiFileDialog::Instance()->Close();
			}
		}
		else
		{
			if (ImGui::Button("Add Font"))
			{
				ADD_FONT_WINDOW = true;
			}
			if (ImGui::BeginListBox("Fonts"))
			{
				for (auto& [font_name, font] : FONTS)
				{
					if (ImGui::Selectable(font_name.c_str()))
					{
						//
					}
				}
				ImGui::EndListBox();
			}
		}
		ImGui::End();
	}
}

