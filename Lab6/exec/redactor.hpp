#ifndef REDACTOR_HPP
#define REDACTOR_HPP

#include "headersList.hpp"

namespace lab6 {
    class Redactor {
    public:
        enum Codes {
            CREATE_NPC,
            READ_NPC,
            SAVE_NPC,
            SAVE_ALL_NPCS,
            PRINT_ALL_NPCS,
            SET_ATTACK_DISTANCE,
            SET_FIGHT_MODE,
            END_CODE
        };

    private:
    // Message brokers to be moved
        FileMessageBroker fmb;
        ConsoleMessageBroker cmb;


    public:
        Redactor(const std::string& logFileName) 
            : fmb(logFileName), keo_file(std::move(fmb)), keo_cons(std::move(cmb)), setTargetsVisitor(&npcs, 0) {}

        ~Redactor() {
            for (auto npc : npcs) {
                delete npc;
            }
        }
        void launch();

    private:
        void execute_redactor_loop(Codes& code);

        void functionTreeSwitch(Codes const code);

        void createNPC();

        void readNPC();

        void saveNPC();

        void saveAllNPCs();

        void printAllNPCs();

        void setAttackDistance();

        void setFightMode();


        void createNPCFromCode(size_t code_int, const std::string& name, const point<size_t>& pos);

        void readNPCFromCode(size_t code_int, const std::string& filename);

        void readCode(Codes& code);

        Codes intToCode(size_t code_int);

        size_t readCodeOfNPC();

        void readName(std::string& name);


    private:

        KillEventObserver<FileMessageBroker> keo_file;
        KillEventObserver<ConsoleMessageBroker> keo_cons;

        CreatorOfOgre<std::allocator<Ogre>> creatorOfOgre;
        CreatorOfBear<std::allocator<Bear>> creatorOfBear;
        CreatorOfSquirrel<std::allocator<Squirrel>> creatorOfSquirrel;

        std::list<NPC*> npcs;

        SetAttackTargetsVisitor<std::list> setTargetsVisitor;
        SetAttackTargetVisitor setAttackTargetVisitor;
        AttackVisitor attackVisitor;

    private:

#define menu_str "\t0. Create NPC\n\
\t1. Read NPC from file\n\
\t2. Save NPC in file\n\
\t3. Save all NPC's\n\
\t4. Print all NPC's\n\
\t5. Set attack distance\n\
\t6. Set fight mode\n\
\t7. Exit\n"

#define npcs_list "\t0. Ogre\n\
\t1. Bear\n\
\t2. Squirrel\n"

    };
};

void lab6::Redactor::launch() {
    Codes code;
    do {
        execute_redactor_loop(code);
    } while (code != END_CODE);
}

void lab6::Redactor::execute_redactor_loop(Codes& code) {
    try {
        readCode(code);
        functionTreeSwitch(code);
    } catch (const std::invalid_argument& e) {
        std::cout << "Error: there's no such code!\n";
        return;
    }
}

void lab6::Redactor::functionTreeSwitch(Codes const code) {
    if (code == CREATE_NPC) {
        createNPC();
    } else if (code == READ_NPC) {
        readNPC();
    } else if (code == SAVE_NPC) {
        saveNPC();
    } else if (code == SAVE_ALL_NPCS) {
        saveAllNPCs();
    } else if (code == PRINT_ALL_NPCS) {
        printAllNPCs();
    } else if (code == SET_ATTACK_DISTANCE) {
        setAttackDistance();
    } else if (code == SET_FIGHT_MODE) {
        setFightMode();
    } else if (code == END_CODE) {
        return;
    }
}

void lab6::Redactor::createNPC() {
    size_t code_int = readCodeOfNPC();
    if (2 < code_int) {
        std::cout << "Error: there's no such character!\n";
        return;
    }

    std::string name; 
    readName(name);
    point<size_t> pos;
    std::cin >> pos.x >> pos.y;

    createNPCFromCode(code_int, name, pos);
}

void lab6::Redactor::readNPC() {
    size_t code_int = readCodeOfNPC();
    if (2 < code_int) {
        std::cout << "Error: there's no such character!\n";
        return;
    }

    std::cout << "Choose a file which from read a character: ";
    std::string filename; std::cin >> filename;

    readNPCFromCode(code_int, filename);
}

