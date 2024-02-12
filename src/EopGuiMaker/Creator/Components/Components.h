#pragma once

#include "imgui.h"
#include "EopGuiMaker/Creator/Components/StyleSettings.h"
#include "EopGuiMaker/Creator/UserWindow.h"
#include "EopGuiMaker/ImGui/imgui_stdlib.h"


namespace EopGuiMaker
{
	class ChildComponent;
	class UserWindow;
#define FLOAT_NOT_EQUAL(a, b) (abs((a)-(b)) < 0.0001)
#define COLOR_IS_EQUAL(a, b) ((a).x == (b).x && (a).y == (b).y && (a).z == (b).z && (a).w == (b).w)
#define IMVEC2_IS_EQUAL(a, b) ((a).x == (b).x && (a).y == (b).y)
#define IS_IN_RECT(a,b,c) ((a).x > (b).x && (a).x < (c).x && (a).y > (b).y && (a).y < (c).y))
	

	enum ComponentTypes {
		ComponentType_Child,
		ComponentType_Button,
		ComponentType_Count
	};

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
		void SetStyles();
		std::string Label;
		void PopStyles() const;
		ImVec2 ScreenSpacePos;
		ImVec2 ScreenSpacePosMax;
		ChildComponent* ParentChild;
		int Flags = 0;
		virtual std::string GenerateCode(){return "";}
		virtual std::string GenerateLuaCode(){return "";}
		UINT32 ActiveStyles;
		UINT64 ActiveColors;
		StyleSettings Styles;
		int Type;
	};

	class GUIMAKER_API ChildComponent : public Component
	{
		public:
		ChildComponent(const char* label, const ImVec2 size = {0,0}, const ImVec2 position = {0,0})
		{
			Size = size;
			Label = label;
			Position = position;
			ActiveStyles = UINT32_MAX;
			ActiveColors = UINT64_MAX;
			Styles.Colors[ImGuiCol_ChildBg] = { 255.0f, 255.0f,255.0f, 150.0f };
			Styles.EditedColors |= 1 << ImGuiCol_ChildBg;
			Type = ComponentType_Child;

		}
		~ChildComponent();
		
		void PropertiesWindow() override;
		
		std::string GenerateCode() override;
		std::string GenerateLuaCode() override;
		void Draw() override;
		void PushComponent(Component* component);
		void PopComponent(const Component* component);
		std::vector<ChildComponent*> Children;
		
		int WindowFlags;
		void GetChildFlags();

	private:
		std::vector<Component*> m_Components;
			
	};



}
