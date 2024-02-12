#include "gmpch.h"
#include "Creator/Components/Components.h"

namespace EopGuiMaker
{
	void ChildComponent::PropertiesWindow()
	{
		if (ImGui::BeginTabBar("Child Properties"))
		{
			if (ImGui::BeginTabItem("Properties"))
			{
				DrawResetButtons();
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

			ImGui::EndTabBar();
		}
		ImGui::Text("Child Properties");
	}

	void ChildComponent::GetChildFlags()
	{
		for (const auto& pair : CHILD_FLAG_NAMES) {
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

	std::string ChildComponent::GenerateCode()
	{
		std::string code;
		code += Styles.GenerateStylesCode();
		code += fmt::format("ImGui::SetCursorPos({{{}f, {}f}});\n", Position.x, Position.y);
		code += fmt::format("ImGui::BeginChild(\"{}\", ImVec2({}f, {}f));\n", Label, Size.x, Size.y);
		for (const auto& component : m_Components)
		{
			code += component->GenerateCode();
		}
		code += fmt::format("ImGui::EndChild();\n");
		code += Styles.GeneratePopCode();
		return code;
	}

	std::string ChildComponent::GenerateLuaCode()
	{
		std::string code;
		code += Styles.GenerateStylesLuaCode();
		code += fmt::format("ImGui.SetCursorPos({}, {});\n", Position.x, Position.y);
		code += fmt::format("ImGui.BeginChild(\"{}\", {}, {})\n", Label, Size.x, Size.y);
		for (const auto& component : m_Components)
		{
			code += component->GenerateLuaCode();
		}
		code += fmt::format("ImGui.EndChild()\n");
		code += Styles.GeneratePopLuaCode();
		return code;
	}

	
	void ChildComponent::PushComponent(Component* component)
	{
		const float spacing_x = ParentWindow->WindowSize.x / ParentWindow->GridSize.Columns;
		const float spacing_y = ParentWindow->WindowSize.y / ParentWindow->GridSize.Rows;
		m_Components.emplace_back(component);
		component->SetPosition(component->Position, spacing_x, spacing_y);
		component->SetSize(component->Size, spacing_x, spacing_y);
		component->ParentChild = this;
		ParentWindow->SelectedComponent = component;
	}

	void ChildComponent::PopComponent(const Component* component)
	{
		if (const auto it = std::find(m_Components.begin(), m_Components.end(), component); it != m_Components.end())
		{
			m_Components.erase(it);
		}
	}

	void ChildComponent::Draw()
	{
		SetStyles();
		ImGui::SetCursorPos(Position);
		ImGui::BeginChild(Label.c_str(), Size, Flags);
		for (auto it = m_Components.end(); it != m_Components.begin(); )
		{
			const auto component = *--it;
			ParentWindow->DrawComponent(component);
		}
		if (ImGui::IsWindowFocused() && ImGui::IsWindowHovered())
		{
			ParentWindow->ComponentKeyPress();
		}
		ImGui::EndChild();
		PopStyles();
	}
}