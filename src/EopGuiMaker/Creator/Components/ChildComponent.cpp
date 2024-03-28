#include "gmpch.h"
#include "Creator/Components/Components.h"

namespace EopGuiMaker
{
	bool ARRAY_CHANGED_CHILD = false;
	void ChildComponent::PropertiesWindow()
	{
		if (ImGui::BeginTabBar("Child Properties"))
		{
			if (ImGui::BeginTabItem("Properties"))
			{
				ImGui::Text("Child Properties");
				ImGui::Checkbox("Show Border Editor Only", &ShowEditorBorder);
				ImGui::Checkbox("Show Background Editor Only", &ShowEditorBackground);
				DrawResetButtons();
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
				DrawSnapOptions();
				for (int i = 0; i < ImGuiStyleVar_COUNT; i++)
				{
					Styles.GetPropertyEditor(i);
				}
				DrawCopyButtons();
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
				GetChildFlags();
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
							ParentWindow->SelectedComponent = component;
						}
					}
					ImGui::EndListBox();
				}
				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}
	}

	void ChildComponent::GetChildFlags()
	{
		for (const auto& [flag, flag_name] : CHILD_FLAG_NAMES) {
			bool is_true = Flags & flag;
			if (const std::size_t always_resize = std::string(flag_name).find("Always Auto"); 
				always_resize == std::string::npos 
				|| Flags & ImGuiChildFlags_AutoResizeX 
				|| Flags & ImGuiChildFlags_AutoResizeY)
			{
				if (ImGui::Checkbox(flag_name, &is_true))
				{
					if (is_true)
						Flags |= flag;
					else
						Flags &= ~flag;
				}
			}
		}
		WindowFlags = GetWindowFlags(WindowFlags, ImGuiWindowFlags_AlwaysAutoResize);
	}

	std::string ChildComponent::GenerateCode()
	{
		std::string code;
		const ImVec4 border_color = Styles.Colors[ImGuiCol_Border];
		const ImVec4 bg_color = Styles.Colors[ImGuiCol_ChildBg];
		if (ShowEditorBorder)
		{
			Flags &= ~ImGuiChildFlags_Border;
			Styles.Colors[ImGuiCol_Border] = ImGui::GetStyleColorVec4(ImGuiCol_Border);
			Styles.EditedColors &= ~(1 << ImGuiCol_Border);
			Styles.SetColorsCount--;
		}
		if (ShowEditorBackground)
		{
			Styles.Colors[ImGuiCol_ChildBg] = ImGui::GetStyleColorVec4(ImGuiCol_ChildBg);
			Styles.EditedColors &= ~(1 << ImGuiCol_ChildBg);
			Styles.SetColorsCount--;
		}
		code += Styles.GenerateStylesCode();
		code += fmt::format("ImGui::SetCursorPos({{{:.1f}f, {:.1f}f}});\n", Position.x, Position.y);
		code += fmt::format("ImGui::BeginChild(\"{}\", ImVec2({:.1f}f, {:.1f}f), {}, {});\n", Label, Size.x, Size.y, Flags, WindowFlags);
		for (const auto& component : m_Components)
		{
			code += component->GenerateCode();
		}
		code += fmt::format("ImGui::EndChild();\n");
		code += Styles.GeneratePopCode();
		if (ShowEditorBorder)
		{
			Flags |= ImGuiChildFlags_Border;
			Styles.Colors[ImGuiCol_Border] = border_color;
			Styles.EditedColors |= 1 << ImGuiCol_Border;
			Styles.SetColorsCount++;
		}
		if (ShowEditorBackground)
		{
			Styles.Colors[ImGuiCol_ChildBg] = bg_color;
			Styles.EditedColors |= 1 << ImGuiCol_ChildBg;
			Styles.SetColorsCount++;
		}
		return code;
	}

	std::string ChildComponent::GenerateLuaCode()
	{
		std::string code;
		const ImVec4 border_color = Styles.Colors[ImGuiCol_Border];
		const ImVec4 bg_color = Styles.Colors[ImGuiCol_ChildBg];
		if (ShowEditorBorder)
		{
			Flags &= ~ImGuiChildFlags_Border;
			Styles.Colors[ImGuiCol_Border] = ImGui::GetStyleColorVec4(ImGuiCol_Border);
			Styles.EditedColors &= ~(1 << ImGuiCol_Border);
			Styles.SetColorsCount--;
		}
		if (ShowEditorBackground)
		{
			Styles.Colors[ImGuiCol_ChildBg] = ImGui::GetStyleColorVec4(ImGuiCol_ChildBg);
			Styles.EditedColors &= ~(1 << ImGuiCol_ChildBg);
			Styles.SetColorsCount--;
		}
		code += Styles.GenerateStylesLuaCode();
		code += fmt::format("ImGui.SetCursorPos({:.1f}, {:.1f});\n", Position.x, Position.y);
		code += fmt::format("ImGui.BeginChild(\"{}\", {:.1f}, {:.1f}, {}, {})\n", Label, Size.x, Size.y, Flags, WindowFlags);
		for (const auto& component : m_Components)
		{
			code += component->GenerateLuaCode();
		}
		code += fmt::format("ImGui.EndChild()\n");
		code += Styles.GeneratePopLuaCode();
		if (ShowEditorBorder)
		{
			Flags |= ImGuiChildFlags_Border;
			Styles.Colors[ImGuiCol_Border] = border_color;
			Styles.EditedColors |= 1 << ImGuiCol_Border;
			Styles.SetColorsCount++;
		}
		if (ShowEditorBackground)
		{
			Styles.Colors[ImGuiCol_ChildBg] = bg_color;
			Styles.EditedColors |= 1 << ImGuiCol_ChildBg;
			Styles.SetColorsCount++;
		}
		return code;
	}

	
	void ChildComponent::PushComponent(Widget* component)
	{
		if (component->Type == ComponentType_Child)
			Children.emplace_back(reinterpret_cast<ChildComponent*>(component));
		m_Components.emplace_back(component);
		ARRAY_CHANGED_CHILD = true;

		component->Parent = this;
		ParentWindow->SelectedComponent = component;
	}

	void ChildComponent::PopComponent(const Widget* component)
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
			ARRAY_CHANGED_CHILD = true;
		}
	}
	void ChildComponent::Draw()
	{
		SetStyles();
		ImGui::SetCursorPos(Position);
		ImGui::BeginChild(Label.c_str(), Size, Flags, WindowFlags);
		ARRAY_CHANGED_CHILD = false;
		for (auto it = m_Components.end(); it != m_Components.begin(); )
		{
			const auto component = *--it;
			ParentWindow->DrawComponent(component);
			if (ARRAY_CHANGED_CHILD)
				break;
		}
		if (ImGui::IsWindowFocused() && ImGui::IsWindowHovered())
		{
			ParentWindow->ComponentKeyPress();
		}
		ImGui::EndChild();
		PopStyles();
	}
}