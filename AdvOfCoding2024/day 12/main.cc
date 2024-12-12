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


int findPerimeter2(char cur, pair<int, int> pos, vector<vector<char>> grid, map<pair<int, int>,bool>& visited){
    // needs to count how many corrners are there
    if(grid[pos.first][pos.second] != cur){
        return 1;
    }
    

    int sum = 0;
    pair<int, int> up = make_pair(pos.first - 1, pos.second);
    pair<int, int> down = make_pair(pos.first + 1, pos.second);
    pair<int, int> left = make_pair(pos.first, pos.second - 1);
    pair<int, int> right = make_pair(pos.first, pos.second + 1);

    if(visited[up] == false){
        if(up.first >= 0 && up.first < grid.size() && up.second >= 0 && up.second < grid[0].size()){ 
            visited[pos] = true;
            sum += findPerimeter2(cur, up, grid, visited);
        }
        else{
            visited[pos] = true;
            sum += 1;
        }
    }
    if(visited[down] == false){
        if(down.first >= 0 && down.first < grid.size() && down.second >= 0 && down.second < grid[0].size()){ 
            visited[pos] = true;
            sum += findPerimeter2(cur, down, grid, visited);
        }
        else{
            sum += 1;
        }
    }
    if(visited[left] == false){
        if(left.first >= 0 && left.first < grid.size() && left.second >= 0 && left.second < grid[0].size()){ 
            visited[pos] = true;
            sum += findPerimeter2(cur, left, grid, visited);
        }
        else{
            sum += 1;
        }
    }
    if(visited[right] == false){
        if(right.first >= 0 && right.first < grid.size() && right.second >= 0 && right.second < grid[0].size()){ 
            visited[pos] = true;
            sum += findPerimeter2(cur, right, grid, visited);
        }
        else{
            sum += 1;
        }
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
                int perimeter = findPerimeter2(grid[i][j], pos, grid, perimeterVisited);
                int area = findArea(grid[i][j], pos, grid, visited);


                int cost = (area * perimeter);
                cout << "A region of " << grid[i][j] << " at x:" << j << " at y: " << i << " plants with price " << area << " * " << perimeter << " = " << cost << endl;
                totalCost += cost;

                //prints out current grid
                for(int row = 0; row < grid.size(); row++){
                    for(int col = 0; col < grid[row].size(); col++){
                        pair<int,int> posC = make_pair(row, col);
                        if(visited[posC] == true){
                            char c = grid[row][col];
                            if(c == grid[i][j]){
                                cout << c;
                            }
                            else{
                                cout << (char)tolower(c);
                            }
                        }
                        else{
                            cout << " ";
                        }
                    }
                    cout << endl;
                }
                cout << endl << endl;
            } 
        }
    }
    

    return totalCost;
}





int main(){
    //ifstream file("data.txt");
    ifstream file("test.txt");
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



    int dis = adv2(grid);
    cout << "dis " << dis << endl;
    return 1;
}