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
		WindowSize.x = width;
		WindowSize.y = height;
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
		GridSize.Rows = rows;
		GridSize.Columns = columns;
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

#define IMVEC2_ADD(a, b) ImVec2(a.x + b.x, a.y + b.y)
	
	bool IS_DRAGGING = false; // Add a flag to track the drag state
	bool IS_RESIZING = false; // Add a flag to track the drag state
	ImVec2 PREV_POS; // Starting position of the drag
	ImVec2 ORIGINAL_POS; // Starting position of the drag
	ImVec2 TEMP_POS; // Starting position of the drag
	ImVec2 ORIGINAL_SIZE; // Starting position of the drag
	ImVec2 TEMP_SIZE; // Starting position of the drag
	constexpr float handle_radius = 5.0f; // Radius of the handle
	void UserWindow::DrawWindow()
	{
		ImGui::Begin(WindowName, &m_IsWindowOpen, ImGuiWindowFlags_NoTitleBar);
		const auto window_size = ImGui::GetWindowSize();
		WindowSize.x = window_size.x;
		WindowSize.y = window_size.y;
		ImGui::SetWindowSize(ImVec2(WindowSize[0], WindowSize[1]));
		const auto window_pos = ImGui::GetWindowPos();
		WindowPosition.x = window_pos.x;
		WindowPosition.y = window_pos.y;
		ImGui::SetWindowPos(ImVec2(WindowPosition[0], WindowPosition[1]));
		const float spacing_x = WindowSize.x / GridSize.Columns;
		const float spacing_y = WindowSize.y / GridSize.Rows;
		if (EnableGrid)
		{
			ImDrawList* draw_list = ImGui::GetWindowDrawList();
			const ImVec2 win_pos = ImGui::GetWindowPos(); // Top-left corner of the window

			// Draw vertical lines
			for (int col = 0; col <= GridSize.Columns; col++) {
				auto start_pos = ImVec2(win_pos.x + col * spacing_x, win_pos.y);
				auto end_pos = ImVec2(win_pos.x + col * spacing_x, win_pos.y + WindowSize.y);
			    draw_list->AddLine(start_pos, end_pos, IM_COL32(255, 255, 255, GridAlpha)); // White lines
			}

			// Draw horizontal lines
			for (int row = 0; row <= GridSize.Rows; row++) {
				auto start_pos = ImVec2(win_pos.x, win_pos.y + row * spacing_y);
				auto end_pos = ImVec2(win_pos.x + WindowSize.x, win_pos.y + row * spacing_y);
			    draw_list->AddLine(start_pos, end_pos, IM_COL32(255, 255, 255, GridAlpha)); // White lines
			}

		}
		for (auto it = m_Components.end(); it != m_Components.begin(); )
		{
			const auto component = *--it;
			component->Draw();
			//Select and drag components
			if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
			{
				//Set selected component
				SelectedComponent = component;

				IS_DRAGGING = true; // Start dragging
				PREV_POS = ImGui::GetMousePos(); // Previous position used for grid snapping
				ORIGINAL_POS = SelectedComponent->Position; //Last position of the component on the snapped grid
				TEMP_POS = SelectedComponent->Position; //Temporary position of the component not snapped to the grid
				ORIGINAL_SIZE = SelectedComponent->Size; //Last size of the component on the snapped grid
				TEMP_SIZE = SelectedComponent->Size; //Temporary size of the component not snapped to the grid

				//Bottom right corner
				if (ImGui::IsMouseHoveringRect(IMVEC2_ADD(ImGui::GetItemRectMax(), ImVec2(-handle_radius, -handle_radius)), IMVEC2_ADD(ImGui::GetItemRectMax(), ImVec2(handle_radius, handle_radius)))) 
				{
					IS_RESIZING = true;
				}

				GUIMAKER_APP_INFO("Component Selected");
			}
			if (SelectedComponent == component)
			{
				if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Delete)))
				{
					PopComponent(SelectedComponent);
					SelectedComponent = nullptr;
					IS_DRAGGING = false; // Stop dragging
					IS_RESIZING = false; // Stop dragging
				}
				if (IS_DRAGGING && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
					
		            ImVec2 mouse_pos = ImGui::GetMousePos();
		            const float diff_x = mouse_pos.x - PREV_POS.x;
		            const float diff_y = mouse_pos.y - PREV_POS.y;
					if (IS_RESIZING)
					{
						const auto new_size = ImVec2(TEMP_SIZE.x + diff_x, TEMP_SIZE.y + diff_y);
						if(!SelectedComponent->IsSnapped)
							SelectedComponent->SetSize(new_size, spacing_x, spacing_y);
						else if (abs(TEMP_SIZE.x - ORIGINAL_SIZE.x) > spacing_x || abs(TEMP_SIZE.y - ORIGINAL_SIZE.y) > spacing_y)
						{
							SelectedComponent->SetSize(new_size, spacing_x, spacing_y);
							ORIGINAL_SIZE = SelectedComponent->Size;
						}
						TEMP_SIZE = new_size;
					}
					else 
					{
						const auto new_pos = ImVec2(TEMP_POS.x + diff_x, TEMP_POS.y + diff_y);
						if(!SelectedComponent->IsSnapped)
							SelectedComponent->SetPosition(new_pos, spacing_x, spacing_y);
						else if (abs(TEMP_POS.x - ORIGINAL_POS.x) > spacing_x || abs(TEMP_POS.y - ORIGINAL_POS.y) > spacing_y)
						{
							SelectedComponent->SetPosition(new_pos, spacing_x, spacing_y);
							ORIGINAL_POS = SelectedComponent->Position;
						}
						TEMP_POS = new_pos;
					}

					PREV_POS = mouse_pos;
					GUIMAKER_APP_INFO("Component Dragged {0}, {1}, {2}, {3}, {4}, {5}", SelectedComponent->Position.x,  SelectedComponent->Position.y, mouse_pos.x, mouse_pos.y, PREV_POS.x, PREV_POS.y);
		            if (!ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
		                IS_DRAGGING = false; // Stop dragging
		                IS_RESIZING = false; // 
						PREV_POS = ImVec2(0, 0);
		                ImGui::ResetMouseDragDelta(ImGuiMouseButton_Left);
		            }
				}
			}
	        if (!ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
	            IS_DRAGGING = false; // Stop dragging
				PREV_POS = ImVec2(0, 0);
	        	IS_RESIZING = false; //
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
