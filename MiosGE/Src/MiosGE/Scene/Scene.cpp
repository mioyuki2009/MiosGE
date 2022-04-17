#include "MiosPch.h"
#include "Scene.h"
#include <tuple>
#include "glm/glm.hpp"
#include "Components.h"
#include "Renderer/Renderer2D.h"
#include "Entity.h"
namespace miosGE {

	static void DoMath(const glm::mat4& transform) {
	
	}
	
	static void OnTransformConstruct(entt::registry& registry, entt::entity entity) {
	
	}


	Scene::Scene()
	{
#if 0
		entt::entity entity = m_Registry.create();
		m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));
		
		m_Registry.on_construct<TransformComponent>().connect<&OnTransformConstruct>();

		if (m_Registry.any_of<TransformComponent>(entity))
			TransformComponent& transform = m_Registry.get<TransformComponent>(entity);

		auto view = m_Registry.view<TransformComponent>();
		for (auto entity : view) {
			TransformComponent& transform = m_Registry.get<TransformComponent>(entity);
		}

		auto group = m_Registry.group(entt::get<TransformComponent, SpriteTransformComponent>);
		for (auto entity : group) {
			auto [transform, sprite] = group.get<TransformComponent, SpriteTransformComponent>(entity);
			Renderer2D::DrawQuad(transform, sprite.Color);
		}
#endif
	}

	Scene::~Scene()
	{
	}


	Entity Scene::CreateEntity(const std::string& name) {
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;

		return entity;
	}

	void Scene::OnUpdate(Timestep ts) {

		Camera* mainCamera = nullptr;
		glm::mat4* cameraTransform = nullptr;
		{
			auto group = m_Registry.group(entt::get<TransformComponent, CameraComponent>);
			for (auto entity : group) {
				auto [transform, camera] = group.get<TransformComponent, CameraComponent>(entity);

				if (camera.Primary) {
					mainCamera = &camera.camera;
					cameraTransform = &transform.Transform;
					break;
				}
			}
		}

		if (mainCamera) {

			Renderer2D::BeginScene(mainCamera->GetProjection(), *cameraTransform);

			auto group = m_Registry.group(entt::get<TransformComponent, SpriteTransformComponent>);
			for (auto entity : group) {
				auto [transform, sprite] = group.get<TransformComponent, SpriteTransformComponent>(entity);
				Renderer2D::DrawQuad(transform, sprite.Color);
			}

			Renderer2D::EndScene();
		}
	}
}