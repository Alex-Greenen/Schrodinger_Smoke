//
// Created by Alex Greenen on 12/15/19.
//

#ifndef SCHRODINGER_SMOKE_ISF_H
#define SCHRODINGER_SMOKE_ISF_H

#include "wavefunction.h"
#include "math_util.h"
#include "field.h"
#include "vector3D.h"

class isf {
public:
    isf() = default;

    field<vector3D> velocity_field();
    void pressure_project();
    void time_evolve();
    void normalise();


    wavefunction* wf1;
    wavefunction* wf2;
    float dt;
    float hbar;
    float grid_size[];
};

field<vector3D> isf::velocity_field(){
    return (wf1->momentum_field()+wf2->momentum_field())/(wf1->density_field(), wf2->density_field());
}


void isf::pressure_project(){
    field<vector3D> v = velocity_field();
    field<float> d = divergence(&v);
    field<float> phase = solve_poisson();
}

void isf::time_evolve(){
    wf1->time_evolve();
    wf2->time_evolve();
}



#endif //SCHRODINGER_SMOKE_ISF_H
