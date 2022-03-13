#pragma once

#ifdef MIOS_WIN64

extern miosGE::Application* miosGE::CreateApplication();

int main(int argc, char** argv) {
	auto app = miosGE::CreateApplication();
	app->Run();
	delete app;
}
#else

#endif
