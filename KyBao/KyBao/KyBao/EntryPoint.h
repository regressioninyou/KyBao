#pragma once 
#ifdef PLATFORM_WINDOWS
extern  KyBao::Application* KyBao::CreateApplication();

int main(int argc,char** argv) {
	printf("hello \n");
	KyBao::Log::Init();
	KyBao_CORE_INFO("hello");
	auto app = KyBao::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif // PLATFROM_WINDOWS
