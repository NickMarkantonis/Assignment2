#include "vec3.h"
#include "ray.h"

#include "Camera.h"

#pragma once

using namespace std;

// Defining the camera
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
    double X = 1 - (float) 2 * x / getWidth();
    double Y = getAspectRatio() - (float) 2 * y / getWidth();

    return vec3(X,Y,-1);
}
