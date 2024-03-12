#include <fstream>
#include "ClassesDef.h"

using namespace std;

class WrongInput {};

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
bool Sphere::Hit(const ray &Ray, float &dist) const {
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

    return vec3(1,X,Y);
}

int Camera::getHeight() const {
    return height;
}

int Camera::getWidth() const {
    return width;
}

vec3 Camera::getCenter() const {
    return center;
}

// World
World::World(vec3 _skyColour) {
    skyColour = _skyColour;
}

void World::Add(Sphere &sphere) {
    Spheres.insert(Spheres.end(), sphere);
}

void World::Render(Camera &cam) const {
    fstream fout;
    fout.open("image.ppm", ios::out | ios::trunc);
    fout << "P3\n" << cam.getWidth() << " " << cam.getHeight() << "\n255\n";
    
    float dist = 100;
    color pixel_colour;
    vec3 Direction;

    for (int i = 1; i <= cam.getHeight(); i++) {
        for (int j = 1; j <= cam.getWidth(); j++) {
            Direction = cam.GetPixelCenter(j,i);
            ray Ray(cam.getCenter(), Direction);

            for (auto k = Spheres.begin(); k < Spheres.end(); k++) {
                if (k->Hit(Ray, dist)) pixel_colour = color(1,0,0);
                else pixel_colour = color(0,0,.5);
            }

            write_color(fout, pixel_colour);
        }
    }
}

/* The function checks the following:
1. If the string is a integer and if it is we return the adequate integer
   If it isn't throw a exception with errorNum == 2
2. In case it is we also check if it possitive
   If it isn't we throw a exception with errorNum == 1
3. If the string is a num but a decimal we throw an exception 
4. If the int is bigger then 
Checking if string is number: user Ben Voigt stackoverflow (https://stackoverflow.com/a/16575025)*/
int isInteger(const string input, const int option) {
    char* p;
    int num;

    strtol(input.c_str(), &p, 10);
    if (*p == 0) // if it is a integer
    {
        num = stoi(input);
        if (num <= 0)
        {
            errno = 1;
            throw WrongInput();
            return 0;
        }
        if (option && num > option)
        {
            errno = 3;
            throw WrongInput();
            return 0;
        }
    } else // if  it isn't
    {
        errno = 2;
        throw WrongInput();
        return 0;
    }

    return num;
}

/* The following function given the input in string form checks 
(using the isInteger(string input)) function if the input provided is correct
In case the int option is true (!= 0) we also check that the returned int is less then 4
if it isn't we throw an exception with errno == 3 */
int checkInputInt(string input, const int option) {
    int inp = 0;
    while (!inp)
    {
        try {
            inp = isInteger(input, option);
        }
        catch (WrongInput& b)
        {
            if (errno == 1) cout << "Number must be possitive integer, please try again: ";
            else if (errno == 2) cout << "Input must be integer, please try again: ";
            else if (errno == 3) cout << "Option must be between 1 and " << option << ": ";
            cin >> input;
            // resseting the error
            errno = 0;
        }
    }

    return inp;
}
