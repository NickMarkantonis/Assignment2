#include "Camera.h"
#include "Sphere.h"
#include "World.h"

#include <fstream>
#include "vec3.h"
#include "ray.h"
#include "color.h"

using namespace std;

// Defining the World
World::World(vec3 _skyColor) {
    skyColor = _skyColor;
}

// Adding a sphere to the world vector
void World::Add(Sphere &sphere) {
    Spheres.push_back(sphere);
}

// renders the photo from the camera given
void World::Render(Camera &cam, const string &name) {
    /** variable meaning:
     * @param pixel_color: the color the pixel will have, is used with the function write_color
     * @param dist: the shortest hit ditance yet for each pixel, gets reset in wvery loop
     * @param total: the total amount of pixels divided by 100, will be used to print the progres of the generation
     * @param k,z: two temp variables that are used in the progres print out
     * @param checkDist: whether or not to check the distance of the current sphere, the first loop id false and from there on it's true
     */
    color pixel_color;
    double dist, total;
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
                if (Spheres[k].Hit(Photon, &dist, &checkDist)) pixel_color = Spheres[k].getColor();
            }

            // writing the final pixel color
            write_color(fout, pixel_color);

            // printing the generating progress
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

