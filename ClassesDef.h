#include "vec3.h"
#include "ray.h"
#include "std_lib_facilities.h"

using namespace std;

// Sphere
class Sphere {
public:
    Sphere(vec3 possition, vec3 color, float radius);
    bool Hit(const ray &Ray, double &dist) const;

    float posX() const;
    float posY() const;
    float posZ() const;

    float Radius() const;
private:
    vec3 possition;
    vec3 color;
    float radius;
};

// Camera
class Camera {
public:
    Camera(vec3 center, int width, int height);
    vec3 GetPixelCenter(int x, int y);

    int getHeight() const;
    int getWidth() const;
private:
    vec3 center;
    int width;
    int height;
    float aspectRatio;
};

/*-------------------------------------------------------------------------------------------------------------------------------
 * functions*/

/* vec3 crossProduct: calulates the cross product (εξωτερικό γινόμενο) of 
 two vectors and return the final correct one  */
vec3 crossProduct(const vec3 &A, const vec3 &B) {
    return vec3(A.y() * B.z() - A.z() * B.y(), -A.x() * B.z() + A.z() * B.x(), A.x() * B.y() - A.y() * B.x());
}

/* bool Dist: calculates whether a ray hits a sphere, by finding
 the disnace between the two and if it's less (or equal) it return true.
 
 * Inspiration on how to calculate said distance from HY-111 */
float Dist(const ray &Ray, const Sphere &sphere) {
    /* @param PS: vector that starts from one random point of the ray (the one saved)
     and ends in the center of the Sphere  
     * @param PS_times_v: cross product between PS and the coords of the vector*/
    vec3 PS(sphere.posX() - Ray.origin().x(), sphere.posY() - Ray.origin().y(), sphere.posZ() - Ray.origin().z());
    vec3 PS_times_v = crossProduct(PS, Ray.direction());


    return (float) (PS_times_v.length() / Ray.direction().length());
}

/* Defining the sphere */
Sphere::Sphere(vec3 _possition, vec3 _color, float _radius) {
    possition = _possition;
    color = _color;
    radius = _radius;
}

/* Calculates whether a ray hits a sphere */
bool Sphere::Hit(const ray &Ray, double &dist) const {
    // making sure the ray is even going somewhat the right dirrection (so that we dont show a cyrcle 
    // even if it is exactly behind the camera)   
    // if (this->posX() - Ray.direction().x() < 0 || this->posY() - Ray.direction().y() < 0 || this->posZ() - Ray.direction().z() < 0) return 0;

    float distance = Dist(Ray, *this);

    if (Dist(Ray, *this) <= Radius()) {
        return 1;
    }
    return 0;
}

/* Returning the center of the sphere in the x axis */
float Sphere::posX() const {
    return (float) possition.x();
}

/* Returning the center of the sphere in the y axis */
float Sphere::posY() const {
    return (float) possition.y();
}

/* Returning the center of the sphere in the z axis */
float Sphere::posZ() const {
    return (float) possition.z();
}

/* Returns the radius of the sphere */
float Sphere::Radius() const {
    return (float) radius;
}

// Camera
/* defining the camera*/
Camera::Camera(vec3 _center, int _width, int _height) {
    center = _center;
    width = _width;
    height = _height;
    aspectRatio = (float) height/width;
}

/* returns a direction vector that is qdequate to the one leaving from the camera  */
vec3 Camera::GetPixelCenter(int x, int y) {
    float X = 1 - (float) 2 * x / width;
    float Y = aspectRatio - (float) 2 * y / width;

    return vec3(-1,X,Y);
}

int Camera::getHeight() const {
    return height;
}

int Camera::getWidth() const {
    return width;
}
