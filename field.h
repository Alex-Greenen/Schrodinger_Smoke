//
// Created by Alex Greenen on 12/15/19.
//

#ifndef SCHRODINGER_SMOKE_FIELD_H
#define SCHRODINGER_SMOKE_FIELD_H


#include "vector3D.h"
#include <array>

using namespace std;

template <class field_type>
class field {
public:
    field(){}
    field(float x_size, float y_size, float z_size, float res){
        grid_size = {x_size, y_size, z_size};
        resolution = res;
        grid_marks = {int(x_size*res), int(y_size*res), int(z_size*res)};
        number_of_grid_nodes = grid_marks[0]*grid_marks[1]*grid_marks[2];
        grid = new field_type[number_of_grid_nodes];
    }

    double* convert_to_real_coordinates(int x, int y, int z);
    void updateGridValue(int x, int y, int z, field_type value);
    field_type getGridValue(int x, int y, int z);

    float grid_size[];
    int grid_marks[];
    int number_of_grid_nodes;
    float resolution;
    field_type* grid;

};

double* field::convert_to_real_coordinates(int x, int y, int z){
    /**
    * Converts grid coordinates to world coordinates
    *
    * @param x X grid point
    * @param y Y grid point
    * @param z Z grid point
    * @return Array of (x,y,z) world coordinates
    */
    double returner[] = {resolution*x, resolution*y, resolution*z};
    return returner;
}

template <class field_type>
void field::updateGridValue(int x, int y, int z, field_type value){
    /**
     * Updates the value of the grid at a given point
     *
     * @param x X grid point
     * @param y Y grid point
     * @param z Z grid point
     * @param value Value to be stored at grid point
     */
    grid[x*grid_marks[1]*grid_marks[2] + y*grid_marks[1] + z] = value;
}

template <class field_type>
const field_type field::getGridValue(int x, int y, int z){
    /**
     * Returns the value of the grid at a given point
     *
     * @param x X grid point
     * @param y Y grid point
     * @param z Z grid point
     * @return Value at grid point
     */
    return grid[x*grid_marks[1]*grid_marks[2] + y*grid_marks[1] + z];
}

const field<vector3D> operator+(const field<vector3D> *v1, const field<vector3D> *v2){
    /**
    * Adds two vector fields to give a vector field
    */
    field<vector3D> newField = field<vector3D>(v1->grid_size[0], v1->grid_size[1], v1->grid_size[2], v1->resolution);
    for (int i = 0; i<newField.number_of_grid_nodes; i++){
        newField.grid[i] = v1->grid[i]+ v2->grid[i];
    }
    return newField;
}

const field<vector3D> operator-(const field<vector3D> *v1, const field<vector3D> *v2){
    /**
    * Substracts two vector fields to give a vector field
    */
    field<vector3D> newField = field<vector3D>(v1->grid_size[0], v1->grid_size[1], v1->grid_size[2], v1->resolution);
    for (int i = 0; i<newField.number_of_grid_nodes; i++){
        newField.grid[i] = v1->grid[i] - v2->grid[i];
    }
    return newField;
}

const field<vector3D> operator*(const field<vector3D> *v1, const field<float> *v2){
    /**
    * Multiplies a vector and scalar field to give a vector field
    */
    field<vector3D> newField = field<vector3D>(v1->grid_size[0], v1->grid_size[1], v1->grid_size[2], v1->resolution);
    for (int i = 0; i<newField.number_of_grid_nodes; i++){
        newField.grid[i] = v1->grid[i]*v2->grid[i];
    }
    return newField;
}

const field<vector3D> operator*(const field<float> *v1, const field<vector3D> *v2){
    /**
    * Multiplies a scalar and vector field to give a vector field
    */
    field<vector3D> newField = field<vector3D>(v1->grid_size[0], v1->grid_size[1], v1->grid_size[2], v1->resolution);
    for (int i = 0; i<newField.number_of_grid_nodes; i++){
        newField.grid[i] = v1->grid[i]*v2->grid[i];
    }
    return newField;
}

const field<vector3D> operator/(const field<vector3D> *v1, const field<float> *v2){
    /**
    * Divides a vector by a scalar field to give a vector field
    */
    field<vector3D> newField = field<vector3D>(v1->grid_size[0], v1->grid_size[1], v1->grid_size[2], v1->resolution);
    for (int i = 0; i<newField.number_of_grid_nodes; i++){
        newField.grid[i] = v1->grid[i]/v2->grid[i];
    }
    return newField;
}

const field<float> operator+(const field<float> *v1, const field<float> *v2){
    /**
    * Adds two scalar fields to give a scalar field
    */
    field<float> newField = field<float>(v1->grid_size[0], v1->grid_size[1], v1->grid_size[2], v1->resolution);
    for (int i = 0; i<newField.number_of_grid_nodes; i++){
        newField.grid[i] = v1->grid[i]+v2->grid[i];
    }
    return newField;
}

const field<float> operator*(const field<float> *v1, const field<float> *v2){
    /**
    * Multiplies two scalar fields to give a scalar field
    */
    field<float> newField = field<float>(v1->grid_size[0], v1->grid_size[1], v1->grid_size[2], v1->resolution);
    for (int i = 0; i<newField.number_of_grid_nodes; i++){
        newField.grid[i] = v1->grid[i]*v2->grid[i];
    }
    return newField;
}

const field<float> operator-(const field<float> *v1, const field<float> *v2){
    /**
    * Substracts two scalar fields to give a scalar field
    */
    field<float> newField = field<float>(v1->grid_size[0], v1->grid_size[1], v1->grid_size[2], v1->resolution);
    for (int i = 0; i<newField.number_of_grid_nodes; i++){
        newField.grid[i] = v1->grid[i]-v2->grid[i];
    }
    return newField;
}

const field<float> operator/(const field<float> *v1, const field<float> *v2){
    /**
    * Divides two scalar fields to give a scalar field
    */
    field<float> newField = field<float>(v1->grid_size[0], v1->grid_size[1], v1->grid_size[2], v1->resolution);
    for (int i = 0; i<newField.number_of_grid_nodes; i++){
        newField.grid[i] = (v1->grid[i])/(v2->grid[i]);
    }
    return newField;
}

#endif //SCHRODINGER_SMOKE_FIELD_H
