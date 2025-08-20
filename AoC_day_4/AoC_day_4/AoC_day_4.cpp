// AoC_day_4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
int main()
{
    auto start = std::chrono::system_clock::now();
    std::fstream file;
    file.open("D:\\!Advent_of_Code\\2024\\AoC_day_4\\input.txt");
    if (file.is_open()) {
        int length = 140;
        std::string word_search[140];
        //std::string word_search[140]
        int row_num = 0;
        std::string tp;
        while (getline(file, tp)) {
            word_search[row_num] = tp;
            row_num++;
        }
        file.close();
        auto pt_1_start = std::chrono::system_clock::now();
        int num_xmas = 0;
        for (int j = 0; j < length; j++) {
            for (int i = 0; i < length; i++) {
                if (i > 2 && j > 2) {
                    //Diagonals
                    if ((word_search[j - 3][i - 3] == 'X' && word_search[j - 2][i - 1] == 'M' && word_search[j - 1][i - 2] == 'A' && word_search[j][i - 3] == 'S') || (word_search[j - 3][i] == 'S' && word_search[j - 2][i - 1] == 'A' && word_search[j - 1][i - 2] == 'M' && word_search[j][i - 3] == 'X')) {
                        num_xmas++;
                    }
                    if ((word_search[j - 3][i - 3] == 'X' && word_search[j - 2][i - 2] == 'M' && word_search[j - 1][i - 1] == 'A' && word_search[j][i] == 'S') || (word_search[j - 3][i - 3] == 'S' && word_search[j - 2][i - 2] == 'A' && word_search[j - 1][i - 1] == 'M' && word_search[j][i] == 'X')) {
                        num_xmas++;
                    }
                }
                if ((j > 2)) {
                    //Verticals
                    if ((word_search[j - 3][i] == 'X' && word_search[j - 2][i] == 'M' && word_search[j - 1][i] == 'A' && word_search[j][i] == 'S') || (word_search[j - 3][i] == 'S' && word_search[j - 2][i] == 'A' && word_search[j - 1][i] == 'M' && word_search[j][i] == 'X')) {
                        num_xmas++;
                    }

                }
                if (i > 2) {
                    //Horizontals
                    if ((word_search[j][i - 3] == 'X' && word_search[j][i - 2] == 'M' && word_search[j][i - 1] == 'A' && word_search[j][i] == 'S') || (word_search[j][i - 3] == 'S' && word_search[j][i - 2] == 'A' && word_search[j][i - 1] == 'M' && word_search[j][i] == 'X')) {
                        num_xmas++;
                    }
                }
            }
        }
        std::cout << "The number of XMAS' horizontally and vertically forwards or backwards is: " << num_xmas << "\n";
        auto pt_2_start = std::chrono::system_clock::now();

        int num_exes = 0;
        for (int j = 2; j < length; j++) {
            for (int i = 2; i < length; i++) {
                if (word_search[j][i] == 'S' && word_search[j - 2][i] == 'S' && word_search[j][i - 2] == 'M' && word_search[j - 2][i - 2] == 'M' && word_search[j - 1][i - 1] == 'A') {
                    num_exes++;
                }
                else if (word_search[j][i] == 'M' && word_search[j][i - 2] == 'M' && word_search[j - 2][i] == 'S' && word_search[j - 2][i - 2] == 'S' && word_search[j - 1][i - 1] == 'A') {
                    num_exes++;
                }
                else if (word_search[j][i] == 'M' && word_search[j - 2][i] == 'M' && word_search[j][i - 2] == 'S' && word_search[j - 2][i - 2] == 'S' && word_search[j - 1][i - 1] == 'A') {
                    num_exes++;
                }
                else if (word_search[j][i] == 'S' && word_search[j][i - 2] == 'S' && word_search[j - 2][i] == 'M' && word_search[j - 2][i - 2] == 'M' && word_search[j - 1][i - 1] == 'A') {
                    num_exes++;
                }
            }
        }
        std::cout << "The number of X's is: " << num_exes <<"\n";
        auto end = std::chrono::system_clock::now();
        auto elapsed_total = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        auto elapsed_file_read = std::chrono::duration_cast<std::chrono::milliseconds>(pt_1_start - start);
        auto elapsed_pt_1 = std::chrono::duration_cast<std::chrono::milliseconds>(pt_2_start - pt_1_start);
        auto elapsed_pt_2 = std::chrono::duration_cast<std::chrono::milliseconds>(end - pt_2_start);
        std::cout << "This program took :" << elapsed_total.count() << "ms\nThis is brokend down by:\n";
        std::cout << "File Read: " << elapsed_file_read.count() << "ms\n";
        std::cout << "Part 1:    " << elapsed_pt_1.count() << "ms\n";
        std::cout << "Part 2:    " << elapsed_pt_2.count() << "ms\n";
    }
}