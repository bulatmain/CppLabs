#ifndef GAME_MODEL_HPP
#define GAME_MODEL_HPP

#include <functional>
#include <thread>
#include <chrono>
#include "headersList.hpp"

namespace lab7 {
    using namespace std::chrono_literals;

    using duration = std::chrono::duration<double, std::milli>;
    using time = std::chrono::time_point<std::chrono::steady_clock>;

    using npc_list = std::list<npc_ptr>;
    using npc_list_ptr = std::shared_ptr<npc_list>;
    using thread_list = std::list<std::thread>;
    using thread_list_ptr = std::shared_ptr<thread_list>;
    using mutex_ptr = std::shared_ptr<std::mutex>;

    class GameModel {   
    public:
        void launch();

        GameModel(ConsoleMessageBroker&& cmb) : cmb(std::move(cmb)) {
            std::srand(std::time(0));
            npcs = std::make_shared<npc_list>();
            npcs_list_mutex = std::make_shared<std::mutex>();
            threads = std::make_shared<thread_list>();
            startTime = std::chrono::steady_clock::now();
            is_running = std::make_shared<bool>(true);
        }

    private:

        void generateNPCPositions(size_t count, point<size_t> edge);
        void launchMoveNPCsThread();
        void printWithDelayAndJoinThreadsAfterGivenTime(std::function<void()> printer, duration delay, duration endTime);
        npc_ptr generateRandomNPC(point<size_t> edge);

        npc_list_ptr npcs;
        mutex_ptr npcs_list_mutex;
        thread_list_ptr threads;
        ConsoleMessageBroker cmb;
        time startTime;

        std::shared_ptr<bool> is_running;

        const size_t npcsCount = 50;
        const point<size_t> mapEdge = { 100, 100 };
        const duration delay = 0.2s;
        const duration endTime = 5s;

        template <int grid, int edge_x, int edge_y>
        struct Printer {
        public:
            Printer(npc_list_ptr npcs, mutex_ptr mutex, const ConsoleMessageBroker& cmb) :
                npcs(npcs), mutex(mutex), cmb(cmb) {}

            void operator()() {
                update();
                print();
            }

            void update() {
                field.fill(0);
                for (auto npc : *npcs) {
                    int i = npc->pos.x / step_x;
                    int j = npc->pos.y / step_y;
                    if (npc->status == ALIVE) {
                        field[i + grid * j] = getNPCLiteral(npc->identify());
                    } else {
                        field[i + grid * j] = '.';
                    }
                }
            }

            void print() {
                std::string map_str;
                for (int j = 0; j < grid; ++j) {
                    for (int i = 0; i < grid; ++i) {
                        char c = field[i + j * grid];
                        map_str += "[";
                        map_str += (c != 0 ? c : ' ');
                        map_str += "]";
                    }
                    map_str += "\n";
                }
                map_str += "\n";
                cmb.sendMessage(map_str);
            }

            void print_alive() {
                std::string map_str = "Still alive {\n";
                for (auto npc : *npcs) {
                    if (npc->status == ALIVE) {
                        map_str += "\t";
                        map_str += getNPCLiteral(npc->identify());
                        map_str += " at pos ";
                        map_str += npc->pos.to_str();
                        map_str += "\n";
                    }
                }
                map_str += "};\n";
                cmb.sendMessage(map_str);
            }

            char getNPCLiteral(typesOfNPCs type) {
                switch (type)
                {
                case type_Ogre:
                    return 'O';
                case type_Bear:
                    return 'B';
                case type_Squirrel:
                    return 'S';
                default:
                    return '?';
                }
            }

        public:
            npc_list_ptr npcs;
            mutex_ptr mutex;
            ConsoleMessageBroker cmb;

            std::array<char, grid*grid> field{0};
            const int step_x = edge_x / grid;
            const int step_y = edge_y / grid;
        };
    };


    void moveNPCs(npc_list_ptr npcs, mutex_ptr mutex, point<size_t> edge, thread_list_ptr threads, std::shared_ptr<bool> is_running, duration delay);
    void moveNPC(npc_ptr npc, point<size_t> edge);
    void tryAttack(npc_ptr npc_1, npc_ptr npc_2, mutex_ptr mutex, thread_list_ptr threads);
    void attack(npc_ptr npc_1, npc_ptr npc_2, mutex_ptr mutex);
};

#include "creators/creatorOfOgre.hpp"
#include "creators/creatorOfBear.hpp"
#include "creators/creatorOfSquirrel.hpp"

void lab7::GameModel::launch() {
    generateNPCPositions(npcsCount, mapEdge);
    launchMoveNPCsThread();
    Printer<20, 100, 100> printer(npcs, npcs_list_mutex, cmb);
    printWithDelayAndJoinThreadsAfterGivenTime(printer, delay, endTime);
    printer.print_alive();
}

