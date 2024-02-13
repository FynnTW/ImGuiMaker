#pragma once
#include "imgui.h"

namespace EopGuiMaker
{
	class Component;
enum FloatStyle
{
	FloatStyle_Alpha = 0,
	FloatStyle_DisabledAlpha,
	FloatStyle_WindowRounding,
	FloatStyle_WindowBorderSize,
	FloatStyle_ChildRounding,
	FloatStyle_ChildBorderSize,
	FloatStyle_PopupRounding,
	FloatStyle_PopupBorderSize,
	FloatStyle_FrameRounding,
	FloatStyle_FrameBorderSize,
	FloatStyle_IndentSpacing,
	FloatStyle_ScrollbarSize,
	FloatStyle_ScrollbarRounding,
	FloatStyle_GrabMinSize,
	FloatStyle_GrabRounding,
	FloatStyle_TabRounding,
	FloatStyle_TabBarBorderSize,
	FloatStyle_SeparatorTextBorderSize,
	FloatStyle_Count,
};

inline std::unordered_map<int, const char*> WINDOW_FLAG_NAMES = {
	{ImGuiWindowFlags_NoTitleBar,"No Title Bar"},
	{ImGuiWindowFlags_NoResize,"No Resize"},
	{ImGuiWindowFlags_NoMove,"No Move"},
	{ImGuiWindowFlags_NoScrollbar,"No Scroll Bar"},
	{ImGuiWindowFlags_NoScrollWithMouse,"No Scroll With Mouse"},
	{ImGuiWindowFlags_NoCollapse,"No Collapse"},
	{ImGuiWindowFlags_AlwaysAutoResize,"Always Auto Resize"},
	{ImGuiWindowFlags_NoBackground,"No Background"},
	{ImGuiWindowFlags_NoSavedSettings,"No Saved Settings"},
	{ImGuiWindowFlags_NoMouseInputs,"No Mouse Inputs"},
	{ImGuiWindowFlags_MenuBar,"Menu Bar"},
	{ImGuiWindowFlags_HorizontalScrollbar,"Horizontal Scrollbar"},
	{ImGuiWindowFlags_NoFocusOnAppearing,"No Focus On Appearing"},
	{ImGuiWindowFlags_NoBringToFrontOnFocus,"No Bring To Front On Focus"},
	{ImGuiWindowFlags_AlwaysVerticalScrollbar,"Always Vertical Scrollbar"},
	{ImGuiWindowFlags_AlwaysHorizontalScrollbar,"Always Horizontal Scrollbar"},
	{ImGuiWindowFlags_NoNavInputs,"No Nav Inputs"},
	{ImGuiWindowFlags_NoNavFocus,"No Nav Focus"},
	{ImGuiWindowFlags_UnsavedDocument,"Unsaved Document"},
	{ImGuiWindowFlags_NoNav,"No Nav"},
	{ImGuiWindowFlags_NoDecoration,"No Decoration"},
	{ImGuiWindowFlags_NoInputs,"No Inputs"},
};

inline std::unordered_map<int, const char*> CHILD_FLAG_NAMES = {
	{ImGuiChildFlags_Border,"Border"},
	{ImGuiChildFlags_AlwaysUseWindowPadding,"Always Use Window Padding"},
	{ImGuiChildFlags_ResizeX,"Resize X"},
	{ImGuiChildFlags_ResizeY,"Resize Y"},
	{ImGuiChildFlags_AutoResizeX,"Auto Resize X"},
	{ImGuiChildFlags_AutoResizeY,"Auto Resize Y"},
	{ImGuiChildFlags_AlwaysAutoResize,"Always Auto Resize"},
	{ImGuiChildFlags_FrameStyle,"Frame Style"},
};

inline std::unordered_map<int, const char*> STYLE_NAMES = {
	{ImGuiStyleVar_Alpha,"Alpha"},
	{ImGuiStyleVar_DisabledAlpha,"Disabled Alpha"},
	{ImGuiStyleVar_WindowPadding,"Window Padding"},
	{ImGuiStyleVar_WindowRounding,"Window Rounding"},
	{ImGuiStyleVar_WindowBorderSize,"Window Border Size"},
	{ImGuiStyleVar_WindowMinSize,"Window Minimum Size"},
	{ImGuiStyleVar_WindowTitleAlign,"Window Title Align"},
	{ImGuiStyleVar_ChildRounding,"Child Rounding"},
	{ImGuiStyleVar_ChildBorderSize,"Child Border Size"},
	{ImGuiStyleVar_PopupRounding,"Popup Rounding"},
	{ImGuiStyleVar_PopupBorderSize,"Popup Border Size"},
	{ImGuiStyleVar_FramePadding,"Frame Padding"},
	{ImGuiStyleVar_FrameRounding,"Frame Rounding"},
	{ImGuiStyleVar_FrameBorderSize,"Frame Border Size"},
	{ImGuiStyleVar_ItemSpacing,"Item Spacing"},
	{ImGuiStyleVar_ItemInnerSpacing,"Item Inner Spacing"},
	{ImGuiStyleVar_IndentSpacing,"Indent Spacing"},
	{ImGuiStyleVar_CellPadding,"Cell Padding"},
	{ImGuiStyleVar_ScrollbarSize,"Scrollbar Size"},
	{ImGuiStyleVar_ScrollbarRounding,"Scrollbar Rounding"},
	{ImGuiStyleVar_GrabMinSize,"Grab Minimum Size"},
	{ImGuiStyleVar_GrabRounding,"Grab Rounding"},
	{ImGuiStyleVar_TabRounding,"Tab Rounding"},
	{ImGuiStyleVar_TabBarBorderSize,"Tab Bar Border Size"},
	{ImGuiStyleVar_ButtonTextAlign,"Button Text Align"},
	{ImGuiStyleVar_SelectableTextAlign,"Selectable Text Align"},
	{ImGuiStyleVar_SeparatorTextBorderSize,"Separator Text Border Size"},
	{ImGuiStyleVar_SeparatorTextAlign,"Separator Text Align"},
	{ImGuiStyleVar_SeparatorTextPadding,"Separator Text Padding"},
};

inline std::unordered_map<int, const char*> STYLE_ID = {
	{ImGuiStyleVar_Alpha,"Alpha"},
	{ImGuiStyleVar_DisabledAlpha,"DisabledAlpha"},
	{ImGuiStyleVar_WindowPadding,"WindowPadding"},
	{ImGuiStyleVar_WindowRounding,"WindowRounding"},
	{ImGuiStyleVar_WindowBorderSize,"WindowBorderSize"},
	{ImGuiStyleVar_WindowMinSize,"WindowMinSize"},
	{ImGuiStyleVar_WindowTitleAlign,"WindowTitleAlign"},
	{ImGuiStyleVar_ChildRounding,"ChildRounding"},
	{ImGuiStyleVar_ChildBorderSize,"ChildBorderSize"},
	{ImGuiStyleVar_PopupRounding,"PopupRounding"},
	{ImGuiStyleVar_PopupBorderSize,"PopupBorderSize"},
	{ImGuiStyleVar_FramePadding,"FramePadding"},
	{ImGuiStyleVar_FrameRounding,"FrameRounding"},
	{ImGuiStyleVar_FrameBorderSize,"FrameBorderSize"},
	{ImGuiStyleVar_ItemSpacing,"ItemSpacing"},
	{ImGuiStyleVar_ItemInnerSpacing,"ItemInnerSpacing"},
	{ImGuiStyleVar_IndentSpacing,"IndentSpacing"},
	{ImGuiStyleVar_CellPadding,"CellPadding"},
	{ImGuiStyleVar_ScrollbarSize,"ScrollbarSize"},
	{ImGuiStyleVar_ScrollbarRounding,"ScrollbarRounding"},
	{ImGuiStyleVar_GrabMinSize,"GrabMinSize"},
	{ImGuiStyleVar_GrabRounding,"GrabRounding"},
	{ImGuiStyleVar_TabRounding,"TabRounding"},
	{ImGuiStyleVar_TabBarBorderSize,"TabBarBorderSize"},
	{ImGuiStyleVar_ButtonTextAlign,"ButtonTextAlign"},
	{ImGuiStyleVar_SelectableTextAlign,"SelectableTextAlign"},
	{ImGuiStyleVar_SeparatorTextBorderSize,"SeparatorTextBorderSize"},
	{ImGuiStyleVar_SeparatorTextAlign,"SeparatorTextAlign"},
	{ImGuiStyleVar_SeparatorTextPadding,"SeparatorTextPadding"},
};

inline std::unordered_map<int, const char*> COLOR_NAMES = {
	{ImGuiCol_Text,"Text"},
	{ImGuiCol_TextDisabled,"Text Disabled"},
	{ImGuiCol_WindowBg,"Window Background"},
	{ImGuiCol_ChildBg,"Child Background"},
	{ImGuiCol_PopupBg,"Popup Background"},
	{ImGuiCol_Border,"Border"},
	{ImGuiCol_BorderShadow,"Border Shadow"},
	{ImGuiCol_FrameBg,"Frame Background"},
	{ImGuiCol_FrameBgHovered,"Frame Background Hovered"},
	{ImGuiCol_FrameBgActive,"Frame Background Active"},
	{ImGuiCol_TitleBg,"Title Background"},
	{ImGuiCol_TitleBgActive,"Title Background Active"},
	{ImGuiCol_TitleBgCollapsed,"Title Background Collapsed"},
	{ImGuiCol_MenuBarBg,"Menu Bar Background"},
	{ImGuiCol_ScrollbarBg,"Scrollbar Background"},
	{ImGuiCol_ScrollbarGrab,"Scrollbar Grab"},
	{ImGuiCol_ScrollbarGrabHovered,"Scrollbar Grab Hovered"},
	{ImGuiCol_ScrollbarGrabActive,"Scrollbar Grab Active"},
	{ImGuiCol_CheckMark,"Check Mark"},
	{ImGuiCol_SliderGrab,"Slider Grab"},
	{ImGuiCol_SliderGrabActive,"Slider Grab Active"},
	{ImGuiCol_Button,"Button"},
	{ImGuiCol_ButtonHovered,"Button Hovered"},
	{ImGuiCol_ButtonActive,"Button Active"},
	{ImGuiCol_Header,"Header"},
	{ImGuiCol_HeaderHovered,"Header Hovered"},
	{ImGuiCol_HeaderActive,"Header Active"},
	{ImGuiCol_Separator,"Separator"},
	{ImGuiCol_SeparatorHovered,"Separator Hovered"},
	{ImGuiCol_SeparatorActive,"Separator Active"},
	{ImGuiCol_ResizeGrip,"Resize Grip"},
	{ImGuiCol_ResizeGripHovered,"Resize Grip Hovered"},
	{ImGuiCol_ResizeGripActive,"Resize Grip Active"},
	{ImGuiCol_Tab,"Tab"},
	{ImGuiCol_TabHovered,"Tab Hovered"},
	{ImGuiCol_TabActive,"Tab Active"},
	{ImGuiCol_TabUnfocused,"Tab Unfocused"},
	{ImGuiCol_TabUnfocusedActive,"Tab Unfocused Active"},
	{ImGuiCol_PlotLines,"Plot Lines"},
	{ImGuiCol_PlotLinesHovered,"Plot Lines Hovered"},
	{ImGuiCol_PlotHistogram,"Plot Histogram"},
	{ImGuiCol_PlotHistogramHovered,"Plot Histogram Hovered"},
	{ImGuiCol_TableHeaderBg,"Table Header Background"},
	{ImGuiCol_TableBorderStrong,"Table Border Strong"},
	{ImGuiCol_TableBorderLight,"Table Border Light"},
	{ImGuiCol_TableRowBg,"Table Row Background"},
	{ImGuiCol_TableRowBgAlt,"Table Row Background Alt"},
	{ImGuiCol_TextSelectedBg,"Text Selected Background"},
	{ImGuiCol_DragDropTarget,"Drag Drop Target"},
	{ImGuiCol_NavHighlight,"Nav Highlight"},
	{ImGuiCol_NavWindowingHighlight,"Nav Windowing Highlight"},
	{ImGuiCol_NavWindowingDimBg,"Nav Windowing Dim Background"},
	{ImGuiCol_ModalWindowDimBg,"Modal Window Dim Background"},
};

inline std::unordered_map<int, const char*> COLOR_ID = {
	{ImGuiCol_Text,"Text"},
	{ImGuiCol_TextDisabled,"TextDisabled"},
	{ImGuiCol_WindowBg,"WindowBg"},
	{ImGuiCol_ChildBg,"ChildBg"},
	{ImGuiCol_PopupBg,"PopupBg"},
	{ImGuiCol_Border,"Border"},
	{ImGuiCol_BorderShadow,"BorderShadow"},
	{ImGuiCol_FrameBg,"FrameBg"},
	{ImGuiCol_FrameBgHovered,"FrameBgHovered"},
	{ImGuiCol_FrameBgActive,"FrameBgActive"},
	{ImGuiCol_TitleBg,"TitleBg"},
	{ImGuiCol_TitleBgActive,"TitleBgActive"},
	{ImGuiCol_TitleBgCollapsed,"TitleBgCollapsed"},
	{ImGuiCol_MenuBarBg,"MenuBarBg"},
	{ImGuiCol_ScrollbarBg,"ScrollbarBg"},
	{ImGuiCol_ScrollbarGrab,"ScrollbarGrab"},
	{ImGuiCol_ScrollbarGrabHovered,"ScrollbarGrabHovered"},
	{ImGuiCol_ScrollbarGrabActive,"ScrollbarGrabActive"},
	{ImGuiCol_CheckMark,"CheckMark"},
	{ImGuiCol_SliderGrab,"SliderGrab"},
	{ImGuiCol_SliderGrabActive,"SliderGrabActive"},
	{ImGuiCol_Button,"Button"},
	{ImGuiCol_ButtonHovered,"ButtonHovered"},
	{ImGuiCol_ButtonActive,"ButtonActive"},
	{ImGuiCol_Header,"Header"},
	{ImGuiCol_HeaderHovered,"HeaderHovered"},
	{ImGuiCol_HeaderActive,"HeaderActive"},
	{ImGuiCol_Separator,"Separator"},
	{ImGuiCol_SeparatorHovered,"SeparatorHovered"},
	{ImGuiCol_SeparatorActive,"SeparatorActive"},
	{ImGuiCol_ResizeGrip,"ResizeGrip"},
	{ImGuiCol_ResizeGripHovered,"ResizeGripHovered"},
	{ImGuiCol_ResizeGripActive,"ResizeGripActive"},
	{ImGuiCol_Tab,"Tab"},
	{ImGuiCol_TabHovered,"TabHovered"},
	{ImGuiCol_TabActive,"TabActive"},
	{ImGuiCol_TabUnfocused,"TabUnfocused"},
	{ImGuiCol_TabUnfocusedActive,"TabUnfocusedActive"},
	{ImGuiCol_PlotLines,"PlotLines"},
	{ImGuiCol_PlotLinesHovered,"PlotLinesHovered"},
	{ImGuiCol_PlotHistogram,"PlotHistogram"},
	{ImGuiCol_PlotHistogramHovered,"PlotHistogramHovered"},
	{ImGuiCol_TableHeaderBg,"TableHeaderBg"},
	{ImGuiCol_TableBorderStrong,"TableBorderStrong"},
	{ImGuiCol_TableBorderLight,"TableBorderLight"},
	{ImGuiCol_TableRowBg,"TableRowBg"},
	{ImGuiCol_TableRowBgAlt,"TableRowBgAlt"},
	{ImGuiCol_TextSelectedBg,"TextSelectedBg"},
	{ImGuiCol_DragDropTarget,"DragDropTarget"},
	{ImGuiCol_NavHighlight,"NavHighlight"},
	{ImGuiCol_NavWindowingHighlight,"NavWindowingHighlight"},
	{ImGuiCol_NavWindowingDimBg,"NavWindowingDimBg"},
	{ImGuiCol_ModalWindowDimBg,"ModalWindowDimBg"},
};

enum ImVec2Style
{
	ImVec2Style_WindowPadding = 0,
	ImVec2Style_WindowMinSize,
	ImVec2Style_WindowTitleAlign,
	ImVec2Style_FramePadding,
	ImVec2Style_ItemSpacing,
	ImVec2Style_ItemInnerSpacing,
	ImVec2Style_CellPadding,
	ImVec2Style_ButtonTextAlign,
	ImVec2Style_SelectableTextAlign,
	ImVec2Style_SeparatorTextAlign,
	ImVec2Style_SeparatorTextPadding,
	ImVec2Style_Count,
};

#define FLOAT_NOT_EQUAL(a, b) (abs((a)-(b)) > 0.0001)
#define COLOR_IS_EQUAL(a, b) ((a).x == (b).x && (a).y == (b).y && (a).z == (b).z && (a).w == (b).w)
#define IMVEC2_IS_EQUAL(a, b) ((a).x == (b).x && (a).y == (b).y)

class GUIMAKER_API StyleSettings
{
public:
	float FloatStyles[FloatStyle_Count];
	ImVec2 ImVec2Styles[ImVec2Style_Count];
	ImVec4 Colors[ImGuiCol_COUNT];
	int SetStylesCount = 0;
	int SetColorsCount = 0;
	UINT32 EditedStyles = 0;
	UINT64 EditedColors = 0;
	std::string Font;
	bool PushedFont = false;


