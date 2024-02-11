#pragma once

#include "imgui.h"

namespace EopGuiMaker
{
	class GUIMAKER_API Component
	{
	public:
		Component() = default;
		~Component() = default;
		ImVec2 Position;
		ImVec2 Size;
		bool IsSnapped;
		virtual void Draw(){}

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
		const char* Label;
		void Draw() override
		{
			ImGui::SetCursorPos(Position);
			if (ImGui::Button(Label, Size))
			{

			}
		}
	};

}