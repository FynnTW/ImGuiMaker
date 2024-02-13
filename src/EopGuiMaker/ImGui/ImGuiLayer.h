#pragma once
#include "EopGuiMaker/Creator/UserWindow.h"
#include "EopGuiMaker/Layer.h"
#include "EopGuiMaker/Events/ApplicationEvent.h"
#include "EopGuiMaker/Events/MouseEvent.h"
#include "EopGuiMaker/Creator/Components/StyleSettings.h"

class UserWindow;

namespace EopGuiMaker
{
	class GUIMAKER_API ImGuiLayer final : public Layer
	{
	public:
		ImGuiLayer();

		~ImGuiLayer();

		void OnUpdate() override;
		void OnAttach() override;
		void OnDetach() override;
		void OnEvent(Event& event) override;
		UserWindow* ThisWindow;
		void ItemListBox();
		int AddCount[ComponentType_Count]{};
		void CreateChildWindow(const std::string& name, ImVec2 size);
		void CreateButtonWindow(const std::string& name, ImVec2 size, const std::string& text);
		static bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		void SetSelectedComponent(Component* component) {m_SelectedComponent = component;}
		[[nodiscard]] Component* GetSelectedComponent() const { return m_SelectedComponent; }
		ImGuiContext* Context{};
		StyleSettings* CopiedStyle{};
	private:
		float m_Time = 0.0f;
		Component* m_SelectedComponent{};
	};
	static std::unordered_map<std::string, Component*> ITEMS;
	bool IsLabelValid(const std::string& label);
	
}
