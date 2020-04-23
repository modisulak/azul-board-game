
#include "LinkedList.h"

Node::Node(Tile value, Node *next, Node *prev) :
        value(value),
        next(next),
        prev(prev) {}

LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
}

LinkedList::LinkedList(LinkedList &other) :
        head(other.head),
        tail(other.tail) {
    if (head != nullptr) {
        Node *current = head;
        while (current != nullptr) {
            addBack(current->value);
            current = current->next;
        }
    }
}

LinkedList::~LinkedList() {
    if (head != nullptr) {
        Node *current = head;
        while (current != nullptr) {
            Node *toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }
}

int LinkedList::size() {
    Node *current = head;
    int i = 0;
    while (current != nullptr) {
        current = current->next;
        i++;
    }
    return i;
}

char LinkedList::get(int index) {
    char toReturn = '\0';
    if (index < size()) {
        Node *current = head;
        int i = 0;
        while (i <= index) {
            toReturn = current->value;
            current = current->next;
            i++;
        }
    }
    return toReturn;
}

void LinkedList::addFront(char value) {
    Node *toAdd = new Node(value, head, nullptr);
    if (head == nullptr) {
        head = toAdd;
        tail = toAdd;
    } else {
        head->prev = toAdd;
        head = toAdd;
    }
}

void LinkedList::removeFront() {
    head = head->next;
    delete head->prev;
    head->prev = nullptr;
}

void LinkedList::addBack(char value) {
    Node *toAdd = new Node(value, nullptr, tail);
    if (head == nullptr) {
        head = toAdd;
        tail = toAdd;
    } else {
        tail->next = toAdd;
        tail = toAdd;
    }
}

void LinkedList::removeBack() {
    tail = tail->prev;
    delete tail->next;
    tail->next = nullptr;
}

void LinkedList::clear() {
    Node *current = head;
    while (current != nullptr) {
        Node *toClear = current;
        current = current->next;
        delete toClear;
    }
    head = nullptr;
    tail = nullptr;
}

