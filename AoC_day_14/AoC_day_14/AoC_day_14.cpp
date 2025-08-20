// AoC_day_14.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <vector>
//            y,x
//int si[2] = { 7,11 };
//int hlf_line[2] = { 3,5 };
const int si[2] = { 103,101 };
const int hlf_line[2] = { 51,50 };

std::vector<int> ownUpdatePos(std::vector<int> vec) {
    vec[0] = (vec[0] + 100*vec[2]) % si[0];
    vec[1] = (vec[1] + 100*vec[3]) % si[1];
    return vec;
}



int main()
{
    std::fstream file;
    file.open("D:\\!Advent_of_Code\\2024\\AoC_day_14\\input.txt");
    std::string tp;
    std::list < std::vector<int>> all_robots;
    while (getline(file, tp)) {
        //std::cout << "New Line\n";
        std::vector<int> robot = { 0,0,0,0 };
        tp.erase(0, 2);
        size_t com = tp.find(',');
        robot[1] = std::stoi(tp.substr(0, com));
        tp.erase(0, com + 1);
        com = tp.find(' ');
        robot[0] = std::stoi(tp.substr(0, com));

        tp.erase(0, com + 3);
        com = tp.find(',');
        robot[3] = std::stoi(tp.substr(0, com));
        tp.erase(0, com + 1);
        robot[2] = std::stoi(tp);
        //std::cout << "Line\n";
        //td::cout << robot[0] << "," << robot[1] << "," << robot[2] << "," << robot[3];
        //std::cout << "\n\n";
        all_robots.push_back(robot);
    }
    //std::cout << "-6%5 is: " << -6 % 5 << "\n";
    int length = all_robots.size();
    std::list<float> variance_x_lst;
    std::list<float> variance_y_lst;
    for (int i = 0; i < 7603; i++) {
        //float mean_x = 0;
        //float mean_y = 0;
        auto it = all_robots.begin();
        int room[103][101] = { 0 };
        while (it != all_robots.end()) {
            std::vector<int> robot = *it;
            robot[0] = (robot[0] + robot[2]) % si[0];
            robot[1] = (robot[1] + robot[3]) % si[1];
            if (robot[0] < 0) {
                robot[0] += si[0];
            }
            if (robot[1] < 0) {
                robot[1] += si[1];
            }
            //mean_x += robot[1];
            //mean_y += robot[0];
            room[robot[0]][robot[1]] += 1;
            *it = robot;
            it++;
        }
        //mean_x = mean_x / length;
        //mean_y = mean_y / length;
        //float var_x = 0;
        //float var_y = 0;
        //it = all_robots.begin();
        //while (it != all_robots.end()) {
            //std::vector<int>robot = *it;
            //var_x += (robot[1] - mean_x) * (robot[1] - mean_x);
            //var_y += (robot[0] - mean_y) * (robot[0] - mean_y);
            //it++;
        //}
        //std::cout << "Second" << i + 1 << ": x_var: " << var_x << " y_var: " << var_y << "\n";
        //variance_x_lst.push_back(var_x/length);
        //variance_y_lst.push_back(var_y/length);
        //if(i<0){
            //std::cout << "\nAfter second: 7603\n";
            //for (int j = 0; j < 103; j++) {
                //for (int k = 0; k < 101; k++) {
                    //std::cout << room[j][k];
                //}
                //std::cout << '\n';
            //}
        //}
        
        //std::cout << robot[0] << "," << robot[1] << "," << robot[2] << "," << robot[3] <<"\n";
    }
    int room[103][101] = { 0 };
    auto it = all_robots.begin();
    while (it != all_robots.end()) {
        std::vector<int> robot = *it;
        room[robot[0]][robot[1]] += 1;
        it++;
    }
    std::cout << "\nAfter second: 7603\n";
    for (int j = 0; j < 103; j++) {
        for (int k = 0; k < 101; k++) {
            std::cout << room[j][k];
        }
        std::cout << '\n';
    }
    /*
    float min_x_var = 10000000000;
    auto it_x = variance_x_lst.begin();
    int x = 1;
    int min_x = 1;
    while (it_x != variance_x_lst.end()) {
        if (*it_x < min_x_var) {
            min_x = x;
            min_x_var = *it_x;
        }
        x++;
        it_x++;
    }
    float min_y_var = 100000000;
    auto it_y = variance_y_lst.begin();
    int y = 1;
    int min_y = 1;
    while (it_y != variance_y_lst.end()) {
        if (*it_y < min_y_var) {
            min_y = y;
            min_y_var = *it_y;
        }
        y++;
        it_y++;
    }
    variance_x_lst.sort();
    variance_y_lst.sort();
    std::cout << "Min x variance: " << min_x_var << " at time " << min_x << ". Min y variance: " << min_y_var << " at time: "<< min_y << "\n";

    int quart_1 = 0;
    int quart_2 = 0;
    int quart_3 = 0;
    int quart_4 = 0;
    auto it = all_robots.begin();
    while (it != all_robots.end()) {
        std::vector<int> robot = *it;
        if (robot[0] < hlf_line[0] && robot[1] < hlf_line[1]) {
            quart_1++;
        }
        else if (robot[0] < hlf_line[0] && robot[1] > hlf_line[1]) {
            quart_2++;
        }
        else if (robot[0] > hlf_line[0] && robot[1] < hlf_line[1]) {
            quart_3++;
        }
        else if (robot[0] > hlf_line[0] && robot[1] > hlf_line[1]) {
            quart_4++;
        }
        it++;
    }
    int total = quart_1 * quart_2 * quart_3 * quart_4;
    std::cout << "The answer to part 1 is: " << total;*/
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
