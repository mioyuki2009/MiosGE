#pragma once
#include "Core/Layer.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"

namespace miosGE {
	class MIOS_API ImGuiLayer :public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End(); 

		void BlockEvents(bool block) { m_BlockEvents = block; }
		void SetDarkThemeColors();
	
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};
}
