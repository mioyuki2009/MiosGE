
#include "string.h"
#include "MiosGE/MioGE.h"
#include "imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Platform/OpenGL/OpenGLShader.h"
#include "glm/gtc/type_ptr.hpp"


class TestLayer : public miosGE::Layer {
public:
	TestLayer() :Layer("Test") ,m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_SquarePosition(0.0f)
	{
		m_VertexArray.reset(miosGE::VertexArray::Create());
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f , 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f , 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f , 0.8f, 0.8f, 0.2f, 1.0f,
		};
		std::shared_ptr<miosGE::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(miosGE::VertexBuffer::Create(vertices, sizeof(vertices)));
		miosGE::BufferLayout layout = {
			{miosGE::ShaderDataType::Float3, "a_Position"},
			{miosGE::ShaderDataType::Float4, "a_Color"},
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0,1,2 };
		std::shared_ptr<miosGE::IndexBuffer> indexBuffer;
		indexBuffer.reset(miosGE::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(miosGE::VertexArray::Create());
		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f ,
			 0.5f, -0.5f, 0.0f ,
			 0.5f,  0.5f, 0.0f ,
			-0.5f,  0.5f, 0.0f
		};
		std::shared_ptr<miosGE::VertexBuffer> squareVB;
		squareVB.reset(miosGE::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{miosGE::ShaderDataType::Float3, "a_Position"},
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0,1,2,2,3,0 };
		std::shared_ptr<miosGE::IndexBuffer> squareIB;
		squareIB.reset(miosGE::IndexBuffer::Create(squareIndices, sizeof(squareIndices)));
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
		m_Shader.reset(miosGE::Shader::Create(vertexSrc, fragmentSrc));

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

		m_FlatColorShader.reset(miosGE::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));
	}

	void OnUpdate(miosGE::Timestep ts) override {
		if (miosGE::Input::IskeyPressed(MIOS_KEY_LEFT)) {
			m_CameraPosition.x -= m_CameraSpeed * ts;
		}
		else if (miosGE::Input::IskeyPressed(MIOS_KEY_RIGHT)) {
			m_CameraPosition.x += m_CameraSpeed * ts;
		}
		if (miosGE::Input::IskeyPressed(MIOS_KEY_DOWN)) {
			m_CameraPosition.y -= m_CameraSpeed * ts;
		}
		else if (miosGE::Input::IskeyPressed(MIOS_KEY_UP)) {
			m_CameraPosition.y += m_CameraSpeed * ts;
		}

		if (miosGE::Input::IskeyPressed(MIOS_KEY_J)) {
			m_SquarePosition.x += m_SquareMoveSpeed * ts;
		}
		else if (miosGE::Input::IskeyPressed(MIOS_KEY_L)) {
			m_SquarePosition.x -= m_SquareMoveSpeed * ts;
		}

		if (miosGE::Input::IskeyPressed(MIOS_KEY_I)) {
			m_SquarePosition.y += m_SquareMoveSpeed * ts;
		}
		else if (miosGE::Input::IskeyPressed(MIOS_KEY_K)) {
			m_SquarePosition.y -= m_SquareMoveSpeed * ts;
		}

		miosGE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		miosGE::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		miosGE::Renderer::BeginScene(m_Camera);

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

		miosGE::Renderer::Submit(m_Shader, m_VertexArray);

		miosGE::Renderer::EndScene();

	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Setting");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}
	
	void OnEvent(miosGE::Event& event) override {
	}
		
private:
	std::shared_ptr<miosGE::Shader> m_Shader;
	std::shared_ptr<miosGE::VertexArray> m_VertexArray;

	std::shared_ptr<miosGE::Shader> m_FlatColorShader;
	std::shared_ptr<miosGE::VertexArray> m_SquareVA;

	miosGE::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 5.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquarePosition;
	float m_SquareMoveSpeed = 5.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f ,0.8f };
};


class SandBox : public miosGE::Application {
public:
	SandBox() {
		PushLayer(new TestLayer());
	};
	~SandBox() {};

};
miosGE::Application* miosGE::CreateApplication() {
	return new SandBox();
}