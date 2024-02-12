#pragma once

#include "Components.h"

namespace EopGuiMaker
{
	class GUIMAKER_API ButtonComponent : public Component
	{
		public:
		ButtonComponent(const char* label, const ImVec2 size, const ImVec2 position)
			: Label(label)
		{
			Size = size;
			Position = position;

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
		}
		ButtonComponent* Clone() override;
		void PropertiesWindow() override;

		std::string Label;
		std::string GenerateCode() override;
		std::string GenerateLuaCode() override;
		void Draw() override;
	};
}