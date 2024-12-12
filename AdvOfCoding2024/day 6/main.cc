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
#include <thread> 
#include <chrono>
using namespace std;

// move the guard until it goes out of bound of map, row or col min or max
// move fowards if one dirctionNext exist && if next is not #, 
// if dirctionNext DNE then end it
// if next is not # then change directionNext by right, (N, S, E ,W) N->E->S->W->N
// count next time that it moves one spot

int adv(vector<vector<char>> myMap){
    char nextDirection = '^';
    int row = 0, col = 0;


    for(int firstRow = 0; firstRow < myMap.size(); firstRow++){
        for(int firstCol = 0; firstCol < myMap[firstRow].size(); firstCol++){
            char curPlace = myMap[firstRow][firstCol];
            if(curPlace == '>'){
                nextDirection = '>';
                row = firstRow;
                col = firstCol;
                break;
            }
            else if(curPlace == 'v'){
                nextDirection = 'v';
                row = firstRow;
                col = firstCol;
                break;
            }
            else if(curPlace == '<'){
                nextDirection = '<';
                row = firstRow;
                col = firstCol;
                break;
            }
            else if(curPlace == '^'){
                nextDirection = '^';
                row = firstRow;
                col = firstCol;
                break;
            }
        }
    }

    bool running = true;

    while(running){
        //std::this_thread::sleep_for(std::chrono::milliseconds(100));

        //cout << "row: " << row << ", col: " << col << ", direction: " << nextDirection << ", sum: " << sum << endl;
        //char curPlace = myMap[row][col];

        if(nextDirection == '^'){
            if(row-1 >= 0){
                // next spot is in map
                if(myMap[row-1][col] != '#'){
                    // empty space so move and inc count
                    row--;
                    myMap[row][col] = 'X';
                }
                else if(myMap[row-1][col] == '#'){
                    nextDirection = '>';
                }
            }
            else if (row-1 < 0){
                running = false;
            }
        }
        else if(nextDirection == '>'){
            if(col+1 < myMap[row].size()){
                // next spot is in map
                if(myMap[row][col+1] != '#'){
                    col++;
                    myMap[row][col] = 'X';
                }
                else if(myMap[row][col+1] == '#'){
                    nextDirection = 'v';
                }
            }
            else{
                running = false;
            }
        }
        else if(nextDirection == 'v'){
            if(row+1 < myMap.size()){
                // next spot is in map
                if(myMap[row+1][col] != '#'){
                    row++;
                    myMap[row][col] = 'X';
                }
                else if(myMap[row+1][col] == '#'){
                    nextDirection ='<';
                }
            }
            else{
                running = false;
            }
        }
        else if(nextDirection == '<'){
            if(col-1 >= 0){
                // next spot is in map
                if(myMap[row][col-1] != '#'){
                    col--;
                    myMap[row][col] = 'X';
                }
                else if(myMap[row][col-1] == '#'){
                    nextDirection = '^';
                }
            }
            else{
                running = false;
            }
        }
        else{
            running = false;;
        }
    }


    int sum = 0;
    for(int x = 0; x < myMap.size(); x++){
        for(int y = 0; y < myMap[x].size(); y++){
            char cur = myMap[x][y];
            if(cur == 'X'){
                sum++;
            }
        }
    }

    
    return sum;
}

bool loopchecker(vector<vector<char>> myMap){
    char nextDirection = '^';
    int row = 0, col = 0;


    for(int firstRow = 0; firstRow < myMap.size(); firstRow++){
        for(int firstCol = 0; firstCol < myMap[firstRow].size(); firstCol++){
            char curPlace = myMap[firstRow][firstCol];
            if(curPlace == '>'){
                nextDirection = '>';
                row = firstRow;
                col = firstCol;
                break;
            }
            else if(curPlace == 'v'){
                nextDirection = 'v';
                row = firstRow;
                col = firstCol;
                break;
            }
            else if(curPlace == '<'){
                nextDirection = '<';
                row = firstRow;
                col = firstCol;
                break;
            }
            else if(curPlace == '^'){
                nextDirection = '^';
                row = firstRow;
                col = firstCol;
                break;
            }
        }
    }
    
    int max = myMap.size() * myMap[0].size();
    int times = 0;

    bool running = true;

    while(running){
        //std::this_thread::sleep_for(std::chrono::milliseconds(100));

        //cout << "row: " << row << ", col: " << col << ", direction: " << nextDirection << ", sum: " << sum << endl;
        //char curPlace = myMap[row][col];
        if(times > max){
            return -1;
        }

        if(nextDirection == '^'){
            if(row-1 >= 0){
                // next spot is in map
                if(myMap[row-1][col] != '#'){
                    // empty space so move and inc count
                    row--;
                    times++;
                }
                else if(myMap[row-1][col] == '#'){
                    nextDirection = '>';
                }
            }
            else if (row-1 < 0){
                running = false;
            }
        }
        else if(nextDirection == '>'){
            if(col+1 < myMap[row].size()){
                // next spot is in map
                if(myMap[row][col+1] != '#'){
                    col++;
                    times++;
                }
                else if(myMap[row][col+1] == '#'){
                    nextDirection = 'v';
                }
            }
            else{
                running = false;
            }
        }
        else if(nextDirection == 'v'){
            if(row+1 < myMap.size()){
                // next spot is in map
                if(myMap[row+1][col] != '#'){
                    row++;
                    times++;
                }
                else if(myMap[row+1][col] == '#'){
                    nextDirection ='<';
                }
            }
            else{
                running = false;
            }
        }
        else if(nextDirection == '<'){
            if(col-1 >= 0){
                // next spot is in map
                if(myMap[row][col-1] != '#'){
                    col--;
                    times++;
                }
                else if(myMap[row][col-1] == '#'){
                    nextDirection = '^';
                }
            }
            else{
                running = false;
            }
        }
        else{
            running = false;;
        }
    }

    return false;
}


int adv2(vector<vector<char>> myMap){
    int sum = 0;

    for(int row = 0; row < myMap.size(); row++){
        for(int col = 0; col < myMap[row].size(); col++){
            char og = myMap[row][col];
            if(myMap[row][col] == '#'){
                continue;
            }
            else{
                myMap[row][col] = '#';
            }

            if(loopchecker(myMap)){
                sum++;
            }

            myMap[row][col] = og;
        }
    }
    // put a box (#) in each space. After placeing it check if it loops inf
    // if it does loop inf add to sum
    // change space back to . and move to next


    return sum;
}


int main(){
    ifstream inputFile("data.txt");
    if (!inputFile) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    vector<vector<char>> Input;  // This will store the 2D grid of characters
    string line;

    // Read the file line by line
    while (getline(inputFile, line)) {
        vector<char> row;  // Temporary vector to store a row of characters
        for (char c : line) {
            row.push_back(c);  // Add each character in the line to the row vector
        }
        Input.push_back(row);  // Add the row to the 2D vector
    }

    inputFile.close();


    vector<vector<char>> TestInput = {
        {'.', '.', '.', '.', '#', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '#', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '#', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '#', '.', '.', '^', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '#', '.'},
        {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '#', '.', '.', '.'}
    };
    
    //int dis = adv2(TestInput);
    int dis = adv2(Input);

    // for (int a = 0; a < TestInput.size(); a++) {
    //     for (int b = 0; b < TestInput[a].size(); b++) {
    //         cout << TestInput[a][b] << " ";
    //     }
    //     cout << endl;
    // }


    cout << "dis " << dis << endl;
}