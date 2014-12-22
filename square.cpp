#include "polygon.hpp"
#include <cmath>

class Square : public Polygon {
public:
    Square(int x) : Polygon(x) {}
    virtual double area() const {
        return side_length_ * side_length_;
    }
};


// the class factories

extern "C" Polygon* create(int x) {
    return new Square(x);
}

extern "C" void destroy(Polygon* p) {
    delete p;
}
