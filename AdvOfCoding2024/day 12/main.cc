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

int findArea(char cur, pair<int, int> pos, vector<vector<char>> grid ,map<pair<int, int>,bool>& visited){
    if(grid[pos.first][pos.second] != cur){
        visited[pos] = false;
        return 0;
    }

    int sum = 1;
    pair<int, int> up = make_pair(pos.first - 1, pos.second);
    pair<int, int> down = make_pair(pos.first + 1, pos.second);
    pair<int, int> left = make_pair(pos.first, pos.second - 1);
    pair<int, int> right = make_pair(pos.first, pos.second + 1);

    if(visited[up] == false && up.first >= 0 && up.first < grid.size() && up.second >= 0 && up.second < grid[0].size()){ 
        visited[up] = true;
        sum += findArea(cur, up, grid, visited);
    }
    if(visited[down] == false && down.first >= 0 && down.first < grid.size() && down.second >= 0 && down.second < grid[0].size()){ 
        visited[down] = true;
        sum += findArea(cur, down, grid, visited);
    }
    if(visited[left] == false && left.first >= 0 && left.first < grid.size() && left.second >= 0 && left.second < grid[0].size()){ 
        visited[left] = true;
        sum += findArea(cur, left, grid, visited);
    }
    if(visited[right] == false && right.first >= 0 && right.first < grid.size() && right.second >= 0 && right.second < grid[0].size()){ 
        visited[right] = true;
        sum += findArea(cur, right, grid, visited);
    }

    return sum;

}

int findPerimeter(char cur, pair<int, int> pos, vector<vector<char>> grid, map<pair<int, int>,bool>& visited){
    if(grid[pos.first][pos.second] != cur){
        return 1;
    }
    visited[pos] = true;

    int sum = 0;
    pair<int, int> up = make_pair(pos.first - 1, pos.second);
    pair<int, int> down = make_pair(pos.first + 1, pos.second);
    pair<int, int> left = make_pair(pos.first, pos.second - 1);
    pair<int, int> right = make_pair(pos.first, pos.second + 1);

    if(visited[up] == false){
        if(up.first >= 0 && up.first < grid.size() && up.second >= 0 && up.second < grid[0].size()){ 
            sum += findPerimeter(cur, up, grid, visited);
        }
        else{
            sum += 1;
        }
    }
    if(visited[down] == false){
        if(down.first >= 0 && down.first < grid.size() && down.second >= 0 && down.second < grid[0].size()){ 
            sum += findPerimeter(cur, down, grid, visited);
        }
        else{
            sum += 1;
        }
    }
    if(visited[left] == false){
        if(left.first >= 0 && left.first < grid.size() && left.second >= 0 && left.second < grid[0].size()){ 
            sum += findPerimeter(cur, left, grid, visited);
        }
        else{
            sum += 1;
        }
    }
    if(visited[right] == false){
        if(right.first >= 0 && right.first < grid.size() && right.second >= 0 && right.second < grid[0].size()){ 
            sum += findPerimeter(cur, right, grid, visited);
        }
        else{
            sum += 1;
        }
    }

    return sum;
}

int adv(vector<vector<char>> grid){
    int totalCost = 0;
    map<pair<int, int>,bool> visited;
    

    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid[i].size(); j++){
            pair<int, int> pos = make_pair(i, j);
            if(visited[pos] == false){ // if it's not visited and not a space
                visited[pos] = true;
                map<pair<int, int>,bool> perimeterVisited;
                int perimeter = findPerimeter(grid[i][j], pos, grid, perimeterVisited);
                int area = findArea(grid[i][j], pos, grid, visited);

                int cost = (area * perimeter);
                cout << "A region of " << grid[i][j] << " at x:" << j << " at y: " << i << " plants with price " << area << " * " << perimeter << " = " << cost << endl;
                totalCost += cost;

                //prints out current grid
                // for(int row = 0; row < grid.size(); row++){
                //     for(int col = 0; col < grid[row].size(); col++){
                //         pair<int,int> posC = make_pair(row, col);
                //         if(visited[posC] == true){
                //             char c = grid[row][col];
                //             if(c == grid[i][j]){
                //                 cout << c;
                //             }
                //             else{
                //                 cout << (char)tolower(c);
                //             }
                //         }
                //         else{
                //             cout << " ";
                //         }
                //     }
                //     cout << endl;
                // }
                // cout << endl << endl;
            } 
        }
    }
    

    return totalCost;
}


