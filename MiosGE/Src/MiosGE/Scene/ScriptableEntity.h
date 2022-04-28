#pragma once

#include "Entity.h"

namespace miosGE {
	class ScriptableEntity 
	{
	public:
		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}

	protected:
		virtual void OnCreate() {};
		virtual void OnDestory() {};
		virtual void OnUpdate(Timestep ts) {};

	private:
		Entity m_Entity;
		friend Scene;
	};
}
