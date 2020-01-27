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
        wf1 = wavefunction(w, dt, hbar, 0.9);
        wf2 = wavefunction(w, dt, hbar, 0.1);
    }


    float dt;
    float hbar;
    wavefunction wf1;
    wavefunction wf2;
    world* w;

    field<vector3D> velocity_field();
    void time_evolve();
    void pressure_project();
    void normalise();
    void apply_velocity_induction(field<vector3D>* velocity_field);
    void set_velocity_induction(field<vector3D>* velocity_field);
    void vortex_ring(vector3D center, vector3D normal, float radius, float strength);
    void apply_vorticity_induction(vector3D point, vector3D tangent, float crit_dist, float strength);
    void post_setup();
};

void isf::pressure_project(){
    field<vector3D> v = velocity_field();
    field<float> d = divergence(&v);
    field<float> phase = solve_poisson(&d)/hbar ;
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

void isf::post_setup(){
    pressure_project();
    normalise();
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
                float phase = (velocity[0]*x + velocity[1]*y + velocity[2]*z)/hbar ;
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
                float phase = (velocity[0]*x + velocity[1]*y + velocity[2]*z)/hbar ;
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



void isf::vortex_ring(vector3D center, vector3D normal, float radius, float strength){
    //This function is not yet written
    normal.normalise();
    for (int x=0; x<w->grid_marks[0]; x++){
        for (int y=0; y<w->grid_marks[1]; y++){
            for (int z=0; z<w->grid_marks[2]; z++){
                vector3D relative_position = vector3D(x-center[0],y-center[1],z-center[2]);
                float a = dot(relative_position, relative_position) - radius*radius;
                float b = 2 * dot(relative_position, normal);
                wf1.real.updateGridValue(x, y, z, a*wf1.real.getGridValue(x,y,z) -b*wf1.imaginary.getGridValue(x,y,z));
                wf1.imaginary.updateGridValue(x, y, z, b*wf1.real.getGridValue(x,y,z) +a*wf1.imaginary.getGridValue(x,y,z));
            }
        }
    }
}

void isf::apply_vorticity_induction(vector3D point, vector3D tangent, float crit_dist, float strength){
    //This function is not yet written
}

#endif //SCHRODINGER_SMOKE_ISF_H
