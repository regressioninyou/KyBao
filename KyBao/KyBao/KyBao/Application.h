// KyBao.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once
#include "Core.h"
#include "Events/ApplicationEvent.h" 
#include "KyBao/Window.h"
namespace KyBao {
	class  Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	Application* CreateApplication();
}

// TODO: 在此处引用程序需要的其他标头。
