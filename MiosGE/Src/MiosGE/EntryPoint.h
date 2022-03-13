#pragma once

#ifdef MIOS_WIN64

extern miosGE::Application* miosGE::CreateApplication();

int main(int argc, char** argv) {
	miosGE::Log::Init();

	MIOS_CORE_WARN("Initialized Log!");
	MIOS_INFO("Hello");
	auto app = miosGE::CreateApplication();
	app->Run();
	delete app;
}
#else

#endif
