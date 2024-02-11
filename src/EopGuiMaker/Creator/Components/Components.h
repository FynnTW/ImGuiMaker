#pragma once

#include "imgui.h"

namespace EopGuiMaker
{
	class GUIMAKER_API Component
	{
	public:
		Component() = default;
		~Component() = default;
		ImVec2* Position;
		ImVec2* Size;
		bool IsSnapped;

	};

	class GUIMAKER_API ButtonComponent : public Component
	{
		public:
		const char* Label;
	};

}