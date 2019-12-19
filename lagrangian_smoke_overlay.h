//
// Created by Alex Greenen on 12/19/19.
//

#ifndef SCHRODINGER_SMOKE_LAGRANGIAN_SMOKE_OVERLAY_H
#define SCHRODINGER_SMOKE_LAGRANGIAN_SMOKE_OVERLAY_H

#include "wavefunction.h"
#include "math_util.h"
#include "field.h"
#include "vector3D.h"
#include <vector>

using namespace std;

class lagrangian_smoke_overlay: public world {
    lagrangian_smoke_overlay(float x_size, float y_size, float z_size, float res): world(x_size, y_size, z_size, res){}

    vector<vector3D>* particle_locations_perframe;
    float particle_radius;
    array<int, 3> rgb;
    float dt;
    int frames;
    int currentFrame;

    void create_particle(float x, float y, float z){ particle_locations_perframe[currentFrame].emplace_back(vector3D(x,y,z));}

    void evolve_particles(field<vector3D>* velocity_field){
        for (int particle = 0; particle < particle_locations_perframe[currentFrame].size(); particle++){
            vector3D current_particle_pos = particle_locations_perframe[currentFrame][particle];
            int xbase = int(current_particle_pos[0]/resolution);
            int ybase = int(current_particle_pos[1]/resolution);
            int zbase = int(current_particle_pos[2]/resolution);
            float xbetween = current_particle_pos[0]-xbase;
            float ybetween = current_particle_pos[1]-ybase;
            float zbetween = current_particle_pos[2]-zbase;
            // use linear interpolation between grid points
            vector3D velocity = xbetween *  velocity_field->getGridValue(xbase, ybetween, zbetween)
            vector3D moved_particle = vector3D(particle_locations_perframe[currentFrame]+dt*velocity_field->getGridValue())
            particle_locations_perframe[currentFrame+1].emplace_back(moved_particle);
        }

        currentFrame++;
    }

    void output_to_file(){

    }

};


#endif //SCHRODINGER_SMOKE_LAGRANGIAN_SMOKE_OVERLAY_H
