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

int adv(){
    int sum = 0;

    

    return sum;
}


int main(){
    ifstream file("data.txt");
    if(!file.is_open()){
        cout << "FUCK an ERROR opening file" << endl;
        return -1;
    }
    string line;
    while(getline(file, line)){
        
    }
    
    cout << endl;
    int dis = adv();
    cout << "dis " << dis << endl;
    return 1;
}