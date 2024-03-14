#include "vec3.h"
#include "ray.h"

#pragma once

using namespace std;

class Camera {
public:
    Camera(vec3 center, int width, int height);
    vec3 pixelCenter(int x, int y) const;

    int getHeight() const;
    int getWidth() const;
    float getAspectRatio() const;
    vec3 getPos() const;
private:
    vec3 center;
    int width;
    int height;
    float aspectRatio;
};

/* defining the camera*/
Camera::Camera(vec3 _center, int _width, int _height) {
    center = _center;
    width = _width;
    height = _height;
    aspectRatio = (float) height/width;
}

int Camera::getHeight() const {
    return height;
}

int Camera::getWidth() const {
    return width;
}

float Camera::getAspectRatio() const {
    return aspectRatio;
}

vec3 Camera::getPos() const {
    return center;
}

/* creating for each pixel a direction vector */
vec3 Camera::pixelCenter(int y, int x) const {
    float X = 1 - (float) 2 * x / getWidth();
    float Y = getAspectRatio() - (float) 2 * y / getWidth();

    return vec3(-1,X,Y);
}
