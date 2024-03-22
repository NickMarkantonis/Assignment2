#ifndef SPHERE_H
#define SHPERE_H

#include "vec3.h"
#include "ray.h"

#pragma once
#pragma warning

using namespace std;

// Sphere
class Sphere {
public:
    Sphere(vec3 possition, vec3 color, float radius);
    bool Hit(ray &Ray, double *dist, bool *checDist) const;

    double getPosX() const {return possition.x();}
    double getPosY() const {return possition.y();}
    double getPosZ() const {return possition.z();}
    double getRadius() const {return radius;}
    vec3 getColor() {return color;}
private:
    vec3 possition;
    vec3 color;
    float radius;
};

#endif SPHERE_H
