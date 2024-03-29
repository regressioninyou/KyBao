#include "KyBao/Render/GraphicsContext.h"

struct GLFWwindow;
namespace KyBao {
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowhanle);
		virtual void Init() override ;
		virtual void SwapBuffers() override;
	private :
		GLFWwindow* m_windowhanle;
	};
}