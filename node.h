#ifndef __NODE_H__
#define __NODE_H__

#pragma once

class Node{
    private:
        int row, col, data;
        Node* next;

        friend class LinkedList;
    public:
        Node();
        ~Node();
        Node(int row, int col, int data);
        Node(int row, int col, int data, Node* next);
};

#endif
