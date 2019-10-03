/////////////////////////////////////////////////////////
//
// LAB 4: Stack and Queue
//
//
//	Basic
//
//
/////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
using namespace std;

struct LlItem {
	int data;
	LlItem* next;
	LlItem() : next(NULL) {}
	LlItem(int a, LlItem* p) : data(a), next(p) {}
};

class Stack {

public:
	virtual void Create() = 0;
	virtual void Push(const int& item) = 0;
	virtual void Pop() = 0;
	virtual int Top() = 0;
	virtual bool isEmpty() = 0;
	virtual bool isFull() = 0;
	virtual void Clear() = 0;
	virtual int Size() = 0;
};

class LinkedStack : public Stack {

private:
	int size;
	LlItem* sTop;
public:
	void Create() {
		size = 0;
		sTop = NULL;
	}

	void Clear()
	{
		size = 0;
		while (sTop != NULL)
		{
			LlItem* tmp = sTop;
			sTop = sTop->next;
			delete tmp;
		}
	}

	void Push(const int& newE) {
		LlItem* tmp = new LlItem(newE, sTop);
		sTop = tmp;
		size++;
	}

	void Pop() {
		LlItem* tmp = sTop;
		sTop = sTop->next;
		delete tmp;
		size--;
	}

	int Top() {
		if (isEmpty()) return INT8_MIN;
		return sTop->data;
	}

	bool isEmpty() {
		return sTop == NULL;
	}

	bool isFull() {
		LlItem* temp = new LlItem;
		if (!temp) return true;
		return false;
	}

	int Size() {
		return size;
	}

	void PrintStack() {
		cout << "Print: ";
		LlItem* temp;
		temp = sTop;
		while (temp != NULL) {
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}
};

/*
 * main for trash
 */

int main(int argc, char* argv[]) {
	LinkedStack* list = NULL;
	ifstream ifs;
	ifs.open(argv[1]);
	if (!ifs) {
		std::cout << "Unable to open file";
		exit(1); // terminate with error
	}
	char command;
	int val, temp;
	try {
		while (ifs >> command) {
			switch (command) {
			case 'l': //create an object of LinkedStack
				if (list != NULL) delete list;
				list = new LinkedStack();
				list->Create();
				break;
			case 'p': //push an element to the top of the stack
				ifs >> val;
				list->Push(val);
				cout << "Push " << val << endl;
				break;
			case 'r': //pop an element from the top of the stack
				list->Pop();
				cout << "Pop" << endl;
				break;
			case 't': //return top element of stack
				temp = list->Top();
				cout << "Top: " << temp << endl;
				break;
			case 'e': //check if stack is empty or not
				temp = list->isEmpty();
				if (temp) {
					cout << "Stack is empty" << endl;
				}
				else {
					cout << "Stack is not empty" << endl;
				}
				break;
			case 'f': //check if stack is full or not, if stack is linkedstack return false
				temp = list->isFull();
				if (temp) {
					cout << "Stack is full" << endl;
				}
				else {
					cout << "Stack is not full" << endl;
				}
				break;
			case 'c': //clear the stack
				list->Clear();
				break;
			case 's': //return the size (number of elements) of stack
				temp = list->Size();
				cout << "Size: " << temp << endl;
				break;
			case 'z':
				list->PrintStack();
				break;
			}
		}
	}
	catch (char const* s) {
		printf("An exception occurred. Exception type: %s\n", s);
	}
	if (list != NULL) delete list;
	ifs.close();
	return 0;
}