#ifndef CONSOLE_MESSAGE_BROKER_HPP
#define CONSOLE_MESSAGE_BROKER_HPP

#include <iostream>
#include <mutex>

#include "messageBroker/messageBroker.hpp"

namespace lab7 {
    class ConsoleMessageBroker : public MessageBroker<std::mutex> {
    public:
        using super = MessageBroker<std::mutex>;
        using mutex_type_ptr = super::mutex_type_ptr;
        ConsoleMessageBroker(mutex_type_ptr mutex_ptr) 
            : super(mutex_ptr) {}

        void unsafeSendMessage(const std::string& message) {
            std::cout << message;
        }
    };
};

#endif