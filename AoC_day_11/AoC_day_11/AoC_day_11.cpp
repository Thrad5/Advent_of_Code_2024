// AoC_day_11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <cmath>
#include <tuple>

void printList(std::list<unsigned long long int> to_print) {

    for (auto v : to_print) {
        std::cout << v << ", ";
    }
    std::cout << "\n";
}
void printList(std::list<int> to_print) {

    for (auto v : to_print) {
        std::cout << v << ", ";
    }
    std::cout << "\n";
}

void printList(std::list<std::list< int>> to_print) {
    std::cout << "[\n";
    for (auto v : to_print) {
        std::cout << "    ";
        printList(v);
    }
    std::cout << "]\n";
}

std::tuple<std::list<unsigned long long int>,std::list<int>> blink(std::list<unsigned long long int> to_blink) {
    auto it = to_blink.begin();
    std::list<int> singledigit;
    while (it != to_blink.end()) {
        if (*it > 10) {
        double to_test = *it;
        int test = floor(log10(to_test));
        if (to_test == 0) {
            *it = 1;
            it++;
        }
        else if (test % 2 == 1) {
            int devisor = ceil(floor(log10(to_test)) / 2);
            int pow = std::pow(10, devisor);
            unsigned long long int new_it = floor(to_test / (std::pow(10, devisor)));
            unsigned long long int scnd_hlf = *it % pow;
            *it = new_it;
            it++;
            to_blink.insert(it, scnd_hlf);

        }
        else {
            *it = *it * 2024;
            it++;
        }
        }
        else {
            unsigned long long int test = *it;
            auto count = to_blink.remove(test);
            for (int i = 0; i < count; i++) {
                singledigit.push_back(test);
            }
            it = to_blink.begin();
        }
    }
    return std::make_tuple(to_blink,singledigit);
}


int main()
{
    std::list<unsigned long long int> input = { 0,1,10,99,999 };
    //std::list<unsigned long int> input = { 125,17 };
    //std::list<unsigned long long int> input = { 200 };
    std::list<int> known_loop_digits;
    int number_of_blinks = 1;
    std::list<std::list<int>> groups_of_single;
    std::list<int> triplets;
    for (int i = 0; i < number_of_blinks; i++) {
        std::list<int> singledigit;
        std::cout << i << "\n";
        //printList(input);
        auto it_2 = input.begin();
        while (it_2 != input.end()) {
            float test = *it_2;
            float logs = log10(test);
            if (2 <= logs and logs <= 3) {
                //std::cout << *it_2 << ", " << log10(test) << ";  ";
                triplets.push_back(*it_2);
            }
            it_2++;
        }
        //std::cout << "\n";
        tie(input,singledigit) = blink(input);
        auto it = input.begin();
        while (it != input.end()) {
            auto truth = std::find(triplets.begin(), triplets.end(), *it);
            if (truth != triplets.end()) {
                known_loop_digits.push_back(*it);
                auto to_rem = *it;
                input.remove(to_rem);
                it = input.begin();
            }
            else {
                it++;
            }
        }
        groups_of_single.push_back(singledigit);
    }
    std::cout << "The number of stones is " << input.size() << "\n There are" << known_loop_digits.size() <<" stones which loop with three digits.\n";
    printList(known_loop_digits);
    printList(input);
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
