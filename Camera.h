#include "vec3.h"
#include "ray.h"

class Camera {
public:
    Camera(vec3 center, int width, int height);
    vec3 pixelCenter(int x, int y);

    int getHeight() const {return height;}
    int getWidth() const {return width;}
    vec3 getPos() const {return center;}
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

/* creating for each pixel a direction vector */
vec3 Camera::pixelCenter(int x, int y) {
    float X = 1 - (float) 2 * x / width;
    float Y = aspectRatio - (float) 2 * y / width;

    return vec3(-1,X,Y);
}
