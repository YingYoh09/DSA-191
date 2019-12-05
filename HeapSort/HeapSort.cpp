#include <iostream>
#include <fstream>
using namespace std;

void HeapDown(int* arr, int N, int i) {
	while (i < N) {
		int left = i * 2 + 1;
		if (left >= N) return;
		if (left + 1 < N)
			if (arr[left] < arr[left + 1]) left++;
		if (arr[i] >= arr[left])
			return;
		swap(arr[i], arr[left]);
		i = left;
	}

}

void BuildHeap(int* arr, int N) {
	for (int i = N / 2; i > -1; i--)
		HeapDown(arr, N, i);
}


void HeapSort(int* arr, int N) {
	BuildHeap(arr, N);
	int last = N - 1;
	for (int i = 0; i < N; i++)
	{
		swap(arr[last], arr[0]);
		HeapDown(arr, last, 0);
		--last;
	}
}

void print(int* arr, int N) {
	for (int i = 0; i < N; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

int main(int argc, char* argv[]) {
	int arr[] = { 19, 4, 5, 6, 3, 2, 4, 1, 2, 5, 6, 7, 3 };

	int i = 0;
	int N = sizeof(arr) / sizeof(arr[0]);

	HeapSort(arr, N);
	print(arr, N);
	cin.get();
	return 0;
}