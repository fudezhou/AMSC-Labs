#include "greet.hpp"
#include <iostream>

void greet(const std::string &name) { // constant reference is to avoid unecesary copied
    std::cout << "Hello, " << name << "!" << std::endl;
}