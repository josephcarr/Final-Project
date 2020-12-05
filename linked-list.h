#include "node.h"
#include <vector>
#include <string>

class LinkedList{
    private:
        Node* head;
        unsigned int size;

        void push_backR(Node* temp, int row, int col, int data);
        void to_stringR(Node* temp, std::string &listString);
    public:
        LinkedList();
        LinkedList(int rows, int cols);
        ~LinkedList();

        int rows, cols;

        Node* get_head();
        void push_back(int row, int col, int data);
        int get_size();
        std::string to_string();
};
