#ifndef VISITOR_HPP

#define VISITOR_HPP

#include <string>

#include "declarations/declarations.hpp"
#include "auxiliry/point.hpp"

namespace lab6 {
    class Visitor {
    public:
	    virtual void visitOgre(Ogre* ogre) const {};
	    virtual void visitBear(Bear* bear) const {};
	    virtual void visitSquirrel(Squirrel* squirrel) const {};
    };
};

#endif