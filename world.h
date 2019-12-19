//
// Created by Alex Greenen on 12/19/19.
//

#ifndef SCHRODINGER_SMOKE_WORLD_H
#define SCHRODINGER_SMOKE_WORLD_H

#include <array>;

using namespace std;

class world {
public:
    world(float x_size, float y_size, float z_size, float res){
        resolution = res;
        grid_marks = {int(x_size/res), int(y_size/res), int(z_size/res)};
        grid_size = {grid_marks[0]*resolution, grid_marks[1]*resolution, grid_marks[2]*resolution};
        number_of_grid_nodes = grid_marks[0]*grid_marks[1]*grid_marks[2];
    }
    array<float,3> grid_size;
    array<int,3> grid_marks;
    int number_of_grid_nodes;
    float resolution;
};


#endif //SCHRODINGER_SMOKE_WORLD_H
