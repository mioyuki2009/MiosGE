#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "MiosGE/Log.h"
namespace miosGE {
	Application::Application() {
	
	}

	Application::~Application() {

	}


	void Application::Run() {
		/*while (true)
		{

		}*/
		WindowResizeEvent e(1280, 720);
		MIOS_TRACE(e);

		while (true);
	}

}

