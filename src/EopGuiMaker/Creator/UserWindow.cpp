#include "gmpch.h"
#include "UserWindow.h"
#include "ImGui/imgui_stdlib.h"

#include "imgui.h"
#include <format>

namespace EopGuiMaker
{
	void UserWindow::SetWindowName(const char* window_name)
	{
		WindowName = *window_name;
	};
	void UserWindow::SetWindowSize(const ImVec2 size)
	{
		WindowSize = size;
		ImGui::SetWindowSize(WindowName.c_str(), size);
	};
	bool UserWindow::IsWindowOpen() const
	{
		return m_IsWindowOpen;
	};
	bool UserWindow::IsGridEnabled() const
	{
		return EnableGrid;
	};
	void UserWindow::SetGridSize(const int rows, const int columns)
	{
		GridSize.Rows = rows;
		GridSize.Columns = columns;
		SnapComponents();
	};
	void UserWindow::DrawGrid() const
	{
		const ImVec2 spacing = GetSpacing();
		if (EnableGrid)
		{
			ImDrawList* draw_list = ImGui::GetWindowDrawList();
			const ImVec2 win_pos = ImGui::GetWindowPos(); // Top-left corner of the window

			// Draw vertical lines
			for (int col = 0; col <= GridSize.Columns; col++) {
				auto start_pos = ImVec2(win_pos.x + col * spacing.x, win_pos.y);
				auto end_pos = ImVec2(win_pos.x + col * spacing.x, win_pos.y + WindowSize.y);
			    draw_list->AddLine(start_pos, end_pos, IM_COL32(255, 255, 255, GridAlpha)); // White lines
			}

			// Draw horizontal lines
			for (int row = 0; row <= GridSize.Rows; row++) {
				auto start_pos = ImVec2(win_pos.x, win_pos.y + row * spacing.y);
				auto end_pos = ImVec2(win_pos.x + WindowSize.x, win_pos.y + row * spacing.y);
			    draw_list->AddLine(start_pos, end_pos, IM_COL32(255, 255, 255, GridAlpha)); // White lines
			}

		}
	};
	void UserWindow::CloseWindow()
	{
		m_IsWindowOpen = false;
	};
	void UserWindow::OpenWindow()
	{
		m_IsWindowOpen = true;
		Style = StyleSettings();
		ImGui::SetNextWindowPos(WindowPosition);
		ImGui::SetNextWindowSize(WindowSize);
	};

	void UserWindow::SnapComponents()
	{
		const float spacing_x = WindowSize.x / GridSize.Columns;
		const float spacing_y = WindowSize.y / GridSize.Rows;
		for (auto it = m_Components.end(); it != m_Components.begin(); )
		{
			const auto component = *--it;
			if (component->IsSnappedPos)
				component->SetPosition(component->Position, spacing_x, spacing_y);
			if (component->IsSnappedSize)
				component->SetSize(component->Size, spacing_x, spacing_y);
		}
	}

	void UserWindow::SetFont()
	{
		Style.PushedFont = false;
		if (!Style.Font.empty())
		{
			if (FONTS.find(Style.Font) == FONTS.end()) {
				return;
			}
			ImGui::PushFont(FONTS[Style.Font]);
			Style.PushedFont = true;
		}
	}

	void UserWindow::PopFont() const
	{
		if (Style.PushedFont)
		{
			ImGui::PopFont();
		}
	}

#define IMVEC2_ADD(a, b) ImVec2((a).x + (b).x, (a).y + (b).y)
	
	bool IS_DRAGGING = false; // Add a flag to track the drag state
	bool IS_RESIZING = false; // Add a flag to track the drag state
	bool USER_WANT_MOVE = false; // Add a flag to track the drag state
	ImVec2 PREV_POS; // Starting position of the drag
	ImVec2 ORIGINAL_POS; // Starting position of the drag
	ImVec2 TEMP_POS; // Starting position of the drag
	ImVec2 ORIGINAL_SIZE; // Starting position of the drag
	ImVec2 TEMP_SIZE; // Starting position of the drag
	bool ARRAY_CHANGED = false;
	constexpr float handle_radius = 8.0f; // Radius of the handle
	void UserWindow::DrawWindow()
	{
		SetStyles();
		SetFont();
		ImGui::Begin(WindowName.c_str(), &m_IsWindowOpen, Flags);

		WindowSize = ImGui::GetWindowSize();
		WindowPosition = ImGui::GetWindowPos();
		DrawGrid();
		
		ARRAY_CHANGED = false;
		for (auto it = m_Components.end(); it != m_Components.begin(); )
		{
			const auto component = *--it;
			DrawComponent(component);
			if (ARRAY_CHANGED)
				break;
		}

		for (auto it = DeletionComponents.rbegin(); it != DeletionComponents.rend();)
		{
			PopComponent(*it);
			it = std::vector<Component*>::reverse_iterator(DeletionComponents.erase(std::next(it).base()));
		}

		if (ImGui::IsWindowFocused() && ImGui::IsWindowHovered())
		{
			ComponentKeyPress();
		}

		ImGui::End();
		PopStyles();
		PopFont();
	}

