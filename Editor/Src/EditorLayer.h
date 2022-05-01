#pragma once

#include "MiosGE/MioGE.h"
#include "Panels/SceneHierarchyPanel.h"
#include "MiosGE/Renderer/EditorCamera.h"

namespace miosGE {
	class EditorCamera;

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;
	private:
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);

		void NewScene();
		void OpenScene();
		void SaveSceneAs();

	private:
		OrthographicCameraController m_CameraController;

		Ref<Texture2D> m_CheckerboardTexture;
		Ref<Framebuffer> m_Framebuffer;
		Ref<Scene> m_ActiveScene;
		Entity m_SquareEntity;
		Entity m_CameraEntity;
		Entity m_SecondCamera;

		Entity m_HoveredEntity;

		bool m_PrimaryCamera = false;
		EditorCamera m_EditorCamera;

		bool m_ViewportFocused = false;
		bool m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f};
		glm::vec2 m_ViewportBounds[2] = {};

		int m_GizmoType = -1;
		// Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
	};

}