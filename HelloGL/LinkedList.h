#pragma once

template <typename T>
struct ListNode
{
	T data;
	ListNode* next;
};

template <typename T>
class LinkedList
{
private:
	ListNode<T>* _head;
	unsigned int _size;
public:
	LinkedList();
	~LinkedList();

	ListNode<T>* MakeNode(T data);
	void PrintList() { PrintList(_head); }
	void PrintList(ListNode<T>* p);
	void DeleteList() { DeleteList(_head); }
	void DeleteList(ListNode<T>* p);
	ListNode<T>* InsertFirst(T data);
	ListNode<T>* InsertFirst(ListNode<T>* newNode);
	ListNode<T>* GetNode(int pos) { return GetNode(pos, _head); }
	ListNode<T>* GetNode(int pos, ListNode<T>* p);
	ListNode<T>* Find(T val) { return Find(val, _head); }
	ListNode<T>* Find(T val, ListNode<T>* p);
	void InsertAfter(ListNode<T>* newNode, ListNode<T>* p);
	void DeleteAfter(ListNode<T>* p);

	ListNode<T>* Head() { return _head; }
	unsigned int Size() { return _size; }

	T operator[](unsigned int i) { return GetNode(i)->data; }
};

template <typename T>
LinkedList<T>::LinkedList()
{
	_head = nullptr;
	_size = 0;
}


template <typename T>
LinkedList<T>::~LinkedList()
{
	DeleteList();
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
	if (p != nullptr)
	{
		if (p->next != nullptr)
		{
			DeleteList(p->next);
		}
		delete p;
		p = nullptr;
		_size--;
	}
}


template <typename T>
ListNode<T>* LinkedList<T>::InsertFirst(T data)
{
	ListNode<T>* newNode = MakeNode(data);
	newNode->next = _head;
	_head = newNode;
	_size++;
	return newNode;
}


template <typename T>
ListNode<T>* LinkedList<T>::InsertFirst(ListNode<T>* newNode)
{
	newNode->next = _head;
	_head = newNode;
	_size++;
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
	_size++;
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