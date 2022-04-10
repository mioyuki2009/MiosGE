
#include "MiosGE/MioGE.h"
#include "Core/EntryPoint.h"
#include "imgui.h"
#include "glm/gtc/type_ptr.hpp"
#include "EditorLayer.h"

namespace miosGE {

	class MiosEdit : public Application {
	public:
		MiosEdit() :
			Application("mios Editor")
		{
			PushLayer(new EditorLayer());
		};
		~MiosEdit() {};

	};
	Application* CreateApplication() {
		return new MiosEdit();
	}

}