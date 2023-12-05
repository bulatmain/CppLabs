#ifndef CREATOR_OF_NPC

#define CREATOR_OF_NPC

#include <fstream>
#include "declarations/declarations.hpp"

namespace lab7 {
    class CreatorOfNPC {
    public:
        NPC* getNPC();
        virtual void createNPC() = 0;

    protected:
        NPC* npc = nullptr;
    
    protected:
        virtual void readName(std::string& name, std::ifstream& fin);
        virtual void readPos(point<size_t>& pos, std::ifstream& fin);
        virtual void readStatus(statusOfNPC& status, std::ifstream& fin);

    };

    std::string trim(const std::string& str, const std::string& whitespace = " \n");
};

#include "npc/npc.hpp"
#include "auxiliry/point.hpp"

lab7::NPC* lab7::CreatorOfNPC::getNPC() {
    NPC* _npc = npc;
    npc = nullptr;
    return _npc;
}

void lab7::CreatorOfNPC::readName(std::string& name, std::ifstream& fin) {
    std::getline(fin, name, '\n');
    name = trim(name);
}

void lab7::CreatorOfNPC::readPos(point<size_t>& pos, std::ifstream& fin) {
    fin >> pos.x >> pos.y;
}

void lab7::CreatorOfNPC::readStatus(statusOfNPC& status, std::ifstream& fin) {
    std::string statusString;
    fin >> statusString;
    status = strToStatus(statusString);
}

std::string lab7::trim(const std::string& str, const std::string& whitespace) {
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

#endif