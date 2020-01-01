#include "world.h"
#include "field.h"
#include "vector3D.h"
//#include "wavefunction.h"
//#include "isf.h"
//#include "lagrangian_smoke_overlay.h"


float x_size = 5;
float y_size = 5;
float z_size = 5;
float res = 0.01;
float dt = 0.1;
float hbar = 0.5;
int maxFrames = 20;

int main() {

    field<vector3D> fieldA = field<vector3D>(x_size, y_size, z_size, res, vector3D(1,1,1));
    field<vector3D> fieldB = field<vector3D>(x_size, y_size, z_size, res, vector3D(1,1,1));

    field<vector3D> result = 3*fieldA;

    std::cout << result.grid[0];


//    wavefunction wf = wavefunction(x_size, y_size, z_size, res, dt, hbar, 0.1);
//
//    isf schr_flow = isf(x_size, y_size, z_size, res, dt, hbar);
//    schr_flow.post_setup(); //terminating with uncaught exception of type std::bad_alloc: std::bad_alloc
//
////    lagrangian_smoke_overlay buffer = lagrangian_smoke_overlay (x_size, y_size, z_size, res, dt, maxFrames);
//    for (int temp = 1; temp < 20 ; ++temp){
//        buffer.create_particle(float(temp*temp)/8,float(temp)/20,float(cos(temp))*5);
//    }

//    for (int frame = 0; frame < maxFrames; ++frame){
//        schr_flow.time_evolve();
//        schr_flow.pressure_project();
//        schr_flow.normalise();
//        field<vector3D> flow = schr_flow.velocity_field();
//        buffer.evolve_particles(&flow);
//    }
//    buffer.write_to_file();

}