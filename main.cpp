#include <iostream>
#include <fstream>
#include <string>
#include "src/infiniteDouble.h"
#include "src/infiniteDouble.cpp"

int main() {
    InfiniteDouble nums[2];
    std::string line;
    std::ifstream infile("input.txt");
    if (infile.is_open()) {
        int i = 0;
        while (getline(infile, line)) {
            if (i > 1) {
                std::cout << "too many lines in file" << std::endl;
                return 1;
            }
            nums[i] = InfiniteDouble(line);
            i++;
        }
        if (i < 1) {
            std::cout << "should be 2 double in file" << std::endl;
            return 1;
        }
        infile.close();
    } else {
        std::cout << "Unable to open input file";
        return 1;
    }

    std::ofstream outfile("output.txt");
    if (outfile.is_open()) {
        outfile << nums[0] << " + " << nums[1] << " = " << nums[0] + nums[1] << std::endl;
        outfile << nums[0] << " * " << nums[1] << " = " << nums[0] * nums[1] << std::endl;
        outfile.close();
    } else {
        std::cout << "Unable to open file";
        return 1;
    }
    return 0;
}