	UINT32 IsFloatStyle = 
		  1 << ImGuiStyleVar_Alpha
		| 1 << ImGuiStyleVar_DisabledAlpha
		| 1 << ImGuiStyleVar_WindowRounding
		| 1 << ImGuiStyleVar_WindowBorderSize
		| 1 << ImGuiStyleVar_ChildRounding
		| 1 << ImGuiStyleVar_ChildBorderSize
		| 1 << ImGuiStyleVar_PopupRounding
		| 1 << ImGuiStyleVar_PopupBorderSize
		| 1 << ImGuiStyleVar_FrameRounding
		| 1 << ImGuiStyleVar_FrameBorderSize
		| 1 << ImGuiStyleVar_IndentSpacing
		| 1 << ImGuiStyleVar_ScrollbarSize
		| 1 << ImGuiStyleVar_ScrollbarRounding
		| 1 << ImGuiStyleVar_GrabMinSize
		| 1 << ImGuiStyleVar_GrabRounding
		| 1 << ImGuiStyleVar_TabRounding
		| 1 << ImGuiStyleVar_TabBarBorderSize
		| 1 << ImGuiStyleVar_SeparatorTextBorderSize;

	UINT32 IsImVec2Style = 
		  1 << ImGuiStyleVar_WindowPadding
		| 1 << ImGuiStyleVar_WindowMinSize
		| 1 << ImGuiStyleVar_WindowTitleAlign
		| 1 << ImGuiStyleVar_FramePadding
		| 1 << ImGuiStyleVar_ItemSpacing
		| 1 << ImGuiStyleVar_ItemInnerSpacing
		| 1 << ImGuiStyleVar_CellPadding
		| 1 << ImGuiStyleVar_ButtonTextAlign
		| 1 << ImGuiStyleVar_SelectableTextAlign
		| 1 << ImGuiStyleVar_SeparatorTextAlign
		| 1 << ImGuiStyleVar_SeparatorTextPadding;

