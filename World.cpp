#include "Camera.h"
#include "Sphere.h"
#include "World.h"

#include <fstream>
#include "vec3.h"
#include "ray.h"
#include "color.h"

using namespace std;

/* Defining the World */
World::World(vec3 _skyColor) {
    skyColor = _skyColor;
}

/* Adds the Sphere given to the vector */
void World::Add(Sphere &sphere) {
    Spheres.insert(Spheres.end(), sphere);
}

// renders the phto from the camera given
void World::Render(Camera &cam, const string &name) {
    color pixel_color;
    float dist, total;
    int k = 0, z = 0;
    bool checkDist;

    // creating the image
    fstream fout;
    fout.open(name + ".ppm", ios::out | ios::trunc);
    fout << "P3\n" << cam.getWidth() << " " << cam.getHeight() << "\n255\n";

    total = cam.getHeight() * cam.getWidth() / 100;

    // going throught all the pixels
    for (int i = 0; i < cam.getHeight(); i++) {
        for (int j = cam.getWidth(); j > 0; j--) {
            // defining the default color as the sy color
            pixel_color = this->getSkyColor();
            // generating a ray based on the pixel
            ray Photon(cam.getPos() ,cam.pixelCenter(i, j));
            // we start the check distance as false so that in the fist loop it is not checked
            checkDist = false;
            // we have to reset the distance in each loop
            dist = -1;

            for (int k = 0; k < this->Spheres.size(); k++) {
                // if the photon is not going the correct direction to begin with we skip 
                // if (Spheres[k].posX() + Spheres[k].Radius() > Photon.origin().x()) continue;
                if (Spheres[k].Hit(Photon, &dist, &checkDist)) pixel_color = Spheres[k].getColor();
            }

            // writing the final pixel color
            write_color(fout, pixel_color);

            if (z >= total) {
                k++;
                cout << "Generating " << k << "%\n";
                z = 0;
            }
            z++;
        }
    }
    cout << "Generating Done!\n";
}

