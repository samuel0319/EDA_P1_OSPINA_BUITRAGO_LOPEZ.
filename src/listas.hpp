#ifndef lista_hpp
#define lista_hpp

class listas{
private:

    struct Nodo{

        int data;
        Nodo *next;
    };
    Nodo *head;
    Nodo *tail;
    int count;

public:
    listas();
    ~listas();

    bool enqueue(int value);
    bool dequeue(int &value);
    bool isEmpty() const;
    int front() const;
    int rear() const;
    int size() const;
    void print() const;
};

#endif