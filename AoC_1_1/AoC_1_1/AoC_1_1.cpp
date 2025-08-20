// AoC_1_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>

void print_list(std::list<int> mylist) {
    for (auto v : mylist) {
        std::cout << v << ", ";
    }
    std::cout << "\n";
}

int main()
{
    std::fstream file;
    file.open("D:\\!Advent_of_Code\\2024\\AoC_1_1\\input.txt", std::ios::in);
    std::list<int> list_1 = { 9999999 };
    std::list<int> list_2 = { 9999999 };
    std::string tp_1;
    std::string tp_2;
    int line = 0;
    if (file.is_open()) {
        std::string tp;
        while (getline(file, tp)) {
            //seperate the two lists
            tp_1 = tp.substr(0, tp.find('   '));
            tp_2 = tp.substr(tp.find('   '));
            int to_ins_1 = std::stoi(tp_1);
            int to_ins_2 = std::stoi(tp_2);
            if (line == 0) {
                list_1.push_front(to_ins_1);
                list_2.push_front(to_ins_2);
            }
            else {
                auto it_1 = list_1.begin();
                auto it_2 = list_2.begin();
                bool have_Inserted_1 = false;
                bool have_Inserted_2 = false;
                for (int i = 0; i < line+1; i++) {
                    if (to_ins_1 < *it_1 && !have_Inserted_1) {
                        list_1.insert(it_1, to_ins_1);
                        have_Inserted_1 = true;
                    }
                    if (to_ins_2 < *it_2 && !have_Inserted_2) {
                        list_2.insert(it_2, to_ins_2);
                        have_Inserted_2 = true;
                    }
                    it_1++;
                    it_2++;
                }
                
            }
            line++;

        }
        file.close();
        list_1.pop_back();
        list_2.pop_back();
        //print_list(list_1);
        auto it_1 = list_1.begin();
        auto it_2 = list_2.begin();
        int sum = 0;
        while (it_1 != list_1.end()) {
            int diff = abs(*it_1 - *it_2);
            sum = sum + diff;
            it_1++;
            it_2++;
        }
        std::cout << sum << "\n";
        it_1 = list_1.begin();
        std::list<int> unique_in_1 = { *it_1 };
        std::list<int> number_in_1 = { 9999 };
        int unique = 1;
        auto it_uq_in_1 = unique_in_1.begin();
        it_1++;
        while (it_1 != list_1.end()) {
            
            
            if (*it_1 == *it_uq_in_1) {
                unique++;
            }
            else {
                std::replace(number_in_1.begin(), number_in_1.end(), 9999, unique);
                number_in_1.push_back(9999);
                unique_in_1.push_back(*it_1);
                it_uq_in_1++;
                unique = 1;
            }
            it_1++;
        }
        std::replace(number_in_1.begin(), number_in_1.end(), 9999, unique);
        //print_list(unique_in_1);
        //print_list(number_in_1);
        it_2 = list_2.begin();
        int new_sum = 0;
        while (it_2 != list_2.end()) {
            it_uq_in_1 = unique_in_1.begin();
            auto it_num_in_1 = number_in_1.begin();
            for (int i = 0; i < unique_in_1.size(); i++) {
                if (*it_2 == *it_uq_in_1) {
                    new_sum = new_sum + (*it_uq_in_1 * *it_num_in_1);
                    break;
                }
                it_uq_in_1++;
                it_num_in_1++;
            }
            it_2++;
        }
        std::cout << new_sum << "\n";
    }
    std::cout << "Hello World!\n";
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
