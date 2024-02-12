#include "gmpch.h"
#include "Components.h"

#include "ImGui/ImGuiLayer.h"

namespace EopGuiMaker
{
	void Component::SetPosition(const ImVec2 position, const float grid_spacing_x, const float grid_spacing_y)
	{
		Position = position;
		if (IsSnappedPos)
		{
			if (const float mod_x = fmod(Position.x, grid_spacing_x); mod_x > 0.5f)
				Position.x += grid_spacing_x - mod_x;
			else
				Size.x -= mod_x;
			if (const float mod_y = fmod(Position.y, grid_spacing_y); mod_y > 0.5f)
				Position.y += grid_spacing_y - mod_y;
			else
				Position.y -= mod_y;
		}
	}
	void Component::SetSize(const ImVec2 size, const float grid_spacing_x, const float grid_spacing_y)
	{
		Size = size;
		if (IsSnappedSize)
		{
			if (const float mod_x = fmod(Size.x, grid_spacing_x); mod_x > 0.5f)
				Size.x += grid_spacing_x - mod_x;
			else
				Size.x -= mod_x;
			if (const float mod_y = fmod(Size.y, grid_spacing_y); mod_y > 0.5f)
				Size.y += grid_spacing_y - mod_y;
			else
				Size.y -= mod_y;
		}
	}
	void Component::DrawCopyButtons()
	{
		if (ImGui::Button("Copy Style"))
		{
			ParentWindow->CopiedStyle = new StyleSettings(Styles);
		}
		ImGui::SameLine();
		if(ImGui::Button("Paste Style"))
		{
			if (ParentWindow->CopiedStyle)
				Styles = *ParentWindow->CopiedStyle;
		}
	}
	
	void Component::DrawSnapOptions()
	{
		ImGui::Checkbox("Is Size Snapped", &IsSnappedSize);
		ImGui::Checkbox("Is Position Snapped", &IsSnappedPos);
	}

	void Component::SetStyles()
	{
		Styles.SetStylesCount = 0;
		Styles.SetColorsCount = 0;

		for (int i = 0; i < ImGuiStyleVar_COUNT; i++)
			if (1 << i & ActiveStyles)
				Styles.SetStyle(i);

		for (int i = 0; i < ImGuiCol_COUNT; i++)
			if (1ULL << i & ActiveColors)
				Styles.SetColor(i);
	}

	void Component::PopStyles() const
	{
		Styles.PopStyles();
		Styles.PopColors();
	}
	
	void Component::DrawResetButtons()
	{
		if (ImGui::Button("Reset Style"))
			Styles.ResetStyles();
		ImGui::SameLine();
		if (ImGui::Button("Reset Colors"))
			Styles.ResetColors();
		ImGui::InputText("Label", &Label);
		DrawParentsBox();
	}
	
	void Component::DrawProperties()
	{
		for (int i = 0; i < ImGuiStyleVar_COUNT; i++)
		{
			if (1 << i & ActiveStyles)
				Styles.GetPropertyEditor(i);
		}
		for (int i = 0; i < ImGuiCol_COUNT; i++)
		{
			if (1ULL << i & ActiveColors)
				Styles.GetColorEditor(i);
		}
	}

	void Component::DrawParentsBox()
	{
		if (ParentChild)
		{
			ImGui::Text("Parent: %s", ParentChild->Label.c_str());
			if (ImGui::Button("Add To Main Window"))
			{
				ParentChild->PopComponent(this);
				ParentWindow->PushComponent(this);
			}
		}
		else
		{
			ImGui::Text("Parent: Main Window");
		}
		if (!ParentWindow->Children.empty())
		{
			if (ImGui::BeginListBox("Children"))
			{
				for (const auto& child : ParentWindow->Children)
				{
					if (ImGui::Selectable(child->Label.c_str()))
					{
						ParentWindow->PopComponent(this);
						child->PushComponent(this);
					}
				}
				ImGui::EndListBox();
			}
		}

	}
	



}
