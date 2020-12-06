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

    //converts linked list into table showing rows, cols, and values
void LinkedList::to_stringR(Node* temp, std::string &listString) {
    if (temp == nullptr) {
        return;
    }

    listString += std::to_string(temp->row) + "\t" + std::to_string(temp->col) + "\t" + std::to_string(temp->data) + "\n";

    this->to_stringR(temp->next, listString);

    return;
}

    //writes the matrix to a new file
void LinkedList::writeR(Node* temp, std::string outfile) {
    if (temp == nullptr) {
        return;
    }

    //write to new file
	std::ofstream outMatrix;
	outMatrix.open(outfile);
    for (int i = 0; i < this->rows; i++) {
    	for (int j = 0; j < this->cols; j++) {
    	    if (i == temp->row && j == temp->col) {
    		    outMatrix << std::to_string(temp->data);
    		    temp = temp->next;
    	    }
    	    //if there isn't a node that has the position of i,j, it puts a zero to the file
    	    else {
    	        outMatrix << std::to_string(0);
    	    }

    		if (j <= this->cols - 2) {
    		    outMatrix << ' ';
    		}
    	}

    	if (temp != nullptr) {
    	    outMatrix << '\n';
    	}
    }
    outMatrix.close();

    return;
}

//Public Methods

Node* LinkedList::get_head() {
    return this->head;
}

int LinkedList::get_rows() {
    return this->rows;
}

int LinkedList::get_cols() {
    return this->cols;
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

    //method that adds matrixTwo to matrixOne
void LinkedList::add(Node* headOne, Node* headTwo) {
    if (headOne == nullptr || headTwo == nullptr) {
        return;
    }

    //adds matrix values to finalMatrix until either matrix One or Two ends
    while (headOne != nullptr && headTwo != nullptr) {
        //if rows and cols are the same, add the 2 values and go to the next elements of both matricies
        if (headOne->row == headTwo->row) {
            if (headOne->col == headTwo->col) {
                this->push_back(headOne->row, headOne->col, headOne->data + headTwo->data);
                headOne = headOne->next;
                headTwo = headTwo->next;
            }
            //if headOne col < headTwo col, only push headOne value and go to next element in matrixOne
            else if (headOne->col < headTwo->col) {
                this->push_back(headOne->row, headOne->col, headOne->data);
                headOne = headOne->next;
            }
            //if headOne col > headTwo col, only push headTwo value and go to next element in matrixTwo
            else {
                this->push_back(headTwo->row, headTwo->col, headTwo->data);
                headTwo = headTwo->next;
            }
        }
        //if headOne row < headTwo row, only push headOne value and go to next element in matrixOne
        else if (headOne->row < headTwo->row) {
            this->push_back(headOne->row, headOne->col, headOne->data);
            headOne = headOne->next;
        }
        //if headOne row > headTwo row, only push headTwo value and go to next element in matrixTwo
        else {
            this->push_back(headTwo->row, headTwo->col, headTwo->data);
            headTwo = headTwo->next;
        }
    }

    //since the size of the sparse matricies can differ, we need to check if there are elements left over from each matrix
    //pushes leftover elements from matrixOne to finalMatrix
    while (headOne != nullptr) {
        this->push_back(headOne->row, headOne->col, headOne->data);
        headOne = headOne->next;
    }

    //pushes leftover elements from matrixTwo to finalMatrix
    while (headTwo != nullptr) {
        this->push_back(headTwo->row, headTwo->col, headTwo->data);
        headTwo = headTwo->next;
    }

    return;
}

    //multiplies the matricies
void LinkedList::multiply(const int& r, const int& c, Node* headOne, Node* headTwo) {
    if (headOne == nullptr || headTwo == nullptr) {
        return;
    }

    int sum = 0;

    while (headOne != nullptr && headTwo != nullptr) {
        //checks if the first matrix element row = the row of the element we are computing
        if (headOne->row == r) {
            //checks if the second matrix element col = the col of the element we are computing
            if (headTwo->col == c) {
                //checks if the first matrix element col = the row of the second matrix element so we can multiply them and add them to the sum
                if (headOne->col == headTwo->row) {
                    sum += headOne->data * headTwo->data;
                    headOne = headOne->next;
                    headTwo = headTwo->next;
                }
                //if matrixOne col < matrixTwo row, go to next element in matrixOne
                else if (headOne->col < headTwo->row) {
                    headOne = headOne->next;
                }
                //if matrixOne col > matrixTwo row, go to next element in matrixOne
                else {
                    headTwo = headTwo->next;
                }
            }
            //if matrixTwo col does not = the col of the element we are computing, go to next element of matrixTwo
            else {
                headTwo = headTwo->next;
            }
        }
        //if matrixOne row does not = the row of the element we are computing, go to next element of matrixone
        else {
            headOne = headOne->next;
        }
    }

    //push the sum to the finalMatrix if the value is not 0
    if (sum != 0) {
        this->push_back(r, c, sum);
    }

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

//helps write Sparse Matrix to a text file
void LinkedList::write(std::string outfile) {
    this->writeR(this->head, outfile);

    return;
}
