#pragma once

#include "Platform/Events.h"

struct WindowResizeEvent : public Event
{
    int width;
    int height;

    WindowResizeEvent(int w, int h)
        : width(w), height(h) {}

    EventType GetType() const override
    {
        return EventType::WindowResize;
    }
};