	StyleSettings()
	{
		if (ImGui::GetCurrentContext())
		{
			ResetStyles();
			ResetColors();
		}
	}

	StyleSettings(const StyleSettings& other)
	{
		memcpy(FloatStyles, other.FloatStyles, sizeof(FloatStyles));
		memcpy(ImVec2Styles, other.ImVec2Styles, sizeof(ImVec2Styles));
		memcpy(Colors, other.Colors, sizeof(Colors));
		SetStylesCount = other.SetStylesCount;
		SetColorsCount = other.SetColorsCount;
	}

	void SetFloatStyle(const int style)
	{
		if (const int float_style_index = GetFloatStyleIndex(style); float_style_index != -1)
		{
			if (EditedStyles & 1 << style)
			{
				ImGui::PushStyleVar(style, FloatStyles[float_style_index]);
				SetStylesCount++;
			}
		}
	}


	void PopStyles() const
	{
		if (SetStylesCount > 0)
			ImGui::PopStyleVar(SetStylesCount);
	}

	void SetColor(const int color)
	{
		if (color >= ImGuiCol_COUNT)
			return;

		if (EditedColors & 1ULL << color)
		{
			ImGui::PushStyleColor(color, Colors[color]);
			SetColorsCount++;
		}
	}

	std::string GenerateStylesCode()
	{
		std::string code;
		if (SetStylesCount > 0)
		{
			
			for (int i = 0; i < ImGuiStyleVar_COUNT; i++)
			{
				if (IsFloatStyle & (1 << i))
				{
					if (const int float_index = GetFloatStyleIndex(i); EditedStyles & 1 << i)
					{
						if (const auto style_id_index = STYLE_ID.find(i); style_id_index != STYLE_ID.end())
						{
							code += fmt::format("ImGui::PushStyleVar(ImGuiStyleVar_{}, {:.3f}f);\n", style_id_index->second, FloatStyles[float_index]);
						}
					}
				}
				else if (IsImVec2Style & (1 << i))
				{
					if (const int im_vec2_index = GetImVec2StyleIndex(i); EditedStyles & 1 << i)
					{
						if (const auto style_id_index = STYLE_ID.find(i); style_id_index != STYLE_ID.end())
						{
							code += fmt::format("ImGui::PushStyleVar(ImGuiStyleVar_{}, ImVec2({}f, {:.3f}f));\n", style_id_index->second, ImVec2Styles[im_vec2_index].x, ImVec2Styles[im_vec2_index].y);
						}
					}
				}
			}
		}
		if (SetColorsCount > 0)
		{
			for (int i = 0; i < ImGuiCol_COUNT; i++)
			{
				if (EditedColors & 1ULL << i)
				{
					if (const auto color_id_index = COLOR_ID.find(i); color_id_index != COLOR_ID.end())
					{
						code += fmt::format("ImGui::PushStyleColor(ImGuiCol_{}, ImVec4({:.3f}f, {:.3f}f, {:.3f}f, {:.3f}f));\n", color_id_index->second, Colors[i].x, Colors[i].y, Colors[i].z, Colors[i].w);
					}
				}
			}
		}
		return code;
	}

