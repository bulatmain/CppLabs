#ifndef KILL_EVENT_OBSERVER_HPP
#define KILL_EVENT_OBSERVER_HPP

#include "npc/npc.hpp"
#include "observer/eventWriterObserver.hpp"

namespace lab6 {
    template <typename MessageBroker>
    class KillEventObserver : public EventWriterObserver<MessageBroker>  {
    public:
        KillEventObserver(MessageBroker&& messageBroker) 
            : EventWriterObserver<MessageBroker>(std::move(messageBroker)) {}
        virtual void update(NPC const* subject) {
            EventWriterObserver<MessageBroker>::writeMessage(subject->name + " is murdered!\n");
        }
    };
};

#endif