
#include "string.h"
#include "MiosGE/MioGE.h"
#include "imgui.h"
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

class TestLayer : public miosGE::Layer {
public:
	TestLayer() :Layer("Test") {
	}

	void OnUpdate() override {
		//MIOS_INFO("TestLayer::Update");

		/*if (miosGE::Input::IskeyPressed(MIOS_KEY_TAB)) {
			MIOS_TRACE("Tab Key Pressed(poll)");
		}*/

	}

	virtual void OnImGuiRender() override {
		
		ImGui::Begin("Test");
		ImGui::Text("Hello world");
		ImGui::ColorEdit4("", new float[4]);
		ImGui::End();
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
	};
	~SandBox() {};

};
miosGE::Application* miosGE::CreateApplication() {
	return new SandBox();
}