	std::string GenerateStylesLuaCode()
	{
		std::string code;
		if (SetStylesCount > 0)
		{
			
			for (int i = 0; i < ImGuiStyleVar_COUNT; i++)
			{
				if (IsFloatStyle & (1 << i))
				{
					if (const int float_index = GetFloatStyleIndex(i); EditedStyles & 1 << i)
					{
						if (const auto style_id_index = STYLE_ID.find(i); style_id_index != STYLE_ID.end())
						{
							code += fmt::format("ImGui.PushStyleVar(ImGuiStyleVar.{}, {:.3f})\n", style_id_index->second, FloatStyles[float_index]);
						}
					}
				}
				else if (IsImVec2Style & (1 << i))
				{
					if (const int im_vec2_index = GetImVec2StyleIndex(i); EditedStyles & 1 << i)
					{
						if (const auto style_id_index = STYLE_ID.find(i); style_id_index != STYLE_ID.end())
						{
							code += fmt::format("ImGui.PushStyleVar(ImGuiStyleVar.{}, {:.3f}, {:.3f})\n", style_id_index->second, ImVec2Styles[im_vec2_index].x, ImVec2Styles[im_vec2_index].y);
						}
					}
				}
			}
		}
		if (SetColorsCount > 0)
		{
			for (int i = 0; i < ImGuiCol_COUNT; i++)
			{
				if (EditedColors & 1ULL << i)
				{
					if (const auto color_id_index = COLOR_ID.find(i); color_id_index != COLOR_ID.end())
					{
						code += fmt::format("ImGui.PushStyleColor(ImGuiCol.{}, {:.3f}, {:.3f}, {:.3f}, {:.3f})\n", color_id_index->second, Colors[i].x, Colors[i].y, Colors[i].z, Colors[i].w);
					}
				}
			}
		}
		return code;
	}

