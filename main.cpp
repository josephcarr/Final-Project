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
    if (argc < 5) {
        std::cout << "Not enough arguments" << std::endl;
        return 0;
    }

    std::string fileOne = argv[1], fileTwo = argv[2], outfile = argv[3], operation = argv[4];
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

    //checks if matricies are same size for adddition
    if (operation == "a" && (matrixOne.get_rows() != matrixTwo.get_rows() || matrixOne.get_cols() != matrixTwo.get_cols())) {
        std::cout << "Matricies are not the same size." << std::endl;
        return 0;
    }
    //checks if cols of matrixOne == rows of matrixTwo for multiplication
    else if (operation == "m" && matrixOne.get_cols() != matrixTwo.get_rows()) {
        std::cout << "matrixOne columns are not the same size as the rows of matrixTwo" << std::endl;
        return 0;
    }

    //creates a Linked List matrix for final operation
    LinkedList finalMatrix(matrixOne.get_rows(), matrixTwo.get_cols());

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

    if (operation == "a") {
        finalMatrix.add(matrixOne.get_head(), matrixTwo.get_head());
    }
    else if (operation == "m") {
        for (int r = 0; r < finalMatrix.get_rows(); r++) {
            for (int c = 0; c < finalMatrix.get_cols(); c++) {
                finalMatrix.multiply(r, c, matrixOne.get_head(), matrixTwo.get_head());
            }
        }
    }

    //prints out the contents of matricies
    matrixString = matrixOne.to_string();
    std::cout << "Matrix One:" << "\n" << matrixString << std::endl;

    matrixString = matrixTwo.to_string();
    std::cout << "Matrix Two:" << "\n" << matrixString << std::endl;

    matrixString = finalMatrix.to_string();
    std::cout << "Matrix Final:" << "\n" << matrixString << std::endl;

    finalMatrix.write(outfile);

    return 0;
}
