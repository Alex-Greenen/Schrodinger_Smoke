//
// Created by Alex Greenen on 2/4/20.
//



#ifndef SCHRODINGER_SMOKE_SET_UPS_H
#define SCHRODINGER_SMOKE_SET_UPS_H

#include "world.h"
#include "field.h"
#include "vector3D.h"
#include "wavefunction.h"
#include "isf.h"
#include "output_particle.h"
#include "output_field.h"

#include <iostream>
#include <vector>

void set_jet_velocity(isf& schr_flow){
    field<float> wf1density = schr_flow.wf1.density_field();
    wf1density = apply_element_wise(&wf1density, sqrt);
    field<float> wf2density = schr_flow.wf2.density_field();
    wf2density = apply_element_wise(&wf2density, sqrt);

    for (int x=0; x < schr_flow.w->grid_marks[0]; x++){
        for (int y = 0; y< schr_flow.w->grid_marks[1]; y++){
            float rsq = sqrt(square((float) x - ((float) schr_flow.w->grid_marks[0])/2) + square((float) y - (float) schr_flow.w->grid_marks[1]/2));
            if (rsq < ((float) schr_flow.w->grid_marks[0])/3){
                for (int z = 0; z < ((float) schr_flow.w->grid_marks[2])/2; z++) {
                    vector3D position = schr_flow.w->convert_to_worldCoordintates(x,y,z);
                    float phase = vector3D(0,0,0.3)*position/schr_flow.hbar;
                    schr_flow.wf1.real.updateGridValue(x,y,z, cos(phase) * wf1density.getGridValue(x,y,z));
                    schr_flow.wf1.imaginary.updateGridValue(x,y,z, sin(phase) * wf1density.getGridValue(x,y,z));

                    schr_flow.wf2.real.updateGridValue(x,y,z, cos(phase) * wf2density.getGridValue(x,y,z));
                    schr_flow.wf2.imaginary.updateGridValue(x,y,z, sin(phase) * wf2density.getGridValue(x,y,z));
                }
            }
        }
    }
}

void add_jet_particles(output_particle& buffer){
    for (int x = 0; x < buffer.w->grid_marks[0]; x++) {
        for (int y = 0; y < buffer.w->grid_marks[1]; y++) {
            float rsq = sqrt(square((float) x - ((float) buffer.w->grid_marks[0]) / 2) +
                             square((float) y - (float) buffer.w->grid_marks[1] / 2));
            if (rsq < ((float) buffer.w->grid_marks[0]) / 3) {
                buffer.create_particle(x * buffer.w->resolution, y * buffer.w->resolution, 3*buffer.w->resolution);
            }
        }
    }
}

void set_jet_velocity2(isf& schr_flow){
    vector3D velocity = vector3D(0,0,0.9);
    field<float> wf1density = schr_flow.wf1.density_field();
    wf1density = apply_element_wise(&wf1density, sqrt);
    field<float> wf2density = schr_flow.wf2.density_field();
    wf2density = apply_element_wise(&wf2density, sqrt);

    for (int x=0; x < schr_flow.w->grid_marks[0]; x++){
        for (int y = 0; y< schr_flow.w->grid_marks[1]; y++){
            float rsq = sqrt(square((float) x - ((float) schr_flow.w->grid_marks[0])/2) + square((float) y - (float) schr_flow.w->grid_marks[1]/2));
            if (rsq < ((float) schr_flow.w->grid_marks[0])/3){
                for (int z = 0; z < ((float) schr_flow.w->grid_marks[2])/4; z++) {
                    vector3D position = schr_flow.w->convert_to_worldCoordintates(x,y,z);
                    float phase = velocity*position/schr_flow.hbar;
                    schr_flow.wf1.real.updateGridValue(x,y,z, cos(phase) * wf1density.getGridValue(x,y,z));
                    schr_flow.wf1.imaginary.updateGridValue(x,y,z, sin(phase) * wf1density.getGridValue(x,y,z));

                    schr_flow.wf2.real.updateGridValue(x,y,z, cos(phase) * wf2density.getGridValue(x,y,z));
                    schr_flow.wf2.imaginary.updateGridValue(x,y,z, sin(phase) * wf2density.getGridValue(x,y,z));
                }
                for (int z = int(3*schr_flow.w->grid_marks[2]/4); z < schr_flow.w->grid_marks[2]; z++) {
                    vector3D position = schr_flow.w->convert_to_worldCoordintates(x,y,z);
                    float phase = -1*velocity*position/schr_flow.hbar;
                    schr_flow.wf1.real.updateGridValue(x,y,z, cos(phase) * wf1density.getGridValue(x,y,z));
                    schr_flow.wf1.imaginary.updateGridValue(x,y,z, sin(phase) * wf1density.getGridValue(x,y,z));

                    schr_flow.wf2.real.updateGridValue(x,y,z, cos(phase) * wf2density.getGridValue(x,y,z));
                    schr_flow.wf2.imaginary.updateGridValue(x,y,z, sin(phase) * wf2density.getGridValue(x,y,z));
                }
            }
        }
    }
}

void add_jet_particles2(output_particle& buffer){
    for (int x = 0; x < buffer.w->grid_marks[0]; x++) {
        for (int y = 0; y < buffer.w->grid_marks[1]; y++) {
            float rsq = sqrt(square((float) x - ((float) buffer.w->grid_marks[0]) / 2) +
                             square((float) y - (float) buffer.w->grid_marks[1] / 2));
            if (rsq < ((float) buffer.w->grid_marks[0]) / 3) {
                buffer.create_particle(x * buffer.w->resolution, y * buffer.w->resolution, 3*buffer.w->resolution);
                buffer.create_particle(x * buffer.w->resolution, y * buffer.w->resolution, buffer.w->grid_size[2]-3*buffer.w->resolution);
            }
        }
    }
}

void set_ring_velocity(isf& schr_flow){
    vector3D center = vector3D(1,1,1);
    float radius = 14*schr_flow.w->resolution;
    vector3D normal = vector3D(0,0,1);
    float width = 6*schr_flow.w->resolution;
    schr_flow.vortex_ring(center, normal, radius, width);
}

void add_ring_particles(output_particle& buffer){
    vector3D center = vector3D(1,1,1);
    float radius = 26*buffer.w->resolution;

    for (int x = 0; x < buffer.w->grid_marks[0]; x++) {
        for (int y = 0; y < buffer.w->grid_marks[1]; y++) {
            for (int z = 0; z < buffer.w->grid_marks[2]; z++) {
                vector3D relPos = buffer.w->convert_to_worldCoordintates(x, y, z) - center;
                float d = sqrt(relPos*relPos);
                if (d<radius){
                    buffer.create_particle(x * buffer.w->resolution, y * buffer.w->resolution, z * buffer.w->resolution);
                }
            }
        }
    }
}

#endif //SCHRODINGER_SMOKE_SET_UPS_H
