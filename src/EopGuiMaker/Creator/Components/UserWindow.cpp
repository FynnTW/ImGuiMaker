#include "gmpch.h"
#include "Creator/Components/Components.h"


namespace EopGuiMaker
{
	void UserWindow::SetWindowName(const char* window_name)
	{
		Label = *window_name;
	};
	void UserWindow::SetSize(const ImVec2 size)
	{
		Size = size;
		ImGui::SetWindowSize(Label.c_str(), size);
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
				auto end_pos = ImVec2(win_pos.x + col * spacing.x, win_pos.y + Size.y);
			    draw_list->AddLine(start_pos, end_pos, IM_COL32(255, 255, 255, GridAlpha)); // White lines
			}

			// Draw horizontal lines
			for (int row = 0; row <= GridSize.Rows; row++) {
				auto start_pos = ImVec2(win_pos.x, win_pos.y + row * spacing.y);
				auto end_pos = ImVec2(win_pos.x + Size.x, win_pos.y + row * spacing.y);
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
		Styles = StyleSettings();
		ImGui::SetNextWindowPos(Position);
		ImGui::SetNextWindowSize(Size);
	};

	void ParentComponent::SnapComponents()
	{
		for (auto it = m_Components.end(); it != m_Components.begin(); )
		{
			const auto component = *--it;
			if (component->IsSnappedPos)
				component->SetPosition(component->Position);
			if (component->IsSnappedSize)
				component->SetSize(component->Size);
		}
	}

	void UserWindow::SetFont()
	{
		Styles.PushedFont = false;
		if (!Styles.Font.empty())
		{
			if (FONTS.find(Styles.Font) == FONTS.end()) {
				return;
			}
			ImGui::PushFont(FONTS[Styles.Font]);
			Styles.PushedFont = true;
		}
	}

	void UserWindow::PopFont() const
	{
		if (Styles.PushedFont)
		{
			ImGui::PopFont();
		}
	}

	
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
	void UserWindow::Draw()
	{
		SetStyles();
		SetFont();
		ImGui::Begin(Label.c_str(), &m_IsWindowOpen, Flags);

		Size = ImGui::GetWindowSize();
		Position = ImGui::GetWindowPos();
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
			it = std::vector<Widget*>::reverse_iterator(DeletionComponents.erase(std::next(it).base()));
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
		return {Size.x / GridSize.Columns, Size.y / GridSize.Rows};
	}