	void ResetStyles()
	{
		EditedStyles = 0;
		for (int i = 0; i < FloatStyle_Count; i++)
		{
			FloatStyles[i] = GetImGuiFloat(i);
		}
		for (int i = 0; i < ImVec2Style_Count; i++)
		{
			ImVec2Styles[i] = GetImGuiImVec2(i);
		}
	}

	[[nodiscard]] std::string GeneratePopCode() const
	{
		std::string code;
		if (SetStylesCount > 0)
		{
			code += "ImGui::PopStyleVar(" + std::to_string(SetStylesCount) + ");\n";
		}
		if (SetColorsCount > 0)
		{
			code += "ImGui::PopStyleColor(" + std::to_string(SetColorsCount) + ");\n";
		}
		return code;
	}

[[nodiscard]] std::string GeneratePopLuaCode() const
	{
		std::string code;
		if (SetStylesCount > 0)
		{
			code += "ImGui.PopStyleVar(" + std::to_string(SetStylesCount) + ")\n";
		}
		if (SetColorsCount > 0)
		{
			code += "ImGui.PopStyleColor(" + std::to_string(SetColorsCount) + ")\n";
		}
		return code;
	}

	void ResetColors()
	{
		EditedColors = 0;
		for (int i = 0; i < ImGuiCol_COUNT; i++)
		{
			Colors[i] = ImGui::GetStyleColorVec4(i);
		}
	}

