#include "Stack.h"

using namespace std;

template <class T>
stack<T> :: stack(int SizeOfStack)
{
    top=-1;                    //stack is empty
    size=SizeOfStack;
    array_ptr = new T[SizeOfStack];
}


template <class T>
void stack<T> :: push(T data)
{
    top++;
    array_ptr[top]=data;
}

template <class T>
T stack<T> :: peek()
{
    if(isEmpty())
        exit(EXIT_FAILURE);

    else
        return array_ptr[top];
}


template <class T>
void stack<T> :: pop()
{
    if(isEmpty())
        exit(EXIT_FAILURE);
    else
        top--;
}


template <class T>

bool stack<T> :: isEmpty()
{
    return (top==-1);
}


template <class T>
bool stack<T> :: isFull()
{
    return (top==size-1);
}

