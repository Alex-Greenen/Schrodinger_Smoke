//
// Created by Alex Greenen on 12/15/19.
//

#ifndef SCHRODINGER_SMOKE_WAVEFUNCTION_H
#define SCHRODINGER_SMOKE_WAVEFUNCTION_H

#include <stdexcept>
#include "field.h"
#include "vector3D.h"

class wavefunction {
public:
    wavefunction(){}
    wavefunction(field<float>* initial_real, field<float>* initial_imaginary, field<float>* _potential, double _hbar, double _dt):
            real(initial_real), imaginary(initial_imaginary), potential(_potential),hbar(_hbar), dt(_dt){}

    field<float>* real;
    field<float>* imaginary;
    field<float>* potential;
    double hbar;
    double dt;

    field<vector3D> divergence(char ri);
    field<float> laplacian(char ri);

    void time_evolve();
    void apply_phase(float phase_angle);

    field<vector3D> velocity_field();
    field<float> density_field();

};

field<vector3D> wavefunction::divergence(char ri){
    /**
    * Converts grid coordinates to world coordinates
    *
    * @param ri Tells which part to use: 'r' for real part, 'i' for imaginary
    * @param pos Indicated grid location to study
    * @return Laplacian or reel/imaginary part at grid point (x,y,z)
    */
    field<float>* grid_ref;
    if (ri == 'r') {
        grid_ref = real;
    } else if(ri == 'i') {
        grid_ref = imaginary;
    } else {
        throw std::invalid_argument("Neither Real not Imaginary");
    }

    field<vector3D> temp_vect_field = field<vector3D>();

    for (int x=1; x<grid_ref->grid_marks[0]-1; x++){
        for (int y=1; y<grid_ref->->grid_marks[1]; x++){
            for (int z=1; z<grid_ref->->grid_marks[2]; x++){
                float xdiv = (grid_ref->getGridValue(x+1, y, z) - grid_ref->getGridValue(x-1, y, z)/grid_ref->resolution;
                float ydiv = (grid_ref->getGridValue(x+1, y, z) - grid_ref->getGridValue(x-1, y, z)/grid_ref->resolution;
                float zdiv = (grid_ref->getGridValue(x+1, y, z) - grid_ref->getGridValue(x-1, y, z)/grid_ref->resolution;
                temp_vect_field.updateGridValue(x,y,z,vector3D(xdiv,ydiv,zdiv));
            }
        }
    }
    return temp_vect_field;
}


field<float> wavefunction::laplacian(char ri){
    /**
    * Converts grid coordinates to world coordinates
    *
    * @param ri Tells which part to use: 'r' for real part, 'i' for imaginary
    * @param pos Indicated grid location to study
    * @return Laplacian or reel/imaginary part at grid point (x,y,z)
    */
    field<float>* grid_ref;
    if (ri == 'r') {
        grid_ref = real;
    } else if(ri == 'i') {
        grid_ref = imaginary;
    } else {
        throw std::invalid_argument("Neither Real not Imaginary");
    }

    field<float> temp_float_field = field<float>();

    for (int x=1; x<grid_ref->grid_marks[0]-1; x++){
        for (int y=1; y<grid_ref->->grid_marks[1]; x++){
            for (int z=1; z<grid_ref->->grid_marks[2]; x++){
                float laplacian = 0.0;
                laplacian += grid_ref->getGridValue(x+1, y, z)
                             + grid_ref->getGridValue(x-1, y, z)
                             + grid_ref->getGridValue(x, y+1, z)
                             + grid_ref->getGridValue(x, y-1, z)
                             + grid_ref->getGridValue(x, y, z+1)
                             + grid_ref->getGridValue(x, y, z-1)
                             - 6* grid_ref->getGridValue(x, y, z);
                laplacian /= (grid_ref->resolution)*(grid_ref->resolution);
                temp_float_field.updateGridValue(x,y,z,laplacian);
            }
        }
    }
    return temp_float_field;
}


field<vector3D> wavefunction::velocity_field(){
    field<vector3D> temp = divergence('i') * *real + *imaginary * divergence('r');
    return temp;
}

void wavefunction::time_evolve(){
    /**
    * Evolves the wavefunction using the half-step formula.
   */

    // At t += dt/2, evolve R
    for(int x = 0; x < real->grid_marks[0]; x++){
        for(int y = 0; y < real->grid_marks[1]; y++){
            for(int z = 0; z < real->grid_marks[2]; z++){
                double value = real->getGridValue(x,y,z) +dt * ((-hbar*hbar/2)*laplacian('i',x,y,z) + potential->getGridValue(x,y,z)*imaginary->getGridValue(x,y,z));
                real->updateGridValue(x,y,z, value);
            }
        }
    }

    // At t += dt, evolve I
    for(int x = 0; x < real->grid_marks[0]; x++){
        for(int y = 0; y < real->grid_marks[1]; y++){
            for(int z = 0; z < real->grid_marks[2]; z++){
                double value = imaginary->getGridValue(x,y,z) - dt * ((-hbar*hbar/2)*laplacian('r',x,y,z) + potential->getGridValue(x,y,z)*real->getGridValue(x,y,z));
                imaginary->updateGridValue(x,y,z, value);
            }
        }
    }
}

#endif //SCHRODINGER_SMOKE_WAVEFUNCTION_H
