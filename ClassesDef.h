#include "vec3.h"
#include "std_lib_facilities.h"

using namespace std;

/* struct ray:
 * defines a ray in the 3D space 
 * @param coords: a vector in the 3D space that defines the dirrection of the ray 
 * @param point:  a point (ussualy the starting point) that defines one point from which the ray passes */
struct ray {
    vec3 coords;
    vec3 point;
};


// Sphere
class Sphere {
public:
    Sphere(vec3 possition, vec3 color, float radius);
    bool Hit(const ray &Ray, double &dist) const;

    float posX() const;
    float posY() const;
    float posZ() const;
private:
    vec3 possition;
    vec3 color;
    float radius;
};
