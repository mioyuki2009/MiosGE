
#include "MiosGE/MioGE.h"
#include "Core/EntryPoint.h"
#include "imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "glm/gtc/type_ptr.hpp"
#include "Sandbox2D.h"

class TestLayer : public miosGE::Layer {
public:
	TestLayer() :Layer("Test") ,m_CameraController(1280.0f/720.0f)
	{
		m_VertexArray = miosGE::VertexArray::Create();
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f , 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f , 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f , 0.8f, 0.8f, 0.2f, 1.0f,
		};
		miosGE::Ref<miosGE::VertexBuffer> vertexBuffer;
		vertexBuffer = miosGE::VertexBuffer::Create(vertices, sizeof(vertices));
		miosGE::BufferLayout layout = {
			{miosGE::ShaderDataType::Float3, "a_Position"},
			{miosGE::ShaderDataType::Float4, "a_Color"},
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0,1,2 };
		miosGE::Ref<miosGE::IndexBuffer> indexBuffer;
		indexBuffer = miosGE::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA = miosGE::VertexArray::Create();
		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		miosGE::Ref<miosGE::VertexBuffer> squareVB;
		squareVB = miosGE::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{miosGE::ShaderDataType::Float3, "a_Position"},
			{miosGE::ShaderDataType::Float2, "a_Texcoord"},
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0,1,2,2,3,0 };
		miosGE::Ref<miosGE::IndexBuffer> squareIB;
		squareIB = miosGE::IndexBuffer::Create(squareIndices, sizeof(squareIndices));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 460 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position; 
			out vec4 v_Color; 
			void main(){
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0f);
			}	

		)";
		std::string fragmentSrc = R"(
			#version 460 core
			
			out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main(){
				color = vec4(v_Position * 0.5 + 0.5 ,1.0);
				color = v_Color;
			}	

		)";

		

		m_Shader = miosGE::Shader::Create("VertexColorColor", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 460 core
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position; 
			void main(){
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0f);
			}	

		)";
		std::string flatColorShaderFragmentSrc = R"(
			#version 460 core
			
			out vec4 color;
			in vec3 v_Position;
			uniform vec3 u_Color;
			void main(){
				color = vec4(u_Color, 1.0f);
			}	

		)";

		m_FlatColorShader = miosGE::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		m_TextureShader = miosGE::Shader::Create("assets/shaders/Texture.glsl");

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = miosGE::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoLogTexture = miosGE::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<miosGE::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<miosGE::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(miosGE::Timestep ts) override {
		m_CameraController.OnUpdate(ts);

		miosGE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		miosGE::RenderCommand::Clear();

		miosGE::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
		glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);

		std::dynamic_pointer_cast<miosGE::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<miosGE::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 20; x++) {
				glm::vec3 pos(x * 0.11f, y * 0.11 , 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

				miosGE::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}
		
		m_Texture->Bind();
		miosGE::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_ChernoLogTexture->Bind();
		miosGE::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		// Triangle
		//miosGE::Renderer::Submit(m_Shader, m_VertexArray);

		miosGE::Renderer::EndScene();

	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Setting");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}
	
	void OnEvent(miosGE::Event& e) override {
		m_CameraController.OnEvent(e);

	}
		
private:
	miosGE::ShaderLibrary m_ShaderLibrary;

	miosGE::Ref<miosGE::Shader> m_Shader;
	miosGE::Ref<miosGE::VertexArray> m_VertexArray;

	miosGE::Ref<miosGE::Shader> m_FlatColorShader, m_TextureShader;
	miosGE::Ref<miosGE::VertexArray> m_SquareVA;

	miosGE::Ref<miosGE::Texture> m_Texture, m_ChernoLogTexture;

	miosGE::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f ,0.8f };
};


class SandBox : public miosGE::Application {
public:
	SandBox() {
		//PushLayer(new TestLayer());
		PushLayer(new Sandbox2D());
	};
	~SandBox() {};

};
miosGE::Application* miosGE::CreateApplication() {
	return new SandBox();
}