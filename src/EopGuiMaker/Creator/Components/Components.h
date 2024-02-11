#pragma once

#include "imgui.h"
#include "EopGuiMaker/Creator/UserWindow.h"

namespace EopGuiMaker
{

	class GUIMAKER_API Component
	{
	public:
		Component() = default;
		~Component() = default;
		void SetPosition(const ImVec2 position, const float grid_spacing_x, const float grid_spacing_y)
		{
			Position = position;
			if (IsSnapped)
			{
				Position.x -= fmod(Position.x, grid_spacing_x);
				Position.y -= fmod(Position.y, grid_spacing_y);
			}
		}
		void SetSize(const ImVec2 size, const float grid_spacing_x, const float grid_spacing_y)
		{
			Size = size;
			if (IsSnapped)
			{
				Size.x -= fmod(Size.x, grid_spacing_x);
				Size.y -= fmod(Size.y, grid_spacing_y);
			}
		}
		ImVec2 Position;
		ImVec2 Size;
		virtual Component* Clone(){ return this;};
		void TextSettings()
		{
			ImGui::NewLine();
			ImGui::ColorEdit4("Text Color", &TextColor.x);
			ImGui::ShowFontSelector("Fonts");
			ImGui::NewLine();
		};
		bool IsSnapped = true;
		ImVec4 TextColor = ImGui::GetStyle().Colors[ImGuiCol_Text];
		virtual void Draw(){}
		virtual void PropertiesWindow(){}

	};

#define COLOR_IS_EQUAL(a, b) ((a).x == (b).x && (a).y == (b).y && (a).z == (b).z && (a).w == (b).w)
#define IMVEC2_IS_EQUAL(a, b) ((a).x == (b).x && (a).y == (b).y)
#define COMPARE_FLOATS(a, b) (abs((a)-(b)) < 0.0001)

	class GUIMAKER_API ButtonComponent : public Component
	{
		public:
		ButtonComponent(const char* label, const ImVec2 size, const ImVec2 position)
			: Label(label)
		{
			Size = size;
			Position = position;
		}
		ButtonComponent* Clone() override
		{
			ButtonComponent* clone = new ButtonComponent(Label.c_str(), Size, Position);
			clone->IsSnapped = IsSnapped;
			clone->TextColor = TextColor;
			clone->TextAlignment = TextAlignment;
			clone->FramePadding = FramePadding;
			clone->FrameRounding = FrameRounding;
			clone->Color = Color;
			clone->HoveredColor = HoveredColor;
			clone->ActiveColor = ActiveColor;
			clone->FrameBorderSize = FrameBorderSize;
			clone->Size = Size;
			clone->Position.x = Position.x + 10.0;
			clone->Position.y = Position.y + 10.0;
			return clone;
		}
		void PropertiesWindow() override
		{
			ImGui::Text("Button Properties");
			TextSettings();
			char* text = new char[100];
			text = const_cast<char*>(Label.c_str());
			ImGui::InputText("Text", text, 100);
			if (!std::string(text).empty())
				Label = text;
			ImGui::Checkbox("Is Snapped", &IsSnapped);
			
			ImGui::InputFloat2("Text Alignment", &TextAlignment.x);
			ImGui::InputFloat2("Frame Padding", &FramePadding.x);
			ImGui::InputFloat("Frame Rounding", &FrameRounding);
			ImGui::InputFloat("Frame Border Size", &FrameBorderSize);
			ImGui::ColorEdit4("Color", &Color.x);
			ImGui::ColorEdit4("Hovered Color", &HoveredColor.x);
			ImGui::ColorEdit4("Active Color", &ActiveColor.x);
		}
		std::string Label;
		ImVec2 TextAlignment = ImGui::GetStyle().ButtonTextAlign;
		float FrameRounding = ImGui::GetStyle().FrameRounding;
		ImVec2 FramePadding = ImGui::GetStyle().FramePadding;
		ImVec4 Color = ImGui::GetStyle().Colors[ImGuiCol_Button];
		ImVec4 HoveredColor = ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered];
		ImVec4 ActiveColor = ImGui::GetStyle().Colors[ImGuiCol_ButtonActive];
		float FrameBorderSize = ImGui::GetStyle().FrameBorderSize;
		void Draw() override
		{
			int color_count = 0, style_count = 0;

			if (!COLOR_IS_EQUAL(Color, ImGui::GetStyle().Colors[ImGuiCol_Button]))
			{
				ImGui::PushStyleColor(ImGuiCol_Button, Color);
				color_count++;
			}

			if (!COLOR_IS_EQUAL(HoveredColor, ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered]))
			{
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, HoveredColor);
				color_count++;
			}

			if (!COLOR_IS_EQUAL(ActiveColor, ImGui::GetStyle().Colors[ImGuiCol_ButtonActive]))
			{
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, ActiveColor);
				color_count++;
			}

			if (!COLOR_IS_EQUAL(TextColor, ImGui::GetStyle().Colors[ImGuiCol_Text]))
			{
				ImGui::PushStyleColor(ImGuiCol_Text, TextColor);
				color_count++;
			}

			if (!IMVEC2_IS_EQUAL(TextAlignment, ImGui::GetStyle().ButtonTextAlign))
			{
				ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, TextAlignment);
				style_count++;
			}

			if(!IMVEC2_IS_EQUAL(FramePadding, ImGui::GetStyle().FramePadding))
			{
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, FramePadding);
				style_count++;
			}

			if (abs(FrameRounding-ImGui::GetStyle().FrameRounding) >= 0.0001)
			{
				ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, FrameRounding);
				style_count++;
			}

			if (abs(FrameBorderSize-ImGui::GetStyle().FrameBorderSize) >= 0.0001)
			{
				ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, FrameBorderSize);
				style_count++;
			}
			
			ImGui::SetCursorPos(Position);
			if (ImGui::Button(Label.c_str(), Size))
			{

			}
			ImGui::PopStyleVar(style_count);
			ImGui::PopStyleColor(color_count);
		}
	};

}