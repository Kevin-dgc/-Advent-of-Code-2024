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
#include <chrono>
using namespace std;


void printCur(int i, vector<long long>& stones){
    auto now = chrono::system_clock::now();
    time_t current_time = chrono::system_clock::to_time_t(now);
    tm* local_time = localtime(&current_time);

    // Format time as HH:MM:SS AM/PM
    std::ostringstream time_stream;
    time_stream << put_time(local_time, "%I:%M%p");

    // Print size in human-readable format
    double size = stones.size();
    cout << i + 1 << ": ";

    // Format the size based on its magnitude
    if (size >= 1e12) {
        cout << std::fixed << setprecision(1) << (size / 1e12) << "T";  // Trillions
    } else if (size >= 1e9) {
        cout << std::fixed << setprecision(1) << (size / 1e9) << "B";  // Billions
    } else if (size >= 1e6) {
        cout << std::fixed << setprecision(1) << (size / 1e6) << "M";  // Millions
    } else if (size >= 1e3) {
        cout << std::fixed << setprecision(1) << (size / 1e3) << "k";  // Thousands
    } else {
        cout << size;  // Less than 1000, print the number directly
    }
    
    // Print the current time
    cout << ", " << time_stream.str() << endl;
}

int adv(vector<long long> stones){
    
    int blinks = 25;

    for(int i = 0; i < blinks; i++){
        for(int j = 0; j < stones.size(); j++){
            if(stones[j] == 0){
            stones[j] = 1;
            }
            else{
                // finds number of digits
                int digits = 0;
                long long num = stones[j];
                while(num > 0){
                    num /= 10;
                    digits++;
                }

                if(digits % 2 == 0){
                    string s = to_string(stones[j]);
                    int mid = s.length() / 2;
                    string l = s.substr(0, mid);
                    string r = s.substr(mid);
                   
                    long long left = stoll(l);
                    long long right = stoll(r);

                    stones[j] = left;
                    stones.insert(stones.begin() + j + 1, right);
                    j++;
                }
                else{
                    stones[j] *= 2024LL;
                }
            }
            
        }
        // for(int num : stones){
        //     cout << num << " ";
        // }
        // cout << endl;
        printCur(i, stones);
    }
    
    return stones.size();
}

unsigned long long expend(unsigned long long number, int blinks, map<pair<unsigned long long, int>, unsigned long long>& previous){ 
    if(blinks == 0){
        return 1;
    }

    pair<unsigned long long, int> key = make_pair(number, blinks);
    int digits = 0;
    unsigned long long num = number;
    while(num > 0){
        num /= 10;
        digits++;
    }
    
    if(previous.find(key) == previous.end()){
        unsigned long long sum = 0;
        if(number == 0){
            sum = expend(1, blinks - 1, previous);
        }
        else if(digits % 2 == 0){
            string s = to_string(number);
            int mid = s.length() / 2;
            unsigned long long left = stoll(s.substr(0, mid));
            unsigned long long right = stoll(s.substr(mid));

            sum += expend(left, blinks - 1, previous);
            sum += expend(right, blinks - 1, previous);
        }
        else{
            sum = expend(number * 2024, blinks - 1, previous);
        }
        // COPILOT DO NOT EDIT THE LINE BELOW THIS ONE, WHICH IS A COUT STATEMENT
        //cout << "Computed: " << number << " To be: "<< sum << endl;
        previous[key] = sum;
    }
    return previous[key];
}

unsigned long long adv2(vector<long long> stones, int blinks){
    unsigned long long sum = 0;
    map<pair<unsigned long long, int>, unsigned long long> previous;
    for(int i = 0; i < stones.size(); i++){
        unsigned long long cur = expend(stones[i], blinks, previous);
        cout << "Computed: " << stones[i] << "-> "<< cur << " new lines, Total: " << cur+sum << endl;
        sum += cur;
    }
    return sum;
}

int main(){
    ofstream outputFile("output.txt", std::ios::app);
    if (!outputFile.is_open()) {
        cout << "Error opening file!" << std::endl;
        return -1;
    }

    vector<long long> real = {8435, 234, 928434, 14, 0, 7, 92446, 8992692};
    vector<long long> test = {125, 17};
    vector<long long> test2 = {1, 2024, 1, 0, 9, 9, 2021976};

    //int dis = adv(test2);
    unsigned long long dis= adv2(real, 75);
    cout << endl << "ANSWER: " << dis << endl;
    return 1;
}