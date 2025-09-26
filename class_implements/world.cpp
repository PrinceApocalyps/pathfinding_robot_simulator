#include "../class_headers/robot.h"
#include "../class_headers/point.h"
#include "../class_headers/world.h"
#include <vector>
#include <iostream>

world::world(){
    Size = 10;
    world_cell.resize(Size, std::vector<point>(Size));
    robot roomba;

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

//helper functions
void world::displayWorld(int row, int col, int num_coins){
    bool coinFound = false;

    for(int i=0; i<Size; i++){
        for(int j=0; j<Size; j++){
            bool isCoin = false;
            bool isRobot = (i==row && j==col);

            //check if a coin is at this position
            for (int k = 0; k < Coins.size(); ++k) {
                if (Coins[k].getX() == i && Coins[k].getY() == j) {
                    isCoin = true;
                    if (isRobot && isCoin) {
                        coinFound = true;
                        // Swap with last and pop_back for fast removal
                        std::swap(Coins[k], Coins.back());
                        Coins.pop_back();
                    }
                    break;  // stop after first coin found
                }
            }





            // Determine what to print in the cell
            if (isRobot || coinFound) {
                std::cout << "🤖";
                coinFound = false;
            } else if (isCoin) {
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
