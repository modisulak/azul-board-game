#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "main.h"

class Node {
public:
   Node(Tile value, Node* next, Node* prev);

   Tile value;
   Node* next;
   Node* prev;
};

class LinkedList {
public:
   LinkedList();
   LinkedList(LinkedList& other);
   ~LinkedList();

   /**
    * Return the current size of the Linked List.
    */
   int size();

   /**
    * Get the value at the given index.
    */
   char get(int index);

   /**
    * Add the value to the back of the Linked List
    */
   void addBack(char value);

   /**
    * Add the value to the front of the Linked List
    */
   void addFront(char value);

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

   Node* head;
   Node* tail;
};

#endif // LINKED_LIST_H
