#include "GuiMakerApp.h"

#include <EopGuiMaker.h>
#include <ImGui.h>

class ExampleLayer : public EopGuiMaker::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		GUIMAKER_APP_INFO("ExampleLayer::Update");
	}

	void OnEvent(EopGuiMaker::Event& event) override
	{
		GUIMAKER_APP_TRACE("{0}", event.ToString());
	}
};


class GuiMakerApp : public EopGuiMaker::Application
{
public:
	GuiMakerApp()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new EopGuiMaker::ImGuiLayer());
	}

	~GuiMakerApp() override
	= default;
};

EopGuiMaker::Application* EopGuiMaker::CreateApplication()
{
	return new GuiMakerApp();
}
