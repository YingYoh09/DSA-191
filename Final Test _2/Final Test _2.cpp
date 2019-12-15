/*
 * Hãy hiện thức một số phương thức trên lớp MaxHeap đã được dựng sẵn trong đề bài:


- Phương thức printValuesLargerThan(int k): in tất cả các phần tử của heap (theo thứ tự xuất hiện) có giá trị lớn hơn k. Không được phép duyệt hết tất cả các phần tử. Khi in luôn có một khoảng trắng phía sau phần tử, không xuống dòng.


- Phương thức isMaxHeap(int* arr, int size): kiểm tra một mảng có phải là một max heap hay không.


Sinh viên phải chú ý các hiện thực có sẵn của lớp MaxHeap và không được sử dụng vòng lặp.


 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <math.h>
#include <cctype>
#include <algorithm>
#define FILENAME "f_g1q2_sol.cpp"
#define MAXNUMBER 1000
using namespace std;

bool codeCheck();

class MaxHeap {
private:
	int arr[MAXNUMBER];
	int count;
protected:
	int reHeapUp(int pos);
	int reHeapDown(int pos);
	void printValuesLargerThanRec(int k, int pos);
	static bool isMaxHeapRec(int* arr, int pos, int size);

public:
	MaxHeap();
	void print();
	int* toArray();
	int getSize();

	int buildHeap(int* a, int size);
	void printValuesLargerThan(int k);
	static bool isMaxHeap(int* a, int size);
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

	MaxHeap* h = new MaxHeap();

	cout << n << endl;

	if (n % 3 == 0) {
		h->buildHeap(arr, n);
		h->printValuesLargerThan(arr[0]);
		h->print();
	}
	else {
		h->buildHeap(arr, n);

		if (n % 2 == 0)
			cout << MaxHeap::isMaxHeap(arr, n);
		else
			cout << MaxHeap::isMaxHeap(h->toArray(), n);


		cout << endl;
		h->print();
	}
	ifs.close();
	cin.get();
	return 0;
}

int MaxHeap::reHeapUp(int position) {
	if (position > 0) {
		int parent = floor((position - 1) / 2);
		if (arr[position] > arr[parent]) {
			swap(arr[position], arr[parent]);

			return 1 + reHeapUp(parent);
		}
		else return 0;
	}
	else return 0;
}

int MaxHeap::reHeapDown(int position) {
	int left = position * 2 + 1;
	int right = position * 2 + 2;
	int large = 0;
	if (left < count) {
		if (right < count && arr[right] > arr[left]) {
			large = right;
		}
		else large = left;
		if (arr[large] > arr[position]) {
			swap(arr[large], arr[position]);
			return 1 + reHeapDown(large);
		}
		else return 0;
	}
	else return 0;
}

int* MaxHeap::toArray() {
	return arr;
}

int MaxHeap::getSize() {
	return count;
}

MaxHeap::MaxHeap() {
	count = 0;
}

void MaxHeap::print() {
	for (int i = 0; i < count; i++) cout << arr[i] << " ";
	cout << endl;
}

int MaxHeap::buildHeap(int* a, int size) {
	memcpy(arr, a, size * sizeof(int));
	count = size;
	int swapCount = 0;
	for (int i = size / 2; i >= 0; i--)
		swapCount += reHeapDown(i);

	return swapCount;
}

/* Your code MUST NOT contain any words in the following list:
{"include", "while", "for", "goto"} even in the comments */

//----------------------------------------------
// Restriction area
//----------------------------------------------

void MaxHeap::printValuesLargerThanRec(int k, int pos) {
	cout << "Call recursion" << endl;
	// TODO
	int left = pos * 2 + 1;
	int right = pos * 2 + 2;
	
	if (pos >= getSize())
		return;

	if (arr[pos] <= k) {
		return;
	}

	cout << arr[pos] << " ";

	printValuesLargerThanRec(k, left);
	printValuesLargerThanRec(k, right);
}

void MaxHeap::printValuesLargerThan(int k) {
	printValuesLargerThanRec(k, 0);
}

bool MaxHeap::isMaxHeapRec(int* arr, int pos, int size) {
	if (pos > (size - 2) / 2)
		return true;
	int left = 2 * pos + 1;
	int right = 2 * pos + 2;
	if (arr[pos] >= arr[left] && arr[pos] >= arr[right] && isMaxHeapRec(arr, left, size) && isMaxHeapRec(arr, right, size))
	{
		return true;
	}
	return false;
}

bool MaxHeap::isMaxHeap(int* arr, int size) {
	return isMaxHeapRec(arr, 0, size);
}

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
	char* todoSegment = strstr(fileContent, "// Restriction area");
	int numberOfForbiddenKeyword = sizeof(forbiddenKeyword) / sizeof(const char*);
	for (int i = 0; i < numberOfForbiddenKeyword; i++) { if (strstr(todoSegment, forbiddenKeyword[i])) return false; }
	delete[] fileContent;
	return true;
}
