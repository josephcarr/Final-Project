#include "linked-list.h"
#include <iostream>

LinkedList::LinkedList(){
    this->head = nullptr;
    this->rows = 0;
    this->cols = 0;
    this->size = 0;
}

LinkedList::LinkedList(int rows, int cols) {
    this->head = nullptr;
    this->rows = rows;
    this->cols = cols;
    this->size = 0;
}

LinkedList::~LinkedList(){
    if (this->head){
        delete this->head;
    }
}

//Private Methods
void LinkedList::push_backR(Node* temp, int row, int col, int data) {
    if (temp == nullptr) {
        return;
    }

    this->push_backR(temp->next, row, col, data);

    if (temp->next == nullptr) {
        temp->next = new Node(row, col, data);
    }

    return;
}

void LinkedList::to_stringR(Node* temp, std::string &listString) {
    if (temp == nullptr) {
        return;
    }

    listString += std::to_string(temp->row) + "\t" + std::to_string(temp->col) + "\t" + std::to_string(temp->data) + "\n";

    this->to_stringR(temp->next, listString);

    return;
}

//Public Methods
Node* LinkedList::get_head() {
    return this->head;
}

void LinkedList::push_back(int row, int col, int data) {
    if(this->head == nullptr) {
        this->head = new Node(row, col, data);
    }
    else {
        this->push_backR(this->head, row, col, data);
    }

    this->size++;

    return;
}

int LinkedList::get_size() {
    return this->size;
}

std::string LinkedList::to_string(){
    std::string stringified;
    stringified += "Row \t Col \t Val \n";

    this->to_stringR(this->head, stringified);

    return stringified;
}
