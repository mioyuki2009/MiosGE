#pragma once
#include "entt.hpp"
#include "Core/Timestep.h"
namespace miosGE {
	class Entity;

	class Scene {
	public:
		Scene();
		virtual ~Scene();

		Entity CreateEntity(const std::string& name = std::string());
		void OnUpdate(Timestep ts);

	private:
		entt::registry m_Registry;
		friend class Entity;
	};
}