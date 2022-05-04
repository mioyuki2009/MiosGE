#include "MiosPch.h"
#include "Entity.h"

namespace miosGE {

	Entity::Entity(entt::entity handle, Scene* scene):
		m_EntityHandle(handle), m_Scene(scene)
	{
	}
}