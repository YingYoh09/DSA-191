#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

void bubbleSort(int arr[], int length)
{
	for (int i = 0; i < length; i++)
	{
		bool flag = true;
		for (int j = 0; j < length - i - 1; j++)
		{
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
				flag = false;
			}
		}
		if (flag) break;
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
	bubbleSort(arr, size);
	printArr(arr, size);
	cin.get();
	return 0;
}