#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
using namespace std;

class Node {
public:
	double coeff;
	int exp;
	Node* link;

	Node(double coeff, int exp) {
		this->coeff = coeff;
		this->exp = exp;
		this->link = NULL;
	}
};


class Polynomial {
	Node* head;

protected:
	int insertNode(Node* pPre, double coeff, int exp) {
		Node* pNew = new Node(coeff, exp);
		if (pNew == NULL)
			return 0;
		if (pPre == NULL) {
			pNew->link = this->head;
			this->head = pNew;
		}
		else {
			pNew->link = pPre->link;
			pPre->link = pNew;
		}
		return 1;
	}

	void deleteNode(Node* pPre, Node* pLoc) {
		if (pPre == NULL) {
			this->head = pLoc->link;
		}
		else {
			pPre->link = pLoc->link;
		}

		delete pLoc;
	}

public:
	Polynomial() {
		this->head = NULL;
	}

	Polynomial(const Polynomial& a) {
		Node* p = a.head;
		head = NULL;
		while (p != NULL) {
			insertTerm(p->coeff, p->exp);
			p = p->link;
		}
	}

	~Polynomial() {
		this->clear();
	}

	void clear() {
		Node* temp;
		while (this->head != NULL) {
			temp = this->head;
			this->head = this->head->link;
			delete temp;
		}
	}

	void print() {
		if (head == NULL) {
			printf("NULL\n");
			return;
		}
		if (head->exp == 0)
			printf("%g", head->coeff);
		else if (head->exp == 1)
			printf("%gx ", head->coeff);
		else
			printf("%gx^%d ", head->coeff, head->exp);
		Node* p = head->link;
		while (p != NULL) {
			// print coefficient
			if (p->coeff > 0)
				printf("+ %g", p->coeff);
			else
				printf("- %g", abs(p->coeff));
			// print exponent
			if (p->exp == 1)
				printf("x ");
			else if (p->exp != 0)
				printf("x^%d ", p->exp);
			p = p->link;
		}
		cout << endl;
	}

	const Polynomial& operator=(const Polynomial& a) {
		if (this != &a) {
			clear();
			Node* p = a.head;
			while (p != NULL) {
				insertTerm(p->coeff, p->exp);
				p = p->link;
			}
			return (*this);
		}
	}

	void insertTerm(double coeff, int exp) {
		Node* temp = head;
		Node* insertNode;
		Node* pre = NULL;
		while (temp != NULL && temp->exp > exp)
		{
			pre = temp;
			temp = temp->link;
		}
		if (temp == NULL)
		{
			insertNode = new Node(coeff, exp);
			insertNode->link = NULL;
			if (head == NULL) head = insertNode;
			if (pre != NULL) pre->link = insertNode;
		}
		else if (temp->exp < exp && pre == NULL)
		{
			//at head
			insertNode = new Node(coeff, exp);
			insertNode->link = head;
			head = insertNode;
		}
		else if (temp->exp < exp)
		{
			insertNode = new Node(coeff, exp);
			pre->link = insertNode;
			insertNode->link = temp;
		}
		else
		{
			temp->coeff = temp->coeff + coeff;
			if (temp->coeff == 0)
				deleteNode(pre, temp);
		}
	}

	Polynomial operator+(const Polynomial& b) {
		Node* p1 = this->head;
		Node* p2 = b.head;
		Polynomial pAns;
		while (p1 && p2)
		{
			if (p2 == NULL || (p1 != NULL && p1->exp > p2->exp))
			{
				pAns.insertTerm(p1->coeff, p1->exp);
				p1 = p1->link;
			}
			else if (p1 == NULL || (p2 != NULL && p2->exp > p1->exp))
			{
				pAns.insertTerm(p2->coeff, p2->exp);
				p2 = p2->link;
			}
			else if (p1->exp == p2->exp)
			{
				if (p1->coeff + p2->coeff != 0)
					pAns.insertTerm(p1->coeff + p2->coeff, p1->exp);
				p1 = p1->link;
				p2 = p2->link;
			}
		}
		return pAns;
	}
};

int main(int argc, char** argv) {
	ifstream ifs("inp.txt", ios::in);

	int indexOfComma = 0;
	int numOfLines = 0;
	string temp = "";
	double coeff = 0.0;
	int exp = 0;

	Polynomial poly1;
	Polynomial poly2;

	getline(ifs, temp);
	numOfLines = stoi(temp);

	for (int i = 0; i < numOfLines && ifs.good(); i++) {
		getline(ifs, temp);
		indexOfComma = temp.find(',');

		coeff = stof(temp.substr(0, indexOfComma));
		exp = stoi(temp.substr(indexOfComma + 1));

		poly1.insertTerm(coeff, exp);
	}

	getline(ifs, temp);
	numOfLines = stoi(temp);

	for (int i = 0; i < numOfLines && ifs.good(); i++) {
		getline(ifs, temp);
		indexOfComma = temp.find(',');

		coeff = stof(temp.substr(0, indexOfComma));
		exp = stoi(temp.substr(indexOfComma + 1));

		poly2.insertTerm(coeff, exp);
	}

	Polynomial poly3 = poly1 + poly2;
	poly3.print();

	return 0;
}