#include "node.h"
#include <vector>
#include <string>
#include <fstream>

class LinkedList{
    private:
        Node* head;
        int rows, cols;
        unsigned int size;

        void push_backR(Node* temp, int row, int col, int data);
        void to_stringR(Node* temp, std::string &listString);
        void writeR(Node* temp, std::string outfile);
    public:
        LinkedList();
        LinkedList(int rows, int cols);
        ~LinkedList();

        Node* get_head();
        int get_rows();
        int get_cols();
        void push_back(int row, int col, int data);
        void add(Node* matrixOne, Node* matrixTwo);
        void multiply(const int& r, const int& c, Node* matrixOne, Node* matrixTwo);
        int get_size();
        std::string to_string();
        void write(std::string outfile);
};
