/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dsaLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DSALIB_H
#define DSA191_A1_DSALIB_H
#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

class DSAException
{
	int _error;
	string _text;
public:

	DSAException() : _error(0), _text("Success")
	{
	}

	DSAException(int err) : _error(err), _text("Unknown Error")
	{
	}

	DSAException(int err, const char* text) : _error(err), _text(text)
	{
	}

	int getError() { return _error; }
	string& getErrorText() { return _text; }
};

template <class T>
struct L1Item
{
	T data;
	L1Item<T>* pNext;
	L1Item<T>* pPrevious;

	L1Item() : pNext(nullptr), pPrevious(nullptr)
	{
	}

	L1Item(T& a) : data(a), pNext(nullptr), pPrevious(nullptr)
	{
	}
};

template <class T>
class L1List
{
	// The head pointer of linked list
	L1Item<T>* _pHead;
	// The rear pointer of linked list
	L1Item<T>* _pRear;
	// number of elements in this list
	size_t _size; 
public:
	L1List() : _pHead(nullptr), _pRear(nullptr), _size(0)
	{
	}
	
	~L1List();

	void clean();

	bool isEmpty()
	{
		return (_pHead == nullptr);
	}

	L1Item<T>* get_p_head() const
	{
		return _pHead;
	}

	L1Item<T>* get_p_rear() const
	{
		return _pRear;
	}
	size_t getSize()
	{
		return _size;
	}

	T& at(int i); // give the reference to the element i-th in the list
	T& operator[](int i); // give the reference to the element i-th in the list

	// find an element similar to a in the list. Set the found index to idx, set idx to -1 if failed. Return true if success.
	//bool find(T& a, int& idx);
	
	
	// insert an element into the list at pointer. this func cannot be false
	int insert(L1Item<T>* pPosition, T& a);

	// remove an element at position i in the list. Return 0 if success, -1 otherwise.
	int remove(L1Item<T>*& pPosition);

	//
	//// insert an element into the list at location i. Return 0 if success, -1 otherwise
	//int insert(int i, T& a);
	//// remove an element at position i in the list. Return 0 if success, -1 otherwise.
	//int remove(int i);

	// insert to the end of the list
	void push_back(T& a);
	// insert to the beginning of the list
	void insertHead(T& a);

	// remove the beginning element of the list
	int removeHead();
	// remove the last element of the list
	int removeLast(); 

	//void reverse();
	
	// traverse to i-th node. Return pNode if success, nullptr otherwise 
	L1Item<T>* traverse(int i);
};

template <class T>
int L1List<T>::insert(L1Item<T>* pPosition, T& a)
{
	//DONE: insert node in position pointer
	L1Item<T>* pNew = new L1Item<T>(a);
	if (pPosition == nullptr)
		return -1;
	if (pPosition == _pHead)
		_pHead = pNew;
	if (pPosition->pPrevious != nullptr) {
		(pPosition->pPrevious)->pNext = pNew;
		pNew->pPrevious = pPosition->pPrevious;
	}
	if (pPosition != nullptr) {
		pNew->pNext = pPosition;
		pPosition->pPrevious = pNew;
	}
	++_size;
	return 0;
}

template <class T>
int L1List<T>::remove(L1Item<T>*& pPosition)
{
	//DONE: remove a node pPosition
	if (pPosition == nullptr) return -1;

	if (pPosition == _pHead)
		_pHead = pPosition->pNext;
	if (pPosition == _pRear)
		_pRear = pPosition->pPrevious;
	if (pPosition->pNext != nullptr)
		(pPosition->pNext)->pPrevious = pPosition->pPrevious;
	if (pPosition->pPrevious != nullptr)
		(pPosition->pPrevious)->pNext = pPosition->pNext;
	--_size;
	delete pPosition;
	pPosition = nullptr;
	return 0;
}

template <class T>
void L1List<T>::push_back(T& a)
{
	// DONE: push back
	L1Item<T>* pNew = new L1Item<T>(a);
	if (isEmpty())
	{
		_pHead = pNew;
	}
	else
	{
		_pRear->pNext = pNew;
		pNew->pPrevious = _pRear;
	}
	_pRear = pNew;
	++_size;
}

/// Return 0 if success, -1 otherwise
template <class T>
void L1List<T>::insertHead(T& a)
{
	// DONE: insert head
	if (_pHead == nullptr)
		push_back(a);
	else insert(_pHead, a);
}

/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeHead()
{
	// DONE: remove head
	if (remove(_pHead) == -1)
		return -1;
	return 0;
}

/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeLast()
{
	// DONE: remove last node
	if (remove(_pRear) == -1)
		return -1;
	return 0;
}

template <class T>
L1Item<T>* L1List<T>::traverse(int i)
{
	// DONE: Traverse to i-th node
	L1Item<T>* node = _pHead;
	for (; i > 0 && node->pNext != nullptr; --i)
	{
		node = node->pNext;
	}
	if (i == 0) return node;
	else return nullptr;
}

template <class T>
L1List<T>::~L1List()
{
	//DONE: Destructor
	L1Item<T>* pTemp;
	while (_pHead != nullptr)
	{
		pTemp = _pHead;
		_pHead = _pHead->pNext;
		delete pTemp;
	}
	_pHead = nullptr;
	_pRear = nullptr;
}

#endif //DSA191_A1_DSALIB_H
