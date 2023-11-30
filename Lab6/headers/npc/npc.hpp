#ifndef NPC_HPP

#define NPC_HPP


#include <list>
#include <string>

#include "declarations/declarations.h"

#include "auxiliry/point.hpp"
#include "observer/observer.hpp"

namespace lab6 {
    class NPC {
    public:
    	std::string name;
    	point<size_t> pos;

    	std::list<Observer*> observers;

    public:
    	virtual void attachObserver(Observer* observer);

    	virtual void detachObserver(Observer* observer);

        virtual void notifyObservers() const;

    	virtual void accept(Visitor* v) = 0;

        virtual typesOfNPCs identify();
    };

};

void lab6::NPC::attachObserver(lab6::Observer* observer) {
    observers.emplace_back(observer);
}

void lab6::NPC::detachObserver(lab6::Observer* observer) {
    observers.erase(std::find(observers.begin(), observers.end(), observer));
}

void lab6::NPC::notifyObservers() const {
    for (auto const& observer : observers) {
        observer->update(this);
    }
}

lab6::typesOfNPCs lab6::NPC::identify() {
    return typesOfNPCs::type_NPC;
}




#endif