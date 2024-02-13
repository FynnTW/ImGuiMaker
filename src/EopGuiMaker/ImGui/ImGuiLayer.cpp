#include "gmpch.h"
#include "ImGuiLayer.h"

#include <filesystem>

#include "Application.h"
#include <windows.h>
#include "imgui.h"
#include "Creator/Components/ButtonComponent.h"
#include "Creator/Components/ChildComponent.h"
#include "Events/MouseEvent.h"
#include "GLFW/glfw3.h"
#include "OpenGL/imgui_impl_glfw.h"
#include "OpenGL/imgui_impl_opengl3.h"
#include "ImGui/imgui_stdlib.h"
#include "ImGuiFileDialog.h"

namespace EopGuiMaker
{
#define BIND_EVENT_FN(x) [this](auto& event) {return x(event);}

	ImFontAtlas* ATLAS;

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
		ThisWindow = new UserWindow();
	}

	ImGuiLayer::~ImGuiLayer()
	= default;

	bool ADD_FONT_WINDOW = false;
	void FontManager()
	{
		ImGui::Begin("Font Manager");
		static std::string font_name = "Font";
		static float font_size = 16.0f;
		if (ADD_FONT_WINDOW)
		{
			ImGui::InputText("Font Name", &font_name);
			ImGui::InputFloat("Font Size", &font_size);
			if (ImGui::Button("Browse"))
			{
				IGFD::FileDialogConfig config;
				config.path = ".";
				ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".ttf", config);
			}
			// display
			if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) 
			{
			    if (ImGuiFileDialog::Instance()->IsOk()) { // action if OK
				    const std::string file_path_name = ImGuiFileDialog::Instance()->GetFilePathName();
				    const std::string file_path = ImGuiFileDialog::Instance()->GetCurrentPath();
				    const auto add_font = new AddFont();
					add_font->FontName = font_name;
					add_font->FontPath = file_path_name;
					add_font->FontSize = font_size;
					FONT_QUEUE.push_back(add_font);
			    }
			    ADD_FONT_WINDOW = false;
			    // close
			    ImGuiFileDialog::Instance()->Close();
			}
		}
		else
		{
			if (ImGui::Button("Add Font"))
			{
				ADD_FONT_WINDOW = true;
			}
			if (ImGui::BeginListBox("Fonts"))
			{
				for (auto& [font_name, font] : FONTS)
				{
					if (ImGui::Selectable(font_name.c_str()))
					{
						//
					}
				}
				ImGui::EndListBox();
			}
		}
		ImGui::End();
	}
	
	static bool OPEN_NEW_WINDOW_POPUP = false;
	static bool WINDOW_SETTINGS_POPUP = false;
	static bool OPEN_CODE_WINDOW = false;
	std::string CODE;
	ImFont* DEFAULT_FONT;
	std::string DEFAULT_FONT_NAME = "Georgia_Bold";


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
		
		for (const auto& font : FONT_QUEUE) {
			if (FONTS.find(font->FontName) != FONTS.end()) {
				continue;
			}
			GUIMAKER_CORE_INFO(font->FontPath.c_str());
			const auto new_font = ImGui::GetIO().Fonts->AddFontFromFileTTF(font->FontPath.c_str(), font->FontSize);
			FONTS[font->FontName] = new_font;
		}
		FONT_QUEUE.clear();
		if (!ImGui::GetIO().Fonts->IsBuilt())
		{
			ImGui::GetIO().Fonts->Build();
			ImGui_ImplOpenGL3_DestroyFontsTexture();
			ImGui_ImplOpenGL3_CreateFontsTexture();
			if(!DEFAULT_FONT)
			{
				if (FONTS.find(DEFAULT_FONT_NAME) != FONTS.end()) {
					DEFAULT_FONT = FONTS[DEFAULT_FONT_NAME];
				}
			}
		}
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		if (DEFAULT_FONT)
			ImGui::PushFont(DEFAULT_FONT);
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
		    		OPEN_NEW_WINDOW_POPUP = true;
		        }
		    	ImGui::EndMenu();
			}
		    if (ImGui::BeginMenu("Options")) 
			{
		        if (ImGui::MenuItem("Snap Components")) {
		    		ThisWindow->SnapComponents();
		        }
		        if (ImGui::MenuItem("Grid settings")) {
		    		WINDOW_SETTINGS_POPUP = true;
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
		            CODE = ThisWindow->GetOutPutCode();
					OPEN_CODE_WINDOW = true;
		        }
		        if (ImGui::MenuItem("Lua")) {
		            CODE = ThisWindow->GetOutPutCodeLua();
					OPEN_CODE_WINDOW = true;
		        }
				ImGui::EndMenu();
			}
		    if (ImGui::BeginMenu("Font Manager")) 
			{
				FontManager();
				ImGui::EndMenu();
			}
		    if (ImGui::BeginMenu("Debug")) 
			{
				bool debug = true;
		    	ImGui::ShowDebugLogWindow(&debug);
				ImGui::EndMenu();
			}
		}
	    ImGui::EndMainMenuBar();

		if (OPEN_NEW_WINDOW_POPUP) {
			const ImVec2 center = ImGui::GetMainViewport()->GetCenter();
			ImGui::SetNextWindowPos(center);
			ImGui::OpenPopup("Set Window Parameters");
			// Always center this window when appearing
			OPEN_NEW_WINDOW_POPUP = false; // Reset the flag
		}

		if (OPEN_CODE_WINDOW) {
			ImGui::Begin("Code", &OPEN_CODE_WINDOW);
			ImGui::TextWrapped(CODE.c_str());
			if (ImGui::Button("Copy"))
				ImGui::SetClipboardText(CODE.c_str());
			ImGui::SameLine();
			if (ImGui::Button("Close"))
				OPEN_CODE_WINDOW = false;
			ImGui::End();
		}

		if (WINDOW_SETTINGS_POPUP) {
			const ImVec2 center = ImGui::GetMainViewport()->GetCenter();
			ImGui::SetNextWindowPos(center);
			ImGui::OpenPopup("Window Settings");
			WINDOW_SETTINGS_POPUP = false; // Reset the flag
		}


		if (ImGui::BeginPopupModal("Set Window Parameters", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
		    ImGui::InputText("Window Name", &ThisWindow->WindowName);
		    ImGui::InputFloat2("Window Size", &ThisWindow->WindowSize.x);
		    
		    if (ImGui::Button("Set")) {
		        ImGui::CloseCurrentPopup(); // Close the popup when done
				ThisWindow->OpenWindow(); // Set the flag to show the new window
		    }
		    ImGui::SameLine();
		    if (ImGui::Button("Cancel")) {
		        ImGui::CloseCurrentPopup();
		    }
		    
		    ImGui::EndPopup();
		}

		if (ImGui::BeginPopupModal("Window Settings", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {

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
			const std::string name = ThisWindow->SelectedComponent->Label + " Properties";
			ImGui::Begin(name.c_str());
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
		if (DEFAULT_FONT)
			ImGui::PopFont();
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
		if (ImGui::BeginListBox("Items", ImVec2(320, 200))) {
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
					{
						name = name.substr(0, name.find('_') + 1);
						name += std::to_string(AddCount[ComponentType_Button]);
					}
					BUTTON_INC = true;
					ImGui::InputText("Label", &name);

					static std::string text = "Button";
					ImGui::InputText("Text", &text);

					static auto size = ImVec2(100, 50);
					ImGui::InputFloat2("Size", &size.x);
					if (ImGui::Button("Create") && IsLabelValid(name))
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
					{
						name = name.substr(0, name.find('_') + 1);
						name += std::to_string(AddCount[ComponentType_Child]);
					}
					CHILD_INC = true;
					static auto size = ImVec2(400, 200);
					ImGui::InputText("Label", &name);
					ImGui::InputFloat2("Size", &size.x);
					if (ImGui::Button("Create") && IsLabelValid(name))
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


	bool IsLabelValid(const std::string& label)
	{
		if (label.empty())
		{
			GUIMAKER_CORE_ERROR("Label is empty");
			return false;
		}
		for (const auto& [key, item] : ITEMS)
		{
			if (item->Label == label)
			{
				GUIMAKER_CORE_ERROR("Label already exists");
				return false;
			}
		}
		return true;
	}

	void ImGuiLayer::CreateChildWindow(const std::string& name, const ImVec2 size)
	{
		GUIMAKER_CORE_INFO("Added Child");
		auto* new_child = new ChildComponent(name.c_str(), size, ImVec2(0, 0));
		new_child->ParentWindow = ThisWindow;
		ITEMS.insert(std::make_pair(name, new_child));
		AddCount[ComponentType_Child]++;
		ThisWindow->PushComponent(new_child);
	}

	void ImGuiLayer::CreateButtonWindow(const std::string& name, const ImVec2 size, const std::string& text)
	{
		GUIMAKER_CORE_INFO("Added Button");
		auto* new_button = new ButtonComponent(name, size, text);
		new_button->ParentWindow = ThisWindow;
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
		for (const auto& dir_entry : std::filesystem::recursive_directory_iterator(R"(D:\data\Projects\EopGuiMaker\Resources\Fonts)"))
		{
			auto new_font = new AddFont();
			std::string file_name = dir_entry.path().filename().string();
			const std::string file_clean = file_name.substr(0, file_name.find_last_of('.'));
			new_font->FontName = file_clean;
			new_font->FontPath = dir_entry.path().string();
			new_font->FontSize = 16.0f;
			FONT_QUEUE.push_back(new_font);
			GUIMAKER_CORE_INFO(dir_entry.path().string());
		}
		for (const auto& dir_entry : std::filesystem::recursive_directory_iterator(R"(C:\Windows\Fonts)"))
		{
			std::string file_name = dir_entry.path().filename().string();
			const std::size_t ttf_type = std::string(file_name).find(".ttf");
			const std::size_t marlett = std::string(file_name).find("marlett");
			const std::size_t symbolttf = std::string(file_name).find("symbol.ttf");
			const std::size_t webdings = std::string(file_name).find("webdings");
			const std::size_t wingding = std::string(file_name).find("wingding");
			if (ttf_type == std::string::npos
				|| marlett != std::string::npos
				|| webdings != std::string::npos
				|| wingding != std::string::npos
				|| symbolttf != std::string::npos
				)
			{
				continue;
			}
			auto new_font = new AddFont();
			const std::string file_clean = file_name.substr(0, file_name.find_last_of('.'));
			new_font->FontName = file_clean;
			new_font->FontPath = dir_entry.path().string();
			new_font->FontSize = 16.0f;
			FONT_QUEUE.push_back(new_font);
			GUIMAKER_CORE_INFO(dir_entry.path().string());
		}
		OPEN_NEW_WINDOW_POPUP = true;
	}

	void ImGuiLayer::OnDetach()
	{

	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		EventDispatcher event_dispatcher(event);
		event_dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(OnMouseButtonPressed));
	}

	bool ImGuiLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		return false;
	}

}
