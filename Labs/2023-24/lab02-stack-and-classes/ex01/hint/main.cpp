#include <array>
#include <vector>
#include <numbers>
#include <memory>
#include <chrono>
#include <iostream>
#include <string> // this is actually needed?

class Shape {
public:
    // constructor that initializes the name
    // pure virtual getter for the area
    // getter for the shape name (non virtual)
    // virtual destructor
    Shape(const std::string& name) : _name(name) {} // use constant reference to avoid copying the string, this is more efficient
    const std::string& getName() const { return _name; } // const at the end of the function means that the function does not modify the object

    virtual double getArea() const = 0; // pure virtual function, abstract class means that it cannot be instantiated; you will not be able to instantiate a shape
                                        // because you still need to implement its definition
    virtual ~Shape() = default; // this is the syntax for a virtual destructor

private:
    // member with the name of the shape (const)
    std::string _name; // convention for private members: underscore before the name or m_name (m for member), or mName
};

// Implement the classes "Circle" and "Rectangle"
// The constructor must be empty, in the sense the name of the shape
// should not be a user's choice 

// Now implement the classes "Circle" and "Rectangle" with polymorphism

class Circle : public Shape { // this is the syntax for inheritance, you can also use private inheritance
public:
    Circle(double radius) : Shape("Circle"), _radius(radius) {} // this is not passed with const reference because it is a double, not a string, 
                                                                // so passing a double instead of a reference is the same in terms of storage (64 bit)
                                                                // Shape("Circle") is the syntax for calling the constructor of the base class, ie the father class

    virtual double getArea() const override { // override is a keyword that tells the compiler that this function is overriding a function in the base class, you need to specify const
        return std::numbers::pi_v<double> * _radius * _radius;
    }

    virtual ~Circle() = default; // this is the syntax for a virtual destructor
private:
    double _radius;
};

class Rectangle : public Shape {
public:
    Rectangle(double width, double height) : Shape("Rectangle"), _width(width), _height(height) {}

    virtual double getArea() const override {
        return _width * _height;
    }

    virtual ~Rectangle() = default;

private: 
    double _width;
    double _height;
};

int main() {
    // Instantiate vector of shapes
    // Add some shapes
    // Loop over shapes and print

    std::vector<std::shared_ptr<Shape>> shapes;
    // std::vector<Shape> shapes; // this will return an error because Shape is an abstract class, you cannot instantiate it
    shapes.push_back(std::make_shared<Circle>(1.0));
    shapes.push_back(std::make_shared<Rectangle>(1.5, 3.0));

    for (const auto& shapes : shapes) { // this for loop is using the same name for the iterator and the vector, this is not a problem because the scope is different
        std::cout << "Shape: " << shapes->getName() << " - Area: " << shapes->getArea() << std::endl;
    }

    return 0;
}