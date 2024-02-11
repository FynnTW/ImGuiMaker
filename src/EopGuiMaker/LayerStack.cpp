#include "gmpch.h"
#include "LayerStack.h"

namespace EopGuiMaker {

	LayerStack::LayerStack()
	{
		m_LayerInsert = m_Layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (const Layer* layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
	}

	void LayerStack::PopLayer(const Layer* layer)
	{
		if (const auto it = std::find(m_Layers.begin(), m_Layers.end(), layer); it != m_Layers.end())
		{
			m_Layers.erase(it);
			--m_LayerInsert;
		}
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
	}

	void LayerStack::PopOverlay(const Layer* overlay)
	{
		if (const auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay); it != m_Layers.end())
			m_Layers.erase(it);
	}

}