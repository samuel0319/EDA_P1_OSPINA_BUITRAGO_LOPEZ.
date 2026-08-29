#include "listas.hpp"
#include <iostream>

listas :: listas(){
    cabeza = nullptr;
    cola = nullptr;
    count = 0;
}

listas :: ~listas (){
    int valor;
        while (dequeue(valor)){

        }
}

bool listas::isEmpty() const
{
    return cabeza == nullptr;
}

bool listas::enqueue(int value)
{

    Nodo *newNode = new Nodo;

    newNode->data = value;
    newNode->next = nullptr;

    if (isEmpty())
    {

        cabeza = newNode;
        cola = newNode;
    }
    else
    {

        cola->next = newNode;
        cola = newNode;
    }

    count++;

    return true;
}

bool listas::dequeue(int &value)
{

    if (isEmpty())
    {
        return false;
    }

    Nodo *temp = cabeza;

    value = cabeza->data;

    cabeza = cabeza->next;

    delete temp;

    count--;

    if (cabeza == nullptr)
    {
        cola = nullptr;
    }

    return true;
}

int listas::front() const
{

    if (isEmpty())
    {
        return -1;
    }

    return cabeza->data;
}

int listas::rear() const
{

    if (isEmpty())
    {
        return -1;
    }

    return cola->data;
}

int listas::size() const
{
    return count;
}

void listas::print() const
{

    Nodo *current = cabeza;

    if (isEmpty())
    {
        std::cout << "[vacia]\n";
        return;
    }

    std::cout << "[ ";

    while (current != nullptr)
    {

        std::cout << current->data << " ";

        current = current->next;
    }

    std::cout << "]\n";
}
