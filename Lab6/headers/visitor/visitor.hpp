#ifndef VISITOR_HPP

#define VISITOR_HPP

#include <string>

#include "declarations/declarations.h"
#include "auxiliry/point.hpp"

namespace lab6 {
    class Visitor {
    public:
	    virtual void visitOgre(Ogre* ogre) const = 0;
	    virtual void visitBear(Bear* bear) const = 0;
	    virtual void visitSquirrel(Squirrel* squirrel) const = 0;
    };
};

#endif