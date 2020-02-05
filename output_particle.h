//
// Created by Alex Greenen on 12/19/19.
//

#ifndef SCHRODINGER_OUTPUT_PARTICLE_H
#define SCHRODINGER_OUTPUT_PARTICLE_H

#include "wavefunction.h"
#include "math_util.h"
#include "field.h"
#include "vector3D.h"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class output_particle {
public:
    output_particle() = default;
    output_particle(world* _w, float _dt, int _frames): w(_w), dt(_dt){
        particle_locations_perframe.push_back(vector<vector3D>(0));
    }

    vector<vector<vector3D> > particle_locations_perframe;
    world* w;
    float dt;
    int currentFrame = 0;

    void create_particle(float x, float y, float z);
    void evolve_particles(field<vector3D>* velocity_field);
    void write_to_file();
};

void output_particle::write_to_file(){
    ofstream file ("output_particles.json");
    if (file.is_open()) {
        file << "[\n";

        int frames_numb = int(particle_locations_perframe.size())-1;

        for(int frame=0; frame < frames_numb-1; frame++){
            int particle_numb = int(particle_locations_perframe[frame].size()) -1;
            if (particle_numb != -1){ //no particles
                file << "     [\n";
                for(int particle=0; particle < particle_numb; particle++){
                    file << "          " << particle_locations_perframe[frame][particle] << ",\n";
                }
                file << "          " << particle_locations_perframe[frame][particle_numb] <<"\n";
                file << "     ],\n";
            }
        }
        int particle_numb = int(particle_locations_perframe[frames_numb].size()) -1;
        if (particle_numb != -1){ //no particles
            file << "     [\n";
            for(int particle=0; particle < particle_numb; particle++){
                file << "          " << particle_locations_perframe[frames_numb][particle] << ",\n";
            }
            file << "          " << particle_locations_perframe[frames_numb][particle_numb] <<"\n";
            file << "     ]\n";
        }
        else{
            file << "     []\n";
        }
        file << "]\n";
        file.close();
    }
    else cout << "Unable to open file";
}

void output_particle::create_particle(float x, float y, float z){
    particle_locations_perframe[currentFrame].push_back(vector3D(x,y,z));
}

void output_particle::evolve_particles(field<vector3D>* velocity_field){
    particle_locations_perframe.push_back(vector<vector3D>(0));
    for (int particle = 0; particle < particle_locations_perframe[currentFrame].size(); particle++){
        vector3D current_particle_pos = particle_locations_perframe[currentFrame][particle];
        // dividing by the resolution converts us from world point to grid point
        int xbase = int(current_particle_pos[0]/w->resolution);
        int ybase = int(current_particle_pos[1]/w->resolution);
        int zbase = int(current_particle_pos[2]/w->resolution);
        float xbetween = current_particle_pos[0]/w->resolution-xbase;
        float ybetween = current_particle_pos[1]/w->resolution-ybase;
        float zbetween = current_particle_pos[2]/w->resolution-zbase;
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

        // Periodic Boundary Conditions
        if (moved_particle[0] < 0) {moved_particle.e[0] += w->grid_size[0];}
        if (moved_particle[0] > w->grid_size[0]){moved_particle.e[0]-= w->grid_size[0];}
        if (moved_particle[1] < 0){moved_particle.e[1]+= w->grid_size[1];}
        if (moved_particle[1] > w->grid_size[1]){moved_particle.e[1]-= w->grid_size[1];}
        if (moved_particle[2] < 0){moved_particle.e[2]+= w->grid_size[2];}
        if (moved_particle[2] > w->grid_size[2]){moved_particle.e[2]-= w->grid_size[2];}

        particle_locations_perframe[currentFrame+1].push_back(moved_particle);
    }
    currentFrame++;
}


#endif //SCHRODINGER_OUTPUT_PARTICLE_H
