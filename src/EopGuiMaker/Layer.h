#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace EopGuiMaker {

	class GUIMAKER_API Layer
	{
	public:
		explicit Layer(std::string debug_name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		[[nodiscard]] const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}