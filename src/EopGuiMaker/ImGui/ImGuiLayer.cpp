#include "gmpch.h"
#include "ImGuiLayer.h"

#include "Application.h"
#include "imgui.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "OpenGL/imgui_impl_glfw.h"
#include "OpenGL/imgui_impl_opengl3.h"

namespace EopGuiMaker
{
#define BIND_EVENT_FN(x) [this](auto& event) {return x(event);}
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{

	}

	ImGuiLayer::~ImGuiLayer()
	= default;


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
		    // ... Additional menus
		}

	    ImGui::EndMainMenuBar();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnAttach() {
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;

		ImGui_ImplOpenGL3_Init("#version 410");
		ImGui_ImplGlfw_InitForOpenGL(Application::Get().GetWindow().GetNativeWindow(), true);
	}

	void ImGuiLayer::OnDetach()
	{

	}

	void ImGuiLayer::OnEvent(Event& event)
	{
	}

}
