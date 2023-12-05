#ifndef CONSOLE_MESSAGE_BROKER_HPP
#define CONSOLE_MESSAGE_BROKER_HPP

#include <iostream>
#include <memory>
#include <mutex>

#include "messageBroker/messageBroker.hpp"

namespace lab7 {
    template <class mutex_type>
    class ConsoleMessageBroker : public MessageBroker<mutex_type> {
    public:
        using mutex_type_ptr = MessageBroker<mutex_type>::mutex_type_ptr;
        ConsoleMessageBroker(mutex_type_ptr mutex_ptr) 
            : MessageBroker<mutex_type>(mutex_ptr) {}

        void unsafeSendMessage(const std::string& message) {
            std::cout << message;
        }
    };
};

#endif