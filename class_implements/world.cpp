#include "../class_headers/robot.h"
#include "../class_headers/point.h"
#include "../class_headers/world.h"
#include <chrono>
#include <thread>
#include <vector>
#include <iostream>

world::world(){
    Size = 10;
    world_cell.resize(Size, std::vector<point>(Size));
    cooper.init();

    //Fill each point with its (i,j) coordinates
    for (int i = 0; i < Size; i++){
        for (int j = 0; j<Size; j++){
            world_cell[i][j].set(i,j);
        }
    }
}

//setter functions
void world::set(int i, int x, int y){

    Coins.resize(i+1);
    Coins[i].set(x, y);
}


//getter fucntions
int world::getSize(){
    return Size;
}
int world::getNumCoins(){
    return Coins.size();
}

void world::greedyRSim(int totalCoins){
    cooper.moveToward(nearestCoin());
    displayWorld(totalCoins);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

//*******************helper functions

//check for coin
bool world::isCoin(int row, int col){
    //check if a coin is at this position
    for (int k = 0; k < Coins.size(); ++k) {
        if (Coins[k].getX() == row && Coins[k].getY() == col) {
            return true;
        }
    }
    return false;
}

//remove coin
bool world::pickupCoin(int row, int col){
    //check if a coin is at this position
    for (int k = 0; k < Coins.size(); ++k) {
        if (Coins[k].getX() == row && Coins[k].getY() == col) {
            if (cooper.getRow()==row && cooper.getCol()==col) {
                // Swap with last and pop_back for fast removal
                std::swap(Coins[k], Coins.back());
                Coins.pop_back();
                return true;
            }
        }
    }
    return false;
}

//find the nearest coin
point world::nearestCoin(){
    int mindist = 1000;
    point nearest;
    for ( auto &c : Coins) {
        int dist = abs((c.getX() - cooper.getRow())) + abs((c.getY()-cooper.getCol()));
        if(mindist>dist){
            mindist = dist;
            nearest = c;
        }
    }

    return nearest;

}

int world::abs(int x){
    if (x<0){
        return -x;
    }else{
        return x;
    }
}

void world::displayWorld(int num_coins){


    for(int i=0; i<Size; i++){
        for(int j=0; j<Size; j++){
            bool hereCoin = false;
            bool isRobot = (i==cooper.getRow() && j==cooper.getCol());


            hereCoin = isCoin(i,j);
            bool coinFound = pickupCoin(i,j);

            // Determine what to print in the cell
            if (isRobot || coinFound) {
                std::cout << "🤖";

            } else if (hereCoin) {
                std::cout << "💰";
            } else {
                // Use "__" for most columns, "  " for the last column
                //std::cout << (i != Size - 1 ? "__" : "  ");
                std::cout << "⬜";
            }

            // Print the column separator if not the last column
            //if (j != Size - 1) std::cout << "|";
        }
        std::cout << std::endl;
    }
    //std::cout << "Total Coins: " << getNumCoins() << std::endl;
    std::cout << "Coins Found: " << num_coins - getNumCoins() << std::endl;
}


void world::print() const{
    for(int i = 0; i<Coins.size();i++){
        std::cout<<"Coin no. " << i+1;
        Coins[i].print();
    }
}
