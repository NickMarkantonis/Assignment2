#include "vec3.h"
#include "ray.h"

#include "Sphere.h"

using namespace std;

// the following functions even thought not in the Sphere class are in the Sphere.h file as they are only used by it
/* vec3 crossProduct: calulates the cross product (εξωτερικό γινόμενο)*/
inline vec3 crossProduct(const vec3 &A, const vec3 &B) {
    return vec3(A.y() * B.z() - A.z() * B.y(), -A.x() * B.z() + A.z() * B.x(), A.x() * B.y() - A.y() * B.x());
}

/* float Dist: calulates the distance between a Ray and a point the 3D space */
float Dist(const ray &Ray, const Sphere &sphere) {
    // defininf the PS vector
    vec3 PS(sphere.getPosX()-Ray.origin().x(),    sphere.getPosY()-Ray.origin().y(),    sphere.getPosZ()-Ray.origin().z());

    return (float) (crossProduct(PS, Ray.direction()).length() / Ray.direction().length());
}


/** Calculates whether a ray hits a sphere and also if the point of collission is the shortest yet 
 * 
 * @param Ray: the ray of the photon comming from the camera
 * @param dist: the yet shortest distance between the camera and the sphere hitpoint
*/
bool Sphere::Hit(ray &Ray, float *dist, bool *checkDist) const {
    /**
     * @param: Dist_CtoA: the distance from the center of the sphere to the Ray
     * @param: Ldist: the length between the camera and the center of the sphere
     * @param: totalDist: the final distance from the camera center to the point where the Ray hits
    */

    float Dist_CtoA = Dist(Ray, *this);

    if (Dist_CtoA <= this->getRadius()) {
        float Ldist = vec3(this->getPosX() - Ray.origin().x(), this->getPosY() - Ray.origin().y(), this->getPosZ() - Ray.origin().z()).length();
        // squaring the distance as we have to calculate it twice and we save computational resurces by that
        Dist_CtoA *= Dist_CtoA;
        float totalDist = sqrt(Ldist * Ldist + Dist_CtoA) - sqrt(this->getRadius() * this->getRadius() + Dist_CtoA);
        if (!*checkDist) {
            *dist = totalDist;
            // from now on to also check the distance
            *checkDist = true;
            return true;
        }
        if (totalDist < *dist) {
            *dist = totalDist;
            return true;
        } 
    }
    return false;
}


/* Defining the sphere */
Sphere::Sphere(vec3 _possition, vec3 _color, float _radius) {
    possition = _possition;
    color = _color;
    radius = _radius;
}