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
    int size();
    bool hasCycle();
    void printList();
    
    //insert
    void insertAtIndex(const T& e, Rank r);
    void append(const T& e);
    void insertAsFirst(const T& e);
    
    //remove
    T removeAtIndex(Rank r);
    void remove(Rank lo, Rank hi);
    
    //find & search
    ListNodePosi(T) nodeAtIndex(Rank r) const;
};

#pragma mark - Inspection

template <typename T>
int List<T>::size()
{
    return _size;
}

template <typename T>
void List<T>::printList()
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

#pragma mark - Remove

template <typename T>
void List<T>::remove(Rank lo, Rank hi)
{
    
}

template <typename T>
T List<T>::removeAtIndex(Rank r)
{
    list_common_single_arg_assert
    
    ListNodePosi(T) node = nodeAtIndex(r);
    T ret = node->_data;
    
    node->_pred->_succ = node->_succ;
    node->_succ->_pred = node->_pred;
    node->_pred = nullptr;
    node->_succ = nullptr;
    
    _size--;
    delete node;
    
    return ret;
}

#pragma mark - Find & Search

template <typename T>
ListNodePosi(T) List<T>::nodeAtIndex(Rank r) const
{
    if (r < 0 || r > _size)
        return nullptr;
    
    ListNodePosi(T) node = _header->_succ;
    for (int i = 0; i < r; i++)
    {
        node = node->_succ;
    }
    return node;
}


#endif /* List_hpp */