int findCorners(char cur, pair<int, int> pos, vector<vector<char>> grid, map<pair<int, int>,bool>& visited){
    if(grid[pos.first][pos.second] != cur){
        visited[pos] = false;
        return 0;
    }

    int sum = 0;

    pair<int, int> up = make_pair(pos.first - 1, pos.second);
    pair<int, int> down = make_pair(pos.first + 1, pos.second);
    pair<int, int> left = make_pair(pos.first, pos.second - 1);
    pair<int, int> right = make_pair(pos.first, pos.second + 1);

    pair<int, int> upLeft = make_pair(pos.first - 1, pos.second - 1);
    pair<int, int> upRight = make_pair(pos.first - 1, pos.second + 1);
    pair<int, int> downLeft = make_pair(pos.first + 1, pos.second - 1);
    pair<int, int> downRight = make_pair(pos.first + 1, pos.second + 1);

    // check 3x3 square around cur pos to find corners

    vector<vector<char>> corners = {
        {'@', '@', '@'}, 
        {'@', '#', '@'}, 
        {'@', '@', '@'}
    };
    
    if(up.first >= 0 && up.first < grid.size() && up.second >= 0 && up.second < grid[0].size() && grid[up.first][up.second] == cur){
        corners[0][1] = '#';
    }
    if(down.first >= 0 && down.first < grid.size() && down.second >= 0 && down.second < grid[0].size() && grid[down.first][down.second] == cur){
        corners[2][1] = '#';
    }
    if(left.first >= 0 && left.first < grid.size() && left.second >= 0 && left.second < grid[0].size() && grid[left.first][left.second] == cur){
        corners[1][0] = '#';
    }
    if(right.first >= 0 && right.first < grid.size() && right.second >= 0 && right.second < grid[0].size() && grid[right.first][right.second] == cur){
        corners[1][2] = '#';
    }
    if(upLeft.first >= 0 && upLeft.first < grid.size() && upLeft.second >= 0 && upLeft.second < grid[0].size() && grid[upLeft.first][upLeft.second] == cur){
        corners[0][0] = '#';
    }
    if(upRight.first >= 0 && upRight.first < grid.size() && upRight.second >= 0 && upRight.second < grid[0].size() && grid[upRight.first][upRight.second] == cur){
        corners[0][2] = '#';
    }
    if(downLeft.first >= 0 && downLeft.first < grid.size() && downLeft.second >= 0 && downLeft.second < grid[0].size() && grid[downLeft.first][downLeft.second] == cur){
        corners[2][0] = '#';
    }
    if(downRight.first >= 0 && downRight.first < grid.size() && downRight.second >= 0 && downRight.second < grid[0].size() && grid[downRight.first][downRight.second] == cur){
        corners[2][2] = '#';
    }
    // @ means void, # means valid

    /*
    @ @ @
    @ # @
    @ @ @
    */

    vector<bool> cornerVisited = {true, true, true, true};

    // all diagonals are corners unless they have exactly 1 other block next to them
    /*
    @#@                  -#- 
    @#@ -> 2 corners, -> @#@ -> the '-' where corners but becasue they are directly next to a block they are not corners
    @@@                  X@X
    */

    if(corners[0][1] == '#'){
        cornerVisited[0] = !cornerVisited[0];
        cornerVisited[1] = !cornerVisited[1];
    }
    if(corners[2][1] == '#'){
        cornerVisited[2] = !cornerVisited[2];
        cornerVisited[3] = !cornerVisited[3];
    }
    if(corners[1][0] == '#'){
        cornerVisited[0] = !cornerVisited[0];
        cornerVisited[2] = !cornerVisited[2];
    }
    if(corners[1][2] == '#'){
        cornerVisited[1] = !cornerVisited[1];
        cornerVisited[3] = !cornerVisited[3];
    }

    if(corners[0][0] == '#'){
        cornerVisited[0] = false;
    }
    if(corners[0][2] == '#'){
        cornerVisited[1] = false;
    }
    if(corners[2][0] == '#'){
        cornerVisited[2] = false;
    }
    if(corners[2][2] == '#'){
        cornerVisited[3] = false;
    }

    if(corners[0][1] == '@' && corners[1][0] == '@'){
        cornerVisited[0] = true;
    }
    if(corners[0][1] == '@' && corners[1][2] == '@'){
        cornerVisited[1] = true;
    }
    if(corners[2][1] == '@' && corners[1][0] == '@'){
        cornerVisited[2] = true;
    }
    if(corners[2][1] == '@' && corners[1][2] == '@'){
        cornerVisited[3] = true;
    }




    
    // for(int i = 0; i < corners.size(); i++){
    //     for(int j = 0; j < corners[i].size(); j++){
    //         cout << corners[i][j];
    //     }
    //     cout << endl;
    // }




    for(int i = 0; i < cornerVisited.size(); i++){
        //cout << cornerVisited[i] << " ";
        if(cornerVisited[i]){
            sum += 1;
        }
    }
    //cout << endl;

    visited[pos] = true;
    // contines to all of the next inbound squares which are of same char
    if(visited[up] == false && up.first >= 0 && up.first < grid.size() && up.second >= 0 && up.second < grid[0].size()){ 
        visited[up] = true;
        sum += findCorners(cur, up, grid, visited);
    }
    if(visited[down] == false && down.first >= 0 && down.first < grid.size() && down.second >= 0 && down.second < grid[0].size()){ 
        visited[down] = true;
        sum += findCorners(cur, down, grid, visited);
    }
    if(visited[left] == false && left.first >= 0 && left.first < grid.size() && left.second >= 0 && left.second < grid[0].size()){ 
        visited[left] = true;
        sum += findCorners(cur, left, grid, visited);
    }
    if(visited[right] == false && right.first >= 0 && right.first < grid.size() && right.second >= 0 && right.second < grid[0].size()){ 
        visited[right] = true;
        sum += findCorners(cur, right, grid, visited);
    }

    return sum;
}