void lab7::GameModel::generateNPCPositions(size_t count, point<size_t> edge) {
    for (size_t i = 0; i < count; ++i) {
        npcs->push_back(generateRandomNPC(edge));
    }
}

void lab7::GameModel::launchMoveNPCsThread() {
    threads->push_back(std::thread(moveNPCs, npcs, npcs_list_mutex, mapEdge, threads, is_running, delay));
}

void lab7::GameModel::printWithDelayAndJoinThreadsAfterGivenTime(std::function<void()> printer, duration delay, duration endTime) {
    while (true) {
        printer();
        time nowTime = std::chrono::steady_clock::now();
        if (endTime < nowTime - startTime) {
            break;
        }
        std::this_thread::sleep_for(delay);
    }
    *is_running = false;
    for (auto& thread : *threads) {
        thread.join();
    }
}

lab7::npc_ptr lab7::GameModel::generateRandomNPC(lab7::point<size_t> edge) {
    npc_ptr npc;
    typesOfNPCs type = typesOfNPCs(std::rand() % 3 + 1);
    size_t x = std::rand() % edge.x;
    size_t y = std::rand() % edge.y;
    if (type == type_Ogre) {
        CreatorOfOgre creatorOfOgre;
        creatorOfOgre.construct("Ogre", {x, y}, ALIVE);
        npc = creatorOfOgre.getNPC();
    } else if (type == type_Bear) {
        CreatorOfBear creatorOfBear;
        creatorOfBear.construct("Bear", {x, y}, ALIVE);
        npc = creatorOfBear.getNPC();
    } else if (type == type_Squirrel) {
        CreatorOfSquirrel creatorOfSquirrel;
        creatorOfSquirrel.construct("Squirrel", {x, y}, ALIVE);
        npc = creatorOfSquirrel.getNPC();
    }
    return npc;
}

void lab7::moveNPCs(npc_list_ptr npcs, mutex_ptr mutex, point<size_t> edge, thread_list_ptr threads, std::shared_ptr<bool> is_running, duration delay) {
    while (*is_running) {
        {
            std::lock_guard<std::mutex> lock(*mutex);
            for (auto npc : *npcs) {
                moveNPC(npc, edge);
            }
        }
        std::this_thread::sleep_for(delay);
        for (auto npc_1 = npcs->begin(); npc_1 != npcs->end(); ++npc_1) {
            for (auto npc_2 = npcs->begin(); npc_2 != npcs->end(); ++npc_2) {
                tryAttack(*npc_1, *npc_2, mutex, threads);
            }
        }
    }
}

// a + b won't overflow size_t
bool willNotOverflow(size_t a, int b);

size_t newX(size_t oldX, int dx, size_t edgeX);

void lab7::moveNPC(npc_ptr npc, point<size_t> edge) {
    if (npc->status == DEAD) {
        return;
    }
    int movementDistance = npc->getMovementDistance();
    int dx = (std::rand() % (2 * movementDistance)) - movementDistance;
    int dy = (std::rand() % (2 * movementDistance)) - movementDistance;
    size_t new_x = newX(npc->pos.x, dx, edge.x);
    size_t new_y = newX(npc->pos.y, dy, edge.y);
    npc->pos = { new_x, new_y };
}

bool isInRange(lab7::npc_ptr npc_1, lab7::npc_ptr npc_2) {
    return lab7::distance(npc_1->pos, npc_2->pos) <= npc_1->getAttackDistance();
}

void lab7::tryAttack(npc_ptr npc_1, npc_ptr npc_2, mutex_ptr mutex, thread_list_ptr threads) {
    if (npc_1 != npc_2 && isInRange(npc_1, npc_2) && npc_1->status == ALIVE && npc_2->status == ALIVE) {
        threads->push_back(std::thread(attack, npc_1, npc_2, mutex));
    }
} 

void lab7::attack(npc_ptr npc_1, npc_ptr npc_2, mutex_ptr mutex) {
    std::lock_guard<std::mutex> lock(*mutex);
    int npc_1_attack_power = std::rand() % 6;
    int npc_2_defence_power = std::rand() % 6;
    if (npc_2_defence_power < npc_1_attack_power) {
        npc_2->status = DEAD;
    }
}

bool willNotOverflow(size_t a, int b) {
    return (
        (b < 0 && -b < a) ||
        (0 < b && a <= SIZE_MAX - b)
    );
}

size_t newX(size_t oldX, int dx, size_t edgeX) {
    if (willNotOverflow(oldX, dx) && oldX + dx < edgeX) {
        return oldX + dx;
    } else {
        return oldX;
    }
}


#endif