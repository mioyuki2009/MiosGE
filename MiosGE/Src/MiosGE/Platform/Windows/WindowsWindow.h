#pragma once
#include "Window.h"
#include "GLFW/glfw3.h"
#include "Renderer/GraphicsContext.h"
struct GLFWwindow;

namespace miosGE {

    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowsProps& props);
        virtual ~WindowsWindow();

        void OnUpdate() override;

        inline unsigned int GetWidth() const override { return m_Data.Width; }
        inline unsigned int GetHeight() const override { return m_Data.Height; }

        inline void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }
        void SetVSync(bool enabled);
        bool IsVSync() const;

        inline void* GetNativeWindow() const override { return m_Windows; }

    private:
        virtual void Init(const WindowsProps& props);
        virtual void Shutdown();

    private:
        GLFWwindow* m_Windows;
        GraphicsContext* m_Context;
        struct WindowData
        {
            std::string Title;
            unsigned int Width;
            unsigned int Height;
            bool VSync;
            EventCallbackFn EventCallback;
        };

        WindowData m_Data;
    };
}

