#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include "point.h"

class world
{
private:
    int Size;
    std::vector<std::vector<point>> world_cell;
    std::vector<point> Coins;

public:
    world();

    //setter functions
    void set(int i, int x, int y);

    //getter fucntions
    int getSize();
    int getNumCoins();


    //helper functions
    void displayWorld(int,int,int);
    void print() const;
};

#endif // WORLD_H
