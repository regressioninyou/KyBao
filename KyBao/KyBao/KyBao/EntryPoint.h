#pragma once 
#ifdef PLATFORM_WINDOWS
extern  KyBao::Application* KyBao::CreateApplication();

int main(int argc,char** argv) {
	printf("hello \n");
	auto app = KyBao::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif // PLATFROM_WINDOWS
