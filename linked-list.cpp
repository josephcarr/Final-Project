#include "linked-list.h"
#include <iostream>

LinkedList::LinkedList(){
    this->head = nullptr;
    this->tail = head;
    this->rows = 0;
    this->cols = 0;
    this->size = 0;
}

LinkedList::LinkedList(std::string infile) {
    this->head = nullptr;
    this->tail = head;
    this->rows = 0;
    this->cols = 0;
    this->size = 0;

    //read file to vector
    std::ifstream file(infile);
    std::string str, value;
    std::vector<int> values;
    int length = 0, width = 0;

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

    this->rows = length;
    this->cols = width;

    //pushes all none zero values from values to the Linked List Sparse Matrtix
    int count = 0;
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            if (values[count] != 0) {
                this->push_back(i, j, values[count]);
            }
            count++;
        }
    }

}

LinkedList::LinkedList(int rows, int cols) {
    this->head = nullptr;
    this->tail = nullptr;
    this->rows = rows;
    this->cols = cols;
    this->size = 0;
}

LinkedList::~LinkedList(){
    if (this->head){
        delete this->head;
    }
}

/*_______________________________________________________________________________*/
/*|                                                                             |*/
/*----------------------------PRIVATE METHODS------------------------------------*/
/*|                                                                             |*/
/*|_____________________________________________________________________________|*/


/*void LinkedList::push_backR(Node* temp, int row, int col, int data) {
    if (temp == nullptr) {
        return;
    }

    this->push_backR(temp->next, row, col, data);

    if (temp->next == nullptr) {
        temp->next = new Node(row, col, data);
    }

    return;
}*/

//calculates the value of the finalMatrix at element [r, c]
int LinkedList::dotProduct(const int& r, const int& c, Node* headOne, Node* headTwo) {
    int sum = 0;

    //slower version (does not use transpose matrix)
    /*while ((headOne != nullptr && headTwo != nullptr) && (headOne->row <= r)) {
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
    }*/

    //faster version (uses transpose matrix)
    while ((headOne != nullptr && headTwo != nullptr) && (headOne->row <= r)) {
        if ((headOne->row == r && headTwo->row == c) && (headOne->col == headTwo->col)) {
            sum += headOne->data * headTwo->data;
            headOne = headOne->next;
            headTwo = headTwo->next;
        }
        else if (headOne->row < r || (headTwo->row == c && headOne->col < headTwo->col)) {
            headOne = headOne->next;
        }
        else {
            headTwo = headTwo->next;
        }
    }

    return sum;
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

/*_______________________________________________________________________________*/
/*|                                                                             |*/
/*----------------------------PUBLIC METHODS------------------------------------*/
/*|                                                                             |*/
/*|_____________________________________________________________________________|*/

//returns the head of the linked list (first element)
Node* LinkedList::get_head() {
    return this->head;
}

//returns the rows of the matrix
int LinkedList::get_rows() {
    return this->rows;
}

//returns the columns of the matrix
int LinkedList::get_cols() {
    return this->cols;
}

//fills the Linked List Matrix with Nodes containing {row, col, value}
void LinkedList::push_back(int row, int col, int data) {
    /*if(this->head == nullptr) {
        this->head = new Node(row, col, data);
    }
    else {
        this->push_backR(this->head, row, col, data);
    }*/

    Node* newNode = new Node(row, col, data);

    if (this->head == nullptr) {
        this->head = newNode;
        this->tail = head;
    }
    else {
        this->tail->next = newNode;
        this->tail = this->tail->next;
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

//makes a transpose of second matrix (flips the matrix to make rows = cols and cols = rows)
void LinkedList::transpose(Node* head) {
    if (head == nullptr) {
        return;
    }

    while (head != nullptr) {
        this->push_back(head->col, head->row, head->data);
        head = head->next;
    }

    return;
}

//helps multiplies the matricies
void LinkedList::multiply(Node* headOne, Node* headTwo) {
    if (headOne == nullptr || headTwo == nullptr) {
        return;
    }

    int sum;

    //calls function dotProduct to calculate element value at row r and column c
    for (int r = 0; r < this->rows; r++) {
        for (int c = 0; c < this->cols; c++) {
            sum = this->dotProduct(r, c, headOne, headTwo);
            if (sum != 0) {
                this->push_back(r, c, sum);
            }
        }
    }

    /*//push the sum to the finalMatrix if the value is not 0
    if (sum != 0) {
        this->push_back(r, c, sum);
    }*/

    return;
}

//returns list size
int LinkedList::get_size() {
    return this->size;
}

//creates a string to print to console
std::string LinkedList::to_string(){
    std::string stringified;
    stringified += "Row \t Col \t Val \n";

    this->to_stringR(this->head, stringified);

    return stringified;
}

//writes matrix to a text file
void LinkedList::write(std::string outfile) {
    Node* temp = this->head;

    if (temp == nullptr) {
        return;
    }

    //write to new file
	std::ofstream outMatrix;
	outMatrix.open(outfile);
    for (int i = 0; i < this->rows; i++) {
    	for (int j = 0; j < this->cols; j++) {
    	    if (temp != nullptr) {
        	    if (i == temp->row && j == temp->col) {
        		    outMatrix << std::to_string(temp->data);
        		    temp = temp->next;
        	    }
        	    //if there isn't a node that has the position of i,j, it puts a zero to the file
        	    else {
        	        outMatrix << std::to_string(0);
        	    }
    	    }
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

