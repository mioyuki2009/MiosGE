#include "Sandbox2D.h"
#include "imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Renderer/Shader.h"
#include <stdio.h>
#include <chrono>
Sandbox2D::Sandbox2D() :
	Layer("Sandbox2D") , m_CameraController(1280.0f / 720.0f) {	
}

void Sandbox2D::OnAttach()
{
	MIOS_PROFILE_FUNCTION();

	m_CheckerboardTexture = miosGE::Texture2D::Create("assets/textures/Checkerboard.png");
	
    miosGE::FramebufferSpecification fbSpec;
    fbSpec.Width = 1280;
    fbSpec.Height = 720;
}

void Sandbox2D::OnDetach()
{
	MIOS_PROFILE_FUNCTION();

}

void Sandbox2D::OnUpdate(miosGE::Timestep ts)
{
	MIOS_PROFILE_FUNCTION();

	//update
	m_CameraController.OnUpdate(ts);

	//Render
	miosGE::Renderer2D::ResetStates();
	{
		MIOS_PROFILE_SCOPE("Renderer Prep");
        miosGE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		miosGE::RenderCommand::Clear();
	}

	{
		MIOS_PROFILE_SCOPE("Renderer Draw");
		
		static float rotation = 0.0f;
		rotation += ts * 20.0f;

		miosGE::Renderer2D::BeginScene(m_CameraController.GetCamera());
		miosGE::Renderer2D::DrawRotatedQuad({ 1.0f,0.0f }, { 0.8f,0.8f }, glm::radians(-45.0f), { 0.8f,0.2f,0.3f,1.0f });
		miosGE::Renderer2D::DrawQuad({ -1.0f,0.0f }, { 0.8f,0.8f }, { 0.8f,0.2f,0.3f,1.0f });
		miosGE::Renderer2D::DrawQuad({ 0.5f,-0.5f }, { 0.5f,0.75f }, { 0.2f,0.3f,0.8f,1.0f });
		miosGE::Renderer2D::DrawQuad({ 0.0f,0.0f,-0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);
		miosGE::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, glm::radians(rotation), m_CheckerboardTexture, 20.0f);
		miosGE::Renderer2D::EndScene();

		miosGE::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f) {
			for (float x = -5.0f; x < 5.0f; x += 0.5f) {
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				miosGE::Renderer2D::DrawQuad({ x,y }, { 0.45,0.45 }, color);
			}
		}
		miosGE::Renderer2D::EndScene();
	}

	/*if (miosGE::Input::IsMouseButtonPressed(MIOS_MOUSE_BUTTON_LEFT))
	{
		auto [x, y] = miosGE::Input::GetMousePosition();
		auto width = miosGE::Application::Get().GetWindow().GetWidth();
		auto height = miosGE::Application::Get().GetWindow().GetHeight();
		auto bounds = m_CameraController.GetBounds();
		auto pos = m_CameraController.GetCamera().GetPosition();
		x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
		m_Particle.Position = { x + pos.x, y + pos.y };
		for (int i = 0; i < 5; i++)
			m_ParticleSystem.Emit(m_Particle);
	}

	m_ParticleSystem.OnUpdate(ts);
	m_ParticleSystem.OnRender(m_CameraController.GetCamera());*/

}

void Sandbox2D::OnImGuiRender()
{
	MIOS_PROFILE_FUNCTION();

    ImGui::Begin("Setting");

    auto stats = miosGE::Renderer2D::GetStats();
    ImGui::Text("Renderer2D Stats:");
    ImGui::Text("Draw Calls: %d", stats.DrawCalls);
    ImGui::Text("Quads: %d", stats.QuadCount);
    ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
    ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void Sandbox2D::OnEvent(miosGE::Event& e)
{
	m_CameraController.OnEvent(e);
}
