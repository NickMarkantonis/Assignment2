#include "ClassesDef.h"
#include "vec3.h"

// Spheres
Sphere::Sphere(vec3 _possition, vec3 _color, float _radius) {
    possition = _possition;
    color = _color;
    radius = _radius;
}

bool Sphere::Hit(const ray &Ray, double &dist) const {
    float distance = dist(Ray, *this);

    if (distance <= dist && distance < retRadius()) {
        return 1;
    }
    return 0;
}


/* bool Dist: calculates whether a ray hits a sphere, by finding
 the disnace between the two and if it's less (or equal) it return true.
 
 * Inspiration on how to calculate said distance from HY-111 */
float dist(const ray &Ray, Sphere &sphere) {
    /* @param PS: vector that starts from one random point of the ray (the one saved)
     and ends in the center of the Sphere  */
    vec3 PS(sphere.posX() - Ray.point.x(), sphere.posY() - Ray.point.y(), sphere.posZ() - Ray.point.z());
    vec3 PS_times_v = crossProduct(PS, Ray.coords);

    return (PS_times_v.length() / Ray.coords.length());
}


/* vec3 crossProduct: calulates the cross product (εξωτερικό γινόμενο) of 
 two vectors and return the final correct one  */
vec3 crossProduct(const vec3 &A, const vec3 &B) {
    return vec3(A.y() * B.z() - A.z() * B.y(), -A.x() * B.z() + A.z() * B.x(), A.x() * B.y() - A.y() * B.x());
}

float Sphere::posX() const {
    return possition.x();
}

float Sphere::posY() const {
    return possition.y();
}

float Sphere::posZ() const {
    return possition.z();
}

float Sphere::retRadius() const {
    return radius;
}