#include "Application.h"
// KyBao.cpp: 定义应用程序的入口点。
//

#include "KyBao.h"
#include <GLFW/glfw3.h>

namespace KyBao {
#define BIND_EVENT_FN(x) std::bind(&Application::x,this,std::placeholders::_1)
	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}
	Application::~Application() {

	}

	void Application::Run() {
		
		while (m_Running)
		{
			glClearColor(0,0,0,1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		};
	}
	void  Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		KyBao_CORE_INFO("{0}", e);
	}
	bool KyBao::Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}