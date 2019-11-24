#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <string.h>
#include <time.h>

using namespace std;

template <typename T>
class node
{
public:
	T data;
	node<T>* left = NULL;
	node<T>* right = NULL;
	int balance = 0;
	node(T data)
	{
		this->data = data;
	};

	// you can implement other relevant things here
	// TODO



};

template <typename T>
class AVLtree
{
	node<T>* root = NULL;

	// you can implement other relevant things here

	node<T>* rotateRight(node<T>*& root)
	{
		node<T>* temp = root->left;
		root->left = temp->right;
		temp->right = root;
		return temp;
	}

	node<T>* rotateLeft(node<T>*& root)
	{
		node<T>* temp = root->right;
		root->right = temp->left;
		temp->left = root;
		return temp;
	}

	//Left subtree is higher than the right subtree
	node<T>*& leftBalance(node<T>*& root, bool& taller)
	{
		node<T>* leftTree = root->left;
		//Left Left case
		if (leftTree->balance > 0)
		{
			//slide sai thu tu
			root->balance = 0;
			leftTree->balance = 0;
			root = rotateRight(root);
			taller = false;
		}
		else
		{
			//Left right case
			node<T>* rightTree = leftTree->right;
			if (rightTree->balance > 0)
			{
				root->balance = -1;
				leftTree->balance = 0;
			}
			else if (rightTree->balance == 0)
			{
				//slide thieu
				root->balance = 0;
				leftTree->balance = 0;
			}
			else
			{
				root->balance = 0;
				leftTree->balance = 1;
			}
			rightTree->balance = 0;
			root->left = rotateLeft(leftTree);
			root = rotateRight(root);
			taller = false;
		}
		return root;
	}

	//Right subtree is higher than the left subtree
	node<T>*& rightBalance(node<T>*& root, bool& taller)
	{
		node<T>* rightTree = root->right;
		//right right case
		if (rightTree->balance < 0)
		{
			root->balance = 0;
			rightTree->balance = 0;
			root = rotateLeft(root);
			taller = false;
		}
		else
		{
			//right left case
			node<T>* leftTree = rightTree->left;
			if (leftTree->balance < 0)
			{
				root->balance = 1;
				rightTree->balance = 0;
			}
			else if (leftTree->balance == 0)
			{
				//slide thieu
				root->balance = 0;
				rightTree->balance = 0;
			}
			else
			{
				root->balance = 0;
				rightTree->balance = -1;
			}
			leftTree->balance = 0;
			root->right = rotateRight(rightTree);
			root = rotateLeft(root);
			taller = false;
		}
		return root;
	}


	node<T>* add(node<T>*& root, node<T>*& newPtr, bool& taller)
	{
		if (root == NULL)
		{
			root = newPtr;
			taller = true;
			return root;
		}
		if (newPtr->data < root->data)
		{
			root->left = add(root->left, newPtr, taller);
			//left subtree is taller
			if (taller)
			{
				if (root->balance > 0)
					root = leftBalance(root, taller);
				else if (root->balance == 0)
					root->balance = 1;
				else
				{
					root->balance = 0;
					taller = false;
				}
			}
		}
		else //slide sai
		{
			root->right = add(root->right, newPtr, taller);
			//right subtree is taller
			if (taller)
			{
				if (root->balance < 0)
					root = rightBalance(root, taller);
				else if (root->balance == 0)
					root->balance = -1;
				else
				{
					root->balance = 0;
					taller = false;
				}
			}
		}
		return root;
	}


	/*
	 * The (sub)tree is shorter after a deletion on the right branch. Adjust the balance factors and if necessary balance the tree by rotating right.
	 */
	node<T>* removeLeftBalance(node<T>*& root, bool& shorter)
	{
		if (root->balance < 0)
		{
			root->balance = 0;
		}
		else if (root->balance == 0)
		{
			root->balance = 1;
			shorter = false;
		}
		else
		{
			node<T>* leftTree = root->left;
			if (leftTree->balance < 0)
			{
				node<T>* rightTree = leftTree->right;
				if (rightTree->balance < 0)
				{
					leftTree->balance = 1;
					root->balance = 0;
				}
				else if (rightTree->balance == 0)
				{
					root->balance = -1;
					leftTree->balance = 0;
				}
				else
				{
					root->balance = -1;
					leftTree->balance = 0;
				}
				rightTree->balance = 0;
				root->left = rotateLeft(leftTree);
				//slide thieu
				root = rotateRight(root);
			}
			else
			{

				if (leftTree->balance != 0)
				{
					root->balance = 0;
					leftTree->balance = 0;
				}
				else
				{
					root->balance = 1;
					leftTree->balance = -1;
					shorter = false;
				}
				root = rotateRight(root);
			}
		}
		return root;
	}

