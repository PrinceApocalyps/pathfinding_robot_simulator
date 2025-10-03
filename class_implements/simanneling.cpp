#include "simanneling.h"
#include <cmath>
#include <algorithm>
#include <iostream>


SimAnneling::SimAnneling()
    :gen(rd()),
    prob_dist(0.0, 1.0)

{
    intialTemp = 1000.0;
    coolingRate=0.995;
    maxIterations = 10000;

}

SimAnneling::SimAnneling(double intialTemp, double coolingRate, int maxIterations)
:gen(rd()),
    prob_dist(0.0, 1.0)
{
    this -> intialTemp = intialTemp;
    this -> coolingRate=coolingRate;
    this -> maxIterations = maxIterations;
}

//calculate the manhattan distance between 2 nodes/points
int SimAnneling::calcDist(point &p1, point &p2){
    return std::abs(p1.getX()-p2.getX())+std::abs(p1.getY()-p2.getY());
}


//calculate the total trip distance
int SimAnneling::calcTripDist(std::vector<point> &Trip){
    if(Trip.empty()) return 0;

    int totalDist = 0;
    //Distance form robot to coin 1;
    totalDist += calcDist(start, Trip[0]);

    //Distance betwween consecutive coins
    for (int i =0; i < Trip.size()-1; i++){
        totalDist += calcDist(Trip[i],Trip[i+1]);
        }

    return totalDist;

}
//calculate swap delta
//probability of accepting a move
bool SimAnneling::acceptMove(int costDiff, double temp){
    if (costDiff < 0){
        return true;
    }

    double acceptProb = std::exp(-costDiff/temp);
    return prob_dist(gen) < acceptProb;
}

//main algorithm

void SimAnneling::optimize(const std::vector<point> &coins, const point &startPos){
    if(coins.empty()){
      bestTrip.clear();
        return;
    }

    start = startPos;

    //random initial start
    currentTrip = coins;
    std::shuffle(currentTrip.begin(), currentTrip.end(), gen);
    currentCost = calcTripDist(currentTrip);

    //initialize best solution
    bestTrip = currentTrip;
    bestCost = currentCost;

    double temp = intialTemp;
    std::uniform_int_distribution<> indexDist(0, currentTrip.size() - 1);

    //main Loop
    for (int iterations=0; iterations <  maxIterations; iterations++){
        int i = indexDist(gen);
        int j = indexDist(gen);

        //create alt trip
        std::vector<point> altTrip = currentTrip;
        std::swap(altTrip[i],altTrip[j]);

        int altCost = calcTripDist(altTrip);

        int costDiff = altCost - currentCost;

        //accept trip
        if (acceptMove(costDiff, temp)) {
            currentTrip = altTrip;
            currentCost = altCost;

            if (currentCost < bestCost) {
                bestTrip = currentTrip;
                bestCost = currentCost;
            }
        }



        temp *= coolingRate;
        if (temp < 1e-6) break; // stop when "frozen"
    }

}


//parameter setters
void SimAnneling::setInitTemp(double temp){
    intialTemp = temp;
}
void SimAnneling::setCoolingRate(double rate){
    coolingRate = rate;
}
void SimAnneling::setMaxIteration(int max){
    maxIterations = max;
}

//parameter getters
double SimAnneling::getInitTemp(){
    return intialTemp;
}
double SimAnneling::getCoolingTemp(){
    return coolingRate;
}
int SimAnneling::getMaxIterations(){
    return maxIterations;
}
std::vector<point> SimAnneling::getBestTrip(){
    return bestTrip;
}

