#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <fstream>
#include "linked-list.h"

void readFile(int& length, int& width, const std::string& infile, std::vector<int>& values) {
    //read file to vector
    std::ifstream file(infile);
    std::string str, value;
    while (std::getline(file, str)) {
        // process line
        for (int i = 0; i < str.size(); i++) {
            if (str[i] != ' ') {
                value += str[i];
            }
            else {
                values.push_back(std::stoi(value));
                value.clear();
                width++;
            }
        }

        values.push_back(std::stod(value));
        value.clear();
        width++;

        length++;
    }

    width /= length;

    return;
}

int main(int argc, char **argv) {
    //check for enough arguments
    if (argc < 4) {
        std::cout << "Not enough arguments" << std::endl;
        return 0;
    }

    std::string fileOne = argv[1], fileTwo = argv[2], operation = argv[3];
    std::vector<int> valuesOne, valuesTwo;
    int length = 0, width = 0, size;
    std::string matrixString;

    //read first file and creates Linked List based off of the rows and column
    readFile(length, width, fileOne, valuesOne);
    LinkedList matrixOne(length, width);

    length = 0;
    width = 0;

    //read second file and creates Linked List based off of the rows and column
    readFile(length, width, fileTwo, valuesTwo);
    LinkedList matrixTwo(length, width);

    //pushes all none zero values from valuesOne to matrixOne
    int count = 0;
    for (int i = 0; i < matrixOne.get_rows(); i++) {
        for (int j = 0; j < matrixOne.get_cols(); j++) {
            if (valuesOne[count] != 0) {
                matrixOne.push_back(i, j, valuesOne[count]);
            }
            count++;
        }
    }

    //pushes all none zero values from valuesTwo to matrixTwo
    count = 0;
    for (int i = 0; i < matrixTwo.get_rows(); i++) {
        for (int j = 0; j < matrixTwo.get_cols(); j++) {
            if (valuesTwo[count] != 0) {
                matrixTwo.push_back(i, j, valuesTwo[count]);
            }
            count++;
        }
    }

    /*size = matrixOne.get_size();
    std::cout << "Size: " << size << std::endl;*/

    matrixString = matrixOne.to_string();
    std::cout << "Matrix One:" << "\n" << matrixString << std::endl;

    matrixString = matrixTwo.to_string();
    std::cout << "Matrix Two:" << "\n" << matrixString << std::endl;
}
