#pragma once

#include "imgui.h"

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
		bool IsSnapped;
		virtual void Draw(){}
		virtual void PropertiesWindow(){}

	};

	class GUIMAKER_API ButtonComponent : public Component
	{
		public:
		ButtonComponent(const char* label, const ImVec2 size, const ImVec2 position)
			: Label(label)
		{
			Size = size;
			Position = position;
		}
		void PropertiesWindow() override
		{
			ImGui::Text("Button Properties");
			char* text = new char[100];
			text = const_cast<char*>(Label.c_str());
			ImGui::InputText("Text", text, 100);
			if (!std::string(text).empty())
				Label = text;
			ImGui::Checkbox("Is Snapped", &IsSnapped);
		}
		std::string Label;
		void Draw() override
		{
			ImGui::SetCursorPos(Position);
			if (ImGui::Button(Label.c_str(), Size))
			{

			}
		}
	};

}