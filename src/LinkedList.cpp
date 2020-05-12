#include "LinkedList.h"

Node::Node(Tile value, shared_ptr<Node> next, shared_ptr<Node> prev) :
        value(value),
        next(move(next)),
        prev(move(prev)) {}

LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
    length = 0;
}

LinkedList::LinkedList(const LinkedList &other) :
        head(other.head),
        tail(other.tail),
        length(other.length) {
    if (head != nullptr) {
        shared_ptr<Node> current = head;
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

Tile LinkedList::get(const unsigned int index) const {
    Tile toReturn = BLANK_SPACE;
    if (index < length) {
        shared_ptr<Node> current = head;
        unsigned int i = 0;
        while (i <= index) {
            toReturn = current->value;
            current = current->next;
            ++i;
        }
    }
    return toReturn;
}

void LinkedList::addFront(const Tile value) {
    shared_ptr<Node> toAdd = make_shared<Node>(value, head, nullptr);
    if (head == nullptr) {
        head = toAdd;
        tail = toAdd;
    } else {
        head->prev = toAdd;
        head = toAdd;
    }
    ++length;
}

void LinkedList::addBack(const Tile value) {
    shared_ptr<Node> toAdd = make_shared<Node>(value, nullptr, tail);
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
            head->prev = nullptr;
        } else {
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

string LinkedList::toString() {
    string list = "";
    if (head != nullptr) {
        shared_ptr<Node> current = head;
        while (current != nullptr) {
            list += current->value;
            current = current->next;
        }
    }
    return list;
}

bool LinkedList::includes(Tile tile) {
    shared_ptr<Node> current = head;
    bool includes = false;
    while (current != nullptr && !includes) {
        if (current->value == tile) {
            includes = true;
        }
        current = current->next;
    }
    return includes;
}
