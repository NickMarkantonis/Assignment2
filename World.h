#include "Camera.h"
#include "Sphere.h"

#include <vector>
#include <fstream>
#include "vec3.h"
#include "ray.h"
#include "color.h"

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

/* Defining the World */
World::World(vec3 _skyColor) {
    skyColor = _skyColor;
}

/* Adds the Sphere given to the vector */
void World::Add(Sphere &sphere) {
    Spheres.insert(Spheres.end(), sphere);
}

// renders the phto from the camera given
void World::Render(Camera &cam) {
    color pixel_color;
    float dist = 100;

    // creating the image
    fstream fout;
    fout.open("image.ppm", ios::out | ios::trunc);
    fout << "P3\n" << cam.getWidth() << " " << cam.getHeight() << "\n255\n";
    

    // going throught all the pixels
    for (int i = 0; i < cam.getHeight(); i++) {
        for (int j = 0; j < cam.getWidth(); j++) {
            // defining the default color as the sy color
            pixel_color = this->getSkyColor();
            // generating a ray based on the pixel
            ray Photon(cam.getPos() ,cam.pixelCenter(i, j));

            for (int k = 0; k < this->Spheres.size(); k++) {
                if (Spheres[k].Hit(Photon, dist)) pixel_color = Spheres[k].getColor();
            }

            // writing the final pixel color
            write_color(fout, pixel_color);
        }
    }

}
