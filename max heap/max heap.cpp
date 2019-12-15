#include <iostream>
#include <fstream>
using namespace std;

void reheapUp(int* arr, int pos)
{
	if (pos > 0)
	{
		int parent = (pos - 1) / 2;
		if (arr[pos] > arr[parent])
		{
			swap(arr[pos], arr[parent]);
			reheapUp(arr, parent);
		}
	}
}

void reheapDown(int* arr, int pos, int lastPos) {
	int left = pos * 2 + 1;
	int right = pos * 2 + 2;

	int max = pos;

	if (left < lastPos && arr[left] > arr[max])
		max = left;

	if (right < lastPos && arr[right] > arr[max])
		max = right;

	if (max != pos) {
		swap(arr[pos], arr[max]);
		reheapDown(arr,max,lastPos);
	}
}

bool deleteHeap(int* arr, int& lastPos, int& data) {
	if (lastPos < 1) return false;
	data = arr[0];
	arr[0] = arr[lastPos - 1];
	arr[lastPos - 1] = -9;
	
	lastPos--;
	reheapDown(arr, 0, lastPos);
	return true;
}

void BuildHeap(int* arr, int N){
	for (int i = N /2; i >= 0; i--)
	{
		reheapDown(arr, i,N);
	}
}
//find 5th max element
int Kmax(int* arr, int N) {
	BuildHeap(arr, N);
	int data;
	for (int i = 0; i < 5; i++) {
		deleteHeap(arr, N, data);
	}
	return data;
}

//last = N-1
bool isMaxHeap(int* arr, int pos, int last) {
	if (pos > last) return true;
	int l = pos * 2 + 1;
	int r = pos * 2 + 2;
	if (l <= last && arr[pos] < arr[l]) return false;
	if (r <= last && arr[pos] < arr[r]) return false;

	return isMaxHeap(arr, l, last) && isMaxHeap(arr, r, last);
}

void print(int* arr, int N) {
	for (int i = 0; i < N; i++) {
		cout << arr[i] << " ";
	}
}

void insertKey(int* arr, int &N, int maxSize, int key)
{
	if (N == maxSize)
	{
		cout << "\nOverflow: Could not insertKey\n";
		return;
	}

	// First insert the new key at the end 
	N++;
	arr[N - 1] = key;
	reheapUp(arr, N - 1);
}

void heapSort(int* arr, int length)
{
	while (length)
	{
		int data;
		deleteHeap(arr, length, data);
		cout << data << ' ';
	}
}
int main() {
	ifstream inFile("inp.txt", ios::in);
	int i = 0;
	int length;

	inFile >> length;
	int* arr = new int[length];
	
	while (inFile >> arr[i]) {
		i++;
	}
	BuildHeap(arr, length);
	heapSort(arr, length);
	system("pause");
}