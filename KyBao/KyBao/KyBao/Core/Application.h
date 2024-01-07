// KyBao.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once
#include "Core.h"
#include "KyBao/Events/ApplicationEvent.h" 
#include "KyBao/Core/Window.h"
#include "LayerStack.h"
#include "KyBao/ImGui/ImGuiLayer.h"
#include "KyBao/Render/Shader.h"
#include "KyBao/Render/Buffer.h"
#include "KyBao/Render/VertexArray.h"
namespace KyBao {
	class  Application
	{
	public:
		Application(const std::string& name);
		virtual ~Application();
		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		void Close();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; };

		inline static Application& Get() { return *s_Instance; };

		inline Window& GetWindow() { return *m_Window; };
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();
}

// TODO: 在此处引用程序需要的其他标头。
