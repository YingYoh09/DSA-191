#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

void shellSort(int arr[], int n)
{
	// Start with a big gap, then reduce the gap 
	for (int gap = n / 2; gap > 0; gap /= 2)
	{
		// Do a gapped insertion sort for this gap size. 
		// The first gap elements a[0..gap-1] are already in gapped order 
		// keep adding one more element until the entire array is 
		// gap sorted  
		for (int i = gap; i < n; i += 1)
		{
			// add a[i] to the elements that have been gap sorted 
			// save a[i] in temp and make a hole at position i 
			int temp = arr[i];

			// shift earlier gap-sorted elements up until the correct  
			// location for a[i] is found 
			int j;
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
				arr[j] = arr[j - gap];

			//  put temp (the original a[i]) in its correct location 
			arr[j] = temp;
		}
	}

}

int shell_sort_recursive(int* arr, int length)
{
	if (length <= 1)    return length;
	length = shell_sort_recursive(arr, length - 1);
	int value = arr[length];
	int i = length - 1;
	while ((i >= 0) && (arr[i] > value)) {
		arr[i + 1] = arr[i];
		i--;
	}
	arr[i + 1] = value;
	return length + 1;
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
	shell_sort_recursive(arr, size);
	printArr(arr, size);
	cin.get();
	return 0;
}