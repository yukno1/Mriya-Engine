#pragma once

#include "Event.h"

#include <sstream>

namespace Miriya {

    class MIR_API WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(const unsigned int width, const unsigned int height) : m_Width(width), m_Height(height) {
        }

        [[nodiscard]] unsigned int GetWidth() const { return m_Width; }
        [[nodiscard]] unsigned int GetHeight() const { return m_Height; }

        // for debugging
        [[nodiscard]] std::string ToString() const override {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
    private:
        unsigned int m_Width, m_Height;
    };


    class MIR_API WindowCloseEvent : public Event {
    public:
        WindowCloseEvent() = default;

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };


    class MIR_API AppTickEvent : public Event {
    public:
        AppTickEvent() = default;

        EVENT_CLASS_TYPE(AppTick)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };


    class MIR_API AppUpdateEvent : public Event {
    public:
        AppUpdateEvent() = default;

        EVENT_CLASS_TYPE(AppUpdate)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };


    class MIR_API AppRenderEvent : public Event {
    public:
        AppRenderEvent() = default;

        EVENT_CLASS_TYPE(AppRender)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };
}
