#include <KyBao.h>
class Sandbox :public KyBao::Application
{
public:
	Sandbox() {};
	~Sandbox() {};

private:

};

KyBao::Application* KyBao::CreateApplication() {
	return new Sandbox();
}