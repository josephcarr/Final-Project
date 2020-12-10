#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <cstring>
#include <ctime>
#include "linked-list.h"

int main(int argc, char **argv) {
    //check for enough arguments
    if (argc < 5) {
        std::cout << "Not enough arguments" << std::endl;
        return 0;
    }

    std::string fileOne = argv[1], fileTwo = argv[2], outfile = argv[3], operation = argv[4];
    int size;
    std::string matrixString;

    //read first file and creates Linked List based off of the rows and column
    LinkedList matrixOne(fileOne);

    //read second file and creates Linked List based off of the rows and column
    LinkedList matrixTwo(fileTwo);

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

    std::cout << "Calculating..." << std::endl;

    uint64_t val;
    unsigned long c_start, c_end;

    if (operation == "a") {
        c_start = std::clock();
        finalMatrix.add(matrixOne.get_head(), matrixTwo.get_head());
        c_end = std::clock();
    }
    else if (operation == "m") {
        LinkedList tMatrix(matrixTwo.get_cols(), matrixTwo.get_rows());
        tMatrix.transpose(matrixTwo.get_head());

        c_start = std::clock();
        finalMatrix.multiply(matrixOne.get_head(), tMatrix.get_head());
        c_end = std::clock();
    }

    float runTime = 1.0 * (c_end - c_start) / CLOCKS_PER_SEC;;

    std::cout << "Done!" << std::endl;

    
    //prints out the contents of matricies
    matrixString = matrixOne.to_string();
    std::cout << "Matrix One:" << "\n" << matrixString << std::endl;

    matrixString = matrixTwo.to_string();
    std::cout << "Matrix Two:" << "\n" << matrixString << std::endl;

    matrixString = finalMatrix.to_string();
    std::cout << "Matrix Final:" << "\n" << matrixString << std::endl;

    finalMatrix.write(outfile);

    std::cout << "Run Time: " << runTime << std::endl;

    return 0;
}
