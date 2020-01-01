//
// Created by Alex Greenen on 12/19/19.
//

#ifndef SCHRODINGER_SMOKE_WORLD_H
#define SCHRODINGER_SMOKE_WORLD_H


class world {
public:
    world() = default;
    world(float x_size, float y_size, float z_size, float res):
            resolution(res),
            number_of_grid_nodes(grid_marks[0]*grid_marks[1]*grid_marks[2]){
        grid_marks[0] = int(x_size/res);
        grid_marks[1] = int(y_size/res);
        grid_marks[2] = int(x_size/res);
        grid_size[0] = grid_marks[0]*resolution;
        grid_size[1] = grid_marks[1]*resolution;
        grid_size[2] = grid_marks[2]*resolution;
    }

    float grid_size[3];
    int grid_marks[3];
    int number_of_grid_nodes;
    float resolution;
};


#endif //SCHRODINGER_SMOKE_WORLD_H
