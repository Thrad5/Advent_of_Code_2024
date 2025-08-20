// AoC_day_15_part_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <tuple>
#include <vector>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
COORD origin = { 0,0 };
//Test 2
//const int x = 8;
//const int y = 8;
//Test 1
//const int x = 20;
//const int y = 10;
//Input
const int x = 100;
const int y = 50;
//Test 3
//const int x = 14;
//const int y = 5;
//Test 4
//const int x = 14;
//const int y = 7;

int cordinateSum(char map[y][x]) {
    int sum = 0;
    for (int v_y = 0; v_y < y; v_y++) {
        for (int v_x = 0; v_x < x; v_x++) {
            if (map[v_y][v_x] == '[') {
                sum += 100 * v_y + v_x;
            }
        }
    }
    return sum;
}


int checkNext(char map[y][x], std::vector<int> vec) {
    if (map[vec[0]][vec[1]] == '#') {
        return 0;
    }
    else if (map[vec[0]][vec[1]] == '.') {
        return 1;
    }
    else if (map[vec[0]][vec[1]] == ']') {
        return 2;
    }
    else {
        return 3;
    }
}

std::tuple<bool,std::vector<std::vector<int>>,std::vector<char>> checkDown(char map[y][x], int pos[2]) {
    std::vector<std::vector<int>> loc_to_check = { {pos[0] + 1,pos[1]} };
    std::vector<std::vector<int>> all_locs = { {pos[0] + 1,pos[1]}};
    std::vector<char> loc_val = { '@' };
    while (loc_to_check.size()!=0){
        std::vector<std::vector<int>> new_loc;
        for (int i = 0; i < loc_to_check.size(); i++) {
            int a = checkNext(map, loc_to_check[i]);
            if (a == 0) {
                return std::make_tuple(false,all_locs,loc_val);
            }
            else if (a == 2) {
                std::vector<int> g = { loc_to_check[i][0] + 1,loc_to_check[i][1] };
                if (std::find(new_loc.begin(), new_loc.end(), g) == new_loc.end()) {
                    new_loc.push_back(g);
                    all_locs.push_back(g);
                    loc_val.push_back(']');
                    loc_val.push_back('[');
                    g[1] = g[1] - 1;
                    new_loc.push_back(g);
                    all_locs.push_back(g);
                }
            }
            else if (a == 3) {
                std::vector<int> g = { loc_to_check[i][0] + 1,loc_to_check[i][1] };
                if (std::find(new_loc.begin(), new_loc.end(), g) == new_loc.end()) {
                    new_loc.push_back(g);
                    all_locs.push_back(g);
                    loc_val.push_back('[');
                    loc_val.push_back(']');
                    g[1] = g[1] + 1;
                    new_loc.push_back(g);
                    all_locs.push_back(g);
                }
            }
        }
        loc_to_check = new_loc;
    }
    return std::make_tuple(true,all_locs,loc_val);
}

std::tuple<bool, std::vector<std::vector<int>>,std::vector<char>> checkUp(char map[y][x], int pos[2]) {
    std::vector<std::vector<int>> loc_to_check = { {pos[0] - 1,pos[1]} };
    std::vector<std::vector<int>> all_locs = { {pos[0] - 1,pos[1]}};
    std::vector<char> loc_val = { '@' };
    while (loc_to_check.size() != 0) {
        std::vector<std::vector<int>> new_loc;
        for (int i = 0; i < loc_to_check.size(); i++) {
            int a = checkNext(map, loc_to_check[i]);
            if (a == 0) {
                return std::make_tuple(false, all_locs, loc_val);
            }
            else if (a == 2) {
                std::vector<int> g = { loc_to_check[i][0] - 1,loc_to_check[i][1] };
                if (std::find(new_loc.begin(), new_loc.end(), g) == new_loc.end()) {
                    new_loc.push_back(g);
                    all_locs.push_back(g);
                    loc_val.push_back(']');
                    loc_val.push_back('[');
                    g[1] = g[1] - 1;
                    new_loc.push_back(g);
                    all_locs.push_back(g);
                }
            }
            else if (a == 3) {
                std::vector<int> g = { loc_to_check[i][0] - 1,loc_to_check[i][1] };
                if (std::find(new_loc.begin(), new_loc.end(), g) == new_loc.end()) {
                    new_loc.push_back(g);
                    all_locs.push_back(g);
                    loc_val.push_back('[');
                    loc_val.push_back(']');
                    g[1] = g[1] + 1;
                    new_loc.push_back(g);
                    all_locs.push_back(g);
                }
            }
        }
        loc_to_check = new_loc;
    }
    return std::make_tuple(true, all_locs, loc_val);
}

std::tuple<bool, std::vector<std::vector<int>>,std::vector<char>> checkLeft(char map[y][x], int pos[2]) {
    std::vector<int> loc_to_check = { pos[0],pos[1] - 1 };
    std::vector<std::vector<int>> all_locs;
    std::vector<char> loc_val;
    int a = checkNext(map,loc_to_check);
    while (a != 0 && a != 1) {
        all_locs.push_back(loc_to_check);
        loc_val.push_back(map[loc_to_check[0]][loc_to_check[1] + 1]);
        loc_to_check[1] = loc_to_check[1] - 1;
        a = checkNext(map, loc_to_check);
    }
    if (a == 0) {
        return std::make_tuple(false, all_locs,loc_val);
    }
    else {
        all_locs.push_back(loc_to_check);
        loc_val.push_back(map[loc_to_check[0]][loc_to_check[1] + 1]);
        loc_to_check[1] = loc_to_check[1] - 1;
        return std::make_tuple(true, all_locs,loc_val);
    }
}

