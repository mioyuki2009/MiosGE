#include "MiosPch.h"
#include "SceneCamera.h"
#include "glm/gtc/matrix_transform.hpp"

namespace miosGE {

	SceneCamera::SceneCamera()
	{
		RecalculateProjection();
	}

	void SceneCamera::SetPerspective(float verticalFov, float nearClip, float farClip) {
		m_ProjectionType = ProjectionType::Perspective;
		m_PerspectiveFov = verticalFov;
		m_PerspectiveNear = nearClip;
		m_PerspectiveFar = farClip;
		RecalculateProjection();
	}

	void SceneCamera::SetOrghographic(float size, float nearClip, float farClip)
	{
		m_ProjectionType = ProjectionType::Orghographic;
		m_OrghographicSize = size;
		m_OrghographicNear = nearClip;
		m_OrghographicFar = farClip;
		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection() {
		
		if (m_ProjectionType == ProjectionType::Perspective) 
		{
			m_Projection = glm::perspective(m_PerspectiveFov, m_AspectRatio, m_PerspectiveNear, m_PerspectiveFar);
		}
		else if (m_ProjectionType == ProjectionType::Orghographic) 
		{
			float orthoLeft = -m_OrghographicSize * m_AspectRatio * 0.5f;
			float orthoRight = -orthoLeft;
			float orthoBottom = -m_OrghographicSize * 0.5f;
			float orthoTop = -orthoBottom;
			m_Projection = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop,
				m_OrghographicNear, m_OrghographicFar);
		}
		
	}

	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height) {
		m_AspectRatio = float(width) / float(height);
		RecalculateProjection();
	}

}