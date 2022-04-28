#include "MiosPch.h"
#include "OrthographicCameraController.h"

#include "Input.h"
#include "KeyCodes.h"
#include "Debug/Instrumentor.h"
#include "Core/KeyCodes.h"
namespace miosGE {
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		:m_AspectRatio(aspectRatio), m_Rotation(rotation),
		m_Camera(-aspectRatio * m_ZoomLevel, aspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		MIOS_PROFILE_FUNCTION();
		if (Input::IsKeyPressed(Key::A)) {
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(Key::D)) {
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;
		}
		if (Input::IsKeyPressed(Key::W)) {
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(Key::S)) {
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
		}

		if (m_Rotation) {
			if (Input::IsKeyPressed(Key::Q)) {
				m_CameraRotation += m_CameraRotationSpeed * ts;
			}
			if (Input::IsKeyPressed(Key::E)) {
				m_CameraRotation -= m_CameraRotationSpeed * ts;
			}
			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		MIOS_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(MIOS_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(MIOS_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));

	}

	void OrthographicCameraController::OnResize(float width, float height)
	{
		m_AspectRatio = width / height;
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		MIOS_PROFILE_FUNCTION();

		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		MIOS_PROFILE_FUNCTION();

		OnResize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}
}
