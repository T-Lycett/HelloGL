#include "LinkedList.h"

#include <iostream>


template <typename T>
LinkedList<T>::LinkedList()
{
	_head = nullptr;
}


template <typename T>
LinkedList<T>::~LinkedList()
{
}

template <typename T>
ListNode<T>* LinkedList<T>::MakeNode(T data)
{
	ListNode<T>* node = new ListNode<T>();
	node->data = data;
	node->next = nullptr;
	return node;
}


template <typename T>
void LinkedList<T>::PrintList(ListNode<T>* p)
{
	if (p != nullptr)
	{
		std::cout << p->data << " ";
		if (p->next != nullptr)
		{
			PrintList(p->next);
		}
	}
}

template <typename T>
void LinkedList<T>::DeleteList(ListNode<T>* p)
{
	if (p->next != nullptr)
	{
		DeleteList(p->next);
	}
	delete p;
}


template <typename T>
ListNode<T>* LinkedList<T>::InsertFirst(ListNode<T>* newNode, ListNode<T>* p)
{
	newNode->next = p;
	p = newNode;
	return newNode;
}


template <typename T>
ListNode<T>* LinkedList<T>::GetNode(int pos, ListNode<T>* p)
{
	int count = 0;
	while (p != nullptr)
	{
		if (count == pos)
			return p;

		count++;
		p = p->next;
	}
	return nullptr;
}


template <typename T>
ListNode<T>* LinkedList<T>::Find(T val, ListNode<T>* p)
{
	if (p != nullptr)
	{
		if (p->data == val)
			return p;
		else
			return Find(p->next, val);
	}
	else
	{
		return nullptr;
	}
}


template <typename T>
void LinkedList<T>::InsertAfter(ListNode<T>* newNode, ListNode<T>* p)
{
	newNode->next = p->next;
	p->next = newNode;
}


template <typename T>
void LinkedList<T>::DeleteAfter(ListNode<T>* p)
{
	ListNode* pTemp;
	if (p != nullptr && p->next != nullptr)
	{
		pTemp = p->next;
		p->next = pTemp->next;
		delete pTemp;
	}
}