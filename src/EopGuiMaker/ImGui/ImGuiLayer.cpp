#include "gmpch.h"
#include "ImGuiLayer.h"

#include "Application.h"
#include "imgui.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "GLFW/glfw3.h"
#include "OpenGL/imgui_impl_glfw.h"
#include "OpenGL/imgui_impl_opengl3.h"

namespace EopGuiMaker
{
#define BIND_EVENT_FN(x) [this](auto& event) {return x(event);}
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
		ThisWindow = new UserWindow();
		ThisWindow->CloseWindow();
	}

	ImGuiLayer::~ImGuiLayer()
	= default;
	
	static bool openNewWindowPopup = false;
	static bool windowSettingsPopup = false;

	void ImGuiLayer::OnUpdate()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		const auto window = Application::Get().GetWindow();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		// Create a full-width menu bar
		if (ImGui::BeginMainMenuBar()) {
		    if (ImGui::BeginMenu("File")) {
		        // Menu items
		        if (ImGui::MenuItem("Exit")) {
		            // Trigger the application to close
		            glfwSetWindowShouldClose(EopGuiMaker::Application::Get().GetWindow().GetNativeWindow(), GLFW_TRUE);
		        }
		        ImGui::EndMenu();
		    }
		    if (ImGui::BeginMenu("Create")) 
			{
				ThisWindow->CloseWindow();
		    	openNewWindowPopup = true;
				ImGui::EndMenu();
			}
		    if (ImGui::BeginMenu("Options")) 
			{
		    	windowSettingsPopup = true;
				ImGui::EndMenu();
			}
		}
	    ImGui::EndMainMenuBar();

		if (openNewWindowPopup) {
			ImVec2 center = ImGui::GetMainViewport()->GetCenter();
			ImGui::SetNextWindowPos(center);
			ImGui::OpenPopup("Create New Window");
			// Always center this window when appearing
			openNewWindowPopup = false; // Reset the flag
		}

		if (windowSettingsPopup) {
			ImVec2 center = ImGui::GetMainViewport()->GetCenter();
			ImGui::SetNextWindowPos(center);
			ImGui::OpenPopup("Window Settings");
			windowSettingsPopup = false; // Reset the flag
		}


		if (ImGui::BeginPopupModal("Create New Window", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		    ImGui::InputText("Window Name", ThisWindow->WindowName, IM_ARRAYSIZE(ThisWindow->WindowName));
		    ImGui::InputFloat2("Window Size", ThisWindow->WindowSize);
		    
		    if (ImGui::Button("Create")) {
		        ImGui::CloseCurrentPopup(); // Close the popup when done
				ThisWindow->OpenWindow(); // Set the flag to show the new window
		    }
		    ImGui::SameLine();
		    if (ImGui::Button("Cancel")) {
		        ImGui::CloseCurrentPopup();
		    }
		    
		    ImGui::EndPopup();
		}

		if (ImGui::BeginPopupModal("Window Settings", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {

		    ImGui::Checkbox("Enable Grid", &ThisWindow->EnableGrid);
		    ImGui::InputInt2("Grid Size", ThisWindow->GridSize);
			ImGui::InputInt("Grid Alpha", &ThisWindow->GridAlpha);
		    
		    if (ImGui::Button("Close")) {
		        ImGui::CloseCurrentPopup(); // Close the popup when done
		    }
		    
		    ImGui::EndPopup();
		}

		bool itemBox = ImGui::BeginListBox("Items", ImVec2(320, 1000));
		if (itemBox) {
			bool Button = ImGui::Selectable("Button", false);
			bool itemTwo = ImGui::Selectable("Item 2", false);
			bool itemThree = ImGui::Selectable("Item 3", false);
			if (Button) {
				GUIMAKER_CORE_INFO("Added Button");
				ThisWindow->PushComponent(new ButtonComponent("Click me", ImVec2(20,20), ImVec2(0,0) ));
			}
			ImGui::EndListBox();
		}

		if (ThisWindow->IsWindowOpen()) {
			ThisWindow->DrawWindow();
			SetSelectedComponent(ThisWindow->SelectedComponent);
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void EopGuiMaker::ImGuiLayer::OnAttach() {
		Context = ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;

		const Application& app = Application::Get();
		app.GetWindow().SetBackgroundImage("D:/data/Projects/EopGuiMaker/Resources/gameBackgroundStrat.png");

		ImGui_ImplOpenGL3_Init("#version 410");
		ImGui_ImplGlfw_InitForOpenGL(app.GetWindow().GetNativeWindow(), true);
	}

	void ImGuiLayer::OnDetach()
	{

	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		EventDispatcher eventDispatcher(event);
		eventDispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(OnMouseButtonPressed));
	}

	bool ImGuiLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		return false;
	}

}
