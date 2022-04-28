#pragma once

#include "Core.h"
#include "KeyCodes.h"

namespace miosGE {

	class MIOS_API Input
	{
	public:
		static bool IsKeyPressed(KeyCode keycode);
		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}