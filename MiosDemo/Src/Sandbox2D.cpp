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
	{
		MIOS_PROFILE_SCOPE("Renderer Prep");
		miosGE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		miosGE::RenderCommand::Clear();
	}
	
	{
		MIOS_PROFILE_SCOPE("Renderer Draw");
		miosGE::Renderer2D::BeginScene(m_CameraController.GetCamera());
		miosGE::Renderer2D::DrawRotatedQuad({ -1.0f,0.0f }, { 0.8f,0.8f }, glm::radians(45.0f), { 0.8f,0.2f,0.3f,1.0f });
		miosGE::Renderer2D::DrawQuad({ 0.5f,-0.5f }, { 0.5f,0.5f }, { 0.2f,0.3f,0.8f,1.0f });
		miosGE::Renderer2D::DrawQuad({ 0.2f,0.5f, -0.0f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f);
		miosGE::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	MIOS_PROFILE_FUNCTION();

	ImGui::Begin("Setting");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(miosGE::Event& e)
{
	m_CameraController.OnEvent(e);
}
