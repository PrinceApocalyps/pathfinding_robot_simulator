#ifndef SIMANNELING_H
#define SIMANNELING_H

#include "../class_headers/point.h"
#include <vector>
#include <random>


class SimAnneling
{
private:
    //SA parameters
    double intialTemp;
    double coolingRate;
    int maxIterations;

    //start position
    point start;

    // Random number generation
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> prob_dist;


    std::vector<point> currentTrip;
    int currentCost;

    std::vector<point> bestTrip;
    int bestCost;


    //****************************Helper functions*********************

    //calculate the manhattan distance between 2 nodes/points
    int calcDist(point &p1, point &p2);
    //calculate the total trip distance
    int calcTripDist(std::vector<point> &Trip);
    //calculate swap delta
    //probability of accepting a move
    bool acceptMove(int costDiff, double temp);


public:
    //constructors
    SimAnneling();
    SimAnneling(double intialTemp, double coolingRate, int maxIterations);

    void optimize(const std::vector<point> &coins, const point &startPos);

    //parameter setters
    void setInitTemp(double temp);
    void setCoolingRate(double rate);
    void setMaxIteration(int max);

    //parameter getters
    double getInitTemp();
    double getCoolingTemp();
    int getMaxIterations();
    std::vector<point> getBestTrip();
};

#endif // SIMANNELING_H