void lab6::Redactor::saveNPC() {
    std::cout << "Please, enter name of choosen npc: ";
    std::string name;
    readName(name);

    auto npc_it = std::find_if(npcs.begin(), npcs.end(), [&name](NPC* npc) { return npc->name == name; });

    if (npc_it == npcs.end()) {
        std::cout << "There's no npc with such name!\n";
        return;
    }

    std::cout << "Please, choose file of npc to be saved: ";
    std::string filename; std::cin >> filename;

    FileMessageBroker fmb(filename);
    SerializeVisitor<FileMessageBroker> serializeVisitor(std::move(fmb));

    (*npc_it)->accept(&serializeVisitor);
}

void lab6::Redactor::saveAllNPCs() {
    std::cout << "Please, choose file of npc to be saved: ";
    std::string filename; std::cin >> filename;

    FileMessageBroker fmb(filename);
    SerializeVisitor<FileMessageBroker> serializeVisitor(std::move(fmb));

    for (auto& npc : npcs) {
        npc->accept(&serializeVisitor);
    }
}

void lab6::Redactor::printAllNPCs() {

    std::cout << "NPC's: {\n";

    ConsoleMessageBroker cmb;
    SerializeVisitor<ConsoleMessageBroker> printVisitor(std::move(cmb));

    for (auto& npc : npcs) {
        npc->accept(&printVisitor);
    }

    std::cout << "};\n\n";
}

void lab6::Redactor::setAttackDistance() {
    std::cout << "Pleace, enter new attack distance: ";
    double attackDistance; std::cin >> attackDistance;
    setTargetsVisitor.setAttackDistance(attackDistance);
}


void lab6::Redactor::setFightMode() {
    for (auto npc : npcs) {
        npc->accept(&setTargetsVisitor);
    }

    for (auto npc : npcs) {
        npc->accept(&setAttackTargetVisitor);
    }

    for (auto npc : npcs) {
        npc->accept(&attackVisitor);
    }

    std::list<NPC*> dead;
    for (auto npc : npcs) {
        if (npc->status == DEAD) {
            dead.emplace_back(npc);
        }
    }

    for (auto& npc : dead) {
        npcs.erase(std::find(npcs.begin(), npcs.end(), npc));
    }
}

void lab6::Redactor::createNPCFromCode(size_t code_int, const std::string& name, const point<size_t>& pos) {
    NPC* npc;
    if (code_int == 0) {
        creatorOfOgre.construct(name, pos, ALIVE, nullptr);
        npc = creatorOfOgre.getNPC();
    } else if (code_int == 1) {
        creatorOfBear.construct(name, pos, ALIVE, nullptr);
        npc = creatorOfBear.getNPC();
    } else if (code_int == 2) {
        creatorOfSquirrel.construct(name, pos, ALIVE); 
        npc = creatorOfSquirrel.getNPC();      
    }
    npc->attachObserver(&keo_file);
    npc->attachObserver(&keo_cons);
    npcs.emplace_back(npc);
}

void lab6::Redactor::readNPCFromCode(size_t code_int, const std::string& filename) {
    NPC* npc;
    if (code_int == 0) {
        creatorOfOgre.readFromFile(filename);
        npc = creatorOfOgre.getNPC();
    } else if (code_int == 1) {
        creatorOfBear.readFromFile(filename);
        npc = creatorOfBear.getNPC();
    } else if (code_int == 2) {
        creatorOfSquirrel.readFromFile(filename);
        npc = creatorOfSquirrel.getNPC();       
    }
    npc->attachObserver(&keo_file);
    npc->attachObserver(&keo_cons);
    npcs.emplace_back(npc);
}

void lab6::Redactor::readCode(Codes& code) {
    std::cout << "What do you want to do?\n\n" << menu_str << std::endl << "Code: ";
    size_t code_int;
    std::cin >> code_int;
    std::cin.get();
    code = intToCode(code_int);
}

void lab6::Redactor::readName(std::string& name) {
    std::getline(std::cin, name);
    lab6::trim(name);
}

lab6::Redactor::Codes lab6::Redactor::intToCode(size_t code_int) {
    return Codes(code_int);
}

size_t lab6::Redactor::readCodeOfNPC() {
    std::cout << "Please, choose one of these characters:\n" << npcs_list << std::endl << "Code: ";
    size_t code_int;
    std::cin >> code_int;
    std::cin.get();
    return code_int;
}

#undef menu_str
#undef npcs_list

#endif