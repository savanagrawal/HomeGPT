#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <unordered_map>
#include <functional>
#include <vector>
#include <any>
#include <tuple>
#include <iostream>

enum class Event {
    test,
    DatasetCreatorComplete,
    DatasetTrainerComplete,
    IntruderThreadKill,
    IntruderMoodThreadKill,
    RfidAuthenticated,
    OpenGarageDoor,
    OpenedGarageDoor,
    CloseGarageDoor,
    ClosedGarageDoor,
    OpenMainDoor,
    OpenedMainDoor,
    CloseMainDoor,
    ClosedMainDoor
};

class EventHandler {
public:
    static EventHandler& getInstance();

    EventHandler(const EventHandler&) = delete;
    EventHandler& operator=(const EventHandler&) = delete;

    void addListener(Event event, std::function<void()> callback);

    template <typename... Args>
    void addListener(Event event, std::function<void(Args...)> callback);

    void emit(Event event);

    template <typename... Args>
    void emit(Event event, Args... args);

    bool isEventRegistered(Event event) const;

private:
    EventHandler() = default;
    ~EventHandler() = default;

    std::unordered_map<Event, std::vector<std::function<void(std::any)>>> listeners;
    static const char* eventToString(Event event);
};


#include "EventHandler.tpp"

#endif // EVENT_HANDLER_H
