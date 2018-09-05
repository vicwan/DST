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
	
protected:
	
	Rank _size;
	int _capacity;
	T* _elem;
	
	
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
	//向量窥视
	const Rank size();	//在返回值前面加 const，说明该返回值只能被读取，不能被修改
    bool isEmpty();
	void printVector();

	//增
	void insert(Rank r, T const& e);
	void append(T const& e);
	
	//删
	T remove(T const& e);	//
	void remove(Rank lo, Rank hi);
	void removeAtIndex(Rank r);
	
	/*
	 查找
	 在函数后面添加 const，说明函数内部不能修改成员变量的值，但是用 mutable 修饰的成员变量除外
	 */
	Rank find(T const& e) const;	//整体查找
	Rank find(T const& e, Rank lo, Rank hi) const;	//无序向量的顺序查找：返回最后一个元素e的位置；失败时，返回lo - 1
	Rank search_binary(T const& e) const;
	Rank search_fibonacci(T const& e) const;
	
	//排序
	
};


/******************** Public ********************/

#pragma mark - Inspection

template <typename T>
const Rank Vector<T>::size()
{
	return _size;
}

template <typename T>
bool Vector<T>::isEmpty()
{
	return _size == 0;
}

template <typename T>
void Vector<T>::printVector()
{
	if (isEmpty())
	{
		std::cout << "Vector 为空" << std::endl;
		return;
	}
	
	printf("Size: %d  Capacity: %d\n", _size, _capacity);
	printf("元素: ");
	for (Rank i = 0; i < _size; i++)
	{
		printf("%d\t", _elem[i]);
	}
	std::cout << std::endl;
}


#pragma mark - Add

template <typename T>
void Vector<T>::insert(Rank r, T const& e)      //size=5, 01234, r=5, hot=4
{
    if (r < 0 || r > _size)
        return;
    
    expand();
    
	Rank hot = _size;
	while (hot > r) {
		_elem[hot] = _elem[hot - 1];
		hot --;
	}
	_elem[hot] = e;
	_size ++;
}

template <typename T>
void Vector<T>::append(T const& e)
{
    insert(_size, e);
}

#pragma mark - Remove

template <typename T>
void Vector<T>::remove(Rank lo, Rank hi)
{
	//异常判断
	if (lo >= hi) throw "Rank lo should not be equal to or greater than rank hi.";
	if (lo < 0) throw "Rank lo should not be less than 0.";
	if (hi > _size) throw "Rank hi should not be greater than the size of vector.";
	
	//后面的元素直接前移覆盖
	while (hi < _size)
	{
		_elem[lo++] = _elem[hi++];
	}
	
	_size = _size - (hi - lo);
	shrink();
}

template <typename T>
void Vector<T>::removeAtIndex(Rank r)
{
	remove(r, r + 1);
}


#pragma mark - Find & Search
template <typename T>
Rank Vector<T>::find(const T &e, Rank lo, Rank hi) const
{
	if (lo < 0 || hi > _size)
		throw "Invalid argument(s)";
	
	while (hi > lo) {
		if (_elem[hi - 1] == e)
			break;
		hi --;
	}
	while ((lo < hi--) && (_elem[hi] != e));
	
	printf("元素 index 为: %d\n", hi);
	return hi;
}

template <typename T>
Rank Vector<T>::find(const T &e) const
{
	return find(e, 0, _size);
}

/******************* Private ********************/
#pragma mark - Private
template <typename T>
void Vector<T>::shrink()
{
    //如果 size > (capacity / 2)
    if (_size > _capacity >> 1) return;
    
    _capacity >>= 1;
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
