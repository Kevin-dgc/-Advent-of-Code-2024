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
#include "lodepng.h"

using namespace std;



void saveGridAsPNG(const std::vector<std::vector<int>>& grid, const std::string& filename) {
        // Get grid dimensions
        size_t height = grid.size();
        if (height == 0) return; // Empty grid
        size_t width = grid[0].size();

        // Create a 1D array to store the image pixels
        std::vector<unsigned char> image(width * height * 4, 255); // Initialize to white (RGBA)

        for (size_t y = 0; y < height; ++y) {
            for (size_t x = 0; x < width; ++x) {
                size_t idx = 4 * (y * width + x); // Index in the 1D array
                if (grid[y][x] == 1) {
                    image[idx + 0] = 255; // Red
                    image[idx + 1] = 255; // Green
                    image[idx + 2] = 255; // Blue
                } else {
                    image[idx + 0] = 0;   // Red
                    image[idx + 1] = 0;   // Green
                    image[idx + 2] = 0;   // Blue
                }
                image[idx + 3] = 255; // Alpha (fully opaque)
            }
        }

        // Encode the image as a PNG and save it to the file
        unsigned error = lodepng::encode(filename, image, width, height);
        if (error) {
            throw std::runtime_error("Error saving PNG: " + std::string(lodepng_error_text(error)));
        }
}

pair<int,int> moveBot(int xMax, int yMax, pair<int,int> pos, pair<int,int> vel){
    int x = pos.first + vel.first;
    int y = pos.second + vel.second;

    if(x < 0){
        x = xMax + (x % xMax) % xMax;
    }
    if(x >= xMax){
        x = x % xMax;
    }
    
    if (y < 0){
        y = (yMax + (y % yMax)) % yMax;
    }
    if (y >= yMax){
         y = y % yMax;
    }

   
    return make_pair(x,y);
}

int adv(int xMax, int yMax, vector<pair<pair<int,int>,pair<int,int>>> &bots, int seconds){
    vector<vector<int>> grid(yMax, vector<int>(xMax, 0));
    
    for(int i = 0; i < bots.size(); i++){
        pair<int,int> location = make_pair(bots[i].first.first, bots[i].first.second);

        for(int j = 0; j < seconds; j++){
            location = moveBot(xMax, yMax, location, bots[i].second);
            // grid[location.second][location.first]++;
            //     for(auto X : grid){
            //         for(auto Y : X){
            //             cout << Y << " ";
            //         }
            //         cout << endl;
            //     }
            //     cout << endl;
            //     grid[location.second][location.first]--;
        }
    grid[location.second][location.first]++;
    }

    // for(int i = 0; i < grid.size(); i++){
    //     for(int j = 0; j < grid[i].size(); j++){
    //         cout << grid[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    // top left Q1
    int Q1 = 0;
    for(int i = 0; i < grid.size()/2; i++){
        for(int j = 0; j < grid[i].size()/2; j++){
            Q1 += grid[i][j];
        }
    }
    
    // top right Q2
    int Q2 = 0;
    for(int i = 0; i < grid.size()/2; i++){
        for(int j = (grid[i].size()/2)+1; j < grid[i].size(); j++){
            Q2 += grid[i][j];
        }
    }
    
    // bottom left Q3
    int Q3 = 0;
    for(int i = (grid.size()/2) +1; i < grid.size(); i++){
        for(int j = 0; j < grid[i].size()/2; j++){
            Q3 += grid[i][j];
        }
    }
    
    // bottom right Q4
    int Q4 = 0;
    for(int i = (grid.size()/2) +1; i < grid.size(); i++){
        for(int j = (grid[i].size()/2)+1; j < grid[i].size(); j++){
            Q4 += grid[i][j];
        }
    }
    cout << "Q1 " << Q1 << " Q2 " << Q2 << " Q3 " << Q3 << " Q4 " << Q4 << endl;
    return Q1 * Q2 * Q3 * Q4;
}

int adv2(int xMax, int yMax, vector<pair<pair<int,int>,pair<int,int>>> &bots){
    int seconds = 0;
    vector<vector<int>> grid(yMax, vector<int>(xMax, 0));


    while(true){ // seconds < 10000
        // cout << "Running, attempt: " << seconds << endl;

        // string filename = "images/" + to_string(seconds) + ".png";
        // saveGridAsPNG(grid, filename);


        for(auto &row : grid) {
            row.assign(row.size(), 0);
        }

        for(int i = 0; i < bots.size(); i++){
            pair<int,int> location = make_pair(bots[i].first.first, bots[i].first.second);

            location = moveBot(xMax, yMax, location, bots[i].second);

            bots[i].first.first = location.first;
            bots[i].first.second = location.second;
        
            grid[location.second][location.first]++;
        }
        seconds++;

        bool dupe = false;
        for(auto row : grid){
            for(auto col : row){
                if(col > 1){
                    dupe = true;
                }
            }
        }
        if(!dupe){
            cout << seconds << endl;
            break;
        }
    }
    
    

    return seconds;
}



vector<pair<pair<int,int>,pair<int,int>>> parse(string filename){
    vector<pair<pair<int, int>, pair<int, int>>> data;

    // Open the file
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "FUCK an ERROR opening file" << endl;
        return data;
    }

    string line;
    while (getline(inputFile, line)) {
        // Parse each line
        int px, py, vx, vy;
        char discard; // To ignore the 'p=', 'v=', and ',' characters
        stringstream ss(line);

        // Parse the line
        ss >> discard >> discard >> px >> discard >> py >> discard >> discard >> vx >> discard >> vy;

        // Add the parsed values to the vector
        data.push_back({{px, py}, {vx, vy}});
    }

    inputFile.close();

    // Output the parsed data (optional, for verification)
    // for (const auto& entry : data) {
    //     cout << "p=(" << entry.first.first << "," << entry.first.second << ") "
    //          << "v=(" << entry.second.first << "," << entry.second.second << ")" << endl;
    // }

    return data;
}

int main(){
    
    vector<pair<pair<int,int>,pair<int,int>>> bots = parse("data.txt");
    vector<pair<pair<int,int>,pair<int,int>>> test = parse("test.txt");

    //int Answer = adv(11,7, test, 100);
    //int Answer = adv(101,103,bots,100);
    int Answer = adv2(101,103,bots);
    cout << "Answer " << Answer << endl;
    return 1;
}