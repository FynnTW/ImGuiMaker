#include "gmpch.h"
#include "ImGuiLayer.h"

#include "Application.h"
#include "imgui.h"
#include "Creator/Components/ButtonComponent.h"
#include "Creator/Components/ChildComponent.h"
#include "Events/MouseEvent.h"
#include "GLFW/glfw3.h"
#include "OpenGL/imgui_impl_glfw.h"
#include "OpenGL/imgui_impl_opengl3.h"
#include "ImGui/imgui_stdlib.h"

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
		    if (ImGui::BeginMenu("Window Parameters")) 
			{
		        if (ImGui::MenuItem("Parameters")) {
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
			ImGui::OpenPopup("Set Window Parameters");
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


		if (ImGui::BeginPopupModal("Set Window Parameters", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		    ImGui::InputText("Window Name", &ThisWindow->WindowName);
		    ImGui::InputFloat2("Window Size", &ThisWindow->WindowSize.x);
		    
		    if (ImGui::Button("Set")) {
		        ImGui::CloseCurrentPopup(); // Close the popup when done
				ThisWindow->SetWindowSize(ThisWindow->WindowSize); // Set the flag to show the new window
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
		if (ThisWindow != nullptr) {
			ImGui::Begin("Window Properties");
			ThisWindow->PropertiesWindow();
			ImGui::End();
		}
		ItemListBox();
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
	
	bool BUTTON_SELECTED = false;
	bool CHILD_SELECTED = false;
	bool BUTTON_INC = false;
	bool CHILD_INC = false;
	void ImGuiLayer::ItemListBox()
	{
		if (bool item_box = ImGui::BeginListBox("Items", ImVec2(320, 200))) {
			if (ImGui::Selectable("Button"))
			{
				BUTTON_SELECTED = true;
			}
			if (ImGui::Selectable("Child", false))
			{
				CHILD_SELECTED = true;
			}
			if (BUTTON_SELECTED)
			{
				ImGui::OpenPopup("Create Button");
				if (ImGui::BeginPopup("Create Button"))
				{
					static std::string name = "Button_";
					if (!BUTTON_INC)
						name += std::to_string(AddCount[ComponentType_Button]);
					BUTTON_INC = true;
					ImGui::InputText("Label", &name);

					static std::string text = "Button";
					ImGui::InputText("Text", &text);

					static auto size = ImVec2(100, 50);
					ImGui::InputFloat2("Size", &size.x);
					if (ImGui::Button("Create"))
					{
						CreateButtonWindow(name, size, text);
						ImGui::CloseCurrentPopup();
						BUTTON_SELECTED = false;
						BUTTON_INC = false;
					}
					ImGui::SameLine();
					if (ImGui::Button("Cancel"))
					{
						ImGui::CloseCurrentPopup();
						BUTTON_SELECTED = false;
					}
					ImGui::EndPopup();
				}
			}
			if (CHILD_SELECTED)
			{
				ImGui::OpenPopup("Create Child");
				if (ImGui::BeginPopup("Create Child"))
				{
					static std::string name = "Child_";
					if (!CHILD_INC)
						name += std::to_string(AddCount[ComponentType_Child]);
					CHILD_INC = true;
					static auto size = ImVec2(100, 50);
					ImGui::InputText("Label", &name);
					ImGui::InputFloat2("Size", &size.x);
					if (ImGui::Button("Create"))
					{
						CreateChildWindow(name, size);
						ImGui::CloseCurrentPopup();
						CHILD_SELECTED = false;
						CHILD_INC = false;
					}
					ImGui::SameLine();
					if (ImGui::Button("Cancel"))
					{
						ImGui::CloseCurrentPopup();
						CHILD_SELECTED = false;
					}
					ImGui::EndPopup();
				}
			}
			ImGui::EndListBox();
		}
	}

	bool ImGuiLayer::IsLabelValid(const std::string& label)
	{
		if (label.empty())
		{
			GUIMAKER_CORE_ERROR("Label is empty");
			return false;
		}
		if (const auto match = ITEMS.find(label); match != ITEMS.end())
		{
			return false;
		}
		return true;
	}

	void ImGuiLayer::CreateChildWindow(const std::string& name, const ImVec2 size)
	{
		GUIMAKER_CORE_INFO("Added Child");
		auto* new_child = new ChildComponent(name.c_str(), size, ImVec2(0, 0));
		ITEMS.insert(std::make_pair(name, new_child));
		AddCount[ComponentType_Child]++;
		ThisWindow->PushComponent(new_child);
		ThisWindow->Children.push_back(new_child);
	}

	void ImGuiLayer::CreateButtonWindow(const std::string& name, const ImVec2 size, const std::string& text)
	{
		GUIMAKER_CORE_INFO("Added Button");
		auto* new_button = new ButtonComponent(name, size, text);
		AddCount[ComponentType_Button]++;
		ITEMS.insert(std::make_pair(name, new_button));
		ThisWindow->PushComponent(new_button);
	}

	void ImGuiLayer::OnAttach() {
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
