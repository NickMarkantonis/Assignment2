#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"

using namespace std;

class Camera {
public:
    Camera(vec3 center, int width, int height);
    vec3 pixelCenter(int x, int y) const;

    int getHeight() const;
    int getWidth() const;
    float getAspectRatio() const;
    vec3 getPos() const;
    float getFc() const;
private:
    vec3 center;
    int width;
    int height;
    float aspectRatio;
    float focalLength = 18.0/18.0;
};

#endif