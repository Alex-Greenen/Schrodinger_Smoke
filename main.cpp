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
int frames = 20;

int main() {

    std::cout << "Setting up. \n";
    world* w = new world(x_size, y_size, z_size, res);
    isf schr_flow = isf(w, dt, hbar);

    //Create a Jet
    field<vector3D> velocityField = field<vector3D>(w);
    for (int x = 0; x<w->grid_marks[0]; x++) {
        for (int y = 0; y<w->grid_marks[1]; y++) {
            float r_from_center = float(sqrt((x - w->grid_marks[0]/2)*(x - w->grid_marks[0]/2) + (y - w->grid_marks[1]/2)*(y - w->grid_marks[1]/2)));
            if ( r_from_center < w->grid_marks[x]/6 ) {
                for (int z = 0; z < int(w->grid_marks[2] / 3); z++) {
                    velocityField.updateGridValue(x, y, z, vector3D(0, 0, 1));
                }
            }
        }
    }
    schr_flow.set_velocity_induction(&velocityField);
    schr_flow.post_setup();

    lagrangian_smoke_overlay buffer = lagrangian_smoke_overlay (w, dt, frames);
    for (int x = 0; x<w->grid_marks[0]; x++) {
        for (int y = 0 ; y<w->grid_marks[1]; y++) {
            buffer.create_particle(x*res, y*res, 2*res);
        }
    }
//    for (int temp = 1; temp < 60 ; ++temp){
//        buffer.create_particle(x_size/2 + randnp1()*x_size/6, y_size/2 + randnp1()*y_size/6, rand01()*z_size/4);
//    }
    std::cout << "Setup Complete. Ready to Simulate. \n";

    for (int frame = 0; frame < frames; ++frame){
        schr_flow.time_evolve();
        schr_flow.pressure_project();
        schr_flow.normalise();
        field<vector3D> flow = schr_flow.velocity_field();
        buffer.evolve_particles(&velocityField);
        std::cout << "Simulated frame " << (frame+1) << ".\n";
    }
    std::cout << "Writing to file.\n";
    buffer.write_to_file();
    std::cout << "File written. End.\n";

}