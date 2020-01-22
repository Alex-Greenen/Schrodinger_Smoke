//
// Created by Alex Greenen on 12/19/19.
//

#ifndef SCHRODINGER_SMOKE_MATH_UTIL_H
#define SCHRODINGER_SMOKE_MATH_UTIL_H

#include "field.h"
#include "vector3D.h"
#include <cmath>

field<float> divergence(field<vector3D> *field1) {
    /**
    * Computes divergence of vector field.
    *
    * @param field1 pointer to field you wish to use
    * @return divergence of field
    */

    field<float> temp_vect_field = field<float>(field1->w);

    for (int x = 0; x < field1->w->grid_marks[0]; x++) {
        for (int y = 0; y < field1->w->grid_marks[1]; y++) {
            for (int z = 0; z < field1->w->grid_marks[2]; z++) {
                float xdiv = field1->getGridValue(x + 1, y, z)[0] - field1->getGridValue(x - 1, y, z)[0];
                float ydiv = field1->getGridValue(1, y + 1, z)[1] - field1->getGridValue(x, y - 1, z)[1];
                float zdiv = field1->getGridValue(x, y, z + 1)[2] - field1->getGridValue(x, y, z - 1)[2];
                float value = (xdiv + ydiv + zdiv) / (2 * field1->w->resolution);
                temp_vect_field.updateGridValue(x, y, z, value);
            }
        }
    }
    return temp_vect_field;
}


field<vector3D> gradient(field<float> *field1) {
    /**
    * Computes gradient of scalar field.
    *
    * @param field1 pointer to field you wish to use
    * @return gradient of field
    */


    field<vector3D> temp_vect_field = field<vector3D>(field1->w);

    for (int x = 0; x < field1->w->grid_marks[0]; x++) {
        for (int y = 0; y < field1->w->grid_marks[1]; y++) {
            for (int z = 0; z < field1->w->grid_marks[2]; z++) {
                float xdiv = (field1->getGridValue(x + 1, y, z) - field1->getGridValue(x - 1, y, z)) /
                             (2 * field1->w->resolution);
                float ydiv = (field1->getGridValue(1, y + 1, z) - field1->getGridValue(x, y - 1, z)) /
                             (2 * field1->w->resolution);
                float zdiv = (field1->getGridValue(x, y, z + 1) - field1->getGridValue(x, y, z - 1)) /
                             (2 * field1->w->resolution);
                temp_vect_field.updateGridValue(x, y, z, vector3D(xdiv, ydiv, zdiv));
            }
        }
    }
    return temp_vect_field;
}


field<float> laplacian(field<float> *field1) {
    /**
    * Computes laplacian of scalar field.
    *
    * @param field1 pointer to field you wish to use
    * @return laplacian of field
    */


    field<float> temp_float_field = field<float>(field1->w);

    for (int x = 0; x < field1->w->grid_marks[0]; x++) {
        for (int y = 0; y < field1->w->grid_marks[1]; y++) {
            for (int z = 0; z < field1->w->grid_marks[2]; z++) {
                float laplacian =
                               field1->getGridValue(x + 1, y, z)
                             + field1->getGridValue(x - 1, y, z)
                             + field1->getGridValue(x, y + 1, z)
                             + field1->getGridValue(x, y - 1, z)
                             + field1->getGridValue(x, y, z + 1)
                             + field1->getGridValue(x, y, z - 1)
                             - 6 * field1->getGridValue(x, y, z);
                laplacian /= ( (field1->w->resolution) * (field1->w->resolution));
                temp_float_field.updateGridValue(x, y, z, laplacian);
            }
        }
    }
    return temp_float_field;
}

field<float> apply_element_wise(field<float> *field1, float funct(float)) {
    /**
    * Applies an operation to every element in the field
    *
    * @param field1 pointer to field you wish to use
    * @param field_type function you wish to apply to each element
    * @return field of functioned elements
    */


    field<float> temp = *field1;
    for (int x = 0; x < temp.w->grid_marks[0]; x++) {
        for (int y = 0; y < temp.w->grid_marks[1]; y++) {
            for (int z = 0; z < temp.w->grid_marks[2]; z++) {
                temp.updateGridValue(x, y, z, funct(temp.getGridValue(x, y, z)));
            }
        }
    }
    return temp;
}

