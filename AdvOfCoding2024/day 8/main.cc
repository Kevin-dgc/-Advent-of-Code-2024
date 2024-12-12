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
using namespace std;


pair<pair<int,int>,pair<int,int>> calculatePoints(int xOne, int yOne, int xTwo, int yTwo){


    int DeltaX = xTwo - xOne;
    int DeltaY = yTwo - yOne;

    if(DeltaX == 0 && DeltaY == 0){
        return {{-1,-1},{-1,-1}};
    }

    return {{xTwo + DeltaX, yTwo + DeltaY}, {xOne - DeltaX, yOne - DeltaY}};
}

vector<int> calculateLine(int xOne, int yOne, int xTwo, int yTwo){
    int DeltaX = xTwo - xOne;
    int DeltaY = yTwo - yOne;

    if(DeltaX == 0 && DeltaY == 0){
        return {-1};
    }
    
    vector<int> results = {
        {1, DeltaX, DeltaY}
    };

    return results;
}

int adv(vector<vector<char>> grid){
    // for (const auto& row : grid) {
    //     for (const auto& cell : row) {
    //         cout << cell;
    //     }
    //     cout << endl;
    // }
    // cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

    vector<vector<char>> newGrid = grid;

    for(int rowOut = 0; rowOut < grid.size(); rowOut++){
        for(int colOut = 0; colOut < grid[rowOut].size(); colOut++){
            char cur = grid[rowOut][colOut];
            
            if(cur != '.'){
                for(int row = 0; row < grid.size(); row++){
                    for(int col = 0; col < grid[row].size(); col++){
                        char curPointer = grid[row][col];

                        if(cur == curPointer){
                            pair<pair<int,int>,pair<int,int>> twoPoints = calculatePoints(colOut, rowOut, col, row);
                            int ptrOneX = twoPoints.first.first;
                            int ptrOneY = twoPoints.first.second;

                            int ptrTwoX = twoPoints.second.first;
                            int ptrTwoY = twoPoints.second.second;
\
                            

                            // checks if ptr One is in bound of NewGrid
                            if(ptrOneY < newGrid.size() && ptrOneY >= 0 && ptrOneX < newGrid[ptrOneY].size() && ptrOneX >= 0){
                                //cout << "Y: " << ptrOneY << " X: " << ptrOneX << endl;
                                newGrid[ptrOneY][ptrOneX] = '#';
                            }

                            if(ptrTwoY < newGrid.size() && ptrTwoY >= 0 && ptrTwoX < newGrid[ptrTwoY].size() && ptrTwoX >= 0){
                                //cout << "Y: " << ptrTwoY << " X: " << ptrTwoX << endl;
                                newGrid[ptrTwoY][ptrTwoX] = '#';
                            }
                        }
                    }
                }
            }
        }
    }

    int sum = 0;
    for (int row = 0; row < newGrid.size(); row++) {
        for (int col = 0; col < newGrid[row].size(); col++) {
            if(newGrid[row][col] == '#'){
                sum++;
            }
            cout << newGrid[row][col];
        }
        cout << endl;
    }

    return sum;
}

int adv2(vector<vector<char>> grid){
    // for (const auto& row : grid) {
    //     for (const auto& cell : row) {
    //         cout << cell;
    //     }
    //     cout << endl;
    // }
    // cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

    vector<vector<char>> newGrid = grid;

    for(int rowOut = 0; rowOut < grid.size(); rowOut++){
        for(int colOut = 0; colOut < grid[rowOut].size(); colOut++){
            char cur = grid[rowOut][colOut];
            
            if(cur != '.'){
                int sum = 0;
                for(int row = 0; row < grid.size(); row++){
                    for(int col = 0; col < grid[row].size(); col++){
                        char curPointer = grid[row][col];

                        if(cur == curPointer){
                            sum++;
                            vector<int> slope = calculateLine(colOut, rowOut, col, row);
                            bool running = true;

                            if(slope[0] != -1){
                                int ptrOneX = col + slope[1];
                                int ptrOneY = row + slope[2];

                                int ptrTwoX = colOut - slope[1];
                                int ptrTwoY = rowOut - slope[2];

                                while(running){
                                    running = false;
                                    // checks if ptr One is in bound of NewGrid
                                    if(ptrOneY < newGrid.size() && ptrOneY >= 0 && ptrOneX < newGrid[ptrOneY].size() && ptrOneX >= 0){
                                        //cout << "Y: " << ptrOneY << " X: " << ptrOneX << endl;
                                        running = true;
                                        //if(grid[ptrOneY][ptrOneX] == '.'){
                                            newGrid[ptrOneY][ptrOneX] = '#';
                                        //}
                                    }

                                    if(ptrTwoY < newGrid.size() && ptrTwoY >= 0 && ptrTwoX < newGrid[ptrTwoY].size() && ptrTwoX >= 0){
                                        //cout << "Y: " << ptrTwoY << " X: " << ptrTwoX << endl;
                                        running = true;
                                        //if(grid[ptrTwoY][ptrTwoX] == '.'){
                                            newGrid[ptrTwoY][ptrTwoX] = '#';
                                        //}
                                    }

                                    ptrOneX += slope[1];
                                    ptrOneY += slope[2];
                                    ptrTwoX -= slope[1];
                                    ptrTwoY -= slope[2];
                                }
                            }
                        }
                    }
                }
                    if(sum >= 2){
                        newGrid[rowOut][colOut] = '#';
                    }
            }
        }
    }

    int sum = 0;
    for (int row = 0; row < newGrid.size(); row++) {
        for (int col = 0; col < newGrid[row].size(); col++) {
            if(newGrid[row][col] == '#'){
                sum++;
            }
            cout << newGrid[row][col];
        }
        cout << endl;
    }

    return sum;
}


int main(){
    //ifstream file("test.txt"); 
    ifstream file("data.txt"); 
    if (!file) {
        cerr << "shit" << endl;
        return -1;
    }

    vector<vector<char>> Grid;
    string line; 

    // Read the file line by line
    while (getline(file, line)) {
        vector<char> row(line.begin(), line.end());
        Grid.push_back(row);
    }

    file.close();

    for (int row = 0; row < Grid.size(); row++){
        Grid[row].pop_back();
    }

    // int xOne = 2, yOne = 3, xTwo = 4, yTwo = 3;
    //int xOne = -5, yOne = 6, xTwo = 2, yTwo = 3;
    // pair<pair<int,int>,pair<int,int>> result = calculatePoints(xOne, yOne, xTwo, yTwo);
    // cout << "ptr 3: (" << result.first.first << ", " << result.first.second << ")\n";
    // cout << "ptr 4: (" << result.second.first << ", " << result.second.second << ")\n";

    int dis = adv2(Grid);
    //int dis = adv(Grid);

    cout << "dis " << dis << endl;
    // idk why but its always missing the bottom right char
    // so if dis isnt correct than dis++ is correct
    // for test case and data you need ++
    // this is for adv and adv2

    return 0;
}