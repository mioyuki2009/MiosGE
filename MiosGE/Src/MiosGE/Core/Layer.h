#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Core/Timestep.h"
namespace miosGE {

	class MIOS_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate(Timestep ts) {};
		virtual void OnImGuiRender() {};
		virtual void OnEvent(Event& event) {};

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName; 
	};

}
