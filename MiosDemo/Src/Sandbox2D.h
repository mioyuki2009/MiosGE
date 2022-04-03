#pragma once

#include "MiosGE/MioGE.h"

class Sandbox2D : public miosGE::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(miosGE::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(miosGE::Event& e) override;
private:
	miosGE::OrthographicCameraController m_CameraController;
	
	//Temp
	miosGE::Ref<miosGE::VertexArray> m_SquareVA;
	miosGE::Ref<miosGE::Shader> m_FlatColorShader;
	
	glm::vec4 m_SquareColor = { 0.2f, 0.3f ,0.8f, 1.0f };
};
