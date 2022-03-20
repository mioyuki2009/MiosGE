#include "MiosGE/MioGE.h"
class TestLayer : public miosGE::Layer {
public:
	TestLayer() :Layer("Test") {}

	void OnUpdate() override {
		MIOS_INFO("TestLayer::Update");
	}

	void OnEvent(miosGE::Event& event) override {
		MIOS_TRACE("{0}", event);
	}

};


class SandBox : public miosGE::Application {
public:
	SandBox() {
		PushLayer(new TestLayer());
		PushLayer(new miosGE::ImGuiLayer());
	};
	~SandBox() {};

};
miosGE::Application* miosGE::CreateApplication() {
	return new SandBox();
}