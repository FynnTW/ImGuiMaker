	#pragma once

	namespace GuiMaker
{
	class MainInterface final : public EopGuiMaker::ImGuiLayer
	{
		public:
		void OnAttach() override;
	};
}
