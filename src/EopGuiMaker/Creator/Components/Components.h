#pragma once

#include "imgui.h"
#include "EopGuiMaker/Creator/Components/StyleSettings.h"
#include "EopGuiMaker/ImGui/imgui_stdlib.h"

#define FLOAT_NOT_EQUAL(a, b) (abs((a)-(b)) < 0.0001)
#define COLOR_IS_EQUAL(a, b) ((a).x == (b).x && (a).y == (b).y && (a).z == (b).z && (a).w == (b).w)
#define IMVEC2_IS_EQUAL(a, b) ((a).x == (b).x && (a).y == (b).y)
#define IS_IN_RECT(a,b,c) ((a).x > (b).x && (a).x < (c).x && (a).y > (b).y && (a).y < (c).y))
#define IMVEC2_ADD(a, b) ImVec2((a).x + (b).x, (a).y + (b).y)

namespace EopGuiMaker
{
#pragma region Forward Declarations
	class ChildComponent;
	class ParentComponent;
	class UserWindow;
	class StyleSettings;
#pragma endregion

#pragma region Enums
	enum ComponentTypes {
		ComponentType_Window,
		ComponentType_Child,
		ComponentType_Button,
		ComponentType_Text,
		ComponentType_Count
	};
#pragma endregion Enums

	/**
	 * \brief Base component class
	 */
	class GUIMAKER_API Component
	{
	public:
		ImVec2 Position{};
		ImVec2 Size{};
		StyleSettings Styles;
		std::string Label;
		std::string TempLabel;
		int Flags = 0;
		int Type;
		UINT32 ActiveStyles;
		UINT64 ActiveColors;
		
		virtual void SetFont() = 0;
		virtual void PopFont() const = 0;
		virtual void SetSize(ImVec2 size) = 0;
		virtual void Draw() = 0;
		virtual void DrawProperties() = 0;
		virtual void SetStyles() = 0;
		virtual void PopStyles() const = 0;
		virtual std::string GenerateCode() = 0;
		virtual std::string GenerateLuaCode() = 0;
		int GetWindowFlags(int flags, UINT32 filter);

	};

	class GUIMAKER_API Widget : virtual public Component
	{
	public:
		Widget() = default;
		~Widget() = default;
		void SetPosition(ImVec2 position);
		void SetSize(ImVec2 size) override;
		void DrawParentsBox();
		virtual Widget* Clone(){ return this;}
		bool IsSnappedSize = true;
		bool IsSnappedPos = true;
		virtual void PropertiesWindow(){}
		UserWindow* ParentWindow;
		ParentComponent* Parent = nullptr;
		void DrawCopyButtons();
		void DrawSnapOptions();
		void DrawResetButtons();
		void DrawProperties() override;
		void SetStyles() override;
		void SetFont() override;
		void PopFont() const override;
		void PopStyles() const override;
	};

	
	class GUIMAKER_API ButtonComponent : public Widget
	{
		public:
		ButtonComponent(const std::string& label, const ImVec2 size, const std::string& text)
		{
			Size = size;
			Position = {0,0};
			Label = label;
			Text = text;
			TempLabel = label;

			ActiveStyles  = 
			1 << ImGuiStyleVar_ButtonTextAlign
			| 1 << ImGuiStyleVar_FramePadding
			| 1 << ImGuiStyleVar_FrameRounding
			| 1 << ImGuiStyleVar_FrameBorderSize;

			ActiveColors = 
			1 << ImGuiCol_Button
			| 1 << ImGuiCol_ButtonHovered
			| 1 << ImGuiCol_ButtonActive
			| 1 << ImGuiCol_Text
			| 1 << ImGuiCol_Border
			| 1 << ImGuiCol_BorderShadow;
			Type = ComponentType_Button;
		}
		ButtonComponent* Clone() override;
		void PropertiesWindow() override;
		std::string Text;
		
		std::string GenerateCode() override;
		std::string GenerateLuaCode() override;
		void Draw() override;
	};

