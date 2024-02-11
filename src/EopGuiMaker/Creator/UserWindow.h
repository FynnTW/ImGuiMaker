#pragma once
#include "Components/Components.h"


namespace EopGuiMaker
{
	class GUIMAKER_API UserWindow
	{
	public:
		UserWindow() = default;
		~UserWindow() = default;

		void SetWindowName(const char* window_name);
		void SetWindowSize(float width, float height);
		bool IsWindowOpen() const;
		bool IsGridEnabled() const;
		void SetGridSize(int rows, int columns);
		void DrawGrid(bool draw);
		void CloseWindow();
		void OpenWindow();
		void DrawWindow();
		char WindowName[128] = "New Window";
		float WindowSize[2] = { 1280.0f, 720.0f };
		float WindowPosition[2] = { 0.0, 0.0};
		bool EnableGrid = true;
		int GridSize[2] = { 10, 10 };
		int GridAlpha = 120;
		void PushComponent(Component* component);
		void PopComponent(const Component* component);
		Component* GetSelectedComponent(ImGuiContext* context);
		Component* HoveredComponent;
		Component* SelectedComponent;

		std::vector<Component*>::iterator begin() { return m_Components.begin(); }
		std::vector<Component*>::iterator end() { return m_Components.end(); }
	private:
		bool m_IsWindowOpen = false;
		std::vector<Component*> m_Components;
	};
}
