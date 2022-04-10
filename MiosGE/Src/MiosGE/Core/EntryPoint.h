#pragma once
#include "Core.h"
#ifdef MIOS_WIN64

extern miosGE::Application* miosGE::CreateApplication();

int main(int argc, char** argv) {
	miosGE::Log::Init();

	MIOS_PROFILE_BEGIN_SESSION("Startup", "MiosProfile-Startup.json");
	auto app = miosGE::CreateApplication();
	MIOS_PROFILE_END_SESSION();

	MIOS_PROFILE_BEGIN_SESSION("Runtime", "MiosProfile-Runtime.json");
	app->Run();
	MIOS_PROFILE_END_SESSION();

	MIOS_PROFILE_BEGIN_SESSION("Startup", "MiosProfile-Release.json");
	delete app;
	MIOS_PROFILE_END_SESSION();
}
#else

#endif
