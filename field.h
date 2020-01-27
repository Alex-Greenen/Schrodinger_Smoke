//
// Created by Alex Greenen on 12/15/19.
//

#ifndef SCHRODINGER_SMOKE_FIELD_H
#define SCHRODINGER_SMOKE_FIELD_H

#include <vector>
#include <cmath>
#include "world.h"
#include "iostream"

using namespace std;

template <class field_type>
class field {
public:
    field() = default;
    field(world* _w): w(_w){
        for (int i =0; i< w->number_of_grid_nodes; i++){
            grid.push_back(field_type());
        }
    }
    field(world* _w, field_type value): w(_w){
        for (int i =0; i< w->number_of_grid_nodes; i++){
            grid.push_back(value);
        }
    }

    vector<field_type> grid;
    world* w;

    void updateGridValue(int x, int y, int z, field_type value);
    field_type getGridValue(int x, int y, int z) const;

    friend ostream& operator<<(ostream& os, const field<field_type>& field1) {
        os << "[\n";
        for(int i=0; i < field1.grid.size(); ++i){
            std::cout << "     " << field1.w->convert_index_to_gridCoordintates(i) << ": ";
            std::cout << field1.grid[i] << ", \n";
        }
        std::cout << "     Last: ";
        std::cout << field1.grid[-1];
        os << "\n ]";
        return os;
    }
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

    //These three lines center apply fourier boundary to the grid
    x = (x + w->grid_marks[0]) % w->grid_marks[0];
    y = (y + w->grid_marks[1]) % w->grid_marks[1];
    z = (z + w->grid_marks[2]) % w->grid_marks[2];

    grid[z*w->grid_marks[0]*w->grid_marks[1] + y*w->grid_marks[0] + x] = value;
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

    //These three lines center apply fourier boundary to the grid
    x = (x + w->grid_marks[0]) % w->grid_marks[0];
    y = (y + w->grid_marks[1]) % w->grid_marks[1];
    z = (z + w->grid_marks[2]) % w->grid_marks[2];

    return grid[z*w->grid_marks[0]*w->grid_marks[1] + y*w->grid_marks[0] + x];
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
const field<field_type> operator*(const float val, const field<field_type>& v2) {
    /**
    * Multiplies a scalar and vector field to give a vector field
    */
    field<field_type> newField = field<field_type>(v2.w);
    for (int i = 0; i<newField.w->number_of_grid_nodes; i++){
        newField.grid[i] = val * v2.grid[i];
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
const field<field_type> operator/(const field<field_type>& v1, float val) {
    /**
    * Divides a vector by a scalar field to give a vector field
    */
    field<field_type> newField = field<field_type>(v1.w);
    for (int i = 0; i<newField.w->number_of_grid_nodes; i++){
        newField.grid[i] = v1.grid[i]/val;
    }
    return newField;
}


template <class field_type>
const field<field_type> operator*(const field<field_type>& v1, const field<field_type>& v2){
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


const field<float> operator*(const field<float>& v1, const field<float>& v2){
    /**
    * Multiplies a scalar and vector field to give a vector field
    */
    field<float> newField = field<float>(v1.w);
    for (int i = 0; i<newField.w->number_of_grid_nodes; i++){
        newField.grid[i] = v1.grid[i]*v2.grid[i];
    }
    return newField;
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
