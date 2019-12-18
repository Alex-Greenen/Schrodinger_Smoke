#include <iostream>
#include "field.h"

int main() {
    vector3D v1 = vector3D(1,1,1);
    vector3D v2 = vector3D(3,3,3);
    vector3D v3 = v1+v2;
    std::cout << v3[0];
    std::cout << "Hello, World!" << std::endl;
    return 0;
}