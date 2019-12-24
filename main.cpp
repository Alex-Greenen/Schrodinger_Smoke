#include <iostream>
#include "field.h"
#include "vector3D.h"
#include "wavefunction.h"
#include "lagrangian_smoke_overlay.h"
#include "isf.h"
#include "world.h"

float x_size = 5;
float y_size = 5;
float z_size = 5;
float res = 0.01;
float dt = 0.1;
float hbar = 0.5;
int maxFrames = 20;

int main() {
    isf schr_flow = isf(x_size, y_size, z_size, res, dt, hbar);
    schr_flow.post_setup();

    lagrangian_smoke_overlay buffer = lagrangian_smoke_overlay (x_size, y_size, z_size, res, dt, maxFrames);
    for (int temp = 1; temp < 20 ; ++temp){
        buffer.create_particle(float(temp*temp)/8,float(temp)/20,float(cos(temp))*5);
    }

    for (int frame = 0; frame < maxFrames; ++frame){
        schr_flow.time_evolve();
        schr_flow.pressure_project();
        schr_flow.normalise();
        field<vector3D> flow = schr_flow.velocity_field();
        buffer.evolve_particles(&flow);
    }
    buffer.write_to_file();

}