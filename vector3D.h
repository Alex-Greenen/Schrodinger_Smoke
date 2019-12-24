//
// Created by Alex Greenen on 12/15/19.
//

#ifndef SCHRODINGER_SMOKE_VECTOR3D_H
#define SCHRODINGER_SMOKE_VECTOR3D_H

#include <iostream>

using namespace std;

class vector3D {
public:
    vector3D(){
        e[0] = 0;
        e[1] = 0;
        e[2] = 0;
    };

    vector3D(const float x, const float y, const float z){
        e[0] = x;
        e[1] = y;
        e[2] = z;
    }

    float e[3];

    const inline vector3D operator+() const { return *this; }
    const inline vector3D operator-() const { return vector3D(-e[0], -e[1], -e[2]); }
    const inline float operator[](int i) const { return e[i]; }
    friend ostream& operator<<(ostream& os, const vector3D& v) {
        os << "[" << v.e[0] << "," << v.e[1] << "," << v.e[2] << "]";
        return os;
    }
    inline float norm() const {return e[0]*e[0]+e[1]*e[1]+e[2]*e[2];}
    void normalise() {
        float n = norm();
        e[0] = e[0]/n;
        e[1] = e[1]/n;
        e[2] = e[2]/n;
    }

};
const inline float dot(const vector3D &v1, const vector3D &v2)  { return v1.e[0] *v2.e[0] + v1.e[1] *v2.e[1]  + v1.e[2] *v2.e[2];}
const inline vector3D cross(const vector3D &v1, const vector3D &v2) {return vector3D((v1.e[1]*v2.e[2] - v1.e[2]*v2.e[1]),(-(v1.e[0]*v2.e[2] - v1.e[2]*v2.e[0])),(v1.e[0]*v2.e[1] - v1.e[1]*v2.e[0]));}

const vector3D operator+(const vector3D &v1, const vector3D &v2) {return vector3D(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);}
const vector3D operator-(const vector3D &v1, const vector3D &v2) {return vector3D(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);}
const vector3D operator*(float t, const vector3D &v) {return vector3D(t*v.e[0], t*v.e[1], t*v.e[2]);}
const vector3D operator/(vector3D v, float t) {return vector3D(v.e[0]/t, v.e[1]/t, v.e[2]/t);}
const vector3D operator*(const vector3D &v, float t){return vector3D(t*v.e[0], t*v.e[1], t*v.e[2]);}

//This line is for coding convenience (replaces dot() function), you cannot actually multiply two vectors.
const inline float operator*(const vector3D &v1, const vector3D &v2) {return dot(v1,v2);}

#endif //SCHRODINGER_SMOKE_VECTOR3D_H