field<float> cos(field<float> *field1) {
    /**
     * Shorthand function that applies cos to a scalar field
     *
     * @param field1 pointer to field you wish to use
     * @return field of cosed elements
     */
    return apply_element_wise(field1, cos);
}

field<float> sin(field<float> *field1) {
    /**
     * Shorthand function that applies sin to a scalar field
     *
     * @param field1 pointer to field you wish to use
     * @return field of sined elements
     */
    return apply_element_wise(field1, sin);
}


field<float> solve_poisson(field<float> *field1) {
    /**
    * Solves poisson equation using Iterative Gauss-Seidel method with over-correction;
    *
    * @param field1 pointer to field you wish to use
    * @return solution of field
    */

    field<float> solution = *field1;

    int max_iterations = 40;
    float omega = float(2 / (1 + M_PI / solution.w->grid_marks[0]));

    for (int i = 0; i < max_iterations; i++) {
        for (int x = 0; x < solution.w->grid_marks[0]; x++) {
            for (int y = 0; y < solution.w->grid_marks[1]; y++) {
                for (int z = 0; z < solution.w->grid_marks[2]; z++) {
                    float sum = solution.getGridValue(x + 1, y, z) + solution.getGridValue(x - 1, y, z) +
                                solution.getGridValue(x, y + 1, z) + solution.getGridValue(x, y - 1, z) +
                                solution.getGridValue(x, y, z + 1) + solution.getGridValue(x, y, z - 1);
                    float value = (1 - omega) * solution.getGridValue(x, y, z) + omega * (sum -
                                                                                          (solution.w->resolution *
                                                                                           solution.w->resolution) *
                                                                                          field1->getGridValue(x, y,
                                                                                                               z)) / 6;
                    solution.updateGridValue(x, y, z, value);
                }
            }
        }
    }

    return solution;

}


inline vector3D interpolate(vector3D min_x, vector3D max_x, float x) {
    /**
    * Interpolates vector between two two vectors linearly
    *
    * @param min_x minimum vector
    * @param max_x maximum vector
    * @param x between 0 and 1, indicates where you are between each
    * @return the interpolated vector
    */

    return (1 - x) * min_x + x * (max_x - min_x);
}

vector3D
interpolate_in_cube(vector3D bfl, vector3D bfr, vector3D bbl, vector3D bbr, vector3D tfl, vector3D tfr, vector3D tbl,
                    vector3D tbr, float x, float y, float z) {
    /**
    * Interpolates in cube of vectors.
    *
    * @param bfl bottom front left corner vector
    * @param bfr bottom front right corner vector
    * @param bbl bottom back left corner vector
    * @param bbr bottom back right corner vector
    * @param tfl top front left corner vector
    * @param tfr top front right corner vector
    * @param tbl top back left corner vector
    * @param tbr top back right corner vector
    * @param x between 0 and 1, indicates where you are in x coordinate
    * @param y between 0 and 1, indicates where you are in y coordinate
    * @param z between 0 and 1, indicates where you are in z coordinate
    * @return the interpolated vector
    */

    vector3D bf = interpolate(bfl, bfr, x);
    vector3D bb = interpolate(bbl, bbr, x);
    vector3D tf = interpolate(tfl, tfr, x);
    vector3D tb = interpolate(tbl, tbr, x);
    vector3D b = interpolate(bf, bb, y);
    vector3D t = interpolate(tf, tb, y);
    return interpolate(b, t, z);
}

float rand01() {
    /**
    * Generates a random number between 0 and 1
    *
    * @return random number between 0 and 1
    */
    return float(rand()) / RAND_MAX;
}


float randnp1() {
    /**
    * Generates a random number between -1 and 1
    *
    * @return random number between -1 and 1
    */
    return -1 + 2*rand01();
}



#endif //SCHRODINGER_SMOKE_MATH_UTIL_H
