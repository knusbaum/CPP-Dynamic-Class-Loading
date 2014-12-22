#include "dlclass.hpp"
#include "polygon.hpp"
#include <iostream>
#include <memory>

int main(void) {

    auto dlTriangle = DLClass<Polygon>("./triangle.so");
    auto dlSquare = DLClass<Polygon>("./square.so");
    
    int x = 5;
    std::shared_ptr<Polygon> triangle = dlTriangle.make_obj(3);
    std::shared_ptr<Polygon> square = dlSquare.make_obj(x);
    
    if(!triangle) {
        std::cerr << "Failed to instantiate a triangle." << std::endl;
        return 1;
    }

    std::cout << "Triangle area: " << triangle->area() << std::endl;
    triangle = std::shared_ptr<Polygon>(NULL);
    
    if(!square) {
        std::cerr << "Failed to instantiate a triangle." << std::endl;
        return 1;
    }

    std::cout << "Square area: " << square->area() << std::endl;
    square = std::shared_ptr<Polygon>(NULL);

    
}
