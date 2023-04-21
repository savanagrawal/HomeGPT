template <typename F>
auto make_function(F&& f) {
    return std::function{std::forward<F>(f)};
}

template <typename... Args>
void EventHandler::addListener(Event event, std::function<void(Args...)> callback) {
    auto wrapper = [callback](std::any args) {
        std::apply(callback, std::any_cast<std::tuple<Args...>>(args));
    };
    listeners[event].push_back(wrapper);
}

template <typename... Args>
void EventHandler::emit(Event event, Args... args) {
    std::cout << "Emitting event: " << eventToString(event) << std::endl;
    if (listeners.find(event) != listeners.end()) {
        auto wrapped_args = std::make_tuple(args...);
        for (const auto& callback : listeners[event]) {
            callback(wrapped_args);
        }
    }
}
