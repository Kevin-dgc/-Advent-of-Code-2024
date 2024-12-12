#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include <limits>
#include <fstream>
using namespace std;


int safe(vector<int> myVec){
    int order = 0; // 1 inc, 2 dec, 0 ERROR (should not happen)
    int safey = 0; 
    
    // checks if its inc or dec order
    if(myVec[0] > myVec[myVec.size()-1]){
        order = 2; // dec ex) 3,2,1
    }
    else{
        order = 1; // inc ex) 1,2,3
    }

    // checks current num and next num
    // if current num doesnt work checks prev num with next num
    // if a check fails then ++ to counter (safey)
    for(int i = 0; i < myVec.size()-2; i++){
        if(order == 1){
            if(!(myVec[i] < myVec[i+1])){
                //cout << "ERROR " << myVec[i] << " <= " << myVec[i+1] << " INC " <<  endl;
                safey++;
            }
            if(!(myVec[i]+3 >= myVec[i+1])){
                //cout << "ERROR " << myVec[i]+3 << " >= " << myVec[i+1] << " INC " << endl;
                safey++;
            }
        }
        else{
            if(!(myVec[i] > myVec[i+1])){
                //cout << "ERROR " << myVec[i] << " >= " << myVec[i+1] << " DEC " << endl;
                safey++;
            }
            if(!(myVec[i]-3 <= myVec[i+1])){
                //cout << "ERROR " << myVec[i]-3 << " <= " << myVec[i+1] << " DEC " << endl;
                safey++;
            }
        }
    }

    //checks the last digit and the one before last
    int i = myVec.size()-1;

    if(order == 1){
        if(!(myVec[i-1] < myVec[i])){
            safey++;
        }
        if(!(myVec[i-1]+3 >= myVec[i])){
            safey++;
        }
    }
    else{
        if(!(myVec[i-1] > myVec[i])){
            safey++;
        }
        if(!(myVec[i-1]-3 <= myVec[i])){
            safey++;
        }
    }

    // prints out list of all vectors with number of safey assigned to them
    // for(int j = 0; j < myVec.size(); j++){
    //     cout << myVec[j] << ", ";
    // }
    // cout << "safety: " << safey << endl;


    return (safey < 1); // allows no errors if line above is commented out
}

int adv(vector<vector<int>> input){
    int totalSafe = 0;

    for(int index = 0; index < input.size(); index++){
        //check all vector<int> is they are safe
        if(safe(input[index])){
            totalSafe++;
        }
        else{
            // loop threw each index and remove it then check if safe
            for(int i = 0; i < input[index].size(); i++){
                vector<int> newInput = input[index];
                newInput.erase(newInput.begin() + i);
                if(safe(newInput)){
                    totalSafe++;
                    break;
                }
            }
        }
    }
    return totalSafe;
}

int main(){

    std::ifstream inputFile("data.txt");
    std::vector<std::vector<int>> input;
    if (!inputFile) {
        std::cerr << "ERROR with file" << std::endl;
        return -1;
    }
    std::string line;
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::vector<int> row;
        int value;
        while (ss >> value) {
            row.push_back(value);
        }
        input.push_back(row);
    }
    inputFile.close();

    // vector<vector<int>> input = {
    //     {7,6,4,2,1},
    //     {1,2,7,8,9},
    //     {9,7,6,2,1},
    //     {1,3,2,4,5},
    //     {8,6,4,4,1},
    //     {1,3,6,7,9}
    // };

    int num = adv(input);
    cout << "safe number " << num << endl;

    // vector<int> myVec = {1,3,6,7,9};

    // bool s = safe(myVec);
    // if(s){
    //     cout << "Safe" << endl;
    // }
    // else{
    //     cout << "Unsafe" << endl;
    // }
    return 0;
}