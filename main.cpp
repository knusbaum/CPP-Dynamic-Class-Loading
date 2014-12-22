#include "dlclass.hpp"
#include "polygon.hpp"
#include <iostream>
#include <memory>

int main(void) {

    auto dl = DLClass<Polygon>("./triangle.so");

    int x = 5;
    std::shared_ptr<Polygon> triangle = dl.make_obj(3);

    if(!triangle) {
        std::cerr << "Failed to instantiate a triangle." << std::endl;
        return 1;
    }
    
    std::cout << triangle->area() << std::endl;
    triangle = std::shared_ptr<Polygon>(NULL);
    
}
