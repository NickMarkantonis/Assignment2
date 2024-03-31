#include "vec3.h"
#include "ray.h"
#include "Sphere.h"

using namespace std;

// the following two function even thought not part of the Sphere class are only used by it and are not needed to be declared anywere else


// vec3 crossProduct: calulates the cross product (εξωτερικό γινόμενο)
inline vec3 crossProduct(const vec3 &A, const vec3 &B) {
    return vec3(A.y() * B.z() - A.z() * B.y(), A.z() * B.x() - A.x() * B.z(), A.x() * B.y() - A.y() * B.x());
}

// float inerProduct: calculates the iner product (εσωτερικό γινόμενο)
inline double inerProduct(const vec3 &A, const vec3 &B) {
    return (float) (A.x() * B.x() + A.y() * B.y() + A.z() * B.z());
}

/** float Dist: calulates the distance between a Ray and a point the 3D space
 * we do it like we where taught in the lesson HY-111 */
double Dist(const ray &Ray, const Sphere &sphere) {
    vec3 PS(sphere.getPosX()-Ray.origin().x(),    sphere.getPosY()-Ray.origin().y(),    sphere.getPosZ()-Ray.origin().z());

    return (crossProduct(PS, Ray.direction()).length() / Ray.direction().length());
}


/** Calculates whether a ray hits a sphere and also if the point of collission is the shortest yet 
 * 
 * @param Ray: the ray of the photon comming from the camera
 * @param dist: the yet shortest distance between the camera and the sphere hitpoint
 * @param checkDist: boolean whether or not to check the distance, is "false" on the first time and from there on is "true"
*/
bool Sphere::Hit(ray &Ray, double *dist, bool *checkDist) const {
    /**
     * @param Dist_CtoA: the distance from the center of the sphere to the Ray
     * @param Ldist: the length between the camera and the center of the sphere
     * @param totalDist: the final distance from the camera center to the point where the Ray hits
    */

    double Dist_CtoA = Dist(Ray, *this);

    if (Dist_CtoA <= getRadius()) {
        vec3 L(getPosX() - Ray.origin().x(), getPosY() - Ray.origin().y(), getPosZ() - Ray.origin().z());
        /** We also have to make sure that the point of contact between the line and the sphre is
         * infront of the camera, to achieve that we calculate the z axis of the closest point to the 
         * center of the shere and then compare it to the possition of the camera in the z axis. If the 
         * point of we found is over the camera (ZofPoint > ZofCamera) we know that the point is behind
         * the camera and should not be rendered (return false)
         * 
         * The way to calculate said point was found from https://chat.openai.com/share/730f2226-59a1-450e-b359-781322599fdb
         * @param t: parameter that saves how many times we have to multiple the vector, starting from the origin of the ray 
         * (camera), in order to reach the point we want if it is negative we know that the vector has to travel backwards
         * so the hit point is behind the camera
        */
        double t = inerProduct(L, Ray.direction());
        if (t < 0) return false;
        
        // squaring the distance as we have to calculate it twice and we save computational resurces by that
        double Ldist = L.length();
        Dist_CtoA *= Dist_CtoA;
        double totalDist = sqrt(Ldist * Ldist - Dist_CtoA) - sqrt(getRadius() * getRadius() - Dist_CtoA);

        // the first time we do not need to check the distance
        if (!*checkDist) {
            *dist = totalDist;
            // from now on to also check the distance
            *checkDist = true;
            return true;
        }
        
        // if the hitpoint is the shortest yet
        if (totalDist < *dist) {
            *dist = totalDist;
            return true;
        } 
    }
    return false;
}


// Defining the Sphere
Sphere::Sphere(vec3 _possition, vec3 _color, float _radius) {
    possition = _possition;
    color = _color;
    radius = _radius;
}
