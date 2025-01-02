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


vector<long long> adv(long long A, int B, int C, vector<long long> programs){
    vector<long long> var;
    for(int i = 0; i < programs.size()-1;){
        long long opCode = programs[i];
        long long opErand = programs[i+1];

        if(opErand == 4){
            opErand = A;
        }
        else if(opErand == 5){
            opErand = B;
        }
        else if(opErand == 6){
            opErand = C;
        }
        else if(opErand == 7){
            // doesnt happen ^
        }


        if(opCode == 0){
            A /= (pow(2,opErand));
            i += 2;
        }
        else if(opCode == 1){
            B ^= opErand; 
            i += 2;
        }
        else if(opCode == 2){
            B = opErand % 8;
            i += 2;
        }
        else if(opCode == 3){
            if(A != 0){
                i = opErand;
            }
            else{
                i += 2;
            }
        }
        else if(opCode == 4){
            B ^= C;
            i += 2;
        }
        else if(opCode == 5){
            var.push_back(opErand%8);
            i += 2;
        }
        else if(opCode == 6){
            B = A/(pow(2,opErand));
            i += 2;
        }
        else if(opCode == 7){
            C = A/(pow(2,opErand));
            i += 2;
        }
    }

    return var;
}

long long adv2(long long A, int B, int C, vector<long long> programs){

    A++;
    long long count = 0;
    while(true){
        vector<long long> temp = adv(A,B,C,programs);
        cout << "Attempt: " << count << endl;
        if(programs == temp){
            return A;
        }
        count++;
        A++;
    }
}

pair<vector<int>,vector<long long>> parse(string filename){
    ifstream file(filename);
    if(!file.is_open()){
        cout << "FUCK an ERROR opening file" << endl;
    }

    vector<int> registers(3);
    vector<long long> program;      
    string line;

    while (getline(file, line)) {
        if (line.find("Register A:") != string::npos) {
            registers[0] = stoi(line.substr(line.find(":") + 1));
        } else if (line.find("Register B:") != string::npos) {
            registers[1] = stoi(line.substr(line.find(":") + 1));
        } else if (line.find("Register C:") != string::npos) {
            registers[2] = stoi(line.substr(line.find(":") + 1));
        }
        else if (line.find("Program:") != string::npos) {
            string numbers = line.substr(line.find(":") + 1);
            stringstream ss(numbers);
            string num;
            while (getline(ss, num, ',')) {
                program.push_back(stoi(num));
            }
        }
    }

    file.close();
    return {registers, program};
}

int main(){
    pair<vector<int>,vector<long long>> input = parse("test2.txt");

    // cout << "Reg: " << endl;
    // for(auto i : input.first){
    //     cout << i << " ";
    // }

    // cout << endl << "Program: " << endl;
    // for(auto i : input.second){
    //     cout << i << " ";
    // }

    // pt 1
    //vector<long long> Answer = adv(input.first[0], input.first[1], input.first[2], input.second);
    // string res = "";
    // for(auto i : Answer){
    //     res += to_string(i);
    //     res += ",";
    // }
    // res.pop_back();
    // cout << "Answer " << res << endl;

    // pt 2, would take appox 383 years to run :/
    long long Answer = adv2(input.first[0], input.first[1], input.first[2], input.second);
    cout << "Answer " << Answer << endl;
    return 1;
}