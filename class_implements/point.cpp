#include "../class_headers/point.h"
#include <iostream>

point::point() {}

//setter functions
void point::set(int x, int y){
    this->x = x;
    this->y = y;
}

void point::setX(int x){
    this->x = x;
}
void point::setY(int y){
    this->y = y;
}

//getter functions
int point::getX(){return x;}
int point::getY(){return y;}


//helper function
void point::print() const{
    std::cout << "(x,y) = " << x << ", " << y << std::endl;
}
