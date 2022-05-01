#pragma once

#include "Renderer/Camera.h"
#include "glm/glm.hpp"

namespace miosGE {
	
	class SceneCamera : public Camera 
	{
	public:
		enum class ProjectionType {Perspective = 0, Orghographic = 1};
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;

		void SetOrghographic(float size, float nearClip, float farClip);
		void SetPerspective(float verticalFov, float nearClip, float farClip);

		void SetViewportSize(uint32_t width, uint32_t height);

		float GetPerspectiveVerticalFov() const { return m_PerspectiveFov; }
		void SetPerspectiveVerticalFov(float verticalFov) { m_PerspectiveFov = verticalFov; RecalculateProjection(); }
		float GetPerspectiveNearClip() const { return m_PerspectiveNear; }
		void SetPerspectiveNearClip(float nearClip) { m_PerspectiveNear = nearClip; RecalculateProjection(); }
		float GetPerspectiveFarClip() const { return m_PerspectiveFar; }
		void SetPerspectiveFarClip(float farClip) { m_PerspectiveFar = farClip; RecalculateProjection(); }

		float GetOrghographicSize() const { return m_OrghographicSize; }
		void SetOrghographicSize(float size) { m_OrghographicSize = size; RecalculateProjection(); }
		float GetOrghographicNearClip() const { return m_OrghographicNear; }
		void SetOrghographicNearClip(float nearClip) { m_OrghographicNear = nearClip; RecalculateProjection(); }
		float GetOrghographicFarClip() const { return m_OrghographicFar; }
		void SetOrghographicFarClip(float farClip) { m_OrghographicFar = farClip; RecalculateProjection(); }

		ProjectionType GetProjectionType() { return m_ProjectionType; }
		void SetProjectionType(ProjectionType type) { m_ProjectionType = type; RecalculateProjection();}

	private:
		void RecalculateProjection();

	private:
		ProjectionType m_ProjectionType = ProjectionType::Orghographic;
		float m_OrghographicSize = 10.0f;
		float m_OrghographicNear = -1.0f, m_OrghographicFar = 1.0f;
		
		float m_PerspectiveFov = glm::radians(45.0f);
		float m_PerspectiveNear = 0.01f, m_PerspectiveFar = 1000.0f;

		float m_AspectRatio = 0.0f;
	};

}