	/*
	 * The (sub)tree is shorter after a deletion on the left branch. Adjust the balance factors and if necessary balance the tree by rotating left.
	 */
	node<T>* removeRightBalance(node<T>*& root, bool& shorter)
	{
		if (root->balance > 0)
		{
			root->balance = 0;
		}
		else if (root->balance == 0)
		{
			root->balance = -1;
			shorter = false;
		}
		else
		{
			node<T>* rightTree = root->right;
			if (rightTree->balance > 0)
			{
				node<T>* leftTree = rightTree->left;
				if (leftTree->balance > 0)
				{
					rightTree->balance = -1;
					root->balance = 0;
				}
				else if (leftTree->balance == 0)
				{
					root->balance = 1;
					rightTree->balance = 0;
				}
				else
				{
					root->balance = 1;
					rightTree->balance = 0;
				}
				leftTree->balance = 0;
				root->right = rotateRight(rightTree);
				//slide thieu
				root = rotateLeft(root);
			}
			else
			{
				if (rightTree->balance != 0)
				{
					root->balance = 0;
					rightTree->balance = 0;
				}
				else
				{
					root->balance = -1;
					rightTree->balance = 1;
					shorter = false;
				}
				root = rotateLeft(root);
			}
		}
		return root;
	}

	int getHeight(node<T>* root)
	{
		if (root == NULL) {
			return 0;
		}
		else
		{
			int l = getHeight(root->left);
			int r = getHeight(root->right);
			if (l < r) l = r;
			return l + 1;
		}
	}

	node<T>* remove(node<T>*& root, T delValue, bool& shorter, bool& success)
	{
		if (root == NULL)
		{
			success = false;
			shorter = false;
			return NULL;
		}
		if (delValue < root->data)
		{
			root->left = remove(root->left, delValue, shorter, success);
			if (shorter)
				root = removeRightBalance(root, shorter);
		}
		else if (delValue > root->data)
		{
			root->right = remove(root->right, delValue, shorter, success);
			if (shorter)
				root = removeLeftBalance(root, shorter);
		}
		else
		{
			if (root->right == NULL)
			{
				node<T>* newRoot = root->left;
				success = true;
				shorter = true;
				delete root;
				root = newRoot;
				return root;
			}
			else if (root->left == NULL)
			{
				node<T>* newRoot = root->right;
				success = true;
				shorter = true;
				delete root;
				root = newRoot;
				return root;
			}
			else
			{
				node<T>* tempPtr = root->right;
				while (tempPtr->left != NULL)
					tempPtr = tempPtr->left;
				root->data = tempPtr->data;
				root->right = remove(root->right, tempPtr->data, shorter, success);

				if (shorter)
					root = removeLeftBalance(root, shorter);
			}
		}
		return root;
	}


	void print(node<T>*& subroot)
	{
		if (subroot == 0)
		{
			cout << '*';
			return;
		}
		cout << subroot->data;
		cout << '(';
		print(subroot->left);
		cout << '|';
		print(subroot->right);
		cout << ')';
		return;
	}

public:
	AVLtree() {}

	bool add(T& data)
	{

		node<T>* newNode = new node<T>(data);
		bool taller = true;
		add(root, newNode, taller);
		return taller;
	}

	// the remove function:
	bool remove(T& data)
	{
		bool success = false;
		bool shorter = false;
		remove(root, data, shorter, success);
		return shorter;
	}

	void print()
	{
		print(root);
	}
};


int main(int argc, char* argv[]) {
	ifstream inFile("inp.txt", ios::in);
	int i;
	int j;
	int k;

	AVLtree<int>* a = new AVLtree<int>;

	if (!inFile) {
		cout << "Unable to open file";
		exit(1); // terminate with error
	}
	inFile >> i;
	int* arr = new int[i];
	for (j = 0; j < i; j++) {
		inFile >> k;
		a->add(k);
	}
	inFile >> i;
	for (j = 0; j < i; j++) {
		inFile >> k;
		a->remove(k);
	}
	inFile >> i;
	for (j = 0; j < i; j++) {
		inFile >> k;
		a->add(k);
	}
	inFile >> i;
	for (j = 0; j < i; j++) {
		inFile >> k;
		a->remove(k);
	}
	a->print();
	
	inFile.close();
	cin.get();
	return 0;
}