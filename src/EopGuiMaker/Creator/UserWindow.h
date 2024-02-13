#pragma once
#include "EopGuiMaker/Creator/Components/Components.h"


namespace EopGuiMaker
{
	class Component;
	class ChildComponent;
	class StyleSettings;

	class GUIMAKER_API UserWindow
	{
	public:
		UserWindow() = default;
		~UserWindow() = default;

		void SetWindowName(const char* window_name);
		void SetWindowSize(ImVec2 size);
		bool IsWindowOpen() const;
		bool IsGridEnabled() const;
		void SetGridSize(int rows, int columns);
		void DrawGrid() const;
		void CloseWindow();
		ImVec2 GetSpacing() const;
		void OpenWindow();
		void DrawWindow();
		void SetFont();
		void PopFont() const;
		void GetWindowFlags();
		std::string WindowName = "New Window";
		ImVec2 WindowSize = { 1280.0f, 720.0f };
		ImVec2 WindowPosition = { 0.0, 0.0};
		void SnapComponents();
		void DrawComponent(Component* component);
		void ComponentKeyPress();
		bool EnableGrid = true;
		int Flags = ImGuiWindowFlags_NoCollapse |
					ImGuiWindowFlags_NoTitleBar;
		struct Grid
		{
			int Columns;
			int Rows;
		};
		Grid GridSize = { 50, 50 };
		int GridAlpha = 120;
		void PushComponent(Component* component);
		void PopComponent(const Component* component);
		Component* HoveredComponent;
		Component* SelectedComponent;
		Component* CopiedComponent;
		StyleSettings* CopiedStyle;
		std::string GetOutPutCode();
		std::string GetOutPutCodeLua();
		StyleSettings Style;
		std::vector<Component*> DeletionComponents;
		std::vector<ChildComponent*> Children;

		std::vector<Component*>::iterator begin() { return m_Components.begin(); }
		std::vector<Component*>::iterator end() { return m_Components.end(); }
		void SetStyles();
		void PopStyles() const;
		void PropertiesWindow();
	private:
		bool m_IsWindowOpen = false;
		std::vector<Component*> m_Components;
	};
}
