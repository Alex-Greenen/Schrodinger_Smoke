//
// Created by Alex Greenen on 1/19/20.
//

#ifndef SCHRODINGER_SMOKE_OUTPUT_FIELD_H
#define SCHRODINGER_SMOKE_OUTPUT_FIELD_H


#include "wavefunction.h"
#include "math_util.h"
#include "field.h"
#include "vector3D.h"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

template <class field_type>
class output_field {
public:
    output_field() = default;
    output_field(world* _w): w(_w){
        vectors_perframe = vector<vector<field_type> >(0, vector<field_type>(0));
    }

    vector<vector<field_type> > vectors_perframe;
    world* w;

    void add_vectorfield( field<field_type> *vect_field){
        int gridPoints = w->number_of_grid_nodes;
        vector<field_type> frame = vector<field_type>(gridPoints, field_type());
        for (int vector_index=0; vector_index < gridPoints; vector_index++){
            frame.push_back(vect_field->grid[vector_index]);
        }
        vectors_perframe.push_back(frame);
    }


    void write_to_file(){
        ofstream file ("output_field.json");
        if (file.is_open()) {

            file << "[\n";

            file << "     [" << w->grid_marks[0] << ", " << w->grid_marks[1] << ", " << w->grid_marks[2] << "],\n";

            int frames_numb = int(vectors_perframe.size())-1;
            int vector_numb = w->number_of_grid_nodes;

            for(int frame=0; frame < frames_numb-1; frame++){
                file << "     [\n";
                for(int vector_index=0; vector_index < vector_numb; vector_index++){
                    file << "          " << vectors_perframe[frame][vector_index] << ",\n";
                }
                file << "          " << vectors_perframe[frame][vector_numb] <<"\n";
                file << "     ],\n";
            }

            file << "     [\n";
            for(int vector_index=0; vector_index < vector_numb; vector_index++){
                file << "          " << vectors_perframe[frames_numb][vector_index] << ",\n";
            }
            file << "          " << vectors_perframe[frames_numb][vector_numb] <<"\n";
            file << "     ]\n";

            file << "]\n";
            file.close();
        }
        else cout << "Unable to open file";
    }
};





#endif //SCHRODINGER_SMOKE_OUTPUT_FIELD_H
