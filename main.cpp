#include "world.h"
#include "field.h"
#include "vector3D.h"
#include "wavefunction.h"
#include "isf.h"
#include "output_particle.h"
#include "output_field.h"

#include <iostream>
#include <vector>

float x_size = 2;
float y_size = 2;
float z_size = 2;
float res = 0.05;
float hbar = 0.05;
float dt = 0.04;
int frames = 30;

using namespace std;

int main() {

    std::cout << "Setting up. \n";
    auto* w = new world(x_size, y_size, z_size, res);
    isf schr_flow = isf(w, dt, hbar);

    //Create a Jet
    field<vector3D> velocityField = field<vector3D>(w);

    for (int x=0; x < w->grid_marks[0]; x++){
        for (int y = 0; y< w->grid_marks[1]; y++){
            float rsq = sqrt(square((float) x - ((float) w->grid_marks[0])/2) + square((float) y - (float) w->grid_marks[1]/2));
            if (rsq < ((float)w->grid_marks[0])/3){
                for (int z = 1; z < 4; z++) {
                    velocityField.updateGridValue(x, y, z, vector3D(0, 0, 0.3));
                }
            }
        }
    }

    schr_flow.set_velocity_induction(&velocityField);
    //schr_flow.pressure_project();
    schr_flow.normalise();

    output_particle buffer = output_particle (w, dt, frames);
    for (int x = 0; x<w->grid_marks[0]; x++) {
        for (int y = 0 ; y<w->grid_marks[1]; y++) {
            buffer.create_particle(x*res, y*res, 2*res);
        }
    }

    std::cout << "Setup Complete. Ready to Simulate. \n";

    for (int frame = 0; frame < frames; ++frame){
        // Iterate Fluid
        schr_flow.time_evolve();
        schr_flow.normalise();
        //schr_flow.pressure_project();

        // Set Velocity
        field<float> wf1density = schr_flow.wf1.density_field();
        wf1density = apply_element_wise(&wf1density, sqrt);
        field<float> wf2density = schr_flow.wf2.density_field();
        wf2density = apply_element_wise(&wf2density, sqrt);

        for (int x=0; x < w->grid_marks[0]; x++){
            for (int y = 0; y< w->grid_marks[1]; y++){
                float rsq = sqrt(square((float) x - ((float) w->grid_marks[0])/2) + square((float) y - (float) w->grid_marks[1]/2));
                if (rsq < ((float)w->grid_marks[0])/3){
                    for (int z = 0; z < ((float) w->grid_marks[2])/2; z++) {
                        vector3D position = w->convert_to_worldCoordintates(x,y,z);
                        float phase = vector3D(0,0,0.3)*position/hbar;
                        schr_flow.wf1.real.updateGridValue(x,y,z, cos(phase) * wf1density.getGridValue(x,y,z));
                        schr_flow.wf1.imaginary.updateGridValue(x,y,z, sin(phase) * wf1density.getGridValue(x,y,z));

                        schr_flow.wf2.real.updateGridValue(x,y,z, cos(phase) * wf2density.getGridValue(x,y,z));
                        schr_flow.wf2.imaginary.updateGridValue(x,y,z, sin(phase) * wf2density.getGridValue(x,y,z));
                    }
                }
            }
        }

        // Advect Particles
        field<vector3D> flow = schr_flow.velocity_field();
        buffer.evolve_particles(&flow);

        std::cout << "Simulated frame " << (frame+1) << ".\n";
    }

    std::cout << "Writing to file.\n";
    buffer.write_to_file();
    std::cout << "File written. End.\n";

}

//
//int main() {
//
//    std::cout << "Setting up. \n";
//    world* w = new world(x_size, y_size, z_size, res);
//    isf schr_flow = isf(w, dt, hbar);
//
//    //Create a Jet
//    field<vector3D> velocityField = field<vector3D>(w);
//    for (int x = 0; x<w->grid_marks[0]; x++) {
//        for (int y = 0; y<w->grid_marks[1]; y++) {
//            float r_from_center = float(sqrt((x - w->grid_marks[0]/2)*(x - w->grid_marks[0]/2) + (y - w->grid_marks[1]/2)*(y - w->grid_marks[1]/2)));
//            if ( r_from_center < w->grid_marks[x]/6 ) {
//                for (int z = 0; z < int(w->grid_marks[2] / 3); z++) {
//                    velocityField.updateGridValue(x, y, z, vector3D(0, 0, 1));
//                }
//            }
//        }
//    }
//    schr_flow.set_velocity_induction(&velocityField);
//    schr_flow.post_setup();
//
//    output_field<vector3D> buffer = output_field<vector3D>(w);
//    std::cout << "Setup Complete. Ready to Simulate. \n";
//
//    for (int frame = 0; frame < frames; ++frame){
//        schr_flow.time_evolve();
//        schr_flow.pressure_project();
//        schr_flow.normalise();
//        field<vector3D> flow = schr_flow.velocity_field();
//        buffer.add_vectorfield(&flow);
//        std::cout << "Simulated frame " << (frame+1) << ".\n";
//    }
//    std::cout << "Writing to file.\n";
//    buffer.write_to_file();
//    std::cout << "File written. End.\n";
//
//}
