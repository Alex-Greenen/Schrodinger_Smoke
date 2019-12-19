//
// Created by Alex Greenen on 12/19/19.
//

#ifndef SCHRODINGER_SMOKE_MATH_UTIL_H
#define SCHRODINGER_SMOKE_MATH_UTIL_H


#include "field.h"
#include "vector3D.h"
#include <cmath>

field<float> divergence(field<vector3D>* field1){
    /**
    * Computes divergence of vector field.
    *
    * @param field1 pointer to field you wish to use
    * @return divergence of field
    */

    field<float> temp_vect_field = field<float>();

    for (int x=0; x<field1->grid_marks[0]; x++){
        for (int y=0; y<field1->grid_marks[1]; y++){
            for (int z=0; z<field1->grid_marks[2]; z++){
                vector3D diffvec = (field1->getGridValue(x+1, y, z) - field1->getGridValue(x-1, y, z))/ (2*field1->resolution);
                float value = diffvec[0] + diffvec[1] + diffvec[2];
                temp_vect_field.updateGridValue(x,y,z, value);
            }
        }
    }
    return temp_vect_field;
}


field<vector3D> gradient(field<float>* field1){
    /**
    * Computes gradient of scalar field.
    *
    * @param field1 pointer to field you wish to use
    * @return gradient of field
    */


    field<vector3D> temp_vect_field = field<vector3D>();

    for (int x=0; x<field1->grid_marks[0]; x++){
        for (int y=0; y<field1->grid_marks[1]; y++){
            for (int z=0; z<field1->grid_marks[2]; z++){
                float xdiv = (field1->getGridValue(x+1, y, z) - field1->getGridValue(x-1, y, z))/(2*field1->resolution);
                float ydiv = (field1->getGridValue(x+1, y, z) - field1->getGridValue(x-1, y, z))/(2*field1->resolution);
                float zdiv = (field1->getGridValue(x+1, y, z) - field1->getGridValue(x-1, y, z))/(2*field1->resolution);
                temp_vect_field.updateGridValue(x,y,z,vector3D(xdiv,ydiv,zdiv));
            }
        }
    }
    return temp_vect_field;
}


field<float> laplacian(field<float>* field1){
    /**
    * Computes laplacian of scalar field.
    *
    * @param field1 pointer to field you wish to use
    * @return laplacian of field
    */


    field<float> temp_float_field = field<float>();

    for (int x=0; x<field1->grid_marks[0]; x++){
        for (int y=0; y<field1->grid_marks[1]; y++){
            for (int z=0; z<field1->grid_marks[2]; z++){
                float laplacian = 0.0;
                laplacian += field1->getGridValue(x+1, y, z)
                             + field1->getGridValue(x-1, y, z)
                             + field1->getGridValue(x, y+1, z)
                             + field1->getGridValue(x, y-1, z)
                             + field1->getGridValue(x, y, z+1)
                             + field1->getGridValue(x, y, z-1)
                             - 6* field1->getGridValue(x, y, z);
                laplacian /= (field1->resolution)*(field1->resolution);
                temp_float_field.updateGridValue(x,y,z,laplacian);
            }
        }
    }
    return temp_float_field;
}

field<float> apply_element_wise(field<float>* field1, float funct(float)){
    field<float> temp = *field1;
    for (int x=0; x<field1->grid_marks[0]; x++) {
        for (int y = 0; y < field1->grid_marks[1]; y++) {
            for (int z = 0; z < field1->grid_marks[2]; z++) {
                temp.updateGridValue(x,y,z, funct(temp.getGridValue(x,y,z)));
            }
        }
    }
}

field<float> cos(field<float>* field1){
    return apply_element_wise(field1, cos);
}

field<float> sin(field<float>* field1){
    return apply_element_wise(field1, sin);
}


field<float> solve_poisson(field<float>* field1) {
    /**
    * Solves poisson equation using multi-grid method;
    *
    * @param field1 pointer to field you wish to use
    * @return solution of field
    */

    field<float> solution;

    return solution;

}






#endif //SCHRODINGER_SMOKE_MATH_UTIL_H
