/**
 * @file EventHandler.h
 * @author Savan Agrawal
 * @version 0.1
 * 
 * Storing all event codes and allowing interfacing with the event managment in global
 */
#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <unordered_map>
#include <functional>
#include <vector>

enum class Event {
    DatasetCreatorComplete,
    DatasetTrainerComplete,
    IntruderThreadKill,
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
    void emit(Event event);
    bool isEventRegistered(Event event) const;

private:
    EventHandler() = default;
    ~EventHandler() = default;

    std::unordered_map<Event, std::vector<std::function<void()>>> listeners;
    static const char* eventToString(Event event);
};

#endif // EVENT_HANDLER_H
