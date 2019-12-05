#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

void insertionSort(int arr[], int start, int end) {
	if (end <= 0) return;

	insertionSort(arr, start, end - 1);

	while (end > start && arr[end] < arr[end - 1])
	{
		swap(arr[end], arr[end - 1]);
		end--;
	}
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
	insertionSort(arr, 0, size - 1);
	printArr(arr, size);
	cin.get();
	return 0;
}