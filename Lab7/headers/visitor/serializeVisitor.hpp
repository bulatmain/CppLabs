#ifndef SERIALIZE_VISITOR_HPP
#define SERIALIZE_VISITOR_HPP

#include "visitor/visitor.hpp"

namespace lab7 {
    template <typename MessageBroker>
    class SerializeVisitor : public Visitor {
    public:
        SerializeVisitor(MessageBroker&& messageBroker) :
            messageBroker(std::move(messageBroker)) {}

	    virtual void visitOgre(Ogre* ogre) {
            writeMessage(
                ogre->name + "\n" +
                std::to_string(ogre->pos.x) + " " + std::to_string(ogre->pos.y) + "\n" +
                statusToStr(ogre->status) + "\n\n"
            );
        }
	    virtual void visitBear(Bear* bear) {
            writeMessage(
                bear->name + "\n" +
                std::to_string(bear->pos.x) + " " + std::to_string(bear->pos.y) + "\n" +
                statusToStr(bear->status) + "\n\n"
            );
        }
	    virtual void visitSquirrel(Squirrel* squirrel) {
            writeMessage(
                squirrel->name + "\n" +
                std::to_string(squirrel->pos.x) + " " + std::to_string(squirrel->pos.y) + "\n" +
                statusToStr(squirrel->status) + "\n\n"
            );
        }

        virtual void swapMessageBroker(MessageBroker&& messageBroker) {
            this->messageBroker = std::move(messageBroker);
        }

    protected:
        MessageBroker messageBroker;

    protected:
        virtual void writeMessage(const std::string& message) {
            messageBroker.sendMessage(message);
        }
    };
};

#endif