#include "../class_headers/robot.h"
#include "../class_headers/point.h"
#include "../class_headers/world.h"
#include <iostream>

robot::robot() {}

// Initializes the robot at (0,0) facing EAST
void robot::init(){
    location.set(0,0);
    orientation = East;
}

// Prints robot's current location and orientation
void robot::print(){
    std::cout << "location: " << location.getX() << "," << location.getY()
              << "  Orientation: ";
    switch (orientation){
    case North:
        std::cout << "North\n";
        break;
    case South:
        std::cout << "South\n";
        break;
    case East:
        std::cout << "East\n";
        break;
    case West:
        std::cout << "West\n";
        break;
    }
}

//getter functions
int robot::getRow(){
    return location.getX();
}
int robot::getCol(){
    return location.getY();
}


// Set orientation
void robot::setOrientation(orientation_type orientation){
    this->orientation = orientation;
}


// Move forward one step (if not at edge)
bool robot::forward(){
    int row = location.getX();
    int col = location.getY();

    switch (orientation) {
    case North:
        if (!northEnd()) { location.set(row-1, col); return true; }
        break;
    case East:
        if (!eastEnd()) { location.set(row, col+1); return true; }
        break;
    case South:
        if (!southEnd()) { location.set(row+1, col); return true; }
        break;
    case West:
        if (!westEnd()) { location.set(row, col-1); return true; }
        break;
    }
    return false; // hit edge
}

// Turn clockwise
void robot::turnCW(){
    switch (orientation) {
    case North:
        setOrientation(East);
        break;
    case East:
        setOrientation(South);
        break;
    case South:
        setOrientation(West);
        break;
    case West:
        setOrientation(North);
        break;
    }

}

// Turn anti-clockwise
void robot::turnAntiCW(){

    switch (orientation) {
    case North:
        setOrientation(West);
        break;
    case East:
        setOrientation(North);
        break;
    case South:
        setOrientation(East);
        break;
    case West:
        setOrientation(South);
        break;
    }
}

// Check edges of the world
bool robot::eastEnd(){
    return location.getY()==9;
}
bool robot::westEnd(){
    return location.getY()==0;
}
bool robot::northEnd(){
    return location.getX()==0;
}
bool robot::southEnd(){
    return location.getX()==9;
}

// Zig-zag movement helpers
bool robot::zag(){
    // reached east edge
    if(eastEnd()){
        turnCW();
        forward();
        turnCW();
        return true;
    }
    return false;
}


bool robot::zig(){
    // reached west edge
    if(westEnd()){
        turnAntiCW();
        forward();
        turnAntiCW();
        return true;
    }
    return false;
}
