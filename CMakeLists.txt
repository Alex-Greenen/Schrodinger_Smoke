cmake_minimum_required(VERSION 3.10)
project(Schrodinger_Smoke)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_STANDARD 11)

add_executable(Schrodinger_Smoke main.cpp field.h vector3D.h wavefunction.h isf.h math_util.h output_particle.h world.h output_field.h set_ups.h)