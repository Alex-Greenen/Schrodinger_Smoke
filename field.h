//
// Created by Alex Greenen on 12/15/19.
//

#ifndef SCHRODINGER_SMOKE_FIELD_H
#define SCHRODINGER_SMOKE_FIELD_H

#include <array>
#include <cmath>
#include "world.h"

using namespace std;

template <class field_type>
class field: public world {
public:
    field() = default;
    field(float x_size, float y_size, float z_size, float res): world(x_size, y_size, z_size, res){
        grid = new field_type[number_of_grid_nodes]();
    }
    field(float x_size, float y_size, float z_size, float res, field_type value): world(x_size, y_size, z_size, res){
        grid = new field_type[number_of_grid_nodes]();
        for (int i =0; i< number_of_grid_nodes; i++){
            grid[i] = value;
        }
    }

    field_type* grid;

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
    x = (x % grid_marks[0] + grid_marks[0]) % grid_marks[0];
    y = (y % grid_marks[1] + grid_marks[1]) % grid_marks[1];
    z = (y % grid_marks[2] + grid_marks[2]) % grid_marks[2];

    grid[x*grid_marks[1]*grid_marks[2] + y*grid_marks[1] + z] = value;
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
    x = (x % grid_marks[0] + grid_marks[0]) % grid_marks[0];
    y = (y % grid_marks[1] + grid_marks[1]) % grid_marks[1];
    z = (y % grid_marks[2] + grid_marks[2]) % grid_marks[2];

    return grid[x*grid_marks[1]*grid_marks[2] + y*grid_marks[1] + z];
}

template <class field_type>
const field<field_type> operator+(const field<field_type>& v1, const field<field_type>& v2){
    /**
    * Adds two vector fields to give a vector field
    */
    field<field_type> newField = field<field_type>(v1.grid_size[0], v1.grid_size[1], v1.grid_size[2], v1.resolution);
    for (int i = 0; i<newField.number_of_grid_nodes; i++){
        newField.grid[i] = v1.grid[i]+ v2.grid[i];
    }
    return newField;
}

template <class field_type>
const field<field_type> operator-(const field<field_type>& v1, const field<field_type>& v2){
    /**
    * Substracts two vector fields to give a vector field
    */
    field<field_type> newField = field<field_type>(v1.grid_size[0], v1.grid_size[1], v1.grid_size[2], v1.resolution);
    for (int i = 0; i<newField.number_of_grid_nodes; i++){
        newField.grid[i] = v1.grid[i] - v2.grid[i];
    }
    return newField;
}

template <class field_type>
const field<field_type> operator*(const field<field_type>& v1, field<field_type>& v2){
    /**
    * Multiplies a vector and scalar field to give a vector field
    */
    field<field_type> newField = field<field_type>(v1.grid_size[0], v1.grid_size[1], v1.grid_size[2], v1.resolution);
    for (int i = 0; i<newField.number_of_grid_nodes; i++){
        newField.grid[i] = v1.grid[i]*v2.grid[i];
    }
    return newField;
}

template <class field_type>
const field<field_type> operator*(const field<field_type>& v1, const field<float>& v2){
    /**
    * Multiplies a vector and scalar field to give a vector field
    */
    field<field_type> newField = field<field_type>(v1.grid_size[0], v1.grid_size[1], v1.grid_size[2], v1.resolution);
    for (int i = 0; i<newField.number_of_grid_nodes; i++){
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

const field<float> operator*(const field<float>& v1, const field<float>& v2){
    /**
    * Multiplies a scalar and vector field to give a vector field
    */
    field<float> newField = field<float>(v1.grid_size[0], v1.grid_size[1], v1.grid_size[2], v1.resolution);
    for (int i = 0; i<newField.number_of_grid_nodes; i++){
        newField.grid[i] = v1.grid[i]*v2.grid[i];
    }
    return newField;
}

template <class field_type>
const field<field_type> operator*(const float v1, const field<field_type>& v2) {
    /**
    * Multiplies a scalar and vector field to give a vector field
    */
    field<field_type> newField = field<field_type>(v2.grid_size[0], v2.grid_size[1], v2.grid_size[2], v2.resolution);
    for (int i = 0; i<newField.number_of_grid_nodes; i++){
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
const field<field_type> operator/(const field<field_type>& v1, const field<float>& v2) {
    /**
    * Divides a vector by a scalar field to give a vector field
    */
    field<field_type> newField = field<field_type>(v1.grid_size[0], v1.grid_size[1], v1.grid_size[2], v1.resolution);
    for (int i = 0; i<newField.number_of_grid_nodes; i++){
        newField.grid[i] = v1.grid[i]/v2.grid[i];
    }
    return newField;
}

template <class field_type>
const field<field_type> operator/(const field<field_type>& v1, float v2) {
    /**
    * Divides a vector by a scalar field to give a vector field
    */
    field<field_type> newField = field<field_type>(v1.grid_size[0], v1.grid_size[1], v1.grid_size[2], v1.resolution);
    for (int i = 0; i<newField.number_of_grid_nodes; i++){
        newField.grid[i] = v1.grid[i]/v2;
    }
    return newField;
}




#endif //SCHRODINGER_SMOKE_FIELD_H
