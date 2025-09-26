#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <chrono>
#include <thread>
#include "./class_headers/robot.h"
#include "./class_headers/point.h"
#include "./class_headers/world.h"

using namespace std;

int main(int argc, char* argv[]) {

    vector<int> num(argc-1);
    //vector<point> point_coin(argc/2);
    world grassland;
    robot cooper;

    if (argc == 1) {
        cout << "Please enter the locations of the coins (0-9)." << endl;
        return 1; // exit early if no arguments
    }


    cout << "Number of arguments: " << argc << endl;

    for (int i = 1; i < argc; i++) {  // start at 1 to skip program name
        cout << "Argument " << i << ": " << argv[i] << "    ";

        int j = i-1;
        try {
            num[j] = stoi(argv[i]); // convert string to int

            // check if num is between 0 and 9
            if ((num[j] < 0 )||( num[j] > 9)) {
                cout << "Error: value " << num[j] << " is out of range (0-9)." << endl;
                return 1;
            }

            cout << "Value " << num[j] << " is valid." << endl;

        } catch (invalid_argument& e) {
            cout << "Error: '" << argv[i] << "' is not a valid number." << endl;
            return 1;
        } catch (out_of_range& e) {
            cout << "Error: '" << argv[i] << "' is out of int range." << endl;
            return 1;
        }
    }


    for (int i = 0; (i < (argc-1)/2); i++) {

        grassland.set(i,num[2*i],num[(2*i)+1] );
    }
    grassland.print();


    cooper.init();
    do {
        std::cout << "\033[2J\033[1;1H";
        if(cooper.forward()){
            //cooper.print();
            grassland.displayWorld(cooper.getRow(), cooper.getCol(),(argc-1)/2);
            if(grassland.getNumCoins()==0){
                std::cout << "All Coins Found!!" << std::endl;
                return 1;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        } else if(cooper.zag()){
            //cooper.print();
            grassland.displayWorld(cooper.getRow(), cooper.getCol(),(argc-1)/2);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        } else {
            cooper.zig();
            //cooper.print();
            grassland.displayWorld(cooper.getRow(), cooper.getCol(),(argc-1)/2);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    } while(!cooper.westEnd() || !cooper.southEnd());



    return 0;
}

