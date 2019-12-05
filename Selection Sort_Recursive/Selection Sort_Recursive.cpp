#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

void swap(int arr[], int num1, int num2) {
	int temp = arr[num1];
	arr[num1] = arr[num2];
	arr[num2] = temp;
}

void selectionSort(int arr[], int start, int end) {
	if (start == end) return;
	int min = start;
	for (int i = start; i <= end; i++) {
		if (arr[min] > arr[i]) min = i;
	}
	swap(arr, start, min);
	
	selectionSort(arr, start + 1, end);
}

void printArr(int arr[], int size) {
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

int main(int argc, char** argv) {
	ifstream inFile("inp.txt", ios::in);
	string input;

	vector<string> num;
	int count = 0;
	while (getline(inFile, input, ',')) {
		num.push_back(input);
	}

	int size = num.size();
	int* arr = new int[size];
	for (auto i = num.begin(); i != num.end(); i++) {
		arr[count] = stoi(*i);
		count++;
	}
	selectionSort(arr, 0, size - 1);
	printArr(arr, size);

	return 0;
}