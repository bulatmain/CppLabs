#ifndef CREATOR_OF_NPC

#define CREATOR_OF_NPC

#include "declarations/declarations.hpp"

namespace lab6 {
    class CreatorOfNPC {
    public:
        NPC* getNPC();
        virtual void createNPC() = 0;
        // In derived define init(Args... args) and construct(Args... args).
    protected:
        NPC* npc = nullptr;
    };
};

#include "npc/npc.hpp"

lab6::NPC* lab6::CreatorOfNPC::getNPC() {
    NPC* _npc = npc;
    npc = nullptr;
    return _npc;
}




#endif