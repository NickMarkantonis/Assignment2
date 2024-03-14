#include "vec3.h"
#include "ray.h"

using namespace std;

// Sphere
class Sphere {
public:
    Sphere(vec3 possition, vec3 color, float radius);
    bool Hit(const ray &Ray, float &dist) const;

    float posX() const {return possition.x();}
    float posY() const {return possition.y();}
    float posZ() const {return possition.z();}
    float Radius() const {return radius;}
    vec3 getColor() {return color;}
private:
    vec3 possition;
    vec3 color;
    float radius;
};

/* Defining the sphere */
Sphere::Sphere(vec3 _possition, vec3 _color, float _radius) {
    possition = _possition;
    color = _color;
    radius = _radius;
}

/* Calculates whether a ray hits a sphere */
bool Sphere::Hit(const ray &Ray, float &dist) const {
    // making sure the ray is even going somewhat the right dirrection (so that we dont show a cyrcle 
    // even if it is exactly behind the camera)   
    // if (this->posX() - Ray.direction().x() < 0 || this->posY() - Ray.direction().y() < 0 || this->posZ() - Ray.direction().z() < 0) return 0;

    return Dist(Ray, *this) <= this->Radius();
}

// the following functions even thought not in the Sphere class are in the Sphere.h file as they are only used by it

/* vec3 crossProduct: calulates the cross product (εξωτερικό γινόμενο)*/
inline vec3 crossProduct(const vec3 &A, const vec3 &B) {
    return vec3(A.y() * B.z() - A.z() * B.y(), -A.x() * B.z() + A.z() * B.x(), A.x() * B.y() - A.y() * B.x());
}

/* float Dist: calulates the distance between a Ray and a point the 3D space */
float Dist(const ray &Ray, const Sphere &sphere) {
    // defininf the PS vector
    vec3 PS(sphere.posX() - Ray.origin().x(), sphere.posY() - Ray.origin().y(), sphere.posZ() - Ray.origin().z());

    return (float) (crossProduct(PS, Ray.direction()).length() / Ray.direction().length());
}
