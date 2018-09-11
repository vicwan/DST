//
//  Stack.hpp
//  DST
//
//  Created by Vic Wan on 2018/9/11.
//  Copyright © 2018 万伟琦. All rights reserved.
//

#ifndef Stack_hpp
#define Stack_hpp

#include <iostream>
#include "Vector.hpp"

template <typename T>
class Stack{
    
private:
    Vector<T> _v;
    
public:
    Stack()
    {
        _v = Vector<T>();
    }
    
    ~Stack()
    {
        delete _v;
    }
    
    void push(T& e);
    void pop();
    T& top();
};

template <typename T>
void Stack<T>::push(T &e)
{
    _v->append(e);
}

template <typename T>
void Stack<T>::pop()
{
    _v->removeAtIndex(_v.size() - 1);
}

template <typename T>
T& Stack<T>::top()
{
    return _v[_v.size() - 1];
}

#endif /* Stack_hpp */
