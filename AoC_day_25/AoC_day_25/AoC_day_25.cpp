// AoC_day_25.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

tuple<vector<vector<int>>, vector<vector<int>>> readFile() {
    fstream file;
    string tp;
    vector<vector<int>> keys;
    vector<vector<int>> locks;
    file.open("D:\\!Advent_of_Code\\2024\\AoC_day_25\\input.txt");
    if (!file.is_open()) {
        cout << "FAILED TO OPEN FILE\n";
    }
    //0 is we need to determine
    //1 is a lock
    //2 is a key
    int key_or_lock = 0;
    vector<int> key_lock = { 0,0,0,0,0 };
    int count = 0;
    while (getline(file, tp)) {
        if (tp == "" && key_or_lock !=0) {
            if (key_or_lock == 1) {
                locks.push_back(key_lock);
            }
            else {
                keys.push_back(key_lock);
            }
            key_lock = { 0,0,0,0,0 };
            key_or_lock = 0;
            continue;
        }
        else if (tp == "#####" && key_or_lock == 0) {
            count = 0;
            key_or_lock = 1;
            continue;
        }
        else if (tp == "....." && key_or_lock == 0) {
            count = 0;
            key_or_lock = 2;
            continue;
        }
        if (count <5){
            count++;
            if (tp[0] == '#') {
                key_lock[0]++;
            }
            if (tp[1] == '#') {
                key_lock[1]++;
            }
            if (tp[2] == '#') {
                key_lock[2]++;
            }
            if (tp[3] == '#') {
                key_lock[3]++;
            }
            if (tp[4] == '#') {
                key_lock[4]++;
            }
        }
    }
    if (key_or_lock == 1) {
        locks.push_back(key_lock);
    }
    else {
        keys.push_back(key_lock);
    }
    return make_tuple(locks, keys);
}

void pt_1(vector<vector<int>> locks, vector <vector<int>> keys) {
    int sum = 0;
    for (vector<int> lock : locks) {
        for (vector<int> key : keys) {
            if ((key[0] + lock[0] < 6) && (key[1] + lock[1] < 6) && (key[2] + lock[2] < 6) && (key[3] + lock[3] < 6) && (key[4] + lock[4] < 6)) {
                sum++;
            }
        }
    }
    cout << "There are " << sum << " unique lock/key pairs which fit without overlapping";
}

int main()
{
    std::cout << "Hello World!\n";
    vector<vector<int>> locks;
    vector<vector<int>> keys;
    tie(locks, keys) = readFile();
    pt_1(locks, keys);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