	class GUIMAKER_API ParentComponent : virtual public Component
	{
	public:
		virtual void PushComponent(Widget* component) = 0;
		virtual void PopComponent(const Widget* component) = 0;
		void SnapComponents();
		std::vector<ChildComponent*> Children;
	protected:
		bool m_IsWindowOpen = false;
		std::vector<Widget*> m_Components;
	};

	class GUIMAKER_API UserWindow : public ParentComponent
	{
	public:
		UserWindow()
		{
			Position = { 0.0, 0.0 };
			Size = { 1280.0f, 720.0f };
			Label = "New Window";
			Flags = ImGuiWindowFlags_NoCollapse
					| ImGuiWindowFlags_NoTitleBar
					| ImGuiWindowFlags_NoMove
					| ImGuiWindowFlags_NoResize
					| ImGuiWindowFlags_NoDecoration;
			Type = ComponentType_Window;
			ActiveStyles = UINT32_MAX;
			ActiveColors = UINT64_MAX;
		}
		~UserWindow() = default;

		void SetWindowName(const char* window_name);
		bool IsWindowOpen() const;
		void SetSize(ImVec2 size) override;
		bool IsGridEnabled() const;
		void SetGridSize(int rows, int columns);
		void DrawGrid() const;
		void CloseWindow();
		[[nodiscard]] ImVec2 GetSpacing() const;
		void OpenWindow();
		void SetFont() override;
		void Draw() override;
		void PopFont() const override;
		void DrawComponent(Widget* component);
		void ComponentKeyPress();
		bool EnableGrid = true;
		struct Grid
		{
			int Columns;
			int Rows;
		};
		Grid GridSize = { 50, 50 };
		int GridAlpha = 1;
		void PushComponent(Widget* component) override;
		void PopComponent(const Widget* component) override;
		std::string GenerateCode() override;
		std::string GenerateLuaCode() override;
		void DrawProperties() override;
		void SetStyles() override;
		void PopStyles() const override;

		Widget* HoveredComponent = nullptr;
		Widget* SelectedComponent = nullptr;
		Widget* CopiedComponent = nullptr;
		StyleSettings* CopiedStyle = nullptr;
		std::vector<Widget*> DeletionComponents;
	};


	class GUIMAKER_API ChildComponent : public Widget, public ParentComponent
	{
		public:
		explicit ChildComponent(const char* label, const ImVec2 size = {0,0}, const ImVec2 position = {0,0})
		{
			Size = size;
			Label = label;
			TempLabel = label;
			Position = position;
			ActiveStyles = UINT32_MAX;
			ActiveColors = UINT64_MAX;
			Styles.Colors[ImGuiCol_ChildBg] = { 1.0f,  1.0f, 1.0f, 0.04f };
			Styles.EditedColors |= 1 << ImGuiCol_ChildBg;
			Styles.Colors[ImGuiCol_Border] = { 0.8627451f, 0.13533255f, 0.13533255f, 1.0f };
			Styles.EditedColors |= 1 << ImGuiCol_Border;
			Type = ComponentType_Child;
			Flags |= ImGuiChildFlags_Border;

		}

		bool ShowEditorBorder = true;
		bool ShowEditorBackground = true;
		int WindowFlags = 0;
		
		void PushComponent(Widget* component) override;
		void PopComponent(const Widget* component) override;

		void PropertiesWindow() override;
		std::string GenerateCode() override;
		std::string GenerateLuaCode() override;
		void Draw() override;

		void GetChildFlags();

			
	};

	inline int COPY_COUNT = 0;

	bool UpdateLabel(const std::string& old_label, const std::string& new_label);

	struct AddFont
	{
		std::string FontName;
		std::string FontPath;
		float FontSize;
	};

	inline std::vector<AddFont*> FONT_QUEUE {

	};

	inline std::unordered_map<std::string, ImFont*> FONTS {

	};

}
