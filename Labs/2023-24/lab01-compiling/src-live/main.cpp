#include "greet.hpp"

#define VAR = 10 // this is bad

constexpr int VAR2 = 10; // this is much better than #define


int main() {
    greet("Fude");
    return 0;
}