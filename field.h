//
// Created by Alex Greenen on 12/15/19.
//

#ifndef SCHRODINGER_SMOKE_FIELD_H
#define SCHRODINGER_SMOKE_FIELD_H

#include <array>
#include <cmath>
#include "world.h"
#include "iostream"

using namespace std;

template <class field_type>
class field {
public:
    field() = default;
    field(world* _w): w(_w){
        grid = new field_type[w->number_of_grid_nodes]();
    }
    field(world* _w, field_type value): w(_w){
        grid = new field_type[w->number_of_grid_nodes]();
        for (int i =0; i< w->number_of_grid_nodes; i++){
            grid[i] = value;
        }
    }

    field_type* grid;
    world* w;

    void updateGridValue(int x, int y, int z, field_type value);
    field_type getGridValue(int x, int y, int z) const;
};


template <class field_type>
void field<field_type>::updateGridValue(int x, int y, int z, field_type value){
    /**
     * Updates the value of the grid at a given point. Wrap around boundary if needed.
     *
     * @param x X grid point
     * @param y Y grid point
     * @param z Z grid point
     * @param value Value to be stored at grid point
     */
    x = (x % w->grid_marks[0] + w->grid_marks[0]) % w->grid_marks[0];
    y = (y % w->grid_marks[1] + w->grid_marks[1]) % w->grid_marks[1];
    z = (y % w->grid_marks[2] + w->grid_marks[2]) % w->grid_marks[2];

    grid[x*w->grid_marks[1]*w->grid_marks[2] + y*w->grid_marks[1] + z] = value;
}

template <class field_type>
field_type field<field_type>::getGridValue(int x, int y, int z) const {
    /**
     * Returns the value of the grid at a given point. Wrap around boundary if needed.
     *
     * @param x X grid point
     * @param y Y grid point
     * @param z Z grid point
     * @return Value at grid point
     */
    x = (x % w->grid_marks[0] + w->grid_marks[0]) % w->grid_marks[0];
    y = (y % w->grid_marks[1] + w->grid_marks[1]) % w->grid_marks[1];
    z = (y % w->grid_marks[2] + w->grid_marks[2]) % w->grid_marks[2];

    return grid[x*w->grid_marks[1]*w->grid_marks[2] + y*w->grid_marks[1] + z];
}




// THE FOLLOWING OPERATORS ARE NOT WORKING

template <class field_type>
const field<field_type> operator+(const field<field_type>& v1, const field<field_type>& v2){
    /**
    * Adds two fields to give a field
    */
    field<field_type> newField = field<field_type>(v1.w);
    for (int i = 0; i<newField.w->number_of_grid_nodes; i++){
        newField.grid[i] = v1.grid[i]+ v2.grid[i];
    }
    return newField;
}

template <class field_type>
const field<field_type> operator-(const field<field_type>& v1, const field<field_type>& v2){
    /**
    * Substracts two fields to give a field
    */
    field<field_type> newField = field<field_type>(v1.w);
    for (int i = 0; i<newField.w->number_of_grid_nodes; i++){
        newField.grid[i] = v1.grid[i] - v2.grid[i];
    }
    return newField;
}

template <class field_type>
const field<field_type> operator*(const float v1, const field<field_type>& v2) {
    /**
    * Multiplies a scalar and vector field to give a vector field
    */
    field<field_type> newField = field<field_type>(v2.w);
    for (int i = 0; i<newField.w->number_of_grid_nodes; i++){
        newField.grid[i] = v1 * v2.grid[i];
    }
    return newField;
}

template <class field_type>
const field<field_type> operator*(const field<field_type>& v1, const float v2) {
    /**
    * Multiplies a scalar and vector field to give a vector field
    */
    return v2*v1;
}

template <class field_type>
const field<field_type> operator/(const field<field_type>& v1, float v2) {
    /**
    * Divides a vector by a scalar field to give a vector field
    */
    field<field_type> newField = field<field_type>(v1.w);
    for (int i = 0; i<newField.w->number_of_grid_nodes; i++){
        newField.grid[i] = v1.grid[i]/v2;
    }
    return newField;
}


template <class field_type>
const field<field_type> operator*(const field<field_type>& v1, field<field_type>& v2){
    /**
    * Multiplies a vector and scalar field to give a vector field
    */
    field<field_type> newField = field<field_type>(v1.w);
    for (int i = 0; i<newField.w->number_of_grid_nodes; i++){
        newField.grid[i] = v1.grid[i]*v2.grid[i];
    }
    return newField;
}

template <class field_type>
const field<field_type> operator*(const field<field_type>& v1, const field<float>& v2){
    /**
    * Multiplies a vector and scalar field to give a vector field
    */
    field<field_type> newField = field<field_type>(v1.w);
    for (int i = 0; i<newField.w->number_of_grid_nodes; i++){
        newField.grid[i] = v1.grid[i]*v2.grid[i];
    }
    return newField;
}

template <class field_type>
const field<field_type> operator*(const field<float>& v1, const field<field_type>& v2){
    /**
    * Multiplies a scalar and vector field to give a vector field
    */
    return v2*v1;
}

template <class field_type>
const field<field_type> operator/(const field<field_type>& v1, const field<float>& v2) {
    /**
    * Divides a vector by a scalar field to give a vector field
    */
    field<field_type> newField = field<field_type>(v1.w);
    for (int i = 0; i<newField.w->number_of_grid_nodes; i++){
        newField.grid[i] = v1.grid[i]/v2.grid[i];
    }
    return newField;
}



#endif //SCHRODINGER_SMOKE_FIELD_H
