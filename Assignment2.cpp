/**
 * @file Assignment2.cpp
 *  
 * @brief Assignment 2 - HY-150
 * 
 * @author: CSD5449
 */

#include "std_lib_facilities.h"
#include "ClassesDef.h"
#include "color.h"

#include <iostream>
#include <fstream>

int main() {
    vec3 pos(0,0,0);
    vec3 colour(1,0,0);
    float radius = 1.0;
    Sphere sphere(pos, colour, radius);

    double dist = 100;

    fstream fout;
    fout.open("image.ppm", ios::out | ios::trunc);
    fout << "P3\n" << 1920 << " " << 1080 << "\n255\n";

    Camera cam(vec3(5,0,0), 1920, 1080);

    for (int i = 1; i <= 1080; i++) {
        for (int j = 1; j <= 1920; j++) {
            vec3 tmp = cam.GetPixelCenter(j,i);
            ray Ray(vec3(5,0,0), tmp);
            color pixel_colour;
            bool doesHit = sphere.Hit(Ray, dist);
            if (sphere.Hit(Ray, dist)) pixel_colour = color(1,0,0);
            else pixel_colour = color(0,0,.5);

            if (i == 540 || j == 960) pixel_colour = color(0,0,0);

            write_color(fout, pixel_colour);
        }
    }

}