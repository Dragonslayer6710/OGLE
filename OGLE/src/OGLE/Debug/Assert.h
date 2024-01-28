#pragma once
#include <filesystem>

#include "OGLE/Debug/Log.h"

#ifdef OGLE_ENABLE_ASSERTS

// Alternatively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define OGLE_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { OGLE##type##ERROR(msg, __VA_ARGS__); OGLE_DEBUGBREAK(); } }
#define OGLE_INTERNAL_ASSERT_WITH_MSG(type, check, ...) OGLE_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define OGLE_INTERNAL_ASSERT_NO_MSG(type, check) OGLE_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", OGLE_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define OGLE_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define OGLE_INTERNAL_ASSERT_GET_MACRO(...) OGLE_EXPAND_MACRO( OGLE_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, OGLE_INTERNAL_ASSERT_WITH_MSG, OGLE_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define OGLE_ASSERT(...) OGLE_EXPAND_MACRO( OGLE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define OGLE_CORE_ASSERT(...) OGLE_EXPAND_MACRO( OGLE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define OGLE_ASSERT(...)
#define OGLE_CORE_ASSERT(...)
#endif
