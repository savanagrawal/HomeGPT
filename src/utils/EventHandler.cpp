// /**
//  * @file EventHandler.cpp
//  * @author Savan Agrawal
//  * @version 0.1
//  * 
//  * Storing all event codes and allowing interfacing with the event managment in global
//  */
// #include "EventHandler.h"
// #include <iostream>

// EventHandler& EventHandler::getInstance() {
//     static EventHandler instance;
//     return instance;
// }

// void EventHandler::addListener(Event event, std::function<void()> callback) {
//     listeners[event].push_back(callback);
// }

// void EventHandler::emit(Event event) {
//     std::cout << "Emitting event: " << eventToString(event) << std::endl;
//     if (listeners.find(event) != listeners.end()) {
//         for (const auto& callback : listeners[event]) {
//             callback();
//         }
//     }
// }

// bool EventHandler::isEventRegistered(Event event) const {
//     return listeners.find(event) != listeners.end();
// }

// const char* EventHandler::eventToString(Event event) {
//     switch (event) {
//         case Event::DatasetCreatorComplete:
//             return "DatasetCreatorComplete";
//         case Event::DatasetTrainerComplete:
//             return "DatasetTrainerComplete";
//         case Event::IntruderThreadKill:
//             return "IntruderThreadKill";
//         case Event::RfidAuthenticated:
//             return "RfidAuthenticated";
//         case Event::OpenGarageDoor:
//             return "OpenGarageDoor";
//         case Event::OpenedGarageDoor:
//             return "OpenedGarageDoor";
//         case Event::CloseGarageDoor:
//             return "CloseGarageDoor";
//         case Event::ClosedGarageDoor:
//             return "ClosedGarageDoor";
//         case Event::OpenMainDoor:
//             return "OpenMainDoor";
//         case Event::OpenedMainDoor:
//             return "OpenedMainDoor";
//         case Event::CloseMainDoor:
//             return "CloseMainDoor";
//         case Event::ClosedMainDoor:
//             return "ClosedMainDoor";
//         default:
//             return "Unknown Event";
//     }
// }




/**
 * @file EventHandler.cpp
 * @author Savan Agrawal
 * @version 0.1
 * 
 * Storing all event codes and allowing interfacing with the event managment in global
 */
/**
 * @file EventHandler.cpp
 * @author Savan Agrawal
 * @version 0.1
 * 
 * Storing all event codes and allowing interfacing with the event managment in global
 */
#include "EventHandler.h"
#include <iostream>

EventHandler& EventHandler::getInstance() {
    static EventHandler instance;
    return instance;
}


void EventHandler::addListener(Event event, std::function<void()> callback) {
    auto wrapper = [callback](std::any args) {
        callback();
    };
    listeners[event].push_back(wrapper);
}

void EventHandler::emit(Event event) {
    std::cout << "Emitting event: " << eventToString(event) << std::endl;
    if (listeners.find(event) != listeners.end()) {
        for (const auto& callback : listeners[event]) {
            callback(std::any{});
        }
    }
}


bool EventHandler::isEventRegistered(Event event) const {
    return listeners.find(event) != listeners.end();
}

const char* EventHandler::eventToString(Event event) {
    switch (event) {
        case Event::DatasetCreatorComplete:
            return "DatasetCreatorComplete";
        case Event::DatasetTrainerComplete:
            return "DatasetTrainerComplete";
        case Event::IntruderThreadKill:
            return "IntruderThreadKill";
        case Event::RfidAuthenticated:
            return "RfidAuthenticated";
        case Event::OpenGarageDoor:
            return "OpenGarageDoor";
        case Event::OpenedGarageDoor:
            return "OpenedGarageDoor";
        case Event::CloseGarageDoor:
            return "CloseGarageDoor";
        case Event::ClosedGarageDoor:
            return "ClosedGarageDoor";
        case Event::OpenMainDoor:
            return "OpenMainDoor";
        case Event::OpenedMainDoor:
            return "OpenedMainDoor";
        case Event::CloseMainDoor:
            return "CloseMainDoor";
        case Event::ClosedMainDoor:
            return "ClosedMainDoor";
        default:
            return "Unknown Event";
    }
}
