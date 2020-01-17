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
int frames = 50;

int main() {

    world* w = new world(x_size, y_size, z_size, res);
    field<vector3D> f = field<vector3D>();



//    world* w = new world(x_size, y_size, z_size, res);
//    isf schr_flow = isf(w, dt, hbar);
//    field<vector3D> velocityField = field<vector3D>(w);
//    for (int x = 0; x<w->grid_marks[0]; x++) {
//        for (int y = int(w->grid_marks[1] / 3); y < int(3 * w->grid_marks[1] / 2); y++) {
//            for (int z = int(w->grid_marks[2] / 3); z < int(3 * w->grid_marks[2] / 2); z++) {
//                velocityField.updateGridValue(x,y,z,vector3D(1,0,0));
//            }
//        }
//    }
//    schr_flow.set_velocity_induction(&velocityField);
//    schr_flow.post_setup();
//
//    lagrangian_smoke_overlay buffer = lagrangian_smoke_overlay (w, dt, frames);
//    for (int temp = 1; temp < 60 ; ++temp){
//        buffer.create_particle(rand01()*x_size, rand01()*y_size, rand01()*z_size);
//    }
//
//    for (int frame = 0; frame < frames-1; ++frame){
//        schr_flow.time_evolve();
//        schr_flow.pressure_project();
//        schr_flow.normalise();
//        field<vector3D> flow = schr_flow.velocity_field();
//        buffer.evolve_particles(&velocityField);
//    }
//    buffer.write_to_file();

}