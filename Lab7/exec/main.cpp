#include <iostream>
#include <thread>
#include "headersList.hpp"
using namespace lab7;

void f(std::shared_ptr<ConsoleMessageBroker> cmb, const std::string& message) {
    cmb->sendMessage(message);
}

int main() {

    std::shared_ptr<std::mutex> mtx_ptr(new std::mutex);

    std::vector<std::thread*> threads;

    for (int i = 0; i < 100; ++i) {    
        auto cmb = std::make_shared<ConsoleMessageBroker>(mtx_ptr);
        threads.push_back(new std::thread(f, cmb, std::to_string(i) + " "));
    }

    for (auto t : threads) {
        t->join();
    }

    return 0;
}