//
//  List.hpp
//  DST
//
//  Created by Vic Wan on 2018/9/9.
//  Copyright © 2018 万伟琦. All rights reserved.
//

#ifndef List_hpp
#define List_hpp

#include <iostream>

#define ListNodePosi(T) ListNode<T>*

#define list_add_single_arg_assert\
        if (r < 0 || r > _size)\
            throw "Invalid argument!";

#define list_common_single_arg_assert\
        if (r < 0 || r >= _size)\
            throw "Invalid argument!";

template <typename T>
struct ListNode {
    T _data;
    ListNodePosi(T) _pred;
    ListNodePosi(T) _succ;
    
    ListNode()
    {
        _pred = nullptr;
        _succ = nullptr;
    }
    
    ListNode(T e, ListNodePosi(T) pred = nullptr, ListNodePosi(T) succ = nullptr) : _data(e), _pred(pred), _succ(succ)
    {
        
    }
    
    ~ListNode()
    {
        _pred = nullptr;
        _succ = nullptr;
    }
    
    ListNodePosi(T) insertAsPred ( T const& e )
    {
        ListNodePosi(T) node = new ListNode(e, _pred, this);
        _pred->_succ = node;
        _pred = node;
    }
    
    ListNodePosi(T) insertAsSucc ( T const& e )
    {
        ListNodePosi(T) node = new ListNode(e, this, _succ);
        _succ->_pred = node;
        _succ = node;
    }
};

typedef int Rank;

template <typename T>
class List {
    
protected:
    int _size;
    ListNodePosi(T) _header;
    ListNodePosi(T) _trailer;
    
    void insertion(List<T>** l, ListNodePosi(T) nodeToInsert);
    
public:
    List()
    {
        //create header and trailer
        _header = new ListNode<T>();
        _trailer = new ListNode<T>();
        
        _header->_succ = _trailer;
        _trailer->_pred = _header;
    }
    
    //链表窥视
    int size() const;
    bool hasCycle() const;
    void printList() const;
    ListNodePosi(T) first();
    ListNodePosi(T) last();
    
    //insert
    void insertAtIndex(const T& e, Rank r);
    void append(const T& e);
    void insertAsFirst(const T& e);
    void insertAfter(ListNodePosi(T) n);
    
    //remove
    T removeAtIndex(Rank r);
    void remove(Rank lo, Rank hi);
    void removeAll();
    
    //find & search
    ListNodePosi(T) nodeAtIndex(Rank r) const;
    
    //sort
    void sort_insertion(Rank lo, Rank hi);
    void sort_selection(Rank lo, Rank hi);
};

#pragma mark - Inspection

template <typename T>
int List<T>::size() const
{
    return _size;
}

template <typename T>
void List<T>::printList() const
{
    if (_size < 1)
    {
        printf("链表长度为空！");
    }
    else
    {
        ListNodePosi(T) node = _header->_succ;
        printf("链表规模为: %d\n",_size);
        printf("链表元素为:\t");
        while (node->_succ != nullptr)
        {
            printf("%d\t", node->_data);
            node = node->_succ;
        }
        std::cout << std::endl;
    }
}

template <typename T>
ListNodePosi(T) List<T>::first()
{
    if (_size < 1)
        return nullptr;
    
    return _header->_succ;
}

template <typename T>
ListNodePosi(T) List<T>::last()
{
    if (_size < 1)
        return nullptr;
    
    return _trailer->_pred;
}

#pragma mark - Add

template <typename T>
void List<T>::insertAtIndex(const T &e, Rank r)
{
    list_add_single_arg_assert
    
    ListNodePosi(T) newNode = new ListNode<T>(e);
    ListNodePosi(T) node = nodeAtIndex(r);
    
    newNode->_pred = node->_pred;
    newNode->_succ = node;
    node->_pred->_succ = newNode;
    node->_pred = newNode;
    
    _size++;
}

template <typename T>
void List<T>::insertAsFirst(const T &e)
{
    insertAtIndex(e, 0);
}

template <typename T>
void List<T>::append(const T &e)
{
    insertAtIndex(e, _size);
}

template <typename T>
void List<T>::insertAfter(ListNode<T> *n)
{
    
}

#pragma mark - Remove

template <typename T>
void List<T>::remove(Rank lo, Rank hi)
{
    if (lo < 0 || hi > _size || hi <= lo)
        throw "Invalid arguments!";
    
    ListNodePosi(T) nodeLo = nodeAtIndex(lo);
    ListNodePosi(T) nodeHi_1 = nodeAtIndex(hi-1);
    
    nodeLo->_pred->_succ = nodeHi_1->_succ;
    nodeHi_1->_succ->_pred = nodeLo->_pred;
    nodeHi_1->_succ = nullptr;  //为了稍后遍历到这个节点能够停止遍历
    
    ListNodePosi(T) tmp = nullptr;
    while (nodeLo != nullptr)
    {
        tmp = nodeLo;
        nodeLo = nodeLo->_succ;
        delete tmp;
        _size --;
    }
}

template <typename T>
T List<T>::removeAtIndex(Rank r)
{
    list_common_single_arg_assert
    
    ListNodePosi(T) node = nodeAtIndex(r);
    T ret = node->_data;
    remove(r, r + 1);
    
    return ret;
}

template <typename T>
void List<T>::removeAll()
{
    remove(0, _size);
}

#pragma mark - Find & Search

template <typename T>
ListNodePosi(T) List<T>::nodeAtIndex(Rank r) const
{
    if (r < 0 || r > _size)
        return nullptr;
    
    ListNodePosi(T) node = _header->_succ;
    
    if (r < (_size >> 1))
    {
        for (int i = 0; i < r; i++)
        {
            node = node->_succ;
        }
    }
    else
    {
        for (int i = _size - 1; i < (_size - r); i++)
        {
            node = node->_pred;
        }
    }
    return node;
}


#pragma mark - Sort



template <typename T>
void List<T>::sort_insertion(Rank lo, Rank hi)    //从剩下的元素中取出一个，插入序列
{
    /*
     （从大向小插）
     从后向前取，插入到严格小于该元素的元素之后
     或者
     从前向后取，插入到第一个不大于该元素的元素之后
     这样，可以保证排序的稳定性
     
     这里取后者。原因是：在极端情况下，也就是所有元素的值全都相等的情况下，可以在新链表中少遍历 Ο(n²) 次
     */
    
    ListNodePosi(T) oldNode = nodeAtIndex(lo);
    
    //先把 lo-hi 全断了，再一个一个接上，用一个临时链表
    List<T> *tmpList = new List<T>();
    
}

template <typename T>
void List<T>::insertion(List<T> **l, ListNode<T> *nodeToInsert)
{
    List *list = *l;
    
    
}

template <typename T>
void List<T>::sort_selection(Rank lo, Rank hi)    //从剩下的元素中选择出最大的一个，放入序列
{
    // 从后向前取元素，保证排序的稳定性
}


#endif /* List_hpp */
