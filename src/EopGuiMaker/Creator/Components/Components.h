#pragma once

#include "imgui.h"
#include "EopGuiMaker/Creator/Components/StyleSettings.h"
#include "EopGuiMaker/Creator/UserWindow.h"

class UserWindow;

namespace EopGuiMaker
{
#define FLOAT_NOT_EQUAL(a, b) (abs((a)-(b)) < 0.0001)
#define COLOR_IS_EQUAL(a, b) ((a).x == (b).x && (a).y == (b).y && (a).z == (b).z && (a).w == (b).w)
#define IMVEC2_IS_EQUAL(a, b) ((a).x == (b).x && (a).y == (b).y)

	class GUIMAKER_API Component
	{
	public:
		Component() = default;
		~Component() = default;
		void SetPosition(ImVec2 position, float grid_spacing_x, float grid_spacing_y);
		void SetSize(ImVec2 size, float grid_spacing_x, float grid_spacing_y);
		ImVec2 Position;
		ImVec2 Size;
		virtual Component* Clone(){ return this;}
		void TextSettings()
		{
			ImGui::NewLine();
			ImGui::ColorEdit4("Text Color", &TextColor.x);
			ImGui::ShowFontSelector("Fonts");
			ImGui::NewLine();
		}
		bool IsSnappedSize = true;
		bool IsSnappedPos = true;
		ImVec4 TextColor = ImGui::GetStyle().Colors[ImGuiCol_Text];
		virtual void Draw(){}
		virtual void PropertiesWindow(){}
		UserWindow* ParentWindow;
		void DrawCopyButtons();
		void DrawSnapOptions();
		void DrawResetButtons();
		void DrawProperties();
		virtual std::string GenerateCode(){return "";}
		virtual std::string GenerateLuaCode(){return "";}
		UINT32 ActiveStyles;
		UINT64 ActiveColors;
		StyleSettings Styles;
	};

}
