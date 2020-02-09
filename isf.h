//
// Created by Alex Greenen on 12/15/19.
//

#ifndef SCHRODINGER_SMOKE_ISF_H
#define SCHRODINGER_SMOKE_ISF_H

#include "wavefunction.h"
#include "math_util.h"
#include "field.h"
#include "vector3D.h"
#include "world.h"

class isf {
public:
    isf() = default;
    isf(world* _w , float _dt, float _hbar): w(_w), dt(_dt), hbar(_hbar) {
        wf1 = wavefunction(w, dt, hbar, 0.9486832);
        wf2 = wavefunction(w, dt, hbar, 0.3162277);
    }


    float dt;
    float hbar;
    wavefunction wf1;
    wavefunction wf2;
    world* w;

    field<vector3D> velocity_field();
    field<float> density_field();
    void time_evolve();
    void pressure_project();
    void normalise();
    void apply_velocity_induction(field<vector3D>* velocity_field);
    void set_velocity_induction(field<vector3D>* velocity_field);
    void vortex_ring(vector3D center, vector3D normal, float radius, float width);
};

void isf::pressure_project(){
    field<vector3D> v = this->velocity_field();
    field<float> d = divergence(&v);
    field<float> phase = (-1/hbar) * solve_poisson(&d) ;
    wf1.apply_phase(&phase);
    wf2.apply_phase(&phase);
}

void isf::time_evolve(){
    wf1.time_evolve();
    wf2.time_evolve();
}

void isf::normalise() {
    field<float> density = wf1.density_field()+ wf2.density_field();
    density = apply_element_wise(&density, sqrt);
    wf1.real = wf1.real/density;
    wf1.imaginary = wf1.imaginary/density;
    wf2.real = wf2.real/density;
    wf2.imaginary = wf2.imaginary/density;
}

field<float> isf::density_field() {
    field<float> density = wf1.density_field()+ wf2.density_field();
    return density;
}


field<vector3D> isf::velocity_field(){
    return (wf1.momentum_field()+wf2.momentum_field())/(wf1.density_field() + wf2.density_field());
}

void isf::apply_velocity_induction(field<vector3D>* velocity_field){
    field<float> phase_field = field<float>(w);
    for (int x = 0; x< w->grid_marks[0]; x++){
        for (int y = 0; y< w->grid_marks[1]; y++){
            for (int z = 0; z< w->grid_marks[2]; z++){
                vector3D velocity = velocity_field->getGridValue(x,y,z);
                vector3D position = w->convert_to_worldCoordintates(x,y,z);
                float phase = velocity*position/hbar ;
                phase_field.updateGridValue(x,y,z, phase);
            }
        }
    }
    wf1.apply_phase(&phase_field);
    wf2.apply_phase(&phase_field);
}

void isf::set_velocity_induction(field<vector3D>* velocity_field){
    field<float> phase_field = field<float>(w);
    for (int x = 0; x < w->grid_marks[0]; x++){
        for (int y = 0; y < w->grid_marks[1]; y++){
            for (int z = 0; z < w->grid_marks[2]; z++){
                vector3D velocity = velocity_field->getGridValue(x,y,z);
                vector3D position = w->convert_to_worldCoordintates(x,y,z);
                float phase = velocity*position/hbar;
                phase_field.updateGridValue(x,y,z, phase);
            }
        }
    }
    field<float> wf1density = wf1.density_field();
    wf1.real = cos(&phase_field) * apply_element_wise(&wf1density, sqrt);
    wf1.imaginary = sin(&phase_field) * apply_element_wise(&wf1density, sqrt);

    field<float> wf2density = wf2.density_field();
    wf2.real = cos(&phase_field) * apply_element_wise(&wf2density,sqrt);
    wf2.imaginary = sin(&phase_field) * apply_element_wise(&wf2density, sqrt);
}



void isf::vortex_ring(vector3D center, vector3D normal, float radius, float width){
    field<vector3D> velocity_field = field<vector3D>(w);
    normal.normalise();
    for (int x = 0; x<w->grid_marks[0]; x++) {
        for (int y = 0 ; y<w->grid_marks[1]; y++) {
            for (int z = 0; z<w->grid_marks[2] ; z++) {
                vector3D rp = w->convert_to_worldCoordintates(x,y,z) - center;
                float zc = rp*normal;
                float dd = sqrt(rp*rp - zc*zc);
                float l = dd-radius;
                float d = sqrt(l*l + zc*zc);
                if (d< width){
                    vector3D v = (zc * (rp-zc*normal) / (rp-zc*normal).norm() - l * normal) /(l*l + zc*zc);
                    velocity_field.updateGridValue(x,y,z, v);
                }
            }
        }
    }
    apply_velocity_induction(&velocity_field);
}

#endif //SCHRODINGER_SMOKE_ISF_H
