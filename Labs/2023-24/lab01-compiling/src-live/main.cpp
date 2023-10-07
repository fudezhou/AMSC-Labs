#include "greet.hpp"

#define VAR 10 // this is bad (preprocessor directive); it is a macro variable

constexpr int VAR2 = 10; // this is much better than #define and it is not a preprocessor directive


int main() {
    greet("Fude");
    return 0;
}