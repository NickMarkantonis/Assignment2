#include "std_lib_facilities.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"

#include "Sphere.h"
#include "World.h"
#include "Camera.h"

#pragma once

// classes will be used for error handling
class notInt {};
class notFloat {};
class wrongInput {};

// checks if a string is a int
bool isInt(string inp) {
    char *p;
    strtol(inp.c_str(), &p, 10);
    return (*p == 0);
}

/** 
 * Takes a string as a parameters representing the raw input from the user, checks for possible faults and calls to read again in case of error
 * if the input is comming from a file the program closes as it cannot re read the input 
 * 
 * @param isFile: in case it's true, whenever wrong input is given the program stops
 * 
 * @param checkInpMin: whether to make sure the number is smaller then the min
 * @param checkInpMax: whether to make sure the number is smaller then the max
 */
int readInt(string inp, int min, int max, bool isFile, bool checkInpMin, bool checkInpMax) {
    /**
     * @param correctInp: if the input is correct, used in the while loop
    */
    bool correctInp = false;
    int num;

    while (!correctInp) {
        try {
            // in case the input is not a int
            if (!isInt(inp)) throw notInt();
            num = stoi(inp);

            if (checkInpMin && num < min) throw wrongInput();
            if (checkInpMax && num > max) throw wrongInput();

            correctInp = true;
        }
        catch (notInt&b) {
            if (isFile) exit(1);
            cout << "input must be integer";
            if (isFile) exit(1);
            cout << ", please enter again:  ";
            cin >> inp;
        }
        catch (wrongInput&b) {
            cout << "input must be";
            if (checkInpMax && checkInpMin) cout << "between " << min << " and " << max;
            else if (checkInpMax) cout << "smaller then " << max;
            else if (checkInpMin) cout << "bigger then " << min;
            if (isFile) exit(1);
            cout << ", please enter again:  ";
            cin >> inp;
        }
    }
    return num;
}

// checks if string is float
bool isFloat(string inp, float *f) {
    bool isfloat;
    istringstream iss(inp);
    iss >> noskipws >> *f;
    isfloat = iss.eof() && !iss.fail();
    return isfloat;
}

// same as in readInt but for floats
float readFLoat(string inp, float min, float max, bool isFile, bool checkInpMin, bool checkInpMax) {
    bool correctInp = false;
    float num;

    while (!correctInp) {
        try {
            if (!isFloat(inp, &num)) throw notFloat();

            if (checkInpMin && num < min) throw wrongInput();
            if (checkInpMax && num > max) throw wrongInput();

            correctInp = true;
        }
        catch (notFloat&b) {
            if (isFile) exit(1);
            cout << "input must be float";
            if (isFile) exit(1);
            cout << ", please enter again:  ";
            cin >> inp;
        }
        catch (wrongInput&b) {
            cout << "input must be";
            if (checkInpMax && checkInpMin) cout << "between " << min << " and " << max;
            else if (checkInpMax) cout << "smaller then " << max;
            else if (checkInpMin) cout << "bigger then " << min;
            if (isFile) exit(1);
            cout << ", please enter again:  ";
            cin >> inp;
        }
    }
    return num;
}

