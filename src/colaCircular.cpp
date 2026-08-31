#include <iostream>
#include "colaCircular.hpp"

colaCircular::colaCircular(int capacity){
    this->capacity = capacity;
        data = new int[capacity];

            head = 0;
            tail = 0;
            count = 0;
}

colaCircular::~colaCircular(){
    delete[] data;
}

bool colaCircular::isEmpty() const{
    return count == 0;
}

bool colaCircular::isFull() const{
    return count == capacity;
}

bool colaCircular::enqueue(int value){

    if (isFull()){
        return false;
    }

    data[tail] = value;

        tail = (tail + 1) % capacity;

    count++;

    return true;
}

bool colaCircular::dequeue(int &value){

    if (isEmpty()){
        return false;
    }

        value = data[head];
        head = (head + 1) % capacity;
        count--;

    return true;
}

int colaCircular::front() const{

    if (isEmpty()){
        return -1;
    }

    return data[head];
}

int colaCircular::rear() const{

    if (isEmpty()){
        return -1;
    }

    int position = (tail - 1 + capacity) % capacity;

    return data[position];
}

int colaCircular::size() const{
    return count;
}

int colaCircular::getCapacity() const{
    return capacity;
}

void colaCircular::print() const{

    if (isEmpty()){
        std::cout << "[vacia]\n";
        return;
    }

    std::cout << "[ ";

    for (int i = 0; i < count; i++){

        int position = (head + i) % capacity;
        std::cout << data[position] << " ";
    }

    std::cout << "]\n";
}