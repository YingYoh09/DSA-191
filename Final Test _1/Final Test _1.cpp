/*
 * Hãy hiện thực hàm đệ quy để đếm và trả về số nút có đúng 2 con trong cây nhị phân.


Chú ý: đọc kỹ lớp với thuộc tính và phương thức đã được dựng sẵn trong code.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <math.h>
#include <cctype>
#define FILENAME "f_g1q1_sol.cpp"
using namespace std;

/* Your code MUST NOT contain any words in the following list:
{"include", "while", "for", "goto"} even in the comments */

//----------------------------------------------
// Begin implementation
//----------------------------------------------

bool codeCheck() {
	const char* forbiddenKeyword[] = { "include", "while", "for", "goto" };
	fstream ifs;
	ifs.open("main.cpp", ios::in);
	if (ifs.fail()) ifs.open(FILENAME, ios::in);
	if (ifs.fail()) return true;
	ifs.seekg(0, ifs.end);
	int fileSize = ifs.tellg();
	ifs.seekg(0, ifs.beg);
	char* fileContent = new char[fileSize];
	ifs.read(fileContent, fileSize);
	ifs.close();
	*strstr(fileContent, "bool codeCheck() {") = '\0';
	char* todoSegment = strstr(fileContent, "// Begin implementation");
	int numberOfForbiddenKeyword = sizeof(forbiddenKeyword) / sizeof(const char*);
	for (int i = 0; i < numberOfForbiddenKeyword; i++) { if (strstr(todoSegment, forbiddenKeyword[i])) return false; }
	delete[] fileContent;
	return true;
}

class Node {
public:
	int data;
	Node* left;
	Node* right;

	Node(int val) {
		data = val;
		left = right = NULL;
	}
};

class BinaryTree
{
private:
	Node* root;
	int size;
protected:
	void clearRecursion(Node* root);
	void addBSTRecursion(Node*& root, int val);
	int deleteBSTRecursion(Node*& root, int val);
	int countTwoChildrenNodesRecursion(Node* root);

public:
	BinaryTree();
	~BinaryTree();
	void clear();
	void addBST(int val);
	int deleteBST(int val);
	void printTreeStructure();
	int countTwoChildrenNodes();
};

int main(int argc, char** argv) {
	if (codeCheck() == false) {
		cout << "Forbidden-keyword rule violation." << endl;
		return -1;
	}

	ifstream ifs;
	ifs.open("inp.txt", ifstream::in);

	string temp;
	getline(ifs, temp);

	int n = stoi(temp);
	int* arr = new int[n];

	for (int i = 0; i < n; i++) {
		getline(ifs, temp);
		arr[i] = stoi(temp);
	}

	BinaryTree* tree = new BinaryTree();
	for (int i = 0; i < n; i++) {
		tree->addBST(arr[i]);
	}

	cout << tree->countTwoChildrenNodes() << endl;

	ifs.close();
	cin.get();
	return 0;
}

BinaryTree::BinaryTree()
{
	root = NULL;
	size = 0;
}

BinaryTree::~BinaryTree()
{
	clear();
}

void BinaryTree::clearRecursion(Node* root) {
	if (root != NULL) {
		clearRecursion(root->left);
		clearRecursion(root->right);
		delete root;
	}
}
void BinaryTree::clear() {
	clearRecursion(root);
}

void BinaryTree::addBSTRecursion(Node*& root, int val) {
	if (root == NULL)
		root = new Node(val);
	else {
		if (val > root->data)
			addBSTRecursion(root->right, val);
		else
			addBSTRecursion(root->left, val);
	}
}

void BinaryTree::addBST(int val) {
	addBSTRecursion(root, val);
}

int BinaryTree::deleteBSTRecursion(Node*& root, int val) {
	if (root == NULL)
		return false;
	else if (root->data > val)
		return deleteBSTRecursion(root->left, val);
	else if (root->data < val)
		return deleteBSTRecursion(root->right, val);
	else {
		if (root->left == NULL) {
			Node* p = root;
			root = root->right;
			delete p;
			return true;
		}
		else if (root->right == NULL) {
			Node* p = root;
			root = root->left;
			delete p;
			return true;
		}
		else {
			Node* p = root->left;
			while (p->right) p = p->right;
			root->data = p->data;
			return deleteBSTRecursion(root->left, p->data);
		}
	}
}

int BinaryTree::deleteBST(int val) {
	return deleteBSTRecursion(root, val);
}



int BinaryTree::countTwoChildrenNodesRecursion(Node* root) {
	if (root == NULL)
	{
		return 0;
	}
	else
	{
		int l = countTwoChildrenNodesRecursion(root->left);
		int r = countTwoChildrenNodesRecursion(root->right);
		if (root->left != NULL && root->right != NULL)
		{
			return l + r + 1;
		}
		else
		{
			return l + r;
		}
	}
}

int BinaryTree::countTwoChildrenNodes() {
	return countTwoChildrenNodesRecursion(root);
}
