#pragma once
#include "EopGuiMaker/Creator/UserWindow.h"
#include "EopGuiMaker/Layer.h"
#include "EopGuiMaker/Events/ApplicationEvent.h"

namespace EopGuiMaker
{
	class GUIMAKER_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();

		~ImGuiLayer();

		void OnUpdate() override;
		void OnAttach() override;
		void OnDetach() override;
		void OnEvent(Event& event) override;
		UserWindow* ThisWindow;
	private:
		float m_Time = 0.0f;
	};
	
}
