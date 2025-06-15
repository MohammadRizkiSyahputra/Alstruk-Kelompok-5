#pragma once

template <typename T>
class LinkedList {
public:
    struct Node {
        T data;
        Node *next;
        Node(const T& d) : data(d), next(nullptr) {}
    };
    LinkedList();                   // Constructor
    ~LinkedList();                  // Destructor
    void append(const T& value);    // Add to end
    void prepend(const T& value);   // Add to beginning
    Node* getHead() const { return head; };
private:
    Node* head;
};

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr) {}

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
    if (!head) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next)
            current = current->next;
        current->next = newNode;
    }
}