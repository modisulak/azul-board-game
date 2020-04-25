#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "Types.h"

class Node {
public:
    Node(Tile value, Node *next, Node *prev);

    Tile value;
    Node *next;
    Node *prev;
};

class LinkedList {
public:
    LinkedList();

    LinkedList(const LinkedList &other);

    ~LinkedList();

    /**
     * Return the current size of the Linked List.
     */
    unsigned int size() const;

    /**
     * Get the value at the given index.
     */
    char get(const unsigned int index) const;

    /**
     * Add the value to the back of the Linked List
     */
    void addBack(const char value);

    /**
     * Add the value to the front of the Linked List
     */
    void addFront(const char value);

    /**
     * Remove the value at the back of the Linked List
     */
    void removeBack();

    /**
     * Remove the value at the front of the Linked List
     */
    void removeFront();

    /**
     * Removes all values from the Linked List
     */
    void clear();

private:
    Node *head;
    Node *tail;
};

#endif // LINKED_LIST_H
