/*
    This is  an example of how memory is allocated in the stack.
*/

#include <iostream>
#include <vector>

void a_funciton(){
    int z;
    std::cout << &z << std::endl;
}

int main() {

    int x;
    int y[3];

    std::cout << &x << std::endl;
    std::cout << &y << std::endl;
    a_funciton();

    std::vector<int> v(3);
    std::cout << v.data() << std::endl;

    for ( int i = 0; i < 10000; i++){
        v.push_back(0);
    }

    std::cout << v.data() << std::endl; // retrieve the considerations made on the memory allocation for vectors

    return 0;
}