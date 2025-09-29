#pragma once

#include <string>

#include "Core.h"
#include "Events/Event.h"

namespace Miriya {

    class MIR_API Layer {
    public:
        explicit Layer(const std::string& name = "Layer"); // debug name. a layer should not have a name in distribution
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnEvent(Event& event) {}

        [[nodiscard]] inline const std::string& GetName() const { return m_DebugName; }
    protected:
        std::string m_DebugName;
    };
}