#include "MiosPch.h"
#include "LayerStack.h"

namespace miosGE {
	LayerStack::LayerStack() {
		m_LayersInstert = m_Layers.begin();
	}
	LayerStack::~LayerStack() {
		for (auto& layer : m_Layers) {
			delete layer;
		}
	}
	void LayerStack::PushLayer(Layer* layer) {
		m_LayersInstert = m_Layers.emplace(m_LayersInstert, layer);
	}
	
	void LayerStack::PushOverlay(Layer* overlay) {
		m_Layers.emplace_back(overlay);
	}
	
	void LayerStack::PopLayer(Layer* layer) {
		assert(layer == m_Layers[0]);

		const auto& it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
			m_LayersInstert--;
		}
	}
	
	void LayerStack::PopOverlay(Layer* overlay) {
		assert(overlay == m_Layers[m_Layers.size() - 1]);

		const auto& it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
		}
	}


}