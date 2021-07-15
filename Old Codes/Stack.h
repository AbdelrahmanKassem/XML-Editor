/*
 * Stack.h
 *
 *  Created on: Jul 9, 2021
 *      Author: Shams
 */

#ifndef STACK_H_
#define STACK_H_

#include <iostream>
#include <cstdlib>

template <class T>
class stack {
private:

    int top;            // index to the top of the stack
    int size;            // size of array
    T *array_ptr;

public:

    stack(int SizeOfStack);
    void push(T data);
    void pop();
    T peek();
    bool isEmpty();
    bool isFull();
    ~stack(){ delete []array_ptr; }

};


#endif /* STACK_H_ */
