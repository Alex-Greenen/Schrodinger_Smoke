#include <iostream>
#include "field.h"
#include "vector3D.h"

int main() {
    field<float> myfield = field<float>(2,2,2,1);
    field<float> myfield2 = field<float>(2,2,2,1);
    myfield.updateGridValue(0, 0, 0, 4.0);
    myfield2.updateGridValue(0, 0, 0, 2);
    field<float> myfield3 = myfield+myfield2;
    std::cout << myfield3.getGridValue(0,0,0) << std::endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}