int adv2(vector<vector<char>> grid){
    int totalCost = 0;
    map<pair<int, int>,bool> visited;
    

    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid[i].size(); j++){
            pair<int, int> pos = make_pair(i, j);
            if(visited[pos] == false){ // if it's not visited and not a space
                visited[pos] = true;
                map<pair<int, int>, bool> perimeterVisited;
                int perimeter = findCorners(grid[i][j], pos, grid, perimeterVisited);
                int area = findArea(grid[i][j], pos, grid, visited);
        
                if(!isalpha(grid[i][j])){
                    continue;
                }

                int cost = (area * perimeter);
                cout << "A region of " << grid[i][j] << " at x:" << j << " at y: " << i << " plants with price " << area << " * " << perimeter << " = " << cost << endl;
                totalCost += cost;

                //prints out current grid
                // for(int row = 0; row < grid.size(); row++){
                //     for(int col = 0; col < grid[row].size(); col++){
                //         pair<int,int> posC = make_pair(row, col);
                //         if(visited[posC] == true){
                //             char c = grid[row][col];
                //             if(c == grid[i][j]){
                //                 cout << c;
                //             }
                //             else{
                //                 cout << (char)tolower(c);
                //             }
                //         }
                //         else{
                //             cout << " ";
                //         }
                //     }
                //     cout << endl;
                // }
                // cout << endl << endl;
            } 
        }
    }
    

    return totalCost;
}





int main(){
    ifstream file("data.txt");
    //ifstream file("test.txt");
    //ifstream file("test2.txt");
    if(!file.is_open()){
        cout << "FUCK an ERROR opening file" << endl;
        return -1;
    }
    vector<vector<char>> grid;
    string line;
    while(getline(file, line)){
        vector<char> row;
        for(char c : line){
            if(c != ' '){ // Exclude white spaces
                row.push_back(c);
            }
        }
        grid.push_back(row);
    }
    file.close();

    // Print the grid
    // cout << "Grid:" << endl;
    // for(const auto& row : grid){
    //     for(char c : row){
    //         cout << c;
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    int Answer = adv2(grid);
    cout << "Answer " << Answer << endl;
    return 1;
}