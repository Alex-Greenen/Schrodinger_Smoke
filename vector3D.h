//
// Created by Alex Greenen on 12/15/19.
//

#ifndef SCHRODINGER_SMOKE_VECTOR3D_H
#define SCHRODINGER_SMOKE_VECTOR3D_H

class vector3D {
public:
    vector3D(){}
    vector3D(const float x, const float y, const float z){
        e[0] = x;
        e[1] = y;
        e[2] = z;
    }

    float e[3];

    const inline vector3D operator+() const { return *this; }
    const inline vector3D operator-() const { return vector3D(-e[0], -e[1], -e[2]); }
    const inline double operator[](int i) const { return e[i]; }
    const inline double operator[](int i) { return e[i]; }
    const inline float dot(const vector3D &v1, const vector3D &v2) { return v1.e[0] *v2.e[0] + v1.e[1] *v2.e[1]  + v1.e[2] *v2.e[2];}
    const inline vector3D cross(const vector3D &v1, const vector3D &v2) {return vector3D((v1.e[1]*v2.e[2] - v1.e[2]*v2.e[1]),(-(v1.e[0]*v2.e[2] - v1.e[2]*v2.e[0])),(v1.e[0]*v2.e[1] - v1.e[1]*v2.e[0]));}

};
const inline vector3D operator+(const vector3D &v1, const vector3D &v2) {return vector3D(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);}
const inline vector3D operator-(const vector3D &v1, const vector3D &v2) {return vector3D(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);}
const inline vector3D operator*(float t, const vector3D &v) {return vector3D(t*v.e[0], t*v.e[1], t*v.e[2]);}
const inline vector3D operator/(vector3D v, float t) {return vector3D(v.e[0]/t, v.e[1]/t, v.e[2]/t);}
const inline vector3D operator*(const vector3D &v, float t) {return vector3D(t*v.e[0], t*v.e[1], t*v.e[2]);}


#endif //SCHRODINGER_SMOKE_VECTOR3D_H
