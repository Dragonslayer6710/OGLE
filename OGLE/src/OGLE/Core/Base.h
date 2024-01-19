#pragma once

#include "OGLE/Core/PlatformDetection.h"

#include <memory>

#ifdef OGLE_DEBUG
#if defined(OGLE_PLATFORM_WINDOWS)
#define OGLE_DEBUGBREAK() __debugbreak()
#elif defined(OGLE_PLATFORM_LINUX)
#include <signal.h>
#define OGLE_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define OGLE_ENABLE_ASSERTS
#else
#define OGLE_DEBUGBREAK()
#endif

#define OGLE_EXPAND_MACRO(x) x
#define OGLE_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define OGLE_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace OGLE {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}

#include "OGLE/Core/Log.h"
#include "OGLE/Core/Assert.h"