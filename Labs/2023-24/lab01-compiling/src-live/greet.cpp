#include "greet.hpp"
#include <iostream>

void greet(const std::string &name) { 
    // constant reference is to avoid unecesary copied, 
    // this variable is not going to be modified and it 
    // is a read-only variable
    std::cout << "Hello, " << name << "!" << std::endl;
}