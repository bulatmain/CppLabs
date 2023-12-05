#ifndef NPC_HPP

#define NPC_HPP

#include <list>
#include <string>

#include "declarations/declarations.hpp"

#include "auxiliry/point.hpp"
#include "observer/observer.hpp"

namespace lab7 {
    class NPC {
    public:
    	std::string name;
    	point<size_t> pos;
        statusOfNPC status;

    	std::list<Observer*> observers;

    public:
    	virtual void attachObserver(Observer* observer);

    	virtual void detachObserver(Observer* observer);

        virtual void notifyObservers() const;

    	virtual void accept(Visitor* v) = 0;

        virtual typesOfNPCs identify();

        virtual ~NPC() = 0;
    };

};

void lab7::NPC::attachObserver(lab7::Observer* observer) {
    observers.emplace_back(observer);
}

void lab7::NPC::detachObserver(lab7::Observer* observer) {
    observers.erase(std::find(observers.begin(), observers.end(), observer));
}

void lab7::NPC::notifyObservers() const {
    for (auto const& observer : observers) {
        observer->update(this);
    }
}

lab7::typesOfNPCs lab7::NPC::identify() {
    return typesOfNPCs::type_NPC;
}

lab7::NPC::~NPC() {}

#endif