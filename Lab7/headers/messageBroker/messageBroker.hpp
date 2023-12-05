#ifndef MESSAGE_BROKER_HPP
#define MESSAGE_BROKER_HPP

#include <memory>
#include <mutex>

namespace lab7 {
    template <class mutex_type>
    class MessageBroker {
    public:
        using mutex_type_ptr = std::shared_ptr<std::mutex>;
        MessageBroker(mutex_type_ptr mutex_ptr)
            : mutex_ptr(mutex_ptr) {}

        void sendMessage(const std::string& message) {
            if (mutex_ptr != nullptr) {
                const std::lock_guard<mutex_type> lock(*mutex_ptr);
                unsafeSendMessage(message);
            } else {
                unsafeSendMessage(message);
            }
        }

        virtual void unsafeSendMessage(const std::string& message) = 0;
        
    protected:
        mutex_type_ptr mutex_ptr;
    };
};

#endif