#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
using namespace std;

template <class T>
class Node {
public:
	T data;
	Node* link;
	Node() {
		this->link = NULL;
	}

	Node(T data) {
		this->data = data;
		this->link = NULL;
	}
};

template <class T>
class Stack {
private:
	Node<T>* top;
	int count;
public:
	Stack() {
		top = NULL;
		count = 0;
	}

	~Stack() {
		clear();
	}
	void push(T val);
	T getTop();
	int pop(T& val);
	void clear();
	bool isEmpty();
	void print2Console();
};

void print(int* arr, int n) {
	Stack<int> s1;
	Stack<int> s2;
	for (int i = n-1; i>=0; i--)
	{
		s1.push(arr[i]);
	}
	for (int i = 0; i < n; i++)
	{
		int tmp;
		s1.pop(tmp);
		while (!s1.isEmpty() && s1.getTop() <= arr[i])
		{
			s2.push(s1.getTop());
			s1.pop(tmp);
		}
		if (s1.isEmpty())
			cout << arr[i] << " -> " << -1 << "\n";
		else cout << arr[i] << " -> " << s1.getTop() << "\n";
		while (!s2.isEmpty())
		{
			s1.push(s2.getTop());
			s2.pop(tmp);
		}
	}
}

int main(int argc, char** argv) {
	ifstream ifs("inp.txt", ios::in);
	string temp;
	getline(ifs, temp);

	int n = stoi(temp);
	int* arr = new int[n];

	for (int i = 0; i < n; i++) {
		getline(ifs, temp);
		arr[i] = stoi(temp);
	}

	print(arr, n);
	return 0;
}

template <class T>
void Stack<T>::clear() {
	T temp;
	while (this->count > 0) {
		this->pop(temp);
	}
}

template <class T>
bool Stack<T>::isEmpty() {
	return count == 0;
}

template <class T>
void Stack<T>::push(T val) {
	Node<T>* pNew = new Node<T>(val);
	pNew->link = top;
	top = pNew;
	count++;
}

template <class T>
void Stack<T>::print2Console() {
	Node<T>* p = top;
	while (p != NULL) {
		cout << p->data << " ";
		p = p->link;
	}
}

template <class T>
int Stack<T>::pop(T& val) {
	if (count == 0) return 0;
	else
	{
		Node<T>* p = top;
		val = top->data;
		top = top->link;
		delete[] p;
		count--;
		return 1;
	}
}

template <class T>
T Stack<T>::getTop() {
	return this->top->data;
}