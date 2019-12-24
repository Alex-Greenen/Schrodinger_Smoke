//
// Created by Alex Greenen on 12/15/19.
//

#ifndef SCHRODINGER_SMOKE_WAVEFUNCTION_H
#define SCHRODINGER_SMOKE_WAVEFUNCTION_H

#include <stdexcept>
#include <cmath>
#include "math_util.h"
#include "field.h"
#include "vector3D.h"
#include "world.h"

class wavefunction: public world {
public:
    wavefunction()= default;

    wavefunction(float x_size, float y_size, float z_size, float res, double _hbar, double _dt, float real_value = 1.0):
            world(x_size, y_size, z_size, res), hbar(_hbar), dt(_dt){
        real = field<float>(x_size, y_size, z_size, res, real_value);
        imaginary = field<float>(x_size, y_size, z_size, res, 0);
        potential = field<float>(x_size, y_size, z_size, res, 0);
    }

    field<float> real;
    field<float> imaginary;
    field<float> potential;
    double hbar;
    double dt;

    void time_evolve();
    void apply_phase(field<float> *phase_angle);
    field<vector3D> velocity_field();
    field<vector3D> momentum_field();
    field<float> density_field();

};

void wavefunction::apply_phase(field<float> *phase_angle){
    field<float> cos_angle = cos(phase_angle);
    field<float> sin_angle = sin(phase_angle);
    real = real * cos_angle - imaginary * sin_angle;
    imaginary = real * sin_angle + imaginary * cos_angle;
}

void wavefunction::time_evolve(){
    /**
    * Evolves the wavefunction using the half-step formula.
   */

    // At t += dt/2, evolve R

    real = real + dt * ((-hbar*hbar/2)*laplacian(&imaginary) + potential * imaginary);

    imaginary = imaginary - dt * ((-hbar*hbar/2)*laplacian(&real) + potential * real);

}

field<vector3D> wavefunction::momentum_field(){
    field<vector3D> temp = hbar *(gradient(&imaginary) * real - imaginary * gradient(&real));
    return temp;
}


field<float> wavefunction::density_field(){
    field<float> temp = real*real + imaginary*imaginary;
    return temp;
}

field<vector3D> wavefunction::velocity_field(){
    return momentum_field()/density_field();;
}



#endif //SCHRODINGER_SMOKE_WAVEFUNCTION_H
