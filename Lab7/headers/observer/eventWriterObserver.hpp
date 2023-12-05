#ifndef EVENT_WRITER_OBSERVER_HPP
#define EVENT_WRITER_OBSERVER_HPP

#include "observer/observer.hpp"

namespace lab7 {
    template <typename MessageBroker>
    class EventWriterObserver : public Observer {
    public:
        EventWriterObserver(MessageBroker&& messageBroker) :
            messageBroker(std::move(messageBroker)) {}

        virtual void writeMessage(const std::string& message) {
            messageBroker.sendMessage(message);
        }

        virtual void update(NPC const* subject) = 0;

    protected:
        MessageBroker messageBroker;

    private:
        EventWriterObserver(const EventWriterObserver&);
        EventWriterObserver& operator=(const EventWriterObserver&);

    };
};

#endif