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
    bool Hit(ray &Ray, float dist) const;

    double posX() const {return possition.x();}
    double posY() const {return possition.y();}
    double posZ() const {return possition.z();}
    double Radius() const {return radius;}
    vec3 getColor() {return color;}
private:
    vec3 possition;
    vec3 color;
    float radius;
};

#endif SPHERE_H
