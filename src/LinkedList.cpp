#include "LinkedList.h"

Node::Node(Tile value, Node *next, Node *prev) :
        value(value),
        next(next),
        prev(prev) {}

LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
    length=0;
}

LinkedList::LinkedList(const LinkedList &other) :
        head(other.head),
        tail(other.tail),
        length(other.length){
    if (head != nullptr) {
        Node *current = head;
        while (current != nullptr) {
            addBack(current->value);
            current = current->next;
        }
    }
}

LinkedList::~LinkedList() {
    clear();
}

unsigned int LinkedList::size() const {
    return length;
}

char LinkedList::get(const unsigned int index) const {
    char toReturn = '\0';
    if (index < length) {
        Node *current = head;
        unsigned int i = 0;
        while (i <= index) {
            toReturn = current->value;
            current = current->next;
            ++i;
        }
    }
    return toReturn;
}

void LinkedList::addFront(const char value) {
    Node *toAdd = new Node(value, head, nullptr);
    if (head == nullptr) {
        head = toAdd;
        tail = toAdd;
    } else {
        head->prev = toAdd;
        head = toAdd;
    }
    ++length;
}

void LinkedList::addBack(const char value) {
    Node *toAdd = new Node(value, nullptr, tail);
    if (head == nullptr) {
        head = toAdd;
        tail = toAdd;
    } else {
        tail->next = toAdd;
        tail = toAdd;
    }
    ++length;
}

void LinkedList::removeFront() {
    if (head != nullptr) {
        if (head->next != nullptr) {
            head = head->next;
            delete head->prev;
            head->prev = nullptr;
        } else {
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        --length;
    }
}

void LinkedList::removeBack() {
    if (tail != nullptr) {
        if (tail->prev != nullptr) {
            tail = tail->prev;
            delete tail->next;
            tail->next = nullptr;
        } else {
            removeFront();
        }
        --length;
    }
}

void LinkedList::clear() {
    while (head != nullptr) {
        removeFront();
    }
}

