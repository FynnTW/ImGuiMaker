#pragma once
#include "EopGuiMaker/Creator/Components/Components.h"
#include "EopGuiMaker/Layer.h"
#include "EopGuiMaker/Events/ApplicationEvent.h"


namespace EopGuiMaker
{
	class GUIMAKER_API ImGuiLayer final : public Layer
	{
	public:

		ImGuiLayer::ImGuiLayer()
			: Layer("ImGuiLayer")
		{
			ThisWindow = new UserWindow();
		}

		void OnUpdate() override;
		void OnAttach() override;
		void OnDetach() override;
		void OnEvent(Event& event) override;
		UserWindow* ThisWindow;
		void ItemListBox();
		int AddCount[ComponentType_Count]{};
		void CreateChildWindow(const std::string& name, ImVec2 size);
		void CreateButtonWindow(const std::string& name, ImVec2 size, const std::string& text);
		StyleSettings* CopiedStyle{};
		static void ProcessFontQueue();
	private:

	};
	static std::unordered_map<std::string, Widget*> ITEMS;
	bool IsLabelValid(const std::string& label);
	
}
