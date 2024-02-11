#include "gmpch.h"
#include "UserWindow.h"

#include "imgui.h"

namespace EopGuiMaker
{
	void UserWindow::SetWindowName(const char* window_name)
	{
		WindowName[0] = *window_name;
	};
	void UserWindow::SetWindowSize(float width, float height)
	{
		WindowSize[0] = width;
		WindowSize[1] = height;
	};
	bool UserWindow::IsWindowOpen() const
	{
		return m_IsWindowOpen;
	};
	bool UserWindow::IsGridEnabled() const
	{
		return EnableGrid;
	};
	void UserWindow::SetGridSize(int rows, int columns)
	{
		GridSize[0] = rows;
		GridSize[1] = columns;
	};
	void UserWindow::DrawGrid(bool draw)
	{
		EnableGrid = draw;
	};
	void UserWindow::CloseWindow()
	{
		m_IsWindowOpen = false;
	};
	void UserWindow::OpenWindow()
	{
		m_IsWindowOpen = true;
		ImGui::SetNextWindowPos(ImVec2(WindowPosition[0], WindowPosition[1]));
		ImGui::SetNextWindowSize(ImVec2(WindowSize[0], WindowSize[1]));
	};

	void UserWindow::DrawWindow()
	{
		ImGui::Begin(WindowName, &m_IsWindowOpen, ImGuiWindowFlags_NoTitleBar);
		auto windowSize = ImGui::GetWindowSize();
		WindowSize[0] = windowSize.x;
		WindowSize[1] = windowSize.y;
		ImGui::SetWindowSize(ImVec2(WindowSize[0], WindowSize[1]));
		auto windowPos = ImGui::GetWindowPos();
		WindowPosition[0] = windowPos.x;
		WindowPosition[1] = windowPos.y;
		ImGui::SetWindowPos(ImVec2(WindowPosition[0], WindowPosition[1]));
		if (EnableGrid)
		{
			float spacingX = WindowSize[0] / GridSize[1];
			float spacingY = WindowSize[1] / GridSize[0];
			ImDrawList* draw_list = ImGui::GetWindowDrawList();
			ImVec2 winPos = ImGui::GetWindowPos(); // Top-left corner of the window

			// Draw vertical lines
			for (int col = 0; col <= GridSize[0]; col++) {
			    ImVec2 startPos = ImVec2(winPos.x + col * spacingX, winPos.y);
			    ImVec2 endPos = ImVec2(winPos.x + col * spacingX, winPos.y + WindowSize[1]);
			    draw_list->AddLine(startPos, endPos, IM_COL32(255, 255, 255, GridAlpha)); // White lines
			}

			// Draw horizontal lines
			for (int row = 0; row <= GridSize[1]; row++) {
			    ImVec2 startPos = ImVec2(winPos.x, winPos.y + row * spacingY);
			    ImVec2 endPos = ImVec2(winPos.x + WindowSize[0], winPos.y + row * spacingY);
			    draw_list->AddLine(startPos, endPos, IM_COL32(255, 255, 255, GridAlpha)); // White lines
			}

		}
		for (auto it = m_Components.end(); it != m_Components.begin(); )
		{
			const auto component = *--it;
			component->Draw();
			if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
			{
				SelectedComponent = component;
				GUIMAKER_APP_INFO("Component Selected");
			}
		}
		ImGui::End();
	};

	
	void UserWindow::PushComponent(Component* component)
	{
		m_Components.emplace_back(component);
	}

	void UserWindow::PopComponent(const Component* component)
	{
		if (const auto it = std::find(m_Components.begin(), m_Components.end(), component); it != m_Components.end())
		{
			m_Components.erase(it);
		}
	}

}
