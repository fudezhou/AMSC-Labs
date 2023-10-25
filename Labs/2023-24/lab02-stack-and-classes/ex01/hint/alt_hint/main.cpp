#include <array>
#include <vector>
#include <numbers>
#include <memory>
#include <chrono>
#include <iostream>
#include "shape.hpp"

int main() {

    // This line declares a std::vector named shapes. This vector is designed to hold objects of type std::shared_ptr<Shape>. 
    // In other words, it's a container for smart pointers to objects of the Shape class or its derived classes.
    // Smart pointers, like 'std::shared_ptr', provide automatic memory management. 
    // They ensure that the memory allocated for objects is released when it's no longer needed, 
    // which helps prevent memory leaks. The use of shared pointers here indicates that multiple 
    // parts of the program can share ownership of the objects in this container.
    std::vector<std::shared_ptr<Shape>> shapes;

    // The '.push_back()' function is used to add an element (or object) to the end of a container, 
    // such as a std::vector. It is a member function provided by many C++ Standard Library containers, 
    // including vectors, and it helps expand the container to accommodate the new element.
    // Arguments are of type std::shared_ptr<Shape> and are created using the 'std::make_shared' function.
    shapes.push_back(std::make_shared<Circle>(6.9));
    shapes.push_back(std::make_shared<Rectangle>(10., 2.));

    // The 'auto' keyword is a placeholder for a type. It tells the compiler to deduce the type of the variable
    // In this case it is deduced to be a std::shared_ptr<Shape> and is used to iterate over the vector of shapes
    for (const auto& shape : shapes) {

        // '->' is the syntax for accessing a method of a pointer, 
        // in this case the methodd getName() and getArea() of the class Shape
        std::cout << "Shape: " << shape->getName() << " - Area: " << shape->getArea() << std::endl;
    }

    return 0;
}
