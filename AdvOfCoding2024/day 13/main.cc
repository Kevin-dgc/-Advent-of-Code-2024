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
#include <limits.h>
#include <cstdlib> 
using namespace std;


//                        X,  Y                 X,  Y                  X,  Y
long double calculateToken(pair<long double,long double> buttonA, pair<long double,long double> buttonB, pair<long double,long double> target){
    // max combo for A and B is no more than 100
    vector<long double> tokens;
    long double tokenSum = 0;

    for(int i = 0; i < 101; i++){
        for(int j = 0; j < 101; j++){
            int x = buttonA.first * i + buttonB.first * j;
            int y = buttonA.second * i + buttonB.second * j;
            if(x == target.first && y == target.second){
                //cout << "i: " << i << " j: " << j << endl;
                tokens.push_back((i*3) + j);
            }
        }   
    }

    long double lowestToken = LONG_LONG_MAX;
    for(long double i = 0; i < tokens.size(); i++){
        //cout << tokens[i] << endl;
        if(tokens[i] < lowestToken){
            lowestToken = tokens[i];
        }
    }

    // If no valid token is found, return 0 or another appropriate value
    if (lowestToken == LONG_LONG_MAX) {
        return 0;
    }

    return lowestToken;
}

long long simulateToken(pair<long double,long double> buttonA, pair<long double,long double> buttonB, pair<long double,long double> target){
    // long double Xa = buttonA.first;
    // long double Ya = buttonA.second;

    // long double Xb = buttonB.first;
    // long double Yb = buttonB.second;

    // long double Xt = target.first;
    // long double Yt = target.second;

    // // If no valid token is found, return 0 or another appropriate value
    // long double B = (Yt - ((Ya*Xt)/Xa))/ (Yb - ((Ya*Xb)/Xa));


    // long double A = ((Xt - (Xb*B))/Xa);
    // // cout << "A: " << A << " B: " << B << endl;
    // if(A < 0 || B < 0 || A != floor(A) || B != floor(B)){
    //     //  cout << "A: " << A << " B: " << B << endl;
    //     //  cout << "Testing A: " << buttonA.first << " " << buttonA.second << " B: " << buttonB.first << " " << buttonB.second << " T: " << target.first << " " << target.second << endl;
    //     return 0;
    // }

    // if(A < 100 && B < 100){
    //         // cout << Xa*A + Xb*B << " ?= " << Xt << " | " << Ya*A + Yb*B << " ?= " << Yt << endl;
    //         // cout << "A: " << A << " B: " << B << endl << endl;
    //     return (A*3) + B;
    // }
    // return 0;
    long double d1 = (target.second * buttonB.first) - (target.first * buttonB.second);
    long double d2 = (buttonB.first * buttonA.second) - (buttonA.first * buttonB.second);

    long double A = d1 / d2;
    long double remainder = fmod(d1, d2);

    long double B = (target.first - (buttonA.first * A)) / buttonB.first;

    if(remainder != 0 || A < 0 || B < 0){
        return LONG_LONG_MAX;
    }

    return 3*A + B;
}


long double adv(vector<vector<pair<long double, long double>>> data){
    long double tokenSum = 0;

    for(int i = 0; i < data.size(); i++){
        //cout << "Processing block " << i + 1 << " of " << data.size() << endl;
        pair<long double,long double> buttonAs = data[i][0];
        pair<long double,long double> buttonBs = data[i][1];
        pair<long double,long double> targets = data[i][2];
        //cout << "Testing: A: " << buttonAs.first << " " << buttonAs.second << " B: " << buttonBs.first << " " << buttonBs.second << " T: " << targets.first << " " << targets.second << endl; 
        long long token = simulateToken(buttonAs, buttonBs, targets);
        if(token == LONG_LONG_MAX){
            continue;
        }
        //cout << "Token: " << token << endl << endl << "New Block" << endl;
        tokenSum += token;
    }

    return tokenSum;
}

vector<vector<pair<long double, long double>>> readTxT(string fileName){
    vector<vector<pair<long double, long double>>> all_blocks;
    ifstream infile(fileName);
    if (!infile) {
        cerr << "Error: Could not open the file!" << endl;
        return all_blocks;
    }

    string line;
    vector<pair<long double, long double>> current_block;

    // Process the file line by line
    while (getline(infile, line)) {
        // Parse each line
        stringstream ss(line);
        string token;
        if (line.find("Button A:") != string::npos) {
            // Extract values after X+ and Y+
            long double x, y;
            ss.ignore(256, '+'); // Ignore till +
            ss >> x;
            ss.ignore(256, '+'); // Ignore till next +
            ss >> y;
            current_block.push_back({x, y});
        } else if (line.find("Button B:") != string::npos) {
            long double x, y;
            ss.ignore(256, '+'); // Ignore till +
            ss >> x;
            ss.ignore(256, '+'); // Ignore till next +
            ss >> y;
            current_block.push_back({x, y});
        } else if (line.find("Prize:") != string::npos) {
            long double x, y;
            ss.ignore(256, '='); // Ignore till =
            ss >> x;
            ss.ignore(256, '='); // Ignore till next =
            ss >> y;
            // change displacement to 0 for pt 1 and 10000000000000 for pt 2
            long double displacement = 10000000000000;
            //long double displacement = 0;
            current_block.push_back({x+displacement, y+displacement});
            // Push the current block to all_blocks after reading Prize
            all_blocks.push_back(current_block);
            current_block.clear();
        }
    }

    infile.close();

    // Debug: Print the read data
    // for (const auto& block : all_blocks) {
    //     for (const auto& p : block) {
    //         cout << "(" << p.first << ", " << p.second << ") ";
    //     }
    //     cout << endl;
    // }

    return all_blocks;
}

int main(){
    //vector<vector<pair<int, int>>> data = readTxT("data.txt");
    vector<vector<pair<long double, long double>>> data = readTxT("data.txt");
    //vector<vector<pair<int, int>>> data = readTxT("test2.txt");

    // for(int i = 0; i < data.size(); i++){
    //     for(int j = 0; j < data[i].size(); j++){
    //         cout << data[i][j].first << " " << data[i][j].second << endl;
    //     }
    // }

    //  pair<int, int> A = make_pair(17,86);
    //  pair<int, int> B = make_pair(84,37);
    //  pair<int, int> T = make_pair(7970,6450);

    long double Answer = adv(data);
    //int Answer = calculateToken(A,B,T);
    cout << fixed << setprecision(0) << "Answer " << Answer << endl;
    return 0; // Return 0 to indicate successful execution
}