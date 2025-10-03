#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <random>
#include "./class_headers/robot.h"
#include "./class_headers/point.h"
#include "./class_headers/world.h"

using namespace std;



// Generate n random coins
void placeRandomCoins(world& grassland, int N) {
    std::random_device rd;   // Seed
    std::mt19937 gen(rd());  // Mersenne Twister RNG
    std::uniform_int_distribution<> dist(0, grassland.getSize() - 1);

    for (int i = 0; i < N; i++) {
        int x = dist(gen);
        int y = dist(gen);
        grassland.set(i, x, y);
    }
}


int main(int argc, char* argv[]) {

    vector<int> num(argc-1);
    //vector<point> point_coin(argc/2);
    world grassland;

    if (argc == 1) {
        cout << "No Argument: Generating random coins\n"
             << "Number of Random coins: Enter number (0-10)" << endl;
        int N;
        std::cin >> N;
        placeRandomCoins(grassland, N);

    }else{
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
        grassland.printCoinXY();

    }





    int total = grassland.getNumCoins();
    int moves = 0;
    grassland.pathfinder();
    //grassland.printTrip();

    while(grassland.getNumCoins()>0){
        moves++;
        std::cout << "\033[2J\033[1;1H";//clear screen
        std::cout << "Total number of coins: " << total << std::endl;
        grassland.printTrip();
        grassland.simulatePathFinder(total);

        std::cout<< "Number of Moves: " << moves << std::endl;
        //grassland.printCoinXY();

        //grassland.greedyRSim(total);

    }

    return 0;
}