	ImVec2 UserWindow::GetSpacing() const
	{
		return {WindowSize.x / GridSize.Columns, WindowSize.y / GridSize.Rows};
	}

	void UserWindow::ComponentKeyPress()
	{
		const ImVec2 spacing = GetSpacing();
		if(ImGui::IsKeyPressed(ImGuiKey_C) && ImGui::IsKeyDown(ImGuiKey_LeftCtrl))
		{
			CopiedComponent = SelectedComponent;
		}
		if(ImGui::IsKeyPressed(ImGuiKey_V) && ImGui::IsKeyDown(ImGuiKey_LeftCtrl))
		{
			if (CopiedComponent)
			{
				const auto new_component = CopiedComponent->Clone();
				PushComponent(new_component);
				new_component->SetPosition(new_component->Position, spacing.x, spacing.y);
				new_component->SetSize(new_component->Size, spacing.x, spacing.y);
			}
		}
		if(ImGui::IsKeyPressed(ImGuiKey_Escape))
		{
			SelectedComponent = nullptr;
		}
		if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
		{
			SelectedComponent = nullptr;
		}
	}

	void UserWindow::DrawComponent(Component* component)
	{
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
		const float spacing_x = WindowSize.x / GridSize.Columns;
		const float spacing_y = WindowSize.y / GridSize.Rows;
		if (IS_DRAGGING && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
			
            ImVec2 mouse_pos = ImGui::GetMousePos();
            const float diff_x = mouse_pos.x - PREV_POS.x;
            const float diff_y = mouse_pos.y - PREV_POS.y;
			if (IS_RESIZING)
			{
				const auto new_size = ImVec2(TEMP_SIZE.x + diff_x, TEMP_SIZE.y + diff_y);
				if(!SelectedComponent->IsSnappedSize)
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
				if(!SelectedComponent->IsSnappedPos)
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
		}
        if (!ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
			if (IS_DRAGGING)
			{
				if (const int children = component->ParentChild ? component->ParentChild->Children.size() : component->ParentWindow->Children.size(); 
					children && (component->Type != ComponentType_Child || children > 1))
				{
					for (const auto& child : component->ParentChild ? component->ParentChild->Children : component->ParentWindow->Children)
					{
						if (child == component)
							continue;
						if (component->Position.x > child->Position.x
							&& component->Position.x < child->Position.x + child->Size.x 
							&& component->Position.y > child->Position.y
							&& component->Position.y < child->Position.y + child->Size.y)
						{
							const float pos_x_relative = component->Position.x / 
								(component->ParentChild ? component->ParentChild->Size.x : component->ParentWindow->WindowSize.x);
							const float pos_y_relative = component->Position.y / 
								(component->ParentChild ? component->ParentChild->Size.y : component->ParentWindow->WindowSize.y);
							if (component->ParentChild)
								component->ParentChild->PopComponent(component);
							else
								component->ParentWindow->PopComponent(component);
							child->PushComponent(component);
							component->SetPosition(ImVec2(pos_x_relative * child->Size.x, pos_y_relative * child->Size.y), spacing_x, spacing_y);
						}
					}
				}
			}
            IS_DRAGGING = false; // Stop dragging
			PREV_POS = ImVec2(0, 0);
	        IS_RESIZING = false; //
        }
		if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Delete)))
		{
			DeletionComponents.push_back(SelectedComponent);
			SelectedComponent = nullptr;
		}
	}

	void UserWindow::SetStyles()
	{
		Style.SetStylesCount = 0;
		Style.SetColorsCount = 0;

		for (int i = 0; i < ImGuiStyleVar_COUNT; i++)
			Style.SetStyle(i);

		for (int i = 0; i < ImGuiCol_COUNT; i++)
			Style.SetColor(i);
	};

	void UserWindow::PropertiesWindow()
	{
		ImGui::Begin("Window Properties");
		if (ImGui::BeginTabBar("Window Properties"))
		{
			if (ImGui::BeginTabItem("Window Properties"))
			{
				if (ImGui::BeginCombo("Font", Style.Font.c_str()))
				{
					for (const auto& [font_name, font] : FONTS)
					{
						const bool is_selected = (Style.Font == font_name);
						if (ImGui::Selectable(font_name.c_str(), is_selected))
							Style.Font = font_name;
						if (is_selected)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}
				for (int i = 0; i < ImGuiStyleVar_COUNT; i++)
				{
					Style.GetPropertyEditor(i);
				}
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Window Colors"))
			{
				for (int i = 0; i < ImGuiCol_COUNT; i++)
				{
					Style.GetColorEditor(i);
				}
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Flags"))
			{
				GetWindowFlags();
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Components"))
			{
				if (ImGui::BeginListBox("Components", {300, 400}))
				{
					for (const auto& component : m_Components)
					{
						if (ImGui::Selectable(component->Label.c_str()))
						{
							SelectedComponent = component;
						}
					}
					ImGui::EndListBox();
				}
				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}
		ImGui::End();
	}

	void UserWindow::GetWindowFlags()
	{
		for (const auto& pair : WINDOW_FLAG_NAMES) {
			bool is_true = Flags & pair.first;
			if (ImGui::Checkbox(pair.second, &is_true))
			{
				if (is_true)
					Flags |= pair.first;
				else
					Flags &= ~pair.first;
			}
		}
	}

	void UserWindow::PopStyles() const
	{
		Style.PopStyles();
		Style.PopColors();
	}

	std::string UserWindow::GetOutPutCode()
	{
		
		std::string code;
		code += "bool IsWindowOpen = true;\n";
		code += fmt::format("ImGui::SetNextWindowPos(ImVec2({:.1f}f, {:.1f}f));\n", WindowPosition.x, WindowPosition.y);
		code += fmt::format("ImGui::SetNextWindowSize(ImVec2({:.1f}f, {:.1f}f));\n", WindowSize.x, WindowSize.y);
		code += Style.GenerateStylesCode();
		code += fmt::format("ImGui::Begin(\"{}\", &IsWindowOpen, {});\n", WindowName, Flags);
		for (const auto& component : m_Components)
		{
			code += component->GenerateCode();
		}
		code += fmt::format("ImGui::End();\n");
		code += Style.GeneratePopCode();
		return code;
	};
	std::string UserWindow::GetOutPutCodeLua()
	{
		std::string code;
		code += "local IsWindowOpen = true\n";
		code += fmt::format("ImGui.SetNextWindowPos({:.1f}, {:.1f})\n", WindowPosition.x, WindowPosition.y);
		code += fmt::format("ImGui.SetNextWindowSize({:.1f}, {:.1f})\n", WindowSize.x, WindowSize.y);
		code += Style.GenerateStylesLuaCode();
		code += fmt::format("ImGui.Begin(\"{}\", IsWindowOpen, {})\n", WindowName, Flags);
		for (const auto& component : m_Components)
		{
			code += component->GenerateLuaCode();
		}
		code += fmt::format("ImGui.End()\n", WindowName);
		code += Style.GeneratePopLuaCode();
		return code;
	};

	
	void UserWindow::PushComponent(Component* component)
	{
		const float spacing_x = WindowSize.x / GridSize.Columns;
		const float spacing_y = WindowSize.y / GridSize.Rows;
		if (component->Type == ComponentType_Child)
			Children.emplace_back(reinterpret_cast<ChildComponent*>(component));
		m_Components.emplace_back(component);
		ARRAY_CHANGED = true;
		component->SetPosition(component->Position, spacing_x, spacing_y);
		component->SetSize(component->Size, spacing_x, spacing_y);
		component->ParentWindow = this;
		SelectedComponent = component;
	}

	void UserWindow::PopComponent(const Component* component)
	{
		if (const auto it = std::find(m_Components.begin(), m_Components.end(), component); it != m_Components.end())
		{
			if (component->Type == ComponentType_Child)
			{
				if (const auto it2 = std::find(Children.begin(), Children.end(), component); it2 != Children.end())
				{
					Children.erase(it2);
				}
			}
			m_Components.erase(it);
			ARRAY_CHANGED = true;
		}
	}

}