	void UserWindow::ComponentKeyPress()
	{
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
				new_component->SetPosition(new_component->Position);
				new_component->SetSize(new_component->Size);
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

	void UserWindow::DrawComponent(Widget* component)
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

			GUIMAKER_APP_INFO("Widget Selected");
		}
		const ImVec2 spacing = GetSpacing();
		if (IS_DRAGGING && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
			const ImVec2 mouse_pos = ImGui::GetMousePos();
            const float diff_x = mouse_pos.x - PREV_POS.x;
            const float diff_y = mouse_pos.y - PREV_POS.y;
			if (IS_RESIZING)
			{
				const auto new_size = ImVec2(TEMP_SIZE.x + diff_x, TEMP_SIZE.y + diff_y);
				if(!SelectedComponent->IsSnappedSize)
					SelectedComponent->SetSize(new_size);
				else if (abs(TEMP_SIZE.x - ORIGINAL_SIZE.x) > spacing.x || abs(TEMP_SIZE.y - ORIGINAL_SIZE.y) > spacing.y)
				{
					SelectedComponent->SetSize(new_size);
					ORIGINAL_SIZE = SelectedComponent->Size;
				}
				TEMP_SIZE = new_size;
			}
			else 
			{
				const auto new_pos = ImVec2(TEMP_POS.x + diff_x, TEMP_POS.y + diff_y);
				if(!SelectedComponent->IsSnappedPos)
					SelectedComponent->SetPosition(new_pos);
				else if (abs(TEMP_POS.x - ORIGINAL_POS.x) > spacing.x || abs(TEMP_POS.y - ORIGINAL_POS.y) > spacing.y)
				{
					SelectedComponent->SetPosition(new_pos);
					ORIGINAL_POS = SelectedComponent->Position;
				}
				TEMP_POS = new_pos;
			}

			PREV_POS = mouse_pos;
		}
        if (!ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
			if (IS_DRAGGING && SelectedComponent == component)
			{
				if (IS_RESIZING && SelectedComponent->Type == ComponentType_Child)
				{
					const auto child = dynamic_cast<ParentComponent*>(SelectedComponent);
					child->SnapComponents();
				}
				if (const int children = component->Parent->Children.size(); 
					children && (component->Type != ComponentType_Child || children > 1))
				{
					for (const auto& child : component->Parent->Children)
					{
						if (child == component)
							continue;
						if (component->Position.x > child->Position.x
							&& component->Position.x < child->Position.x + child->Size.x 
							&& component->Position.y > child->Position.y
							&& component->Position.y < child->Position.y + child->Size.y)
						{
							const float pos_x_relative = component->Position.x / component->Parent->Size.x;
							const float pos_y_relative = component->Position.y / component->Parent->Size.y;
							component->Parent->PopComponent(component);
							child->PushComponent(component);
							component->SetPosition(ImVec2(pos_x_relative * child->Size.x, pos_y_relative * child->Size.y));
							component->SetSize(component->Size);
						}
					}
				}
	            IS_DRAGGING = false; // Stop dragging
				PREV_POS = ImVec2(0, 0);
		        IS_RESIZING = false; //
			}
        }
		if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Delete)))
		{
			DeletionComponents.push_back(SelectedComponent);
			SelectedComponent = nullptr;
		}
	}

	void UserWindow::SetStyles()
	{
		if (Styles.FontScale != 1.0f)
			ImGui::SetWindowFontScale(Styles.FontScale);
		Styles.SetStylesCount = 0;
		Styles.SetColorsCount = 0;

		for (int i = 0; i < ImGuiStyleVar_COUNT; i++)
			Styles.SetStyle(i);

		for (int i = 0; i < ImGuiCol_COUNT; i++)
			Styles.SetColor(i);
	};

	void UserWindow::DrawProperties()
	{
		ImGui::Begin("Window Properties");
		if (ImGui::BeginTabBar("Window Properties"))
		{
			if (ImGui::BeginTabItem("Window Properties"))
			{
				if (ImGui::BeginCombo("Font", Styles.Font.c_str()))
				{
					for (const auto& [font_name, font] : FONTS)
					{
						const bool is_selected = (Styles.Font == font_name);
						if (ImGui::Selectable(font_name.c_str(), is_selected))
							Styles.Font = font_name;
						if (is_selected)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}
				ImGui::SliderFloat("Font Scale", &Styles.FontScale, 0.5f,3.0f);
				for (int i = 0; i < ImGuiStyleVar_COUNT; i++)
				{
					Styles.GetPropertyEditor(i);
				}
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Window Colors"))
			{
				for (int i = 0; i < ImGuiCol_COUNT; i++)
				{
					Styles.GetColorEditor(i);
				}
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Flags"))
			{
				Flags = GetWindowFlags(Flags, 0);
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

	int Component::GetWindowFlags(int flags, const UINT32 filter)
	{
		for (const auto& [flag, flag_name] : WINDOW_FLAG_NAMES) {
			if (filter && filter & flag)
				continue;
			bool is_true = flags & flag;
			if (ImGui::Checkbox(flag_name, &is_true))
			{
				if (is_true)
					flags |= flag;
				else
					flags &= ~flag;
			}
		}
		return flags;
	}

	void UserWindow::PopStyles() const
	{
		Styles.PopStyles();
		Styles.PopColors();
		ImGui::SetWindowFontScale(1.0f);
	}

	std::string UserWindow::GenerateCode()
	{
		
		std::string code;
		code += "bool IsWindowOpen = true;\n";
		code += fmt::format("ImGui::SetNextWindowPos(ImVec2({:.1f}f, {:.1f}f));\n", Position.x, Position.y);
		code += fmt::format("ImGui::SetNextWindowSize(ImVec2({:.1f}f, {:.1f}f));\n", Size.x, Size.y);
		code += Styles.GenerateStylesCode();
		code += fmt::format("ImGui::Begin(\"{}\", &IsWindowOpen, {});\n", Label, Flags);
		for (const auto& component : m_Components)
		{
			code += component->GenerateCode();
		}
		code += fmt::format("ImGui::End();\n");
		code += Styles.GeneratePopCode();
		return code;
	};
	std::string UserWindow::GenerateLuaCode()
	{
		std::string code;
		code += "local IsWindowOpen = true\n";
		code += fmt::format("ImGui.SetNextWindowPos({:.1f}, {:.1f})\n", Position.x, Position.y);
		code += fmt::format("ImGui.SetNextWindowSize({:.1f}, {:.1f})\n", Size.x, Size.y);
		code += Styles.GenerateStylesLuaCode();
		code += fmt::format("ImGui.Begin(\"{}\", IsWindowOpen, {})\n", Label, Flags);
		for (const auto& component : m_Components)
		{
			code += component->GenerateLuaCode();
		}
		code += fmt::format("ImGui.End()\n", Label);
		code += Styles.GeneratePopLuaCode();
		return code;
	};

	
	void UserWindow::PushComponent(Widget* component)
	{
		if (component->Type == ComponentType_Child)
			Children.emplace_back(reinterpret_cast<ChildComponent*>(component));

		m_Components.emplace_back(component);
		ARRAY_CHANGED = true;
		component->SetPosition(component->Position);
		component->SetSize(component->Size);
		component->ParentWindow = this;
		SelectedComponent = component;
	}

	void UserWindow::PopComponent(const Widget* component)
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
