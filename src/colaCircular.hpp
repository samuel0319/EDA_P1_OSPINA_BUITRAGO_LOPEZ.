#ifndef QUEUE_CIRCULAR_HPP
#define QUEUE_CIRCULAR_HPP

class colaCircular
{
private:
    int *data;
    int capacity;
    int head;
    int tail;
    int count;

public:
    colaCircular(int capacity);
    ~colaCircular();

    bool enqueue(int value);
    bool dequeue(int &value);

    bool isFull() const;
    bool isEmpty() const;

    int front() const;
    int rear() const;

    int size() const;
    int getCapacity() const;

    void print() const;
};

#endif