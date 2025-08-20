// AoC_day_21.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include <string>
#include <fstream>

using namespace std;

map<string, string> cache{
    {"AA","A"},   {"A^","<A"}, {"Av","<vA"},{"A>","vA"}, {"A<","<<vA"},
    {"^A",">A"},  {"^^","A"},  {"^v","vA"}, {"^>",">vA"},{"^<","<vA"},
    {"vA","^>A"}, {"v^","^A"}, {"vv","A"},  {"v>",">A"}, {"v<","<A"},
    {">A","^A"},  {">^","^<A"},{">v","<A"}, {">>","A"},  {"><","<<A"},
    {"<A","^>>A"},{"<^","^>A"},{"<v",">A"}, {"<>",">>A"},{"<<","A"}
};

map<string, string> add_cache;

bool is_neighbour(string pair_let) {
    if (pair_let[0] == 'A' && (pair_let[1] == '0' || pair_let[1] == '3')) { return true; }
    else if (pair_let[0] == '0' && (pair_let[1] == 'A' || pair_let[1] == '2')) { return true; }
    else if (pair_let[0] == '2' && (pair_let[1] == '0' || pair_let[1] == '1' || pair_let[1] == '5' || pair_let[1] == '3')) { return true; }
    else if (pair_let[0] == '1' && (pair_let[1] == '4' || pair_let[1] == '2')) { return true; }
    else if (pair_let[0] == '3' && (pair_let[1] == '6' || pair_let[1] == '2' || pair_let[1] == 'A')) { return true; }
    else if (pair_let[0] == '4' && (pair_let[1] == '5' || pair_let[1] == '7' || pair_let[1] == '1')) { return true; }
    else if (pair_let[0] == '5' && (pair_let[1] == '2' || pair_let[1] == '4' || pair_let[1] == '6' || pair_let[1] == '8')) { return true; }
    else if (pair_let[0] == '6' && (pair_let[1] == '5' || pair_let[1] == '3' || pair_let[1] == '9')) { return true; }
    else if (pair_let[0] == '7' && (pair_let[1] == '4' || pair_let[1] == '8')) { return true; }
    else if (pair_let[0] == '8' && (pair_let[1] == '5' || pair_let[1] == '7' || pair_let[1] == '9')) { return true; }
    else if (pair_let[0] == '9' && (pair_let[1] == '6' || pair_let[1] == '8')) { return true; }
    else { return false; }
}

string stage_1(string input) {
    string complete;
    for (int i = 1; i < input.length(); i++) {
        int diff = input[i - 1] - input[i];
        if (input.substr(i - 1, i + 1) == "A0") {
            complete = "<";
        }
        else if (input.substr(i - 1, i + 1) == "A3") {
            complete = "^";
        }
        else if (input.substr(i - 1, i + 1) == "3A") {
            complete = "v";
        }
        else if (input.substr(i - 1, i + 1) == "0A") {
            complete = ">";
        }
        else if (input[i - 1] == input[i]) {
            complete += "A";
        }
        else if (diff == -1) {
            complete += ">";
        }
        else if (diff == 1) {
            complete += "<";
        }
        else if (diff == -3) {
            complete += "^";
        }
        else if (diff == -2) {
            complete += "^";
        }
        else {
            complete += "v";
        }
    }
    return complete;
}
//string stage_2(string input){}

string stage_2(string input) {
    for (int i = 0; i < 2; i++) {
        string next_stage;
        input = "A" + input;
        for (int j = 1; j < input.length(); j++) {
            string test ;
            test += input[j - 1];
            test += input[j];
            //cout << test << ' ' << j << ",";
            next_stage += cache[test];
        }
        //cout << "\n";
        input = next_stage;
    }
    return input;
}

void pt_1(string input[5], int inp[5]) {
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        string trans = stage_1(input[i]);
        std::cout << trans << "\n";
        trans = stage_2(trans);
        if (i == 0) {
            cout << "0";
        }
        cout << inp[i] << "A:" << trans << "\n";
        cout << trans.length() << "\n\n";
        sum += trans.length() * inp[i];
    }
    cout << "The sum is " << sum << " .";
}


int main()
{
    std::cout << "Hello World!\n";
    string input[5] = { "A0022589963AA","A3699885200AA","A321147789963AA","A3654455663AA","A336987789963AA" };
    //string input[5] = { "A36996335563AA","A332114789963AA","A365447885200AA","A369877889963AA","A321147789663AA" };
    int inp[5] = { 29,980,179,456,379 };
    pt_1(input, inp);
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
