//
//  Queue.hpp
//  DST
//
//  Created by Vic Wan on 2018/9/11.
//  Copyright © 2018 万伟琦. All rights reserved.
//

#ifndef Queue_hpp
#define Queue_hpp

#include <iostream>
#include "List.hpp"

template <typename T>
class Queue {

private:
    List<T> *_l;
    
public:
    
    Queue()
    {
        _l = new List<T>();
    }
    
    ~Queue()
    {
        delete _l;
    }
    
    void enqueue(T& e);
    T dequeue();
    T& front();
};

template <typename T>
void Queue<T>::enqueue()
{
    
}

#endif /* Queue_hpp */
