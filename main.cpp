#include "world.h"
#include "field.h"
#include "vector3D.h"
#include "wavefunction.h"
#include "isf.h"
#include "lagrangian_smoke_overlay.h"


float x_size = 3;
float y_size = 3;
float z_size = 3;
float res = 0.1;
float hbar = 0.5;
float dt = 0.1;
int maxFrames = 3;

int main() {

    world* w = new world(x_size, y_size, z_size, res);
    isf schr_flow = isf(w, dt, hbar);
    schr_flow.post_setup(); //error comes from update value.
//
//    lagrangian_smoke_overlay buffer = lagrangian_smoke_overlay (w, dt, maxFrames);
//    for (int temp = 1; temp < 20 ; ++temp){
//        buffer.create_particle(float(temp*temp)/8,float(temp)/20,float(cos(temp))*5);
//    }
//
//    for (int frame = 0; frame < maxFrames; ++frame){
//        schr_flow.time_evolve();
//        schr_flow.pressure_project();
//        schr_flow.normalise();
//        field<vector3D> flow = schr_flow.velocity_field();
//        buffer.evolve_particles(&flow);
//    }
//    buffer.write_to_file();

}