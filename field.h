//
// Created by Alex Greenen on 12/15/19.
//

#ifndef SCHRODINGER_SMOKE_FIELD_H
#define SCHRODINGER_SMOKE_FIELD_H

#include <array>
#include "vector3D.h"

using namespace std;

template <class field_type>
class field {
public:
    field() = default;
    field(float x_size, float y_size, float z_size, float res){
        grid_size = {x_size, y_size, z_size};
        resolution = res;
        grid_marks = {int(x_size*res), int(y_size*res), int(z_size*res)};
        number_of_grid_nodes = grid_marks[0]*grid_marks[1]*grid_marks[2];
        grid = new field_type[number_of_grid_nodes];
    }

    array<float,3> grid_size;
    array<int,3> grid_marks;
    int number_of_grid_nodes;
    float resolution;
    field_type* grid;

    array<double, 3> convert_to_real_coordinates(int x, int y, int z) const;
    void updateGridValue(int x, int y, int z, field_type value);
    field_type getGridValue(int x, int y, int z) const;
};

template <class field_type>
array<double, 3> field<field_type>::convert_to_real_coordinates(int x, int y, int z) const {
    /**
    * Converts grid coordinates to world coordinates. Wrap around boundary if needed.
    *
    * @param x X grid point
    * @param y Y grid point
    * @param z Z grid point
    * @return Array of (x,y,z) world coordinates
    */
    x = (x % grid_marks[0] + grid_marks[0]) % grid_marks[0];
    y = (y % grid_marks[1] + grid_marks[1]) % grid_marks[1];
    z = (y % grid_marks[2] + grid_marks[2]) % grid_marks[2];

    return {resolution*x, resolution*y, resolution*z};
}

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
const field<field_type> operator*(const float v1, const field<field_type>& v2){
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
const field<field_type> operator*(const field<field_type>& v1, const float v2){
    /**
    * Multiplies a scalar and vector field to give a vector field
    */
    return v2*v1;
}

template <class field_type>
const field<field_type> operator/(const field<field_type>& v1, const field<float>& v2){
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
const field<field_type> operator/(const field<field_type>& v1, float v2){
    /**
    * Divides a vector by a scalar field to give a vector field
    */
    field<field_type> newField = field<field_type>(v1.grid_size[0], v1.grid_size[1], v1.grid_size[2], v1.resolution);
    for (int i = 0; i<newField.number_of_grid_nodes; i++){
        newField.grid[i] = v1.grid[i]/v2;
    }
    return newField;
}



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




#endif //SCHRODINGER_SMOKE_FIELD_H
