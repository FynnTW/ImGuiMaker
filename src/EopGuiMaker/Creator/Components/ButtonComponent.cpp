#include "gmpch.h"
#include "Creator/Components/Components.h"
namespace EopGuiMaker
{
	void ButtonComponent::PropertiesWindow()
	{
		ImGui::Text("Button Properties");

		DrawResetButtons();
		
		ImGui::InputText("Text", &Text);

		DrawSnapOptions();
		DrawProperties();
		DrawCopyButtons();
	}

	ButtonComponent* ButtonComponent::Clone()
	{
		auto* clone = new ButtonComponent(Label + "_copy" + std::to_string(COPY_COUNT), Size, Text);
		clone->IsSnappedPos = IsSnappedPos;
		clone->IsSnappedSize = IsSnappedSize;
		clone->Styles = *new StyleSettings(Styles);
		clone->Size = Size;
		clone->ParentWindow = ParentWindow;
		clone->Parent = Parent;
		clone->Position.x = Position.x;
		clone->Position.y = Position.y + Size.y + 1.0f;
		COPY_COUNT++;
		return clone;
	}

	void ButtonComponent::Draw()
	{
		SetStyles();
		ImGui::SetCursorPos(Position);
		if (ImGui::Button(Text.c_str(), Size))
		{

		}
		PopStyles();
	}

	std::string ButtonComponent::GenerateCode()
	{
		std::string code;
		code += Styles.GenerateStylesCode();
		code += fmt::format("ImGui::SetCursorPos({{{:.1f}f, {:.1f}f}});\n", Position.x, Position.y);
		code += fmt::format("if (ImGui::Button(\"{}\", {{{:.1f}f, {:.1f}f}}))\n", Text.c_str(), Size.x, Size.y);
		code += fmt::format("{{\n");
		code += fmt::format("\n");
		code += fmt::format("}}\n");
		code += Styles.GeneratePopCode();
		return code;
	}

	std::string ButtonComponent::GenerateLuaCode()
	{
		std::string code;
		code += Styles.GenerateStylesLuaCode();
		code += fmt::format("ImGui.SetCursorPos({:.1f}, {:.1f});\n", Position.x, Position.y);
		code += fmt::format("if ImGui.Button(\"{}\", {:.1f}, {:.1f}) then\n", Text.c_str(), Size.x, Size.y);
		code += fmt::format("\n");
		code += fmt::format("end\n");
		code += Styles.GeneratePopLuaCode();
		return code;
	}
}