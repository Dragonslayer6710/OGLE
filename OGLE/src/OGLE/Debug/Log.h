#pragma once

#include "OGLE/Core/Base.h"
#include "OGLE/Maths/oglemath.h"

#define GLM_ENABLE_EXPERIMENTAL

// This ignores all warnings raised inside External headers

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <thread>
#include <mutex>
#include <sstream>

namespace OGLE {

	class Log
	{
	public:
		static void Init();

		static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};

}

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
{
	return os << glm::to_string(quaternion);
}

#ifndef MACRO_LOG

// Core log macros
#define OGLE_CORE_TRACE(...)    ::OGLE::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define OGLE_CORE_DEBUG(...)    ::OGLE::Log::GetCoreLogger()->debug(__VA_ARGS__)
#define OGLE_CORE_INFO(...)     ::OGLE::Log::GetCoreLogger()->info(__VA_ARGS__)
#define OGLE_CORE_WARN(...)     ::OGLE::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define OGLE_CORE_ERROR(...)    ::OGLE::Log::GetCoreLogger()->error(__VA_ARGS__)
#define OGLE_CORE_CRITICAL(...) ::OGLE::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define OGLE_TRACE(...)         ::OGLE::Log::GetClientLogger()->trace(__VA_ARGS__)
#define OGLE_DEBUG(...)			::OGLE::Log::GetClientLogger()->debug(__VA_ARGS__)
#define OGLE_INFO(...)          ::OGLE::Log::GetClientLogger()->info(__VA_ARGS__)
#define OGLE_WARN(...)          ::OGLE::Log::GetClientLogger()->warn(__VA_ARGS__)
#define OGLE_ERROR(...)         ::OGLE::Log::GetClientLogger()->error(__VA_ARGS__)
#define OGLE_CRITICAL(...)      ::OGLE::Log::GetClientLogger()->critical(__VA_ARGS__)
#define MACRO_LOG
#endif