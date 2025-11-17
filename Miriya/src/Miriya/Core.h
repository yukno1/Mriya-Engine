#pragma once

#include <memory>

#ifdef MIR_PLATFORM_WINDOWS
    #ifdef MIR_BUILD_DLL
        #define MIR_API __declspec(dllexport)
    #else
        #define MIR_API __declspec(dllimport)
    #endif
#else
    #error Miriya only supports Windows!
#endif


#ifdef MIR_ENABLE_ASSERTS
    #define MIR_ASSERT(x, ...) {if(!(x)) { MIR_ERROR("Assertion Failed: {0}", __VA__ARGS__); __debugbreak();}}
    #define MIR_CORE_ASSERT(x, ...) {if(!(x)) { MIR_CORE_ERROR("Assertion Failed: {0}", __VA__ARGS__); __debugbreak();}}
#else
    #define MIR_ASSERT(x, ...)
    #define MIR_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)

#define MIR_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace Miriya {

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T>
    using Ref = std::shared_ptr<T>;
}