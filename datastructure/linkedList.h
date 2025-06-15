#pragma once

template <typename T>
class LinkedList {
public:
    struct Node {
        T data;
        Node *prev;
        Node *after;
        Node(const T& d) : data(d), prev(nullptr), next(nullptr) {}
    };
    LinkedList();                   // Constructor
    ~LinkedList();                  // Destructor
    void append(const T& value);    // Add to end
    void prepend(const T& value);   // Add to beginning
    Node* getHead() const { return head; };
    Node* getTail() const { return tail; }
private:
    Node* head;
    Node* tail;
};

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr) {}

template <typename T>
LinkedList<T>::~LinkedList() {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

template <typename T>
void LinkedList<T>::append(const T& value) {
    Node* newNode = new Node(value);
    if (!tail) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

// Add to beginning
template <typename T>
void LinkedList<T>::prepend(const T& value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = tail = newNode;
    } else {
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
    }
}
