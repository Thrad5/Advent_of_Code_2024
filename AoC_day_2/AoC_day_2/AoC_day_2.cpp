// AoC_day_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <list>
void printList(std::list<int> mylist) {
    for (auto v : mylist) {
        std::cout << v << ", ";
    }
    std::cout << "\n";
}

void printNestedList(std::list<std::list<int>> nested) {
    std::cout << "[\n";
    for (auto g : nested) {
        std::cout << "    ";
        printList(g);
    }
    std::cout << "]\n";
}

std::list<signed int> seperateRow(std::string row) {
    std::list<signed int> seperated;
    std::string del = " ";
    auto pos = row.find(del);
    while (pos != std::string::npos) {
        seperated.push_back(std::stoi(row.substr(0, pos)));
        row.erase(0, pos + del.length());
        pos = row.find(del);
    }
    seperated.push_back(std::stoi(row));
    return seperated;
}

bool isSuccessful(std::list<int> to_test) {
    auto test_it = to_test.begin();
    int inc_or_dec = 0;
    signed int a = *test_it;
    test_it++;
    while (test_it != to_test.end()) {
        signed int b = *test_it - a;
        if (inc_or_dec == 0) {
            if (0 < b) {
                if (b < 4) {
                    inc_or_dec = 1;
                }
                else {
                    return false;
                }
            }
            else if (0 > b) {
                if (b > -4) {
                    inc_or_dec = 2;
                }
                else {
                    return false;
                }
            }
            else {
                return false;
            }
        }
        else if (inc_or_dec == 1) {
            if (b <= 0) {
                return false;
            }
            else if (b >= 4) {
                return false;
            }
        }
        else if (inc_or_dec == 2) {
            if (b >= 0) {
                return false;
            }
            else if (b <= -4) {
                return false;
            }
        }
        a = *test_it;
        test_it++;
    }
    return true;
}

bool testRemOne(std::list<int> to_test) {
    auto it = to_test.begin();

    int i = 0;
    //std::cout << "\nNew test\n";
    while (it != to_test.end()) {
        //std::cout << "Run: " << i << "\n";
        int a = *it;
        //std::cout << a << "\n";
        to_test.erase(it);
        //printList(to_test);
        bool is_run_success = isSuccessful(to_test);
        if (is_run_success) {
            return true;
        }
        auto replace = to_test.begin();
        if (i == to_test.size()) {
            break;
        }
        if (i == 0) {
            to_test.push_front(a);
            //std::cout << "Pushing To Front";
        }
        else {
            std::advance(replace, i);
            to_test.insert(replace, a);
        }
        
        //printList(to_test);
        it = to_test.begin();
        std::advance(it, i+1);
        i++;
        //std::cout << i << "\n";
        
    }
    return false;
}





int main()
{
    std::fstream file;
    file.open("D:\\!Advent_of_Code\\2024\\AoC_day_2\\input.txt");
    if (file.is_open()) {
        std::string tp;
        int successes = 0;
        std::list<std::list<signed int>> failed_Trials;

        while (std::getline(file, tp)) {
            std::list<signed int> int_list = seperateRow(tp);
            bool successful = isSuccessful(int_list);
            if (successful) {
                successes++;
            }
            else {
                failed_Trials.push_back(int_list);
            }
        }
        std::cout << "There were: " << successes << " successes.\n";
        auto nested_it = failed_Trials.begin();
        while (nested_it != failed_Trials.end()) {
            bool new_success = testRemOne(*nested_it);
            if (new_success) {
                successes++;
            }
            nested_it++;
        }
        std::cout << "There were: " << successes << " successes using the Problem Dampner.\n";
    }
    else {
        std::cout << "No Recognised File";
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
