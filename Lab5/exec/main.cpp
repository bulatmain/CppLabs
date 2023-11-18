#include <iostream>
#include <list>
#include <map>
#include "cust_allocator.hpp"
#include "linked_list.hpp"

using namespace std;
using namespace lab5;

int factorial(int n) {
    if (n == 1 || n == 0) {
        return 1;
    } else {
        return n * (n - 1);
    }
}

int main() {
    using map_allocator_type = cust_allocator<std::pair<int, int>>;
    using list_allocator_type = cust_allocator<node<int>>;

    map<int, int, std::less<int>, map_allocator_type> m;

    for (int i = 0; i < 10; ++i) {
        m[i] = factorial(i);
    }

    for (auto it = m.begin(); it != m.end(); ++it) {
        cout << "[" << it->first << "; " << it->second << "] ";
    }
    cout << endl;

    linked_list<int, list_allocator_type> l;

    for (int i = 0; i < 10; ++i) {
        l.insert(2 * i, l.cend());
    }

    for (auto it = l.begin(); it != l.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    for (int i = 0; i < 10; ++i) {
        l.erase(l.begin());
    }

    return 0;
}