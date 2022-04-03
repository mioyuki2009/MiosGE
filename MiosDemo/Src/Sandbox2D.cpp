#include "Sandbox2D.h"
#include "imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Platform/OpenGL/OpenGLShader.h"
#include "glm/gtc/type_ptr.hpp"
#include "Renderer/Shader.h"

Sandbox2D::Sandbox2D() :
	Layer("Sandbox2D") , m_CameraController(1280.0f / 720.0f) {
	
}

void Sandbox2D::OnAttach()
{
	m_SquareVA = miosGE::VertexArray::Create();
	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};
	miosGE::Ref<miosGE::VertexBuffer> squareVB;
	squareVB.reset(miosGE::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	squareVB->SetLayout({
		{miosGE::ShaderDataType::Float3, "a_Position"},
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0,1,2,2,3,0 };
	miosGE::Ref<miosGE::IndexBuffer> squareIB;
	squareIB.reset(miosGE::IndexBuffer::Create(squareIndices, sizeof(squareIndices)));
	m_SquareVA->SetIndexBuffer(squareIB);

	m_FlatColorShader = miosGE::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(miosGE::Timestep ts)
{
	//update
	m_CameraController.OnUpdate(ts);

	//Render
	miosGE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	miosGE::RenderCommand::Clear();

	miosGE::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<miosGE::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<miosGE::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	miosGE::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	miosGE::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Setting");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(miosGE::Event& e)
{
	m_CameraController.OnEvent(e);
}
