//
//  Vector.hpp
//  DST
//
//  Created by 万伟琦 on 2018/9/5.
//  Copyright © 2018年 万伟琦. All rights reserved.
//

#ifndef Vector_hpp
#define Vector_hpp

#include <iostream>

#define DEFAULT_CAPACITY 3

typedef int Rank;

template <typename T>
class Vector {
private:
    Rank _size;
    int _capacity;
    T* _elem;
    
protected:
    void shrink();
    void expand();
    
public:
    
    Vector( Rank s = 0, T v = 0 )
    {
        _size = s;
        _capacity = (s == 0 ? DEFAULT_CAPACITY : 2 * s);
        
        _elem = new T[_capacity];
        
        for (_size = 0; _size < s; _size ++) {
            _elem[_size] = v;
        }
    }
    
    ~Vector()
    {
        delete [] _elem;
    }
    
    bool isEmpty();
    void append(T const& e);
    void insert(Rank r, T const& e);
    T remove(T& e);
};


/******************** Public ********************/

template <typename T>
void Vector<T>::insert(Rank r, T const& e)
{
    
}

template <typename T>
void Vector<T>::append(T const& e)
{
    
}

template <typename T>
bool Vector<T>::isEmpty()
{
    return _size == 0;
}

/******************* Private ********************/

template <typename T>
void Vector<T>::shrink()
{
    //如果 size < (capacity / 4)
    if (_size < _capacity >> 2) return;
    
    _capacity = _capacity >> 1;
    T *newElem = new T[_capacity];
    
    for (Rank i = 0; i < _size; i++) {
        newElem[i] = _elem[i];
    }
    
    delete [] _elem;
    _elem = newElem;
}

template <typename T>
void Vector<T>::expand()
{
    //扩展为两倍size
    if (_size < _capacity) return;
    
    _capacity = _capacity << 1;
    T *newElem = new T[_capacity];
    
    if (newElem == nullptr)
        return;
    
    //复制元素
    for (Rank i = 0; i < _size; i++) {
        newElem[i] = _elem[i];
    }
    
    //删除原来的空间，并把指针指向新的空间
    delete [] _elem;
    _elem = newElem;
    
}


#endif /* Vector_hpp */
