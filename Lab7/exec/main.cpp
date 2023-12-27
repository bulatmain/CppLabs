#include "gameModel.hpp"
using namespace lab7;


int main() {
    std::shared_ptr<std::mutex> mutex = std::make_shared<std::mutex>();
    ConsoleMessageBroker cmb(mutex);
    
    GameModel gm(std::move(cmb));

    gm.launch();

    return 0;
}