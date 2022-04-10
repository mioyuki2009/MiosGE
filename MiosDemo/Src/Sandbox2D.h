#pragma once

#include "MiosGE/MioGE.h"
#include "ParticleSystem.h"
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

	miosGE::Ref<miosGE::Texture2D> m_CheckerboardTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f ,0.8f, 1.0f };

};

