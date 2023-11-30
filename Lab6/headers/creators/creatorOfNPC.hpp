#ifndef CREATOR_OF_NPC

#define CREATOR_OF_NPC

#include <fstream>
#include "declarations/declarations.hpp"

namespace lab6 {
    class CreatorOfNPC {
    public:
        NPC* getNPC();
        virtual void createNPC() = 0;
        // In derived define init(Args... args) and construct(Args... args).
    protected:
        NPC* npc = nullptr;
    
    protected:

        virtual void readName(std::string& name, std::ifstream& fin);
        virtual void readPos(point<size_t>& pos, std::ifstream& fin);
        virtual void readStatus(statusOfNPC& status, std::ifstream& fin);

    };
};

#include "npc/npc.hpp"
#include "auxiliry/point.hpp"

lab6::NPC* lab6::CreatorOfNPC::getNPC() {
    NPC* _npc = npc;
    npc = nullptr;
    return _npc;
}

void lab6::CreatorOfNPC::readName(std::string& name, std::ifstream& fin) {
    std::getline(fin, name, '\n');
}

void lab6::CreatorOfNPC::readPos(point<size_t>& pos, std::ifstream& fin) {
    fin >> pos.x >> pos.y;
}

void lab6::CreatorOfNPC::readStatus(statusOfNPC& status, std::ifstream& fin) {
    std::string statusString;
    fin >> statusString;
    status = strToStatus(statusString);
}

#endif