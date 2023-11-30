#ifndef CONSOLE_MESSAGE_BROKER_HPP
#define CONSOLE_MESSAGE_BROKER_HPP

#include <iostream>

namespace lab6 {
    class ConsoleMessageBroker {
    public:
        void sendMessage(const std::string& message) {
            std::cout << message;
        }
    };
};

#endif