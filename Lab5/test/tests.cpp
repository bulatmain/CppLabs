#include <gtest/gtest.h>
#include <vector>
#include <map>

#include "cust_allocator.hpp"
#include "linked_list.hpp"

TEST(Allocator, std_vector) {
    std::vector<int, lab5::cust_allocator<int>> v1;

    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);
    v1.push_back(10);
    v1.push_back(10);
    v1.push_back(-1);
    v1.push_back(10);
    v1.push_back(10);
    v1.pop_back();
    v1.pop_back();
    v1.pop_back();
    v1.pop_back();

    std::vector<int> v2 = { 1, 2, 3, 4, 5, 10 };

    ASSERT_TRUE(v1.size() == v2.size());

    for (int i = 0; i < v2.size(); ++i) {
        ASSERT_TRUE(v1[i] == v2[i]);
    }
}

TEST(Allocator, std_map) {
    using map_allocator_type = lab5::cust_allocator<std::pair<const int, int>>;

    std::map<const int, int, std::less<int>, map_allocator_type> m1;

    int64_t counter = 1;
    m1.insert(std::pair<int, int>(0, 0));
    for (int64_t i = 1; i < 10; ++i) {
        counter *= i;
        m1.insert(std::pair<int, int>(i, counter));
    }

    std::map<int, int> m2;

    counter = 1;
    m2.insert(std::pair<int, int>(0, 0));
    for (int64_t i = 1; i < 10; ++i) {
        counter *= i;
        m2.insert(std::pair<int, int>(i, counter));
    }

    for (int i = 0; i < 10; ++i) {
        ASSERT_TRUE(m1[i] == m2[i]);
    }
}


TEST(Allocator, List) {
    using list_allocator_type = lab5::cust_allocator<lab5::node<int>>;
    lab5::linked_list<int, list_allocator_type> l{ 1, 2, 3, 4, 5 };

    for (int i = 0; i < 5; ++i) {
        l.insert(6 + i, l.cend());
    }

    ASSERT_TRUE(l.length() == 10);

    auto it = l.begin();

    for (int i = 0; i < 10; ++i) {
        ASSERT_TRUE(l.at(it++) == i + 1);
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}