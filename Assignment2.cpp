/**
 * @file Assignment2.cpp
 *  
 * @brief Assignment 2 - HY-150
 * 
 * @author: CSD5449
 */

#include "functions.h"

int main() {
    /**
     * @param userInp: the raw input from the user read as a string so that it can be checked for errors
     * @param inputLoc: if the input will come from the terminal (1) or from a file(2)
     * @param isFile: if the input is from a file, usefull for error checking
    */
    int inputLoc, width, height, numSpheres;
    string userInp, imName;
    vec3 camPos, skyColour, sphereColor, spherePos;
    float sphereRadius;
    
    // making the menu
    cout << "Should the input be taken from: \n\t1) Terminal\n\t2) File\n";
    cin >> userInp;
    inputLoc = readInt(userInp, 1, 2, false, true, true);

    if (inputLoc == 1) { // the input comes from the terminal
        cout << "Give image name (no need to add .ppm): ";
        cin >> imName;

        cout << "Give cammera possition\n";
        cout << "X: ";
        cin >> userInp;
        camPos[0] = readFLoat(userInp, 0, 0, false, false, false);
        cout << "Y: ";
        cin >> userInp;
        camPos[1] = readFLoat(userInp, 0, 0, false, false, false);
        cout << "Z: ";
        cin >> userInp;
        camPos[2] = readFLoat(userInp, 0, 0, false, false, false);

        cout << "Give image width: ";
        cin >> userInp;
        width = readInt(userInp, 0,0, false, true, false);

        cout << "Give image height: ";
        cin >> userInp;
        height = readInt(userInp, 0,0, false, true, false);

        Camera cam(camPos, width, height);

        cout << "Give sky color\n";
        cout << "R: ";
        cin >> userInp;
        skyColour[0] = readFLoat(userInp, 0, 1, false, true, true);
        cout << "G: ";
        cin >> userInp;
        skyColour[1] = readFLoat(userInp, 0, 1, false, true, true);
        cout << "B: ";
        cin >> userInp;
        skyColour[2] = readFLoat(userInp, 0, 1, false, true, true);

        World world(skyColour);

        cout << "Give number of spheres: ";
        cin >> userInp;
        numSpheres = readInt(userInp, 0,0, false, true, false);

        for (int i = 1; i <= numSpheres; i++) {
            cout << "For shpere no" << i << ":\n";
            cout << "Give sphere Color\n";
            cout << "R: ";
            cin >> userInp;
            sphereColor[0] = readFLoat(userInp, 0, 1, false, true, true);
            cout << "G: ";
            cin >> userInp;
            sphereColor[1] = readFLoat(userInp, 0, 1, false, true, true);
            cout << "B: ";
            cin >> userInp;
            sphereColor[2] = readFLoat(userInp, 0, 1, false, true, true);

            cout << "Give sphere possition\n";
            cout << "X: ";
            cin >> userInp;
            spherePos[0] = readFLoat(userInp, 0, 0, false, false, false);
            cout << "Y: ";
            cin >> userInp;
            spherePos[1] = readFLoat(userInp, 0, 0, false, false, false);
            cout << "Z: ";
            cin >> userInp;
            spherePos[2] = readFLoat(userInp, 0, 0, false, false, false);

            cout << "Give Sphere radius: ";
            cin >> userInp;
            sphereRadius = readFLoat(userInp, 0,0,false, true, false);

            Sphere tmp(spherePos, sphereColor, sphereRadius);
            world.Add(tmp);
        }
        world.Render(cam);
    }

    
}