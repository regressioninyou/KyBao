#pragma once 

#include <memory>
#ifdef  PLATFORM_WINDOWS_S
	#ifdef BUILD_DLL
		#define DLLAPI __declspec(dllexport)
	#else 
		#define DLLAPI __declspec(dllimport)
	#endif // BUILD_DLL
#endif //  PLATFROM_WINDOWS

#ifdef KyBao_ENABLE_ASSERTS
#define KyBao_ASSERT(x, ...) { if(!(x)) { KyBao_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define KyBao_CORE_ASSERT(x, ...) { if(!(x)) { KyBao_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define KyBao_ASSERT(x, ...)
#define KyBao_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1<<x)

#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }


namespace KyBao {
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}