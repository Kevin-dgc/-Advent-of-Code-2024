#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include <limits>
#include <fstream>


using namespace std;

int adv(vector<int> one, vector<int> two){
    int sum = 0;

    map<int, int> mapMinOne;
    map<int, int> mapMinTwo;
    // puts vectors into maps
    for(int num : one){
        mapMinOne[num]++;
    }
    for(int num : two){
        mapMinTwo[num]++;
    }


    for(int i = 0; i < one.size(); i++){
        int leftMin = numeric_limits<int>::max();
        int rightMin = numeric_limits<int>::max();

        for(map<int,int>::iterator it = mapMinOne.begin(); it != mapMinOne.end(); it++){
            if(it->second > 0 && it->first < leftMin){
                leftMin = it->first;
                it->second--;
            }
        }

        for(map<int,int>::iterator it = mapMinTwo.begin(); it != mapMinTwo.end(); it++){
            if(it->second > 0 && it->first < rightMin){
                rightMin = it->first;
                it->second--;
            }
        }
        // gets min left and right nums

        // gets abs val of distance
        int res = leftMin-rightMin;
        if(res < 0){
            res *= -1;
        }

        sum += res;
    }
    
    return sum;
}


int adv2(vector<int> one, vector<int> two){
    int sum = 0;

    map<int, int> mapMinTwo;
    // puts vectors into maps
    for(int num : two){
        mapMinTwo[num]++;
    }


    for(int i = 0; i < one.size(); i++){
        sum += (one[i] * mapMinTwo[one[i]]);
    }
    
    return sum;
}



int main(){
    vector<int> one;
    vector<int> two;


    ifstream inputFile("data.txt");
    if (!inputFile) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }
    int value;
    bool toggle = true;

    while (inputFile >> value) {
        if (toggle) {
            one.push_back(value);
        } else {
            two.push_back(value);
        }
        toggle = !toggle;
    }
    inputFile.close();

    // for(int i = 0; i < one.size(); i++){
    //     cout << one[i] << "        " << two[i] << endl;
    // }

    int dis = adv(one, two);
    cout << "dis " << dis << endl;

    int sim = adv2(one, two);
    cout << "sim " << sim << endl;
}