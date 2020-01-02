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
#include <iostream>
#include <fstream>

using namespace std;

class lagrangian_smoke_overlay {
public:
    lagrangian_smoke_overlay() = default;
    lagrangian_smoke_overlay(world* _w, float _dt, int _frames): w(_w), dt(_dt), frames(_frames){
        particle_locations_perframe.reserve(frames);
    }

    vector<vector<vector3D> > particle_locations_perframe;
    world* w;
    float dt;
    int frames;
    int currentFrame = 0;

    void create_particle(float x, float y, float z);
    void evolve_particles(field<vector3D>* velocity_field);
    void write_to_file();
};

void lagrangian_smoke_overlay::write_to_file(){
    ofstream file ("output_particles.json");
    if (file.is_open()) {
        file << "[";
        for(int frame=0; frame<particle_locations_perframe.size()-1; ++frame){
            file << "[";
            for(int particle=0; particle < particle_locations_perframe[frame].size()-1; ++particle){
                file << particle_locations_perframe[frame][particle] << ",";
            }
            file << particle_locations_perframe[frame][particle_locations_perframe[frame].size()-1];
            file << "],";;
        }
        file << "[";
        int last_fram_index = int(particle_locations_perframe.size())-1;
        for(int particle=0; particle < particle_locations_perframe[last_fram_index].size()-1; ++particle){
            file << particle_locations_perframe[last_fram_index][particle] << ",";
        }
        file << particle_locations_perframe[last_fram_index][particle_locations_perframe[last_fram_index].size()-1];
        file << "]";;
        file << "]";
        file.close();
    }
    else cout << "Unable to open file";
}

void lagrangian_smoke_overlay::create_particle(float x, float y, float z){
    particle_locations_perframe[currentFrame].push_back(vector3D(x,y,z));
}

void lagrangian_smoke_overlay::evolve_particles(field<vector3D>* velocity_field){
    for (int particle = 0; particle < particle_locations_perframe[currentFrame].size(); particle++){
        vector3D current_particle_pos = particle_locations_perframe[currentFrame][particle];
        int xbase = int(current_particle_pos[0]);
        int ybase = int(current_particle_pos[1]);
        int zbase = int(current_particle_pos[2]);
        float xbetween = current_particle_pos[0]-xbase;
        float ybetween = current_particle_pos[1]-ybase;
        float zbetween = current_particle_pos[2]-zbase;
        // use linear interpolation between grid points
        vector3D velocity = interpolate_in_cube(velocity_field->getGridValue(xbase,ybase,zbase),
                                                velocity_field->getGridValue(xbase+1,ybase,zbase),
                                                velocity_field->getGridValue(xbase,ybase+1,zbase),
                                                velocity_field->getGridValue(xbase+1,ybase+1,zbase),
                                                velocity_field->getGridValue(xbase,ybase,zbase+1),
                                                velocity_field->getGridValue(xbase+1,ybase,zbase+1),
                                                velocity_field->getGridValue(xbase,ybase+1,zbase+1),
                                                velocity_field->getGridValue(xbase+1,ybase+1,zbase+1),
                                                xbetween, ybetween, zbetween);
        vector3D moved_particle = particle_locations_perframe[currentFrame][particle]+dt*velocity;
        particle_locations_perframe[currentFrame+1].push_back(moved_particle);
    }

    currentFrame++;
}


#endif //SCHRODINGER_SMOKE_LAGRANGIAN_SMOKE_OVERLAY_H