	void PopColors() const
	{
		if (SetColorsCount > 0)
			ImGui::PopStyleColor(SetColorsCount);
	}

	void GetPropertyEditor(const int style)
	{
		if ( 1 << style & IsFloatStyle)
		{
			if (const auto style_name_index = STYLE_NAMES.find(style); style_name_index != STYLE_NAMES.end())
			{
				const float old_value = FloatStyles[GetFloatStyleIndex(style)];
				ImGui::InputFloat(style_name_index->second, &FloatStyles[GetFloatStyleIndex(style)]);
				if (FLOAT_NOT_EQUAL(old_value, FloatStyles[GetFloatStyleIndex(style)]))
				{
					EditedStyles |= 1 << style;
				}
			}
		}
		else if ( 1 << style & IsImVec2Style)
		{
			if (const auto style_name_index = STYLE_NAMES.find(style); style_name_index != STYLE_NAMES.end())
			{
				const auto old_value = ImVec2Styles[GetImVec2StyleIndex(style)];
				ImGui::InputFloat2(style_name_index->second, &ImVec2Styles[GetImVec2StyleIndex(style)].x);
				if (!IMVEC2_IS_EQUAL(old_value, ImVec2Styles[GetImVec2StyleIndex(style)]))
				{
					EditedStyles |= 1 << style;
				}
			}
		}
	}

