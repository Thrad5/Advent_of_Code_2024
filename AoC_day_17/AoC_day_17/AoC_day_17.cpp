// AoC_day_17.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
//Input

//Test
//int A = 729;
//int B = 0;
//int C = 0;
//std::vector<int> instructions = { 0,1,5,4,3,0 };



std::vector<int> programme(unsigned long long int A, unsigned long long int B, unsigned long long int C, std::vector<int> instructions) {
    std::vector<int> output;
    int counter = 0;
    while (counter < instructions.size()) {
        int operand = instructions[counter + 1];
        //std::cout << "\nCounter: " << counter << " Opcode: " << instructions[counter] << " Operand: " << operand << " A: " << A << " B: " << B << " C: " << C << "\n";
        if (instructions[counter] == 0) {
            if (operand <= 3) {
                A = A / std::pow(2, operand);
            }
            else if (operand == 4) {
                A = A / std::pow(2, A);
            }
            else if (operand == 5) {
                A = A / std::pow(2, B);
            }
            else if (operand == 6) {
                A = A / std::pow(2, C);
            }
            else {
                std::cout << "Error";
            }
            counter = counter + 2;
        }
        else if (instructions[counter] == 1) {
            B = B ^ operand;
            counter = counter + 2;
        }
        else if (instructions[counter] == 2) {

            if (operand <= 3) {
                B = operand % 8;
            }
            else if (operand == 4) {
                B = A % 8;
            }
            else if (operand == 5) {
                B = B % 8;
            }
            else if (operand == 6) {
                B = C % 8;
            }
            else {
                std::cout << "Error";
            }
            counter = counter + 2;
        }
        else if (instructions[counter] == 3) {
            if (A == 0) {
                counter = counter + 2;
            }
            else {
                counter = operand;
            }
        }
        else if (instructions[counter] == 4) {
            B = B ^ C;
            counter = counter + 2;
        }
        else if (instructions[counter] == 5) {
            if (operand <= 3) {
                output.push_back(operand);
            }
            else if (operand == 4) {
                output.push_back(A % 8);
            }
            else if (operand == 5) {
                output.push_back(B % 8);
            }
            else if (operand == 6) {
                output.push_back(C % 8);
            }
            else {
                std::cout << "Error";
            }
            counter = counter + 2;
        }
        else if (instructions[counter] == 6) {
            if (operand <= 3) {
                B = A / std::pow(2, operand);
            }
            else if (operand == 4) {
                B = A / pow(2, A);
            }
            else if (operand == 5) {
                B = A / pow(2, B);
            }
            else if (operand == 6) {
                B = A / pow(2, C);
            }
            else {
                std::cout << "Error";
            }
            counter = counter + 2;
        }
        else if (instructions[counter] == 7) {
            if (operand <= 3) {
                C = A / std::pow(2, operand);
            }
            else if (operand == 4) {
                C = A / pow(2, A);
            }
            else if (operand == 5) {
                C = A / pow(2, B);
            }
            else if (operand == 6) {
                C = A / pow(2, C);
            }
            else {
                std::cout << "Error";
            }
            counter = counter + 2;

        }
    }
    return output;
}

bool outSameInstr(std::vector<int> instructions, std::vector<int> output) {
    if (instructions.size() != output.size()) {
        return false;
    }
    for (int i = 0; i < instructions.size(); i++) {
        if (instructions[i] != output[i]) {
            return false;
        }
    }
    return true;
}

std::string formatWithCommas(long long number)
{
    std::string number_str = std::to_string(number);

    for (int i = number_str.length() - 3; i > 0; i -= 3)
        number_str.insert(i, ",");

    return number_str;
}

int main()
{
    //Test
    //int A = 2024;
    //std::vector<int> instructions = { 0,3,5,4,3,0 };
    //Input
    std::vector<int> output = programme(A, B, C, instructions);
    std::cout << "The anser to Part 1 is: ";
    for (int i = 0; i < output.size(); i++) {
        std::cout << output[i] << ",";
    }
    std::cout << "\n";
    A = 04532305100000000;
    B = 0;
    C = 0;
    output = programme(A, B, C, instructions);
    bool correct = outSameInstr(instructions, output);
    
    while (!correct && A <= 04532305177777777) {
        A++;
        if (A % 1000000 == 0) {
            std::cout << "Testing A = " << formatWithCommas(A) << "\n";
        }
        output = programme(A, 0, 0, instructions);
        correct = outSameInstr(instructions, output);
    }
    std::cout << "The answer to Part 2 is: " << A << "\n";
    for (int i = 0; i < output.size(); i++) {
        std::cout << output[i] << ",";
    }
    std::cout << "\n";
    for (int i = 0; i < instructions.size(); i++) {
        std::cout << instructions[i] << ",";
    }
    //std::cout << "Hello World!\n";
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