std::tuple<bool, std::vector<std::vector<int>>,std::vector<char>> checkRight(char map[y][x], int pos[2]) {
    std::vector<int> loc_to_check = { pos[0],pos[1] + 1 };
    std::vector<std::vector<int>> all_locs;
    std::vector<char> loc_val;
    int a = checkNext(map, loc_to_check);
    while (a != 0 && a != 1) {
        all_locs.push_back(loc_to_check);
        loc_val.push_back(map[loc_to_check[0]][loc_to_check[1] - 1]);
        loc_to_check[1] = loc_to_check[1] + 1;
        a = checkNext(map, loc_to_check);
    }
    if (a == 0) {
        return std::make_tuple(false, all_locs, loc_val);
    }
    else {
        all_locs.push_back(loc_to_check);
        loc_val.push_back(map[loc_to_check[0]][loc_to_check[1] - 1]);
        return std::make_tuple(true, all_locs, loc_val);
    }
}


void printFrame(char map[y][x],char ins) {
    for (int v_y = 0; v_y < y; v_y++) {
        for (int v_x = 0; v_x < x; v_x++) {
            std::cout << map[v_y][v_x];
        }
        std::cout << '\n';
    }
    std::cout << std::string(x, '*') << "\n";
    std::cout << "Instruction:" << ins << " GPS Sum: " << cordinateSum(map) << "\n\n";
}



int main()
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, 800, 1200, TRUE);
    //SetConsoleCursorPosition(hConsole, origin);
    std::fstream file;
    file.open("D:\\!Advent_of_Code\\2024\\AoC_day_15_part_2\\input.txt");
    char map[y][x];
    bool in_instructions = false;
    std::string tp;
    std::string inst = "";
    int position[2] = { 0,0 };
    int y_pos = 0;
    while (getline(file, tp)) {
        if (tp == "") {
            in_instructions = true;
        }
        else {
            if (in_instructions) {
                inst.append(tp);
            }
            else {
                for (int i = 0; i < tp.length(); i++) {
                    if (tp[i] == '@') {
                        position[0] = y_pos;
                        position[1] = i*2;
                        map[y_pos][i * 2] = '@';
                        map[y_pos][i * 2 + 1] = '.';
                    }
                    else if (tp[i] == '#') {
                        map[y_pos][i * 2] = '#';
                        map[y_pos][i * 2 + 1] = '#';
                    }
                    else if (tp[i] == 'O') {
                        map[y_pos][i * 2] = '[';
                        map[y_pos][i * 2 + 1] = ']';
                    }
                    else{
                        map[y_pos][i * 2] = '.';
                        map[y_pos][i * 2 + 1] = '.';
                    }
                }
            }
            y_pos++;
        }

    }
    printFrame(map,inst[0]);
    
    //SetConsoleCursorPosition(hConsole, origin);
    std::vector < std::vector<int>> all_locs;
    std::vector<char> val_loc;
    bool free_space = false;
    for (int i = 0; i < inst.length(); i++) {
        SetConsoleCursorPosition(hConsole, origin);
        if (inst[i] == '^') {
            std::tie(free_space, all_locs,val_loc) = checkUp(map, position);
            if (free_space) {
                for (int i = 0; i < all_locs.size(); i++) {
                    map[all_locs[i][0] + 1][all_locs[i][1]] = '.';
                }
                for (int i = 0; i < all_locs.size(); i++) {
                    if (val_loc[i] == '@') {
                        position[0] = all_locs[i][0];
                        position[1] = all_locs[i][1];
                    }
                    map[all_locs[i][0]][all_locs[i][1]] = val_loc[i];
                }
            }
        }
        else if (inst[i] == '>') {
            std::tie(free_space, all_locs,val_loc) = checkRight(map, position);
            if (free_space) {
                for (int i = 0; i < all_locs.size(); i++) {
                    map[all_locs[i][0]][all_locs[i][1] - 1] = '.';
                }
                for (int i = 0; i < all_locs.size(); i++) {
                    if (val_loc[i] == '@') {
                        position[0] = all_locs[i][0];
                        position[1] = all_locs[i][1];
                    }
                    map[all_locs[i][0]][all_locs[i][1]] = val_loc[i];
                }
            }
        }
        else if (inst[i] == 'v') {
            std::tie(free_space, all_locs, val_loc) = checkDown(map, position);
            if (free_space) {
                for (int i = 0; i < all_locs.size(); i++) {
                    map[all_locs[i][0] - 1][all_locs[i][1]] = '.';
                }
                for (int i = 0; i < all_locs.size(); i++) {
                    if (val_loc[i] == '@') {
                        position[0] = all_locs[i][0];
                        position[1] = all_locs[i][1];
                    }
                    map[all_locs[i][0]][all_locs[i][1]] = val_loc[i];
                }
            }
        }
        else if (inst[i] == '<') {
            std::tie(free_space, all_locs,val_loc) = checkLeft(map, position);
            if (free_space) {
                for (int i = 0; i < all_locs.size(); i++) {
                    map[all_locs[i][0]][all_locs[i][1] + 1] = '.';
                }
                for (int i = 0; i < all_locs.size(); i++) {
                    if (val_loc[i] == '@') {
                        position[0] = all_locs[i][0];
                        position[1] = all_locs[i][1];
                    }
                    map[all_locs[i][0]][all_locs[i][1]] = val_loc[i];
                }
            }
        }
        printFrame(map,inst[i]);
    }
    printFrame(map,inst[inst.length()-1]);
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
