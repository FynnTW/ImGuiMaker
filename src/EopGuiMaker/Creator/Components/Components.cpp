#include "gmpch.h"
#include "Components.h"

#include "ImGui/ImGuiLayer.h"

namespace EopGuiMaker
{
	void Widget::SetPosition(ImVec2 position)
	{
		const auto spacing = ParentWindow->GetSpacing();
		const ImVec2 parent_size = Parent->Size;
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
			if (const float mod_x = fmod(position.x, spacing.x); mod_x > 0.5f)
				position.x += spacing.x - mod_x;
			else
				Size.x -= mod_x;
			if (const float mod_y = fmod(position.y, spacing.y); mod_y > 0.5f)
				position.y += spacing.y - mod_y;
			else
				position.y -= mod_y;
		}
		Position = position;
	}
	void Widget::SetSize(ImVec2 size)
	{
		const auto spacing = ParentWindow->GetSpacing();
		const ImVec2 parent_size = Parent->Size;
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
			if (const float mod_x = fmod(size.x, spacing.x); mod_x > 0.5f)
				size.x += spacing.x - mod_x;
			else
				size.x -= mod_x;
			if (const float mod_y = fmod(size.y, spacing.y); mod_y > 0.5f)
				size.y += spacing.y - mod_y;
			else
				size.y -= mod_y;
		}
		Size = size;
	}
	void Widget::DrawCopyButtons()
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
	
	void Widget::DrawSnapOptions()
	{
		ImGui::Checkbox("Is Size Snapped", &IsSnappedSize);
		ImGui::Checkbox("Is Position Snapped", &IsSnappedPos);
	}


	void Widget::SetStyles()
	{
		if (Styles.FontScale != 1.0f)
			ImGui::SetWindowFontScale(Styles.FontScale);
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

	void Widget::PopStyles() const
	{
		Styles.PopStyles();
		Styles.PopColors();
		PopFont();
		ImGui::SetWindowFontScale(Parent->Styles.FontScale);
	}
	
	void Widget::DrawResetButtons()
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
		}
		ImGui::SameLine();
		if (ImGui::Button("Set Label"))
		{
			if (IsLabelValid(TempLabel))
			{
				UpdateLabel(Label, TempLabel);
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
	        // Move the Widget pointer to the new key
	        ITEMS[new_label] = it->second;
	    } else {
			GUIMAKER_CORE_WARN("Label already exists");
	        return false;
	    }

	    // Step 3: Erase the old element
	    ITEMS.erase(it);

	    return true; // Update succeeded
	}
	
	void Widget::DrawProperties()
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
			if (1 << i & ActiveStyles)
				Styles.GetPropertyEditor(i);
		}
		for (int i = 0; i < ImGuiCol_COUNT; i++)
		{
			if (1ULL << i & ActiveColors)
				Styles.GetColorEditor(i);
		}
	}

	void Widget::SetFont()
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

	void Widget::PopFont() const
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

	void Widget::DrawParentsBox()
	{
		if (Parent->Type == ComponentType_Child)
		{
			ImGui::Text("Parent: %s", Parent->Label.c_str());
			if (ImGui::Button("Add To Main Window"))
			{
				Parent->PopComponent(this);
				ParentWindow->PushComponent(this);
				this->Parent = ParentWindow;
			}
		}
		else
		{
			ImGui::Text("Parent: Main Window");
		}
		if (const int children = Parent->Children.size(); 
					children && (this->Type != ComponentType_Child || children > 1))
		{
			if (ImGui::BeginListBox("Children", {100.0f, 50.f}))
			{
				for (const auto& child : Parent->Children)
				{
					if (child == this)
						continue;
					if (child == Parent)
						continue;
					if (ImGui::Selectable(child->Label.c_str()))
					{
						const ImVec2 old_size = Parent->Size;
						const float pos_x_relative = Position.x / old_size.x;
						const float pos_y_relative = Position.y / old_size.y;
						Parent->PopComponent(this);
						child->PushComponent(this);
						SetPosition(ImVec2(pos_x_relative * child->Size.x, pos_y_relative * child->Size.y));
					}
				}
				ImGui::EndListBox();
			}
		}

	}
	



}
