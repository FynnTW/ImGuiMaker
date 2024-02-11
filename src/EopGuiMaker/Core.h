#pragma	once

#ifdef GUIMAKER_PLATFORM_WINDOWS
	#ifdef GUIMAKER_BUILD_DLL
		#define GUIMAKER_API __declspec(dllexport)
	#else
		#define GUIMAKER_API __declspec(dllimport)
	#endif
#else
	#error Guimaker only supports Windows!
#endif

#define BIT(x) (1 << (x))

#ifdef GUIMAKER_ENABLE_ASSERTS
	#define GUIMAKER_ASSERT(x, ...) { if(!(x)) { GUIMAKER_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define GUIMAKER_CORE_ASSERT(x, ...) { if(!(x)) { GUIMAKER_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define GUIMAKER_ASSERT(x, ...)
	#define GUIMAKER_CORE_ASSERT(x, ...)
#endif
