#include "gmpch.h"
#include "Components.h"

#include "ImGui/ImGuiLayer.h"

namespace EopGuiMaker
{
	void Component::SetPosition(ImVec2 position, const float grid_spacing_x, const float grid_spacing_y)
	{
		const ImVec2 parent_size = ParentChild ? ParentChild->Size : ParentWindow->WindowSize;
		if (position.x < 0.0f)
			position.x = 0.0f;
		if (position.y < 0.0f)
			position.y = 0.0f;
		if (position.x > parent_size.x - Size.x)
			position.x = parent_size.x - Size.x;
		if (position.y > parent_size.y - Size.y)
			position.y = parent_size.y - Size.y;

		if (IsSnappedPos)
		{
			if (const float mod_x = fmod(position.x, grid_spacing_x); mod_x > 0.5f)
				position.x += grid_spacing_x - mod_x;
			else
				Size.x -= mod_x;
			if (const float mod_y = fmod(position.y, grid_spacing_y); mod_y > 0.5f)
				position.y += grid_spacing_y - mod_y;
			else
				position.y -= mod_y;
		}
		Position = position;
	}
	void Component::SetSize(ImVec2 size, const float grid_spacing_x, const float grid_spacing_y)
	{
		const ImVec2 parent_size = ParentChild ? ParentChild->Size : ParentWindow->WindowSize;
		if (size.x < 0.0f)
			size.x = 1.0f;
		if (size.y < 0.0f)
			size.y = 1.0f;
		if (size.x > parent_size.x - Position.x)
			size.x = parent_size.x - Position.x;
		if (size.y > parent_size.y - Position.y)
			size.y = parent_size.y - Position.y;
		if (IsSnappedSize)
		{
			if (const float mod_x = fmod(size.x, grid_spacing_x); mod_x > 0.5f)
				size.x += grid_spacing_x - mod_x;
			else
				size.x -= mod_x;
			if (const float mod_y = fmod(size.y, grid_spacing_y); mod_y > 0.5f)
				size.y += grid_spacing_y - mod_y;
			else
				size.y -= mod_y;
		}
		Size = size;
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
		SetFont();
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
		PopFont();
	}
	
	void Component::DrawResetButtons()
	{
		if (ImGui::Button("Reset Style"))
			Styles.ResetStyles();
		ImGui::SameLine();
		if (ImGui::Button("Reset Colors"))
			Styles.ResetColors();
		ImGui::InputFloat2("Size", &Size.x);
		ImGui::InputFloat2("Position", &Position.x);
		if (ImGui::InputText("Label", &TempLabel))
		{
			if (IsLabelValid(TempLabel))
			{
				if (UpdateLabel(Label, TempLabel))
					Label = TempLabel;
			}
		}
		DrawParentsBox();
	}

	// Function to update the key/label
	bool UpdateLabel(const std::string& old_label, const std::string& new_label) {
	    // Step 1: Find the old element
	    auto it = ITEMS.find(old_label);
	    if (it == ITEMS.end()) {
			GUIMAKER_CORE_TRACE("Label doesn't Exist");
	        return false; // Update failed
	    }

	    // Step 2: Insert a new element with the new key and move the value
	    // Check if the new label already exists to avoid overwriting
	    if (ITEMS.find(new_label) == ITEMS.end()) {
	        // Move the Component pointer to the new key
	        ITEMS[new_label] = it->second;
	    } else {
			GUIMAKER_CORE_WARN("Label already exists");
	        return false;
	    }

	    // Step 3: Erase the old element
	    ITEMS.erase(it);

	    return true; // Update succeeded
	}
	
	void Component::DrawProperties()
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

	void Component::SetFont()
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

	void Component::PopFont() const
	{
		if (Styles.PushedFont)
		{
			ImGui::PopFont();
		}
	}

	void DrawDebugTab()
	{
		ImGui::Text("Debug");
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
				this->ParentChild = nullptr;
			}
		}
		else
		{
			ImGui::Text("Parent: Main Window");
		}
		if (const int children = ParentChild ? ParentChild->Children.size() : ParentWindow->Children.size(); 
					children && (this->Type != ComponentType_Child || children > 1))
		{
			if (ImGui::BeginListBox("Children", {100.0f, 50.f}))
			{
				for (const auto& child : ParentChild ? ParentChild->Children : ParentWindow->Children)
				{
					if (child == this)
						continue;
					if (child == ParentChild)
						continue;
					if (ImGui::Selectable(child->Label.c_str()))
					{
						const ImVec2 old_size = ParentChild ? ParentChild->Size : ParentWindow->WindowSize;
						const float pos_x_relative = Position.x / old_size.x;
						const float pos_y_relative = Position.y / old_size.y;
						const ImVec2 spacing = ParentWindow->GetSpacing();
						if (ParentChild)
						{
							ParentChild->PopComponent(this);
						}
						else
						{
							ParentWindow->PopComponent(this);
						}
						child->PushComponent(this);
						SetPosition(ImVec2(pos_x_relative * child->Size.x, pos_y_relative * child->Size.y), spacing.x, spacing.y);
					}
				}
				ImGui::EndListBox();
			}
		}

	}
	



}
