#include "node.h"

Node::Node(){
    this->row = 0;
    this->col = 0;
    this->data = 0;
    this->next = nullptr;
}

Node::~Node() {
    if(this->next != nullptr){
        delete this->next;
    }
}

Node::Node(int row, int col, int data) {
    this->row = row;
    this->col = col;
    this->data = data;
    this->next = nullptr;
}

Node::Node(int row, int col, int data, Node* next) {
    this->row = row;
    this->col = col;
    this->data = data;
    this->next = next;
}
