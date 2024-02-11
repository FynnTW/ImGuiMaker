#include <EopGuiMaker.h>
#include "MainInterface.h"
#include "imgui.h"


namespace GuiMaker
{
	void MainInterface::OnAttach()
	{
		ImGuiLayer::OnAttach();
		bool is_open = true;
		is_open = ImGui::Begin("Main Interface", &is_open, ImGuiWindowFlags_MenuBar);

		ImGui::End();
	}
}
