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
#include "Utitlities.hpp"

#define DEFAULT_CAPACITY 3

#define vector_invalid_args_assert\
		if (lo < 0 || hi > _size || lo >= hi)\
			throw "Invalid argument(s)";

#define vector_single_arg_assert\
		if (r < 0 || r > _size)\
			throw "Invalid argument";

typedef int Rank;

template <typename T>
class Vector {
	
protected:
	
	Rank _size;
	int _capacity;
	T* _elem;
	
	
    void shrink();
    void expand();
	
	bool bubble_scan_once(Rank lo, Rank hi);
	Rank bubble_scan_once_fast(Rank lo, Rank hi);
	void merge(Rank lo, Rank mi, Rank hi);
    
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
	
	T& operator [] (Rank r)
	{
		return _elem[r];
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
	Rank search_binary_0(T const& e, Rank lo, Rank hi) const;	//返回不大于e的秩最大者
	Rank search_binary_1(T const& e, Rank lo, Rank hi) const;	//有多个命中元素时，不能保证返回秩最大者；查找失败时，简单地返回-1，而不能指示失败的位置
//	Rank search_fibonacci(T const& e, Rank lo, Rank hi) const;
	
	//排序
	void sort_bubble(Rank lo, Rank hi);
	void sort_bubble_fast(Rank lo, Rank hi);
	void sort_merge(Rank lo, Rank hi);
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
	printf("元素:\t");
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
    vector_single_arg_assert
    
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
	vector_invalid_args_assert
	
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
	vector_single_arg_assert
	remove(r, r + 1);
}


#pragma mark - Find & Search
template <typename T>
Rank Vector<T>::find(const T &e, Rank lo, Rank hi) const
{
	vector_invalid_args_assert
	
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

template <typename T>
Rank Vector<T>::search_binary_0(const T &e, Rank lo, Rank hi) const
{
	vector_invalid_args_assert
	
	while (lo < hi)
	{
		Rank mi = (lo + hi) >> 1;
		
		if (e < _elem[mi])
		{
			hi = mi;
		}
		else
		{
			lo = mi + 1;
		}
	}
	return --lo;
}

template <typename T>
Rank Vector<T>::search_binary_1(const T &e, Rank lo, Rank hi) const
{
	vector_invalid_args_assert
	
	while (lo < hi - 1)
	{
		Rank mi = (lo + hi) >> 1;
		if (e < _elem[mi])
		{
			hi = mi;
		}
		else
		{
			lo = mi;
		}
	}
	if (e == _elem[lo])
		return lo;
	return -1;
}

#pragma mark - Sort
#pragma mark Bubble sort
template <typename T>
void Vector<T>::sort_bubble(Rank lo, Rank hi)
{
	vector_invalid_args_assert
	while (!bubble_scan_once(lo, hi))
		hi --;
}

template <typename T>
bool Vector<T>::bubble_scan_once(Rank lo, Rank hi)
{
	bool isSorted = true;
	while (++lo < hi) {
		
		if (_elem[lo - 1] > _elem[lo])
		{
			util_swap(_elem[lo - 1], _elem[lo]);
			isSorted = false;
		}
	}
	return isSorted;
}

template <typename T>
void Vector<T>::sort_bubble_fast(Rank lo, Rank hi)
{
	vector_invalid_args_assert
	while (lo < (hi = bubble_scan_once_fast(lo, hi)));
}

template <typename T>
Rank Vector<T>::bubble_scan_once_fast(Rank lo, Rank hi)
{
	Rank last = lo;
	while (++lo < hi) {
		if (_elem[lo - 1] > _elem[lo])
		{
			util_swap(_elem[lo - 1], _elem[lo]);
			last = lo;
		}
	}
	return last;
}

#pragma mark Merge sort
template <typename T>
void Vector<T>::sort_merge(Rank lo, Rank hi)
{
	vector_invalid_args_assert
	if (lo == hi - 1)
	{
		return;
	}
	Rank mi = (lo + hi) / 2;
	
	sort_merge(lo, mi);
	sort_merge(mi, hi);
	merge(lo, mi, hi);
}

template <typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi)
{
	Rank lb = hi - mi;
	//申请一块空间, 后半部分复制出去
	T* c = new T[lb];
	
	for(Rank i = 0; i < lb; i++)
	{
		c[i] = _elem[mi + i];
	}
	//从后向前比较 a，c, 创建 3 个索引分别指向 a,b,c 的 hot index
	Rank hotA = mi - 1;
	Rank hotB = hi - 1;
	Rank hotC = lb - 1;
	
	while(hotA < hotB)
	{
		//添加 c
		if (c[hotC] >= _elem[hotA] || hotA < lo)
		{
			_elem[hotB--] = c[hotC--];
		}
		//添加 a
		if (c[hotC] < _elem[hotA] || hotC < 0)
		{
			_elem[hotB--] = _elem[hotA--];
		}
	}
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
