#pragma once
#include "entt.hpp"
#include "Core/Timestep.h"
namespace miosGE {
	class Entity;
	class EditorCamera;
	class Scene {
	public:
		Scene();
		virtual ~Scene();

		Entity CreateEntity(const std::string& name = std::string());
		void DestoryEntity(Entity entity);
		
		void OnUpdateEditor(Timestep ts, EditorCamera& camera);
		void OnUpdateRuntime(Timestep ts);
		void OnViewportResize(uint32_t width, uint32_t height);

		Entity GetPrimaryCameraEntity();

	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

	private:
		entt::registry m_Registry;

		uint32_t m_ViewportWidth = 0;
		uint32_t m_ViewportHeight = 0;

		friend class Entity;
		friend class SceneHierarchyPanel;
		friend class SceneSerializer;
	};
}