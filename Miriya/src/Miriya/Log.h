#pragma once

#include "Miriya/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Miriya {
    class MIR_API Log {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger> &GetClientLogger() { return s_ClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

// Core log macros
#define MIR_CORE_ERROR(...)    ::Miriya::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MIR_CORE_WARN(...)     ::Miriya::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MIR_CORE_INFO(...)     ::Miriya::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MIR_CORE_TRACE(...)    ::Miriya::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MIR_CORE_FATAL(...)    ::Miriya::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define MIR_ERROR(...)         ::Miriya::Log::GetClientLogger()->error(__VA_ARGS__)
#define MIR_WARN(...)          ::Miriya::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MIR_INFO(...)          ::Miriya::Log::GetClientLogger()->info(__VA_ARGS__)
#define MIR_TRACE(...)         ::Miriya::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MIR_FATAL(...)         ::Miriya::Log::GetClientLogger()->fatal(__VA_ARGS__)