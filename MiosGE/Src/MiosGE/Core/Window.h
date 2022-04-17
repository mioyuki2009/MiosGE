#pragma once

#include "MiosPch.h"

#include "Core/Core.h"
#include "Events/Event.h"

namespace miosGE {
	struct WindowsProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowsProps(const std::string& title = "mios Engine",
			uint32_t width = 1280,
			uint32_t height = 720
		) :Title(title), Width(width), Height(height) {};
	};

	class MIOS_API Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {};
		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowsProps& props = WindowsProps());
	};
}