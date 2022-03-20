
#include "string.h"
#include "MiosGE/MioGE.h"
class TestLayer : public miosGE::Layer {
public:
	TestLayer() :Layer("Test") {}

	void OnUpdate() override {
		//MIOS_INFO("TestLayer::Update");

		if (miosGE::Input::IskeyPressed(MIOS_KEY_TAB)) {
			MIOS_TRACE("Tab Key Pressed(poll)");
		}

	}

	void OnEvent(miosGE::Event& event) override {
		//MIOS_TRACE("{0}", event);
		if (event.GetEventType() == miosGE::EventType::KeyPressed) {
			miosGE::KeyPressedEvent& e = (miosGE::KeyPressedEvent&)event;
			if (e.GetKeyCode() == MIOS_KEY_TAB)
				MIOS_TRACE("Tab Key Pressed(event)");
			MIOS_TRACE("{0}", (char)e.GetKeyCode());
		}


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