#ifndef CREATOR_OF_NPC

#define CREATOR_OF_NPC

#include <fstream>
#include "declarations/declarations.hpp"

namespace lab6 {
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

lab6::NPC* lab6::CreatorOfNPC::getNPC() {
    NPC* _npc = npc;
    npc = nullptr;
    return _npc;
}

void lab6::CreatorOfNPC::readName(std::string& name, std::ifstream& fin) {
    std::getline(fin, name, '\n');
    name = trim(name);
}

void lab6::CreatorOfNPC::readPos(point<size_t>& pos, std::ifstream& fin) {
    fin >> pos.x >> pos.y;
}

void lab6::CreatorOfNPC::readStatus(statusOfNPC& status, std::ifstream& fin) {
    std::string statusString;
    fin >> statusString;
    status = strToStatus(statusString);
}

std::string lab6::trim(const std::string& str, const std::string& whitespace) {
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

#endif