//
// Created by Alex Greenen on 12/19/19.
//

#ifndef SCHRODINGER_SMOKE_MATH_UTIL_H
#define SCHRODINGER_SMOKE_MATH_UTIL_H


#include "field.h"
#include "vector3D.h"

field<float> divergence(field<vector3D>* field1){
    /**
    * computes divergence of scalar field.
    *
    * @param ri Tells which part to use: 'r' for real part, 'i' for imaginary
    * @param pos Indicated grid location to study
    * @return Laplacian or reel/imaginary part at grid point (x,y,z)
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
    * Converts grid coordinates to world coordinates
    *
    * @param ri Tells which part to use: 'r' for real part, 'i' for imaginary
    * @param pos Indicated grid location to study
    * @return Laplacian or reel/imaginary part at grid point (x,y,z)
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
    * Converts grid coordinates to world coordinates
    *
    * @param ri Tells which part to use: 'r' for real part, 'i' for imaginary
    * @param pos Indicated grid location to study
    * @return Laplacian or reel/imaginary part at grid point (x,y,z)
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

field<float> solve_poisson(field<float>* field1) {

}


#endif //SCHRODINGER_SMOKE_MATH_UTIL_H
