#include "header.h"

#include <iostream>
#include <algorithm>
#include <exception>

int main() {
    RingBuffer <int> rb(5);
    rb.push_back(1);
    rb.push_back(2);
    rb.push_back(3);
    rb.push_back(4);
    rb.push_back(5);
    rb.push_back(6);
    rb.push_back(7);
    for (int i = 0; i < 5; i++) {
        std::cout << rb[i] << " ";
    }
    std::cout << std::endl;


    RingBuffer <int>::Iterator it = rb.begin();
    *it = 57;
    ++it;
    *it = 75;
    for (int i = 0; i < 5; i++) {
        std::cout << rb[i] << " ";
    }
    std::cout << std::endl;


    std::cout << std::none_of(rb.begin(), rb.end(), [](int a)->bool {return  a < 0;}) << std::endl;
    std::cout << *std::find(rb.begin(), rb.end(), 5) << std::endl;


    rb.pop_back();
    for (auto it1 = rb.begin(); it1 != rb.end(); ++it1) {
        std::cout << *it1 << " ";
    }
    std::cout << std::endl;


    rb.push_front(77);
    for (auto it1 = rb.begin(); it1 != rb.end(); ++it1) {
        std::cout << *it1 << " ";
    }
    std::cout << std::endl;


    rb.pop_front();
    for (auto it1 = rb.begin(); it1 != rb.end(); ++it1) {
        std::cout << *it1 << " ";
    }
    std::cout << std::endl;


    std::cout << *(rb.begin() + 2) << std::endl;


    rb.insert(rb.begin(), 79);
    for (auto it1 = rb.begin(); it1 != rb.end(); ++it1) {
        std::cout << *it1 << " ";
    }
    std::cout << std::endl << *rb.begin() << std::endl;
    try {
        rb.insert(rb.begin() + 1, 79);
    }
    catch (std::exception& err) {
        std::cout << err.what() << std::endl;
    }


    rb.erase(rb.end() - 1);
    for (auto it1 = rb.begin(); it1 != rb.end(); ++it1) {
        std::cout << *it1 << " ";
    }
    std::cout << std::endl;


    std::cout << rb.front() << " " << rb.back() << " " << rb[0] << std::endl;

    rb.push_back(77);
    rb.resize(7);
    for (int& it1 : rb) {
        std::cout << it1 << " ";
    }
    return 0;
}
