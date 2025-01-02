#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include <limits>
#include <fstream>
#include <utility>
#include <cctype>
#include <sstream> 
#include <queue>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <numeric>
#include <functional>
#include <cmath>
#include <bitset>
#include <random>
#include <chrono>
using namespace std;






int adv(vector<vector<char>>& grid, int row, int col, int steps, int direction){
    // start location is gird.size()-2, 1 with 'S'
    // end location is 1, grid[0].size()-2 with 'E
    // 1 up, 2 down, 3 left, 4 right
    //'.' open space, # wall, all edges are #

    // check up
    if(grid[row-1][col] == '.'){
        int dr = 0;
        if(direction == 1){
            dr = 1; // 0 degree turn
        }
        if(direction == 2){
            dr = 2000; // two 90 degree turns
        }
        if(direction == 3){
            dr = 1000; // one 90 degree turn
        }
        if(direction == 4){
            dr = 1000; // one 90 degree turn
        }

        return adv(grid, row-1, col, steps+1, 1) + dr;
    }
    // check down
    if(grid[row+1][col] == '.'){
        int dr = 0;
        if(direction == 1){
            dr = 2000; // two 90 degree turns
        }
        if(direction == 2){
            dr = 1; // 0 degree turn
        }
        if(direction == 3){
            dr = 1000; // one 90 degree turn
        }
        if(direction == 4){
            dr = 1000; // one 90 degree turn
        }
        return adv(grid, row+1, col, steps+1, 2) + dr;
    }
    // check left
    if(grid[row][col-1] == '.'){
        int dr = 0;
        if(direction == 1){
            dr = 1000; // one 90 degree turn
        }
        if(direction == 2){
            dr = 1000; // one 90 degree turn
        }
        if(direction == 3){
            dr = 1; // 0 degree turn
        }
        if(direction == 4){
            dr = 2000; // two 90 degree turns
        }
        return adv(grid, row, col-1, steps+1, 3) + dr;
    }
    // check right
    if(grid[row][col+1] == '.'){
        int dr = 0;
        if(direction == 1){
            dr = 1000; // one 90 degree turn
        }
        if(direction == 2){
            dr = 1000; // one 90 degree turn
        }
        if(direction == 3){
            dr = 2000; // two 90 degree turns
        }
        if(direction == 4){
            dr = 1; // 0 degree turn
        }
        return adv(grid, row, col+1, steps+1, 4) + dr;
    }


    





}


vector<vector<char>> parse(string filename){
    ifstream file(filename);
    vector<vector<char>> grid;

    if(!file.is_open()){
        cout << "FUCK ERROR OPENING FILE" << endl;
        return grid;
    }

    string line;
    while(getline(file, line)){
        if(!line.empty()){
            vector<char> row(line.begin(), line.end());
            grid.push_back(row);
        }
    }

    file.close();
    return grid;
}

int main(){
   vector<vector<char>> grid = parse("test.txt");

    // prints out gird
    cout << "grid: " << endl;
    for(auto row: grid){
        for(auto c : row){
            cout << c << " ";
        }
        cout << endl;
    }

    // int Answer = adv(grid, grid.size()-2, 1, 0, 0);
    // cout << "Answer " << Answer << endl;
    return 1;
}