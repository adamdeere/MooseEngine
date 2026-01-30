#pragma once

enum class EventType
{
    None = 0,
    WindowResize
};

struct Event
{
    virtual ~Event() = default;
    virtual EventType GetType() const = 0;
};
