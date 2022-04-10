#pragma once
#include "entt.hpp"
namespace miosGE {
	class Scene {
	public:
		Scene();
		virtual ~Scene();
	private:
		entt::registry m_Registry;
	};
}