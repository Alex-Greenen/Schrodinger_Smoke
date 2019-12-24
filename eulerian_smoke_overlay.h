//
// Created by Alex Greenen on 12/20/19.
//

#ifndef SCHRODINGER_SMOKE_EULERIAN_SMOKE_OVERLAY_H
#define SCHRODINGER_SMOKE_EULERIAN_SMOKE_OVERLAY_H

#include "wavefunction.h"
#include "math_util.h"
#include "field.h"
#include "vector3D.h"
#include <vector>

class eulerian_smoke_overlay {
public:
    eulerian_smoke_overlay()= default;
    eulerian_smoke_overlay(float x_size, float y_size, float z_size, float res, float _dt, int _frames): world(x_size, y_size, z_size, res), dt(_dt), frames(_frames){
        smoke_density_perframe.reserve(frames);
    }

    vector<field<float> > smoke_density_perframe;
    float dt;
    int frames;
    int currentFrame = 0;

    void add_smoke(float x,float y,float z, float amount);
    void evolve_smoke(field<vector3D>* velocity_field);
};


#endif //SCHRODINGER_SMOKE_EULERIAN_SMOKE_OVERLAY_H
