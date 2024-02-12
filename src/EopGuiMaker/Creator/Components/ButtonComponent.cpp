#include "gmpch.h"
#include "ButtonComponent.h"
namespace EopGuiMaker
{
	void ButtonComponent::PropertiesWindow()
	{
		ImGui::Text("Button Properties");

		DrawResetButtons();

		char* text = new char[100];
		text = const_cast<char*>(Label.c_str());
		ImGui::InputText("Text", text, 100);
		if (!std::string(text).empty())
			Label = text;

		DrawSnapOptions();
		DrawProperties();
		DrawCopyButtons();
	}

	ButtonComponent* ButtonComponent::Clone()
	{
		auto* clone = new ButtonComponent(Label.c_str(), Size, Position);
		clone->IsSnappedPos = IsSnappedPos;
		clone->IsSnappedSize = IsSnappedSize;
		clone->Styles = StyleSettings(Styles);
		clone->Size = Size;
		clone->Position.x = Position.x;
		clone->Position.y = Position.y + Size.y + 1.0f;
		return clone;
	}

	void ButtonComponent::Draw()
	{
		SetStyles();
		ImGui::SetCursorPos(Position);
		if (ImGui::Button(Label.c_str(), Size))
		{

		}
		PopStyles();
	}

	std::string ButtonComponent::GenerateCode()
	{
		std::string code;
		code += Styles.GenerateStylesCode();
		code += fmt::format("ImGui::SetCursorPos({{{}f, {}f}});\n", Position.x, Position.y);
		code += fmt::format("if (ImGui::Button(\"{}\", {{{}f, {}f}}))\n", Label.c_str(), Size.x, Size.y);
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
		code += fmt::format("ImGui.SetCursorPos({}, {});\n", Position.x, Position.y);
		code += fmt::format("if ImGui.Button(\"{}\", {}, {}) then\n", Label.c_str(), Size.x, Size.y);
		code += fmt::format("\n");
		code += fmt::format("end\n");
		code += Styles.GeneratePopLuaCode();
		return code;
	}
}