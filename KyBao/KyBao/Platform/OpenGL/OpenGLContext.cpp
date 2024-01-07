
#include "kbpch.h"
#include "OpenGLContext.h"
#define GLFW_INCLUDE_NONE  // 防止GLFW包含OpenGL头文件
#include <GLFW/glfw3.h>
#include "glad/glad.h"

namespace KyBao {

	OpenGLContext::OpenGLContext(GLFWwindow* windowhanle)
		:m_windowhanle(windowhanle)
	{
		KyBao_CORE_ASSERT(windowhanle,"window Handle is null!");
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_windowhanle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		KyBao_CORE_ASSERT(status, "Failed to initialize Glad!");
		std::stringstream ss,s1,s2;
		ss << "OpenGL Version : " << glGetString(GL_VERSION);;
		KyBao_CORE_INFO(ss.str());
		s1 << "OpenGL Vendor : " << glGetString(GL_VENDOR);
		KyBao_CORE_INFO(s1.str());
		s2 << "OpenGL Renderer : " << glGetString(GL_RENDERER);
		KyBao_CORE_INFO(s2.str());
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowhanle);
	}
}