	void GetColorEditor(const int color)
	{
		if (color >= ImGuiCol_COUNT)
			return;

		if (const auto color_name_index = COLOR_NAMES.find(color); color_name_index != COLOR_NAMES.end())
		{
			const auto old_color = Colors[color];
			ImGui::ColorEdit4(color_name_index->second, &Colors[color].x);
			if (!COLOR_IS_EQUAL(old_color, Colors[color]))
			{
				EditedColors |= 1ULL << color;
			}
		}
	}

	void SetStyle(const int style)
	{
		if ( 1 << style & IsFloatStyle)
		{
			SetFloatStyle(style);
		}
		else if ( 1 << style & IsImVec2Style)
		{
			SetImVec2Style(style);
		}
	}


	void SetImVec2Style(const int style)
	{
		if (const int im_vec2_style_index = GetImVec2StyleIndex(style); im_vec2_style_index != -1)
		{
			if (!IMVEC2_IS_EQUAL(ImVec2Styles[im_vec2_style_index], GetImGuiImVec2(im_vec2_style_index)))
			{
				ImGui::PushStyleVar(style, ImVec2Styles[im_vec2_style_index]);
				SetStylesCount++;
			}
		}
	}

	static float GetImGuiFloat(const int style)
	{
		switch (style)
		{
			case FloatStyle_Alpha:
				return ImGui::GetStyle().Alpha;
			case FloatStyle_DisabledAlpha:
				return ImGui::GetStyle().DisabledAlpha;
			case FloatStyle_WindowRounding:
				return ImGui::GetStyle().WindowRounding;
			case FloatStyle_WindowBorderSize:
				return ImGui::GetStyle().WindowBorderSize;
			case FloatStyle_ChildRounding:
				return ImGui::GetStyle().ChildRounding;
			case FloatStyle_ChildBorderSize:
				return ImGui::GetStyle().ChildBorderSize;
			case FloatStyle_PopupRounding:
				return ImGui::GetStyle().PopupRounding;
			case FloatStyle_PopupBorderSize:
				return ImGui::GetStyle().PopupBorderSize;
			case FloatStyle_FrameRounding:
				return ImGui::GetStyle().FrameRounding;
			case FloatStyle_FrameBorderSize:
				return ImGui::GetStyle().FrameBorderSize;
			case FloatStyle_IndentSpacing:
				return ImGui::GetStyle().IndentSpacing;
			case FloatStyle_ScrollbarSize:
				return ImGui::GetStyle().ScrollbarSize;
			case FloatStyle_ScrollbarRounding:
				return ImGui::GetStyle().ScrollbarRounding;
			case FloatStyle_GrabMinSize:
				return ImGui::GetStyle().GrabMinSize;
			case FloatStyle_GrabRounding:
				return ImGui::GetStyle().GrabRounding;
			case FloatStyle_TabRounding:
				return ImGui::GetStyle().TabRounding;
			case FloatStyle_TabBarBorderSize:
				return ImGui::GetStyle().TabBarBorderSize;
			case FloatStyle_SeparatorTextBorderSize:
				return ImGui::GetStyle().SeparatorTextBorderSize;
			default:
				return -1;
		}
	}

