//
// Created by Alex Greenen on 12/19/19.
//

#ifndef SCHRODINGER_SMOKE_WORLD_H
#define SCHRODINGER_SMOKE_WORLD_H


#include "vector3D.h"

class world {
public:
    world() = default;
    world(float x_size, float y_size, float z_size, float res):
            resolution(res){
        grid_marks[0] = int(x_size/res);
        grid_marks[1] = int(y_size/res);
        grid_marks[2] = int(z_size/res);
        grid_size[0] = grid_marks[0]*resolution;
        grid_size[1] = grid_marks[1]*resolution;
        grid_size[2] = grid_marks[2]*resolution;
        number_of_grid_nodes = grid_marks[0]*grid_marks[1]*grid_marks[2];
    }

    float grid_size[3];
    int grid_marks[3];
    int number_of_grid_nodes;
    float resolution;

    inline vector3D convert_to_worldCoordintates(vector3D gridPoint){
        return gridPoint*resolution;
    }

    inline vector3D convert_to_gridCoordintates(vector3D worldPoint){
        return worldPoint/resolution;
    }

    vector3D convert_index_to_gridCoordintates(const int worldPoint) const {
        int z = worldPoint / (grid_marks[0] * grid_marks[1]);
        int y = (worldPoint-z*grid_marks[0]*grid_marks[1]) / (grid_marks[0]);
        int x = worldPoint-z*grid_marks[0]*grid_marks[1]-y*grid_marks[0];
        return vector3D(x, y, z);
    }

};


#endif //SCHRODINGER_SMOKE_WORLD_H
