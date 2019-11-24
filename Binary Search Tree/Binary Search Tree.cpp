#include <iostream>
#include <fstream>

using namespace std;

class Node
{
public:
	int data;
	Node* left = NULL;
	Node* right = NULL;

};

class BinaryTree
{
private:
	Node* root = NULL;

	void printPostfix(Node* root)
	{
		if (root != NULL)
		{
			cout << root->data << " ";
			printPostfix(root->left);
			printPostfix(root->right);
		}
	}
	void printInorder(Node*& root)
	{
		if (root != NULL)
		{
			printInorder(root->left);
			cout << root->data << ' ';
			printInorder(root->right);
		}
	}

	bool insert(Node*& root, int value) {
		if (root == NULL) {
			root = new Node();
			root->data = value;
			return true;
		}
		else if (root->data > value) {
			return insert(root->left, value);
		}
		else return insert(root->right, value);
	}
		
	//remove a value from BST
	bool remove(Node*& root, int value)
	{
		if (root == NULL) return false;
		if (root->data < value)
			return remove(root->right, value);
		if (root->data > value)
			return remove(root->left, value);
		if (root->data == value) {
			if (root->left == NULL)
			{
				Node* tmp = root;
				root = root->right;
				delete tmp;
			}
			else if (root->right == NULL)
			{
				Node* tmp = root;
				root = root->left;
				delete tmp;
			}
			else
			{
				Node* tNode = root->right;
				while (tNode->left != NULL)
					tNode = tNode->left;
				root->data = tNode->data;
				remove(root->right, tNode->data);
			}
			return true;
		}
	}

	bool find(Node*& root, int value)
	{
		if (root == NULL) return false;
		if (root->data == value) return true;
		if (root->data < value)
			return find(root->right, value);
		return find(root->left, value);
	}

public:

	bool insert(int value)
	{
		return insert(root, value);
	}

	void printPostfix()
	{
		printPostfix(root);
	}

	bool remove(int value)
	{
		return remove(root, value);
	}
	bool find(int value)
	{
		return find(root, value);
	}
};

int main(int argc, char* argv[]) {
	BinaryTree bt;
	ifstream inFile("inp.txt", ios::in);
	int val;
	char command;
	
	while (inFile >> command) {
		switch (command)
		{
		case 'i':   // Insert value to BST
			inFile >> val;
			bt.insert(val);
			break;
		case 'r':
			inFile >> val;
			bt.remove(val);
			break;
		case 'p':
			bt.printPostfix();
			cout << endl;
			break;
		}
	}
	system("pause");
	inFile.close();
	return 0;

}