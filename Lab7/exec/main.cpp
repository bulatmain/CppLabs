#include <iostream>
#include "headersList.hpp"
using namespace lab7;


int main() {

    std::shared_ptr<std::mutex> mtx_ptr(new std::mutex);

    FileMessageBroker<std::mutex> fmb1("file", mtx_ptr);
    FileMessageBroker<std::mutex> fmb2("file", mtx_ptr);
    FileMessageBroker<std::mutex> fmb3("file", mtx_ptr);

    fmb1.sendMessage("A!\n");
    fmb2.sendMessage("B!\n");
    fmb3.sendMessage("C!\n");

    return 0;
}