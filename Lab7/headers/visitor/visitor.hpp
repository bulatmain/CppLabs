#ifndef VISITOR_HPP

#define VISITOR_HPP

#include <string>

#include "declarations/declarations.hpp"
#include "auxiliry/point.hpp"

namespace lab7 {
    class Visitor {
    public:
	    virtual void visitOgre(Ogre* ogre) {};
	    virtual void visitBear(Bear* bear) {};
	    virtual void visitSquirrel(Squirrel* squirrel) {};
    };
};

#endif