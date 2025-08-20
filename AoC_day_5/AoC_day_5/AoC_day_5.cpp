// AoC_day_5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <algorithm>
class My_Filter {
public:
    int target_num;
    std::list<int> to_filter;
    
    My_Filter(int a, int b) {
        target_num = a;
        to_filter.push_back(b);
    }
};
bool check_validity(std::list<int> row, My_Filter filter) {
    std::list<int>::iterator findIter = std::find(row.begin(), row.end(), filter.target_num);
    if (findIter == row.end()) {
        return true;
    }
    std::list<int>::iterator it = row.begin();
    while (it != findIter) {
        int to_test = *it;
        std::list<int>::iterator filter_it = filter.to_filter.begin();
        while (filter_it != filter.to_filter.end()) {
            int test = *filter_it;
            if (to_test == test) {
                return false;
            }
            filter_it++;
        }
        it++;
    }
    return true;
}
int main()
{
    std::list<My_Filter> all_filters;
    std::fstream file;
    file.open("D:\\!Advent_of_Code\\2024\\AoC_day_5\\test.txt");
    if (file.is_open()) {
        bool first_or_second_stage = false;
        std::string tp;
        int pt_1_sum = 0;
        while (getline(file, tp)) {
            if (tp == "\n") {
                first_or_second_stage = true;
                getline(file, tp);
            }
            if (first_or_second_stage) {
                std::list<int> row;
                int end = tp.find(',');
                while (end != -1) {
                    row.push_back(std::stoi(tp.substr(0, end)));
                    tp.erase(tp.begin(), tp.begin() + end + 1);
                    end = tp.find(',');

                }
                row.push_back(std::stoi(tp.substr(0, end)));
                auto it = all_filters.begin();
                int midpoint = row.size() / 2;
                bool succeed = true;
                while (it != all_filters.end()) {
                    if (!check_validity(row, *it)) {
                        succeed = false;
                        break;
                    }
                    it++;
                }
                if (succeed) {
                    auto new_it = row.begin();
                    std::advance(new_it, midpoint);
                    pt_1_sum += *new_it;
                }
            }
            else {
                int after = std::stoi(tp.substr(0, tp.find('|')));
                tp.erase(0, tp.find('|') + 1);
                int before = std::stoi(tp);
                auto it = all_filters.begin();
                bool in_filter = false;
                while (it != all_filters.end()) {
                    /*
                    My_Filter test = *it;
                    int to_test = test.target_num;
                    if (to_test == after) {
                        in_filter = true;
                        test.to_filter.push_back(before);
                        std::replace(all_filters.begin(), all_filters.end(), *it, test);
                        break;
                    }*/
                    it++;
                }
                if (!in_filter) {
                    My_Filter new_filter(after, before);
                    all_filters.push_back(new_filter);
                }
            }
        }
        file.close();
        std::cout << "The Sum of Midpoints is: " << pt_1_sum;
    }
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
