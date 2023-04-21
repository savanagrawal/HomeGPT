#include "EventHandler.h"
#include <iostream>
#include <vector>

int main() {
    EventHandler& eventHandler = EventHandler::getInstance();

    // Register and emit event without arguments using a lambda function
    eventHandler.addListener(Event::test, [] {
        std::cout << "Received no argument event" << std::endl;
    });
    eventHandler.emit(Event::test);

    // Register and emit event with int and float arguments using a lambda function
    eventHandler.addListener(Event::DatasetCreatorComplete, make_function([](int a, float b) {
        std::cout << "Received event with args: " << a << ", " << b << std::endl;
    }));
    eventHandler.emit<int, float>(Event::DatasetCreatorComplete, 42, 3.14f);

    // Register and emit event with a vector of integers using a lambda function
    eventHandler.addListener(Event::DatasetTrainerComplete, make_function([](std::vector<int> vec) {
        std::cout << "Received event with vector: ";
        for (int i : vec) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }));
    eventHandler.emit<std::vector<int>>(Event::DatasetTrainerComplete, std::vector<int>{1, 2, 3, 4, 5});

    return 0;
}
