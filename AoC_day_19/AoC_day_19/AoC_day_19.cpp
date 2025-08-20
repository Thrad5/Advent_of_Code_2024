// AoC_day_19.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>>
#include <string>
#include <fstream>
#include <list>
#include <vector>
#include <set>
#include <numeric>



using namespace std;

set<string> towels;
int max_length;
map<string, unsigned long long int> cache;

void pt_1(set<string> towels, vector<string> designs) {
    int max_towel_length = 0;
    for (auto a : towels) {
        if (a.length() > max_towel_length) {
            max_towel_length = a.length();
        }
    }
    int sum = 0;
    //for each design:
    //keep track of each length of towel you add
    //if you end up at a dead end go back one step and add one to the max_vector
    for (auto design : designs) {
        string recreate = "";
        vector<int> leng_vec;
        int pos = 0;
        int towel_length = 1;
        bool finished = false;
        while (!finished) {
            if (recreate == design) {
                sum++;
                finished = true;
                continue;
            }
            if (towel_length > max_towel_length && leng_vec.size() == 0) {
                finished = true;
                recreate = "";
                continue;
            }
            else if (towel_length > max_towel_length) {
                int subtotal = accumulate(leng_vec.begin(), leng_vec.end() - 1, 0);
                recreate = design.substr(0, subtotal);
                pos = subtotal;
                towel_length = leng_vec.back() + 1;
                leng_vec.pop_back();
                continue;
            }
            string test = design.substr(pos, towel_length);
            //cout << test << ", " << towel_length << "\n";
            if (towels.find(test) != towels.end()) {
                recreate += test;
                pos += towel_length;
                leng_vec.push_back(towel_length);
                towel_length = 1;
            }
            else {
                towel_length++;
            }

        }

    }
    cout << "There are " << sum << " valid designs with available towel patterns" << "\n";
}


unsigned long long int pt_2_recursive(string design) {
    if (design == "") {
        return 1;
    }
    if (cache.contains(design)) {
        return cache[design];
    }
    unsigned long long int sum = 0;
    for (string towel : towels) {
        if (towel == design.substr(0,towel.length())) {
            sum += pt_2_recursive(design.substr(towel.length()));
        }
    }
    cache[design] = sum;
    return sum;
}

/*
void pt_2(set<string> towels, vector<string> designs) {
    int max_towel_length = 0;
    for (auto a : towels) {
        if (a.length() > max_towel_length) {
            max_towel_length = a.length();
        }
    }
    int sum = 0;
    //for each design:
    //keep track of each length of towel you add
    //if you end up at a dead end go back one step and add one to the max_vector
    for (int i = 0; i < designs.size(); i++) {
        auto design = designs[i];
        cout << i << "/" << designs.size() << "\n";
        //cout << design << "\n";
        string recreate = "";
        vector<int> leng_vec;
        int pos = 0;
        int towel_length = 1;
        bool finished = false;
        vector<string> twl;
        while (!finished) {
            if (recreate == design) {
                sum++;
                int subtotal = accumulate(leng_vec.begin(), leng_vec.end() - 1, 0);
                recreate = design.substr(0, subtotal);
                pos = subtotal;
                towel_length = leng_vec.back() + 1;
                leng_vec.pop_back();
                twl.pop_back();
                continue;
            }
            if (towel_length > max_towel_length && leng_vec.size() == 0) {
                finished = true;
                recreate = "";
                continue;
            }
            else if (towel_length > max_towel_length) {
                int subtotal = accumulate(leng_vec.begin(), leng_vec.end() - 1, 0);
                recreate = design.substr(0, subtotal);
                pos = subtotal;
                towel_length = leng_vec.back() + 1;
                leng_vec.pop_back();
                twl.pop_back();
                continue;
            }
            string test = design.substr(pos, towel_length);
            if (towel_length > test.length()) {
                int subtotal = accumulate(leng_vec.begin(), leng_vec.end() - 1, 0);
                recreate = design.substr(0, subtotal);
                pos = subtotal;
                towel_length = leng_vec.back() + 1;
                leng_vec.pop_back();
                twl.pop_back();
                continue;
            }
            //cout << test << ", " << towel_length << "\n";
            if (towels.find(test) != towels.end()) {
                recreate += test;
                pos += towel_length;
                leng_vec.push_back(towel_length);
                towel_length = 1;
                twl.push_back(test);
            }
            else {
                towel_length++;
            }

        }

    }
    cout << "There are " << sum << " valid designs with available towel patterns" << "\n";
}

*/
void pt_2_new(vector<string> designs) {
    unsigned long long int sum = 0;
    for (string design:designs)
    {
        sum += pt_2_recursive(design);
    }
    cout << "There are " << sum << " valid permutations of designs with available towel patterns" << "\n";
}

int main()
{
    cout << "Hello World!\n"; 
    auto comp = [](const string& a, const string& b) -> bool
        { return a.length() < b.length() or (a.length() == b.length() and a < b); };
    vector<string> designs;
    string tp;
    fstream file;
    file.open("D:\\!Advent_of_Code\\2024\\AoC_day_19\\input.txt");
    bool past_blank = false;
    while (getline(file, tp)) {
        if (tp == "") {
            past_blank = true;
            continue;
        }
        if (past_blank) {
            designs.push_back(tp);
        }
        else {
            size_t loc = tp.find(',');
            while (loc != string::npos) {
                if (tp[0] == ' ') {
                    towels.insert(tp.substr(1, loc-1));
                }
                else {
                    towels.insert(tp.substr(0, loc));
                }
                tp.erase(0, loc + 1);
                loc = tp.find(',');
            }
            towels.insert(tp.substr(1,string::npos));
        }
    }
    file.close();
    for (auto a : towels) {
        if (a.length() > max_length) {
            max_length = a.length();
        }
    }
    pt_1(towels, designs);
    
    pt_2_new(designs);
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