	static int GetFloatStyleIndex(const int style)
	{
		switch (style)
		{
			case ImGuiStyleVar_Alpha:
				return FloatStyle_Alpha;
			case ImGuiStyleVar_DisabledAlpha:
				return FloatStyle_DisabledAlpha;
			case ImGuiStyleVar_WindowRounding:
				return FloatStyle_WindowRounding;
			case ImGuiStyleVar_WindowBorderSize:
				return FloatStyle_WindowBorderSize;
			case ImGuiStyleVar_ChildRounding:
				return FloatStyle_ChildRounding;
			case ImGuiStyleVar_ChildBorderSize:
				return FloatStyle_ChildBorderSize;
			case ImGuiStyleVar_PopupRounding:
				return FloatStyle_PopupRounding;
			case ImGuiStyleVar_PopupBorderSize:
				return FloatStyle_PopupBorderSize;
			case ImGuiStyleVar_FrameRounding:
				return FloatStyle_FrameRounding;
			case ImGuiStyleVar_FrameBorderSize:
				return FloatStyle_FrameBorderSize;
			case ImGuiStyleVar_IndentSpacing:
				return FloatStyle_IndentSpacing;
			case ImGuiStyleVar_ScrollbarSize:
				return FloatStyle_ScrollbarSize;
			case ImGuiStyleVar_ScrollbarRounding:
				return FloatStyle_ScrollbarRounding;
			case ImGuiStyleVar_GrabMinSize:
				return FloatStyle_GrabMinSize;
			case ImGuiStyleVar_GrabRounding:
				return FloatStyle_GrabRounding;
			case ImGuiStyleVar_TabRounding:
				return FloatStyle_TabRounding;
			case ImGuiStyleVar_TabBarBorderSize:
				return FloatStyle_TabBarBorderSize;
			case ImGuiStyleVar_SeparatorTextBorderSize:
				return FloatStyle_SeparatorTextBorderSize;
			default:
				return -1;
		}
	}

	static int GetImVec2StyleIndex(const int style)
	{
		switch (style)
		{
			case ImGuiStyleVar_WindowPadding:
				return ImVec2Style_WindowPadding;
			case ImGuiStyleVar_WindowMinSize:
				return ImVec2Style_WindowMinSize;
			case ImGuiStyleVar_WindowTitleAlign:
				return ImVec2Style_WindowTitleAlign;
			case ImGuiStyleVar_FramePadding:
				return ImVec2Style_FramePadding;
			case ImGuiStyleVar_ItemSpacing:
				return ImVec2Style_ItemSpacing;
			case ImGuiStyleVar_ItemInnerSpacing:
				return ImVec2Style_ItemInnerSpacing;
			case ImGuiStyleVar_CellPadding:
				return ImVec2Style_CellPadding;
			case ImGuiStyleVar_ButtonTextAlign:
				return ImVec2Style_ButtonTextAlign;
			case ImGuiStyleVar_SelectableTextAlign:
				return ImVec2Style_SelectableTextAlign;
			case ImGuiStyleVar_SeparatorTextAlign:
				return ImVec2Style_SeparatorTextAlign;
			case ImGuiStyleVar_SeparatorTextPadding:
				return ImVec2Style_SeparatorTextPadding;
			default:
				return -1;
		}
	}

	static ImVec2 GetImGuiImVec2(const int style)
	{
		switch (style)
		{
			case ImVec2Style_WindowPadding:
				return ImGui::GetStyle().WindowPadding;
			case ImVec2Style_WindowMinSize:
				return ImGui::GetStyle().WindowMinSize;
			case ImVec2Style_WindowTitleAlign:
				return ImGui::GetStyle().WindowTitleAlign;
			case ImVec2Style_FramePadding:
				return ImGui::GetStyle().FramePadding;
			case ImVec2Style_ItemSpacing:
				return ImGui::GetStyle().ItemSpacing;
			case ImVec2Style_ItemInnerSpacing:
				return ImGui::GetStyle().ItemInnerSpacing;
			case ImVec2Style_CellPadding:
				return ImGui::GetStyle().CellPadding;
			case ImVec2Style_ButtonTextAlign:
				return ImGui::GetStyle().ButtonTextAlign;
			case ImVec2Style_SelectableTextAlign:
				return ImGui::GetStyle().SelectableTextAlign;
			case ImVec2Style_SeparatorTextAlign:
				return ImGui::GetStyle().SeparatorTextAlign;
			case ImVec2Style_SeparatorTextPadding:
				return ImGui::GetStyle().SeparatorTextPadding;
			default:
				return {-1, -1};
		}
	}

};
}

