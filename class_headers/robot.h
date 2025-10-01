#ifndef ROBOT_H
#define ROBOT_H

#include "../class_headers/point.h"      // project header
#include <iostream>     // standard library header

class robot
{
private:
    char orientation;
    point location;

public:
    // enumarated data type
    enum orientation_type {North, South, East, West};

    robot();

    // Initializes the robot at (0,0) facing EAST
    void init();

    // Prints robot's current location and orientation
    void print();

    //getter functions
    int getRow();
    int getCol();


    // Set orientation
    void setOrientation(orientation_type orientation);

    //movement toward the nearest
    bool moveToward(point target);

    // Move forward one step (if not at edge)
    bool forward();

    // Turn clockwise
    void turnCW();

    // Turn anti-clockwise
    void turnAntiCW();

    // Check edges of the world
    bool eastEnd();
    bool westEnd();
    bool northEnd();
    bool southEnd();

    // Zig-zag movement helpers
    bool zag();  // reached east edge
    bool zig();  // reached west edge

};

#endif // ROBOT_H
