#pragma once

#include "Components.h"

namespace EopGuiMaker
{
	class GUIMAKER_API ButtonComponent : public Component
	{
		public:
		ButtonComponent(const std::string& label, const ImVec2 size, const std::string& text)
		{
			Size = size;
			Position = {0,0};
			Label = label;
			Text = text;

			ActiveStyles  = 
			1 << ImGuiStyleVar_ButtonTextAlign
			| 1 << ImGuiStyleVar_FramePadding
			| 1 << ImGuiStyleVar_FrameRounding
			| 1 << ImGuiStyleVar_FrameBorderSize;

			ActiveColors = 
			1 << ImGuiCol_Button
			| 1 << ImGuiCol_ButtonHovered
			| 1 << ImGuiCol_ButtonActive
			| 1 << ImGuiCol_Text
			| 1 << ImGuiCol_Border
			| 1 << ImGuiCol_BorderShadow;
			Type = ComponentType_Button;
		}
		ButtonComponent* Clone() override;
		void PropertiesWindow() override;
		std::string Text;
		
		std::string GenerateCode() override;
		std::string GenerateLuaCode() override;
		void Draw() override;
	};
}