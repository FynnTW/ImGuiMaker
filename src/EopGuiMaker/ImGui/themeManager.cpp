#include "gmpch.h"
#include "imgui.h"
#include "toml.hpp"
/**
ImGuiStyle* tomlToStyle(const char* filePath)
{
	// Light style from ImThemes
	ImGuiStyle &style = ImGui::GetStyle();

	auto config = toml::parse_file(filePath);
	// Assign the styles
	style.Alpha = config["alpha"].value<float>;
	style.DisabledAlpha = config["disabledAlpha"].value<float>;
	style.WindowPadding = ImVec2(config["windowPadding"][0].value<float>, config["windowPadding"][1].value<float>);
	style.WindowRounding = config["windowRounding"].value<float>;
	style.WindowBorderSize = config["windowBorderSize"].value<float>;
	style.WindowMinSize = ImVec2(config["windowMinSize"][0].value<float>, config["windowMinSize"][1].value<float>);
	style.WindowTitleAlign = ImVec2(config["windowTitleAlign"][0].value<float>, config["windowTitleAlign"][1].value<float>);
	style.WindowMenuButtonPosition = config["windowMenuButtonPosition"].value<ImGuiDir>;
	style.ChildRounding = config["childRounding"].value<float>;
	style.ChildBorderSize = config["childBorderSize"].value<float>;
	style.PopupRounding = config["popupRounding"].value<float>;
	style.PopupBorderSize = config["popupBorderSize"].value<float>;
	style.FramePadding = ImVec2(config["framePadding"][0].value<float>, config["framePadding"][1].value<float>);
	style.FrameRounding = config["frameRounding"].value<float>;
	style.FrameBorderSize = config["frameBorderSize"].value<float>;
	style.ItemSpacing = ImVec2(config["itemSpacing"][0].value<float>, config["itemSpacing"][1].value<float>);
	style.ItemInnerSpacing = ImVec2(config["itemInnerSpacing"][0].value<float>, config["itemInnerSpacing"][1].value<float>);
	style.CellPadding = ImVec2(config["cellPadding"][0].value<float>, config["cellPadding"][1].value<float>);
	style.TouchExtraPadding = ImVec2(config["touchExtraPadding"][0].value<float>, config["touchExtraPadding"][1].value<float>);
	style.IndentSpacing = config["indentSpacing"].value<float>;
	style.ColumnsMinSpacing = config["columnsMinSpacing"].value<float>;
	style.ScrollbarSize = config["scrollbarSize"].value<float>;
	style.ScrollbarRounding = config["scrollbarRounding"].value<float>;
	style.GrabMinSize = config["grabMinSize"].value<float>;
	style.GrabRounding = config["grabRounding"].value<float>;
	style.LogSliderDeadzone = config["logSliderDeadzone"].value<float>;
	style.TabRounding = config["tabRounding"].value<float>;
	style.TabBorderSize = config["tabBorderSize"].value<float>;
	style.TabMinWidthForCloseButton = config["tabMinWidthForCloseButton"].value<float>;
	style.TabBarBorderSize = config["tabBarBorderSize"].value<float>;
	style.TableAngledHeadersAngle = config["tableAngledHeadersAngle"].value<float>;
	style.ColorButtonPosition = config["colorButtonPosition"].value<ImGuiDir>;
	style.ButtonTextAlign = ImVec2(config["buttonTextAlign"][0].value<float>, config["buttonTextAlign"][1].value<float>);
	style.SelectableTextAlign = ImVec2(config["selectableTextAlign"][0].value<float>, config["selectableTextAlign"][1].value<float>);
	style.SeparatorTextBorderSize = config["separatorTextBorderSize"].value<float>;
	style.SeparatorTextAlign = ImVec2(config["separatorTextAlign"][0].value<float>, config["separatorTextAlign"][1].value<float>);
	style.SeparatorTextPadding = ImVec2(config["separatorTextPadding"][0].value<float>, config["separatorTextPadding"][1].value<float>);
	style.DisplayWindowPadding = ImVec2(config["displayWindowPadding"][0].value<float>, config["displayWindowPadding"][1].value<float>);
	style.DisplaySafeAreaPadding = ImVec2(config["displaySafeAreaPadding"][0].value<float>, config["displaySafeAreaPadding"][1].value<float>);
	style.MouseCursorScale = config["mouseCursorScale"].value<float>;
	style.AntiAliasedLines = config["antiAliasedLines"].value<bool>;
	style.AntiAliasedLinesUseTex = config["antiAliasedLinesUseTex"].value<bool>;
	style.AntiAliasedFill = config["antiAliasedFill"].value<bool>;
	style.CurveTessellationTol = config["curveTessellationTol"].value<float>;
	style.CircleTessellationMaxError = config["circleTessellationMaxError"].value<float>;
	style.HoverStationaryDelay = config["hoverStationaryDelay"].value<float>;
	style.HoverDelayShort = config["hoverDelayShort"].value<float>;
	style.HoverDelayNormal = config["hoverDelayNormal"].value<float>;
	style.HoverFlagsForTooltipMouse = config["hoverFlagsForTooltipMouse"].value<ImGuiHoveredFlags>;
	style.HoverFlagsForTooltipNav = config["hoverFlagsForTooltipNav"].value<ImGuiHoveredFlags>;

	// // Access the 'colors' section in the TOML file
	auto colorsTable = config["colors"].as_table();

	// // Expected Output Format
	style.Colors[ImGuiCol_Text] = colorsTable->get("Text")->value<ImVec4>;
	style.Colors[ImGuiCol_TextDisabled] = colorsTable->get("TextDisabled")->value<ImVec4>;
	style.Colors[ImGuiCol_WindowBg] = colorsTable->get("WindowBg")->value<ImVec4>;
	style.Colors[ImGuiCol_ChildBg] = colorsTable->get("ChildBg")->value<ImVec4>;
	style.Colors[ImGuiCol_PopupBg] = colorsTable->get("PopupBg")->value<ImVec4>;
	style.Colors[ImGuiCol_Border] = colorsTable->get("Border")->value<ImVec4>;
	style.Colors[ImGuiCol_BorderShadow] = colorsTable->get("BorderShadow")->value<ImVec4>;
	style.Colors[ImGuiCol_FrameBg] = colorsTable->get("FrameBg")->value<ImVec4>;
	style.Colors[ImGuiCol_FrameBgHovered] = colorsTable->get("FrameBgHovered")->value<ImVec4>;
	style.Colors[ImGuiCol_FrameBgActive] = colorsTable->get("FrameBgActive")->value<ImVec4>;
	style.Colors[ImGuiCol_TitleBg] = colorsTable->get("TitleBg")->value<ImVec4>;
	style.Colors[ImGuiCol_TitleBgActive] = colorsTable->get("TitleBgActive")->value<ImVec4>;
	style.Colors[ImGuiCol_TitleBgCollapsed] = colorsTable->get("TitleBgCollapsed")->value<ImVec4>;
	style.Colors[ImGuiCol_MenuBarBg] = colorsTable->get("MenuBarBg")->value<ImVec4>;
	style.Colors[ImGuiCol_ScrollbarBg] = colorsTable->get("ScrollbarBg")->value<ImVec4>;
	style.Colors[ImGuiCol_ScrollbarGrab] = colorsTable->get("ScrollbarGrab")->value<ImVec4>;
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = colorsTable->get("ScrollbarGrabHovered")->value<ImVec4>;
	style.Colors[ImGuiCol_ScrollbarGrabActive] = colorsTable->get("ScrollbarGrabActive")->value<ImVec4>;
	style.Colors[ImGuiCol_CheckMark] = colorsTable->get("CheckMark")->value<ImVec4>;
	style.Colors[ImGuiCol_SliderGrab] = colorsTable->get("SliderGrab")->value<ImVec4>;
	style.Colors[ImGuiCol_SliderGrabActive] = colorsTable->get("SliderGrabActive")->value<ImVec4>;
	style.Colors[ImGuiCol_Button] = colorsTable->get("Button")->value<ImVec4>;
	style.Colors[ImGuiCol_ButtonHovered] = colorsTable->get("ButtonHovered")->value<ImVec4>;
	style.Colors[ImGuiCol_ButtonActive] = colorsTable->get("ButtonActive")->value<ImVec4>;
	style.Colors[ImGuiCol_Header] = colorsTable->get("Header")->value<ImVec4>;
	style.Colors[ImGuiCol_HeaderHovered] = colorsTable->get("HeaderHovered")->value<ImVec4>;
	style.Colors[ImGuiCol_HeaderActive] = colorsTable->get("HeaderActive")->value<ImVec4>;
	style.Colors[ImGuiCol_Separator] = colorsTable->get("Separator")->value<ImVec4>;
	style.Colors[ImGuiCol_SeparatorHovered] = colorsTable->get("SeparatorHovered")->value<ImVec4>;
	style.Colors[ImGuiCol_SeparatorActive] = colorsTable->get("SeparatorActive")->value<ImVec4>;
	style.Colors[ImGuiCol_ResizeGrip] = colorsTable->get("ResizeGrip")->value<ImVec4>;
	style.Colors[ImGuiCol_ResizeGripHovered] = colorsTable->get("ResizeGripHovered")->value<ImVec4>;
	style.Colors[ImGuiCol_ResizeGripActive] = colorsTable->get("ResizeGripActive")->value<ImVec4>;
	style.Colors[ImGuiCol_Tab] = colorsTable->get("Tab")->value<ImVec4>;
	style.Colors[ImGuiCol_TabHovered] = colorsTable->get("TabHovered")->value<ImVec4>;
	style.Colors[ImGuiCol_TabActive] = colorsTable->get("TabActive")->value<ImVec4>;
	style.Colors[ImGuiCol_TabUnfocused] = colorsTable->get("TabUnfocused")->value<ImVec4>;
	style.Colors[ImGuiCol_TabUnfocusedActive] = colorsTable->get("TabUnfocusedActive")->value<ImVec4>;
	style.Colors[ImGuiCol_PlotLines] = colorsTable->get("PlotLines")->value<ImVec4>;
	style.Colors[ImGuiCol_PlotLinesHovered] = colorsTable->get("PlotLinesHovered")->value<ImVec4>;
	style.Colors[ImGuiCol_PlotHistogram] = colorsTable->get("PlotHistogram")->value<ImVec4>;
	style.Colors[ImGuiCol_PlotHistogramHovered] = colorsTable->get("PlotHistogramHovered")->value<ImVec4>;
	style.Colors[ImGuiCol_TableHeaderBg] = colorsTable->get("TableHeaderBg")->value<ImVec4>;
	style.Colors[ImGuiCol_TableBorderStrong] = colorsTable->get("TableBorderStrong")->value<ImVec4>;
	style.Colors[ImGuiCol_TableBorderLight] = colorsTable->get("TableBorderLight")->value<ImVec4>;
	style.Colors[ImGuiCol_TableRowBg] = colorsTable->get("TableRowBg")->value<ImVec4>;
	style.Colors[ImGuiCol_TableRowBgAlt] = colorsTable->get("TableRowBgAlt")->value<ImVec4>;
	style.Colors[ImGuiCol_TextSelectedBg] = colorsTable->get("TextSelectedBg")->value<ImVec4>;
	style.Colors[ImGuiCol_DragDropTarget] = colorsTable->get("DragDropTarget")->value<ImVec4>;
	style.Colors[ImGuiCol_NavHighlight] = colorsTable->get("NavHighlight")->value<ImVec4>;
	style.Colors[ImGuiCol_NavWindowingHighlight] = colorsTable->get("NavWindowingHighlight")->value<ImVec4>;
	style.Colors[ImGuiCol_NavWindowingDimBg] = colorsTable->get("NavWindowingDimBg")->value<ImVec4>;
	style.Colors[ImGuiCol_ModalWindowDimBg] = colorsTable->get("ModalWindowDimBg")->value<ImVec4>;

	return &style;
}
*/