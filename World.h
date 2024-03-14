#ifndef WORLD_H
#define WORLD_H

#include "Camera.h"
#include "Sphere.h"
#include <vector>

using namespace std;

class World {
public:
    World(vec3 skyColor);

    void Add(Sphere &sphere);
    void Render(Camera &cam);

    vec3 getSkyColor() const {return skyColor;}
    
    vector<Sphere> Spheres;
private:
    vec3 skyColor;
};

#endif
