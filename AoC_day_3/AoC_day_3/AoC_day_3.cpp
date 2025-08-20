#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
std::tuple<char, std::string> findNext (std::string row) {
    char val = row[0];
    row.erase(0, 1);
    switch (val)
    {
    case 0x30:
        return std::make_tuple('0',row);
    case 0x31:
        return std::make_tuple('1', row);
    case 0x32:
        return std::make_tuple('2', row);
    case 0x33:
        return std::make_tuple('3', row);
    case 0x34:
        return std::make_tuple('4', row);
    case 0x35:
        return std::make_tuple('5', row);
    case 0x36:
        return std::make_tuple('6', row);
    case 0x37:
        return std::make_tuple('7', row);
    case 0x38:
        return std::make_tuple('8', row);
    case 0x39:
        return std::make_tuple('9', row);
    case 0x2C:
        return std::make_tuple(',', row);
    case 0x29:
        return std::make_tuple(')', row);
    default:
        return std::make_tuple('g', row);
    }
}
std::tuple<int, std::string> doMul(std::string line) {
    int in_1 = 0;
    int in_2 = 0;
    std::string num_to_add;
    char to_add;
    tie(to_add, line) = findNext(line);
    if (to_add != 'g' && to_add != ',' && to_add != ')') {
        while (to_add != ',') {
            if (to_add != ',' && to_add != ')' && to_add != 'g') {
                num_to_add.push_back(to_add);
                tie(to_add, line) = findNext(line);
            }
            else if (to_add == ')') {
                to_add = 'g';
                num_to_add = "";
                break;
            }
            else if (to_add == 'g') {
                num_to_add = "";
                break;
            }
        }
        if (to_add == ',') {
            in_1 = std::stoi(num_to_add);
            num_to_add = "";
            tie(to_add, line) = findNext(line);
            while (to_add != ')') {
                if (to_add != ',' && to_add != ')' && to_add != 'g') {
                    num_to_add.push_back(to_add);
                    tie(to_add, line) = findNext(line);
                }
                else if (to_add == ',') {
                    to_add = 'g';
                    num_to_add = "";
                    break;
                }
                else if (to_add == 'g') {
                    num_to_add = "";
                    break;
                }
            }
        }
        if (to_add == ')') {
            in_2 = std::stoi(num_to_add);
            num_to_add = "";
            return std::make_tuple(in_1 * in_2,line);
        }
    }
    return std::make_tuple(0, line);
}
int main()
{
    std::fstream file;
    file.open("D:\\!Advent_of_Code\\2024\\AoC_day_3\\input.txt");
    if (file.is_open()) {
        std::string line;
        int sum = 0;
        std::string multiply = "mul(";
        std::string enable = "do()";
        std::string disable = "don't()";
        bool doing = true;
        while (getline(file, line)) {
            while (line.length() != 0) {
                std::size_t nextMul = line.find(multiply);
                std::size_t nextEnable = line.find(enable);
                std::size_t nextDisable = line.find(disable);
                if (nextMul == std::string::npos) {
                    line.clear();
                }
                else if (doing) {
                    if (nextDisable < nextMul) {
                        doing = false;
                        line.erase(0, nextDisable + 7);
                    }
                    else {
                        int temp = 0;
                        line.erase(0, nextMul + 4);
                        tie(temp, line) = doMul(line);
                        sum += temp;
                    }
                }
                else if (!doing) {
                    if (nextEnable == std::string::npos) {
                        line.clear();
                    }
                    else {
                        line.erase(0, nextEnable + 4);
                        doing = true;

                    }
                }
            }
        }
        std::cout << "The sum is: " << sum << "\n";
    }
}