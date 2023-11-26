#ifndef NPC_HPP

#define NPC_HPP


#include <list>
#include <string>

#include "declarations/declarations.h"

#include "auxiliry/point.hpp"
#include "observer/observer.hpp"

namespace lab6 {
    class NPC {
    protected:
    	std::string name;
    	point<size_t> pos;
    	double health;

    	std::list<Observer*> observers;

    public:
    	virtual void attachObserver(Observer* observer);

    	virtual void detachObserver(Observer* observer);

        virtual void notifyObservers() const;

    	virtual void accept(Visitor* v) = 0;

    	virtual std::string getName() const;
    	virtual point<size_t> getPos() const;
    	virtual double getHealth() const;

        friend Visitor;
        friend Observer;

        friend class SetAttackTargetsVisitor;

        friend class CreatorOfNPC;

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

std::string lab6::NPC::getName() const {
    return name;
}

lab6::point<size_t> lab6::NPC::getPos() const {
    return pos;
}

double lab6::NPC::getHealth() const {
    return health;
}





#endif