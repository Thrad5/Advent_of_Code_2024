// AoC_day 15.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <tuple>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
COORD origin = { 0,0 };
//const int x = 8;
//const int y = 8;
const int x = 10;
const int y = 10;
//const int x = 50;
//const int y = 50;
//const int x = 7;
//const int y = 5;

int cordinateSum(char map[y][x]) {
    int sum = 0;
    for (int v_y = 0; v_y < y; v_y++) {
        for (int v_x = 0; v_x < x; v_x++) {
            if (map[v_y][v_x] == 'O') {
                sum += 100 * v_y + v_x;
            }
        }
    }
    return sum;
}

void printFrame(char map[y][x]) {
    for (int v_y = 0; v_y < y; v_y++) {
        for (int v_x = 0; v_x < x; v_x++) {
            std::cout << map[v_y][v_x];
        }
        std::cout << '\n';
    }
    std::cout << std::string(y, '*') << "\n";
    std::cout << " GPS Sum: " << cordinateSum(map) << "\n\n";
}

std::tuple<bool, int, int, int, int, bool> upCheck(char map[y][x], int pos[2]) {
    int offset = 1;
    int rob_new_pos[2] = { pos[0] - offset,pos[1] };
    int box_new_pos[2] = { 0,pos[1] };
    bool move_box = false;
    while (map[pos[0] - offset][pos[1]] != '#') {
        if (map[pos[0] - offset][pos[1]] == '.') {
            box_new_pos[0] = pos[0] - offset;
            return std::make_tuple(true, rob_new_pos[0],rob_new_pos[1],box_new_pos[0], box_new_pos[1], move_box);
        }
        else if (map[pos[0] - offset][pos[1]] == 'O') {
            move_box = true;
        }
        offset++;
    }
    return std::make_tuple(false, 0, 0, 0, 0, false);
}

std::tuple<bool, int, int, int, int, bool> downCheck(char map[y][x], int pos[2]) {
    int offset = 1;
    int rob_new_pos[2] = { pos[0] + offset,pos[1] };
    int box_new_pos[2] = { 0,pos[1] };
    bool move_box = false;
    while (map[pos[0] + offset][pos[1]] != '#') {
        if (map[pos[0] + offset][pos[1]] == '.') {
            box_new_pos[0] = pos[0] + offset;
            return std::make_tuple(true, rob_new_pos[0], rob_new_pos[1], box_new_pos[0], box_new_pos[1], move_box);
        }
        else if (map[pos[0] + offset][pos[1]] == 'O') {
            move_box = true;
        }
        offset++;
    }
    return std::make_tuple(false, 0, 0, 0, 0, false);
}

std::tuple<bool, int, int, int, int, bool> leftCheck(char map[y][x], int pos[2]) {
    int offset = 1;
    int rob_new_pos[2] = { pos[0],pos[1] - offset };
    int box_new_pos[2] = { pos[0],0 };
    bool move_box = false;
    while (map[pos[0]][pos[1] - offset] != '#') {
        if (map[pos[0]][pos[1] - offset] == '.') {
            box_new_pos[1] = pos[1] - offset;
            return std::make_tuple(true, rob_new_pos[0], rob_new_pos[1], box_new_pos[0], box_new_pos[1], move_box);
        }
        else if (map[pos[0]][pos[1] - offset] == 'O') {
            move_box = true;
        }
        offset++;
    }
    return std::make_tuple(false, 0, 0, 0, 0, false);
}

std::tuple<bool, int, int, int, int, bool> rightCheck(char map[y][x], int pos[2]) {
    int offset = 1;
    int rob_new_pos[2] = { pos[0],pos[1] + offset };
    int box_new_pos[2] = { pos[0],0 };
    bool move_box = false;
    while (map[pos[0]][pos[1] + offset] != '#') {
        if (map[pos[0]][pos[1] + offset] == '.') {
            box_new_pos[1] = pos[1] + offset;
            return std::make_tuple(true, rob_new_pos[0], rob_new_pos[1], box_new_pos[0], box_new_pos[1], move_box);
        }
        else if (map[pos[0]][pos[1] + offset] == 'O') {
            move_box = true;
        }
        offset++;
    }
    return std::make_tuple(false, 0, 0, 0, 0, false);
}

int main()
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, 800, 1200, TRUE);
    //SetConsoleCursorPosition(hConsole, origin);
    std::fstream file;
    file.open("D:\\!Advent_of_Code\\2024\\AoC_day_15\\input.txt");
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
                        position[1] = i;
                    }
                    map[y_pos][i] = tp[i];
                }
            }
            y_pos++;
        }
        
    }
    printFrame(map);
    //SetConsoleCursorPosition(hConsole, origin);
    int new_pos[2] = { 0,0 };
    int box_pos[2] = { 0,0 };
    bool free_space = false;
    bool moving_box = false;
    for (int i = 0; i < inst.length(); i++) {
        //etConsoleCursorPosition(hConsole, origin);
        if (inst[i] == '^') {
            std::tie(free_space, new_pos[0], new_pos[1], box_pos[0], box_pos[1], moving_box) = upCheck(map, position);
            if (free_space) {
                map[position[0]][position[1]] = '.';
                map[new_pos[0]][new_pos[1]] = '@';
                if (moving_box) {
                    map[box_pos[0]][box_pos[1]] = 'O';
                }
                position[0] = new_pos[0];
                position[1] = new_pos[1];
            }
        }
        else if (inst[i] == '>') {
            std::tie(free_space, new_pos[0], new_pos[1], box_pos[0], box_pos[1], moving_box) = rightCheck(map, position);
            if (free_space) {
                map[position[0]][position[1]] = '.';
                map[new_pos[0]][new_pos[1]] = '@';
                if (moving_box) {
                    map[box_pos[0]][box_pos[1]] = 'O';
                }
                position[0] = new_pos[0];
                position[1] = new_pos[1];
            }
        }
        else if (inst[i] == 'v') {
            std::tie(free_space, new_pos[0], new_pos[1], box_pos[0], box_pos[1], moving_box) = downCheck(map, position);
            if (free_space) {
                map[position[0]][position[1]] = '.';
                map[new_pos[0]][new_pos[1]] = '@';
                if (moving_box) {
                    map[box_pos[0]][box_pos[1]] = 'O';
                }
                position[0] = new_pos[0];
                position[1] = new_pos[1];
            }
        }
        else if (inst[i] == '<') {
            std::tie(free_space, new_pos[0], new_pos[1], box_pos[0], box_pos[1], moving_box) = leftCheck(map, position);
            if (free_space) {
                map[position[0]][position[1]] = '.';
                map[new_pos[0]][new_pos[1]] = '@';
                if (moving_box) {
                    map[box_pos[0]][box_pos[1]] = 'O';
                }
                position[0] = new_pos[0];
                position[1] = new_pos[1];
            }
        }
    }
    printFrame(map);
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
