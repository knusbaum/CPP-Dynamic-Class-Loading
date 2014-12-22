#include "polygon.hpp"
#include <cmath>

class Triangle : public Polygon {
public:
    Triangle(int x) : Polygon(x) {}
    virtual double area() const {
        return side_length_ * side_length_ * sqrt(3) / 2;
    }
};


// the class factories

extern "C" Polygon* create(int x) {
    return new Triangle(x);
}

extern "C" void destroy(Polygon* p) {
    delete p;
}
