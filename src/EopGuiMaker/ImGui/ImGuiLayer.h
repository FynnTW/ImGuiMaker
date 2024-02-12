#pragma once
#include "EopGuiMaker/Creator/UserWindow.h"
#include "EopGuiMaker/Layer.h"
#include "EopGuiMaker/Events/ApplicationEvent.h"
#include "EopGuiMaker/Events/MouseEvent.h"
#include "EopGuiMaker/Creator/Components/StyleSettings.h"

class UserWindow;

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
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		void SetSelectedComponent(Component* component) {m_SelectedComponent = component;}
		Component* GetSelectedComponent() const { return m_SelectedComponent; }
		ImGuiContext* Context;
		StyleSettings* CopiedStyle;
	private:
		float m_Time = 0.0f;
		Component* m_SelectedComponent;
	};
	
}
