#ifndef __LIST_H__
#define __LIST_H__

#include "node.h"
#include <vector>
#include <string>
#include <fstream>

class LinkedList{
    private:
        Node* head;
        Node* tail;
        int rows, cols;
        unsigned int size;

        //void push_backR(Node* temp, int row, int col, int data);
        int dotProduct(const int& r, const int& c, Node* headOne, Node* headTwo);
        void to_stringR(Node* temp, std::string &listString);
    public:
        LinkedList();
        LinkedList(std::string filname);
        LinkedList(int rows, int cols);
        ~LinkedList();

        Node* get_head();
        int get_rows();
        int get_cols();
        void push_back(int row, int col, int data);
        void add(Node* headOne, Node* headTwo);
        void transpose(Node* head);
        void multiply(Node* headOne, Node* headTwo);
        int get_size();
        std::string to_string();
        void write(std::string outfile);
};

#endif
