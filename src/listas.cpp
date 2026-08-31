#include "listas.hpp"
#include <iostream>

listas::listas(){
    head = nullptr;
    tail = nullptr;
    count = 0;
}

listas::~listas(){
    int value;
    while (dequeue(value)){
    }
}

bool listas::isEmpty() const{
    return head == nullptr;
}

bool listas::enqueue(int value){
    Nodo *newNode = new Nodo;
    newNode->data = value;
    newNode->next = nullptr;

    if (isEmpty()){
        head = newNode;
        tail = newNode;
    }
    else{
        tail->next = newNode;
        tail = newNode;
    }

    count++;
    return true;
}

bool listas::dequeue(int &value){

    if (isEmpty()){
        return false;
    }

    Nodo *temp = head;
    value = head->data;

    head = head->next;

    delete temp;
    count--;

    if (head == nullptr){
        tail = nullptr;
    }

    return true;
}

int listas::front() const{
    if (isEmpty()){
        return -1;
    }
    return head->data;
}

int listas::rear() const{
    if (isEmpty()){
        return -1;
    }
    return tail->data;
}

int listas::size() const{
    return count;
}

void listas::print() const{
    Nodo *current = head;

    if (isEmpty()){
        std::cout << "[vacia]\n";
        return;
    }

    std::cout << "[ ";

    while (current != nullptr){
        std::cout << current->data << " ";
        current = current->next;
    }

    std::cout << "]\n";
}