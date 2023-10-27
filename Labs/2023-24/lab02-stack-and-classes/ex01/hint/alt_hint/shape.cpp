#include "shape.hpp"
#include <numbers>

// Definition of the constructor of the base class Shape;
// it takes a string as parameter and initializes the private member _name with it.
// Shape::Shape mean that you are calling, withing the class Shape, the constructor of the class Shape
Shape::Shape(const std::string& name) : _name(name) {};


// Definition of the getName() for the name of the shape;
// it returns the private member _name.
const std::string& Shape::getName() const {
    return _name;
}

// Definition of the constructor of the derived class Circle;
// it takes a double as parameter and initializes the private member _radius with it.
Circle::Circle(double radius) : Shape("Circle"), _radius(radius) {}

// Definition of the overridden getArea() for the area of the circle;
double Circle::getArea() const {
    return std::numbers::pi_v<double> * _radius * _radius;
}

Rectangle::Rectangle(double width, double height) : Shape("Rectangle"), _width(width), _height(height) {}

double Rectangle::getArea() const {
    return _width * _height;
}
