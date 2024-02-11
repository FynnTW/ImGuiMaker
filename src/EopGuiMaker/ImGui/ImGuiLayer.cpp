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
	}

	ImGuiLayer::~ImGuiLayer()
	= default;
	
	static bool openNewWindowPopup = false;
	static bool windowSettingsPopup = false;
	static bool openCodeWindow = false;
	std::string code = "";

	void ImGuiLayer::OnUpdate()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		auto window = Application::Get().GetWindow();
		if (window.hasBackground)
		{
			if (Application::Get().texture)
			{
				glBindTexture(GL_TEXTURE_2D, Application::Get().texture);

				glUseProgram(window.ShaderProgram);
        
		        // Bind the vertex array
		        glBindVertexArray(window.Quads);
		        
		        // Draw the quad
		        glDrawArrays(GL_TRIANGLES, 0, 6);
		        
		        // Unbind the vertex array
		        glBindVertexArray(0);

			}
		}


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
		        if (ImGui::MenuItem("New Window")) {
		    		openNewWindowPopup = true;
		        }
		    	ImGui::EndMenu();
			}
		    if (ImGui::BeginMenu("Options")) 
			{
		        if (ImGui::MenuItem("Snap Components")) {
		    		ThisWindow->SnapComponents();
		        }
		        if (ImGui::MenuItem("Grid settings")) {
		    		windowSettingsPopup = true;
		        }
		    	ImGui::EndMenu();
			}
		    if (ImGui::BeginMenu("Set BackGround")) 
			{
		        if (ImGui::MenuItem("Strat")) {
		            // Trigger the application to close
		            window.SetBackgroundImage("D:/data/Projects/eopGuiMaker/Resources/gameBackgroundStrat.png");
		        }
		        if (ImGui::MenuItem("Character")) {
		            // Trigger the application to close
		            window.SetBackgroundImage("D:/data/Projects/eopGuiMaker/Resources/gameBackgroundCharacter.png");
		        }
		        if (ImGui::MenuItem("Settlement")) {
		            // Trigger the application to close
		            window.SetBackgroundImage("D:/data/Projects/eopGuiMaker/Resources/gameBackgroundSettlement.png");
		        }
		        if (ImGui::MenuItem("Recruitment")) {
		            // Trigger the application to close
		            window.SetBackgroundImage("D:/data/Projects/eopGuiMaker/Resources/gameBackgroundRecruitment.png");
		        }
		        if (ImGui::MenuItem("Fort")) {
		            // Trigger the application to close
		            window.SetBackgroundImage("D:/data/Projects/eopGuiMaker/Resources/gameBackgroundFort.png");
		        }
		        if (ImGui::MenuItem("Unit")) {
		            // Trigger the application to close
		            window.SetBackgroundImage("D:/data/Projects/eopGuiMaker/Resources/gameBackgroundUnit.png");
		        }
		        if (ImGui::MenuItem("Faction")) {
		            // Trigger the application to close
		            window.SetBackgroundImage("D:/data/Projects/eopGuiMaker/Resources/gameBackgroundFaction.png");
		        }
		        if (ImGui::MenuItem("Economy")) {
		            // Trigger the application to close
		            window.SetBackgroundImage("D:/data/Projects/eopGuiMaker/Resources/gameBackgroundEconomy.png");
		        }
				ImGui::EndMenu();
			}
		    if (ImGui::BeginMenu("Generate Code")) 
			{
		        if (ImGui::MenuItem("C++")) {
		            code = ThisWindow->GetOutPutCode();
					openCodeWindow = true;
		        }
		        if (ImGui::MenuItem("Lua")) {
		            code = ThisWindow->GetOutPutCodeLua();
					openCodeWindow = true;
		        }
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

		if (openCodeWindow) {
			ImGui::Begin("Code", &openCodeWindow);
			ImGui::TextWrapped(code.c_str());
			if (ImGui::Button("Copy"))
				ImGui::SetClipboardText(code.c_str());
			ImGui::SameLine();
			if (ImGui::Button("Close"))
				openCodeWindow = false;
			ImGui::End();
		}

		if (windowSettingsPopup) {
			ImVec2 center = ImGui::GetMainViewport()->GetCenter();
			ImGui::SetNextWindowPos(center);
			ImGui::OpenPopup("Window Settings");
			windowSettingsPopup = false; // Reset the flag
		}


		if (ImGui::BeginPopupModal("Create New Window", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		    ImGui::InputText("Window Name", ThisWindow->WindowName, IM_ARRAYSIZE(ThisWindow->WindowName));
		    ImGui::InputFloat2("Window Size", &ThisWindow->WindowSize.x);
		    
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
		    ImGui::InputInt2("Grid Size", &ThisWindow->GridSize.Columns);
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
				ThisWindow->PushComponent(new ButtonComponent("Button", ImVec2(100,50), ImVec2(0,0) ));
			}
			ImGui::EndListBox();
		}

		if (ThisWindow->IsWindowOpen()) {
			ThisWindow->DrawWindow();
			SetSelectedComponent(ThisWindow->SelectedComponent);
		}

		if (ThisWindow->SelectedComponent != nullptr) {
			ImGui::Begin("Properties");
			ThisWindow->SelectedComponent->PropertiesWindow();
			if (ImGui::Button("Delete")) {
				ThisWindow->PopComponent(ThisWindow->SelectedComponent);
				ThisWindow->SelectedComponent = nullptr;
			}
			ImGui::End();
		}
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		/**
		glUseProgram(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		glDisable(GL_DEPTH_TEST); // ImGui doesn't use depth testing
		glDisable(GL_CULL_FACE); // Ensure face culling is disabled
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Default blend function for ImGui
		*/
	}

	void EopGuiMaker::ImGuiLayer::OnAttach() {
		Context = ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;

		const Application& app = Application::Get();

		ImGui_ImplOpenGL3_Init("#version 410");
		ImGui_ImplGlfw_InitForOpenGL(app.GetWindow().GetNativeWindow(), true);
		ThisWindow->OpenWindow();
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
