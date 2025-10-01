#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include "../class_headers/point.h"
#include "../class_headers/robot.h"

class world
{
private:
    int Size;
    robot cooper;
    std::vector<std::vector<point>> world_cell;
    std::vector<point> Coins;

public:
    world();

    //setter functions
    void set(int i, int x, int y);

    //getter fucntions
    int getSize();
    int getNumCoins();

    void greedyRSim(int totalCoins);

    //helper functions
    bool isCoin(int row, int col);
    bool pickupCoin(int row, int col);
    point nearestCoin();
    int abs(int x);
    void displayWorld(int);
    void print() const;
};

#endif // WORLD_H
