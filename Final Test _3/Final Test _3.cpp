/*
 * Hãy hiện thực lại hàm sắp xếp nhanh QuickSort int quicksort(int* arr, int size) trả về số lần phải thực hiện phép partition. Pivot được chọn cố định là phần tử đầu tiên.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <math.h>
#include <cctype>
#define FILENAME "f_g1q3_sol.cpp"
using namespace std;

bool codeCheck();

int partition(int* arr, int low, int high) {

	int pivot = low;
	int smallerIndex = low + 1;

	for (int i = low + 1; i <= high; i++)
	{
		if (arr[i] < arr[pivot])
		{
			swap(arr[i], arr[smallerIndex]);
			++smallerIndex;
		}
	}
	swap(arr[smallerIndex - 1], arr[pivot]);
	return (smallerIndex - 1);
}

/* Your code MUST NOT contain any words in the following list:
{"include", "while", "for", "goto", "static"} even in the comments */

//----------------------------------------------
// Restriction area
//----------------------------------------------

int quicksortRec(int* arr, int low, int high) {
	if (low < high)
	{
		int pivot = partition(arr, low, high);
		int countP = 1;
		countP += quicksortRec(arr, low, pivot - 1);
		countP += quicksortRec(arr, pivot + 1, high);
		return countP;
	}
	else
	{
		return 0;
	}
}

int quicksort(int* arr, int size) {
	return quicksortRec(arr, 0, size - 1);
}

int main(int argc, char** argv) {
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

	if (n % 2 == 0) {
		quicksort(arr, n);
		for (int i = 0; i < n; i++) cout << arr[i] << " ";
	}
	else {
		cout << "Partition count: " << quicksort(arr, n) << endl;
		for (int i = 0; i < n; i++) cout << arr[i] << " ";
	}
	cin.get();




	ifs.close();

	return 0;
}

bool codeCheck() {
	const char* forbiddenKeyword[] = { "include", "while", "for", "goto", "static" };
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
