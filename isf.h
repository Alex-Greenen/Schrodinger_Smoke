//
// Created by Alex Greenen on 12/15/19.
//

#ifndef SCHRODINGER_SMOKE_ISF_H
#define SCHRODINGER_SMOKE_ISF_H

#include "wavefunction.h"
#include "field.h"

class isf {
public:
    isf(){}

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

void isf::time_evolve(){
    wf1->time_evolve();
    wf2->time_evolve();
}

void pressure_project(){
    
}


#endif //SCHRODINGER_SMOKE_ISF_H
