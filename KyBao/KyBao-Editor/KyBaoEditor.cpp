
#define PLATFORM_WINDOWS
#include <KyBao.h>
#include "EditorLayout.h"
namespace KyBao {
	class KyBaoEditor :public Application
	{
	public:
		KyBaoEditor():Application("KyBao-Editor") {
			PushLayer(new EditorLayout());
		};
		~KyBaoEditor() {};

	private:

	};

}
KyBao::Application* KyBao::CreateApplication() {
	return new KyBao::KyBaoEditor();
}