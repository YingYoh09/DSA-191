#include <iostream>

using namespace std;

void merge(int* arr, int left, int mid, int right)
{
	int* temp = new int[right - left + 1];
	int i = left, j = mid + 1, counter = 0;
	while (i <= mid && j <= right)
	{
		if (arr[i] <= arr[j])
		{
			temp[counter++] = arr[i++];
		}
		else temp[counter++] = arr[j++];
	}
	for (; i <= mid; i++)
		temp[counter++] = arr[i];

	for (; j <= right; j++)
		temp[counter++] = arr[j];

	for (i = 0; i < counter;i++)
	{
		arr[left + i] = temp[i];
	}
	
}

void MergeSort(int* arr, int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;

		MergeSort(arr, left, mid);
		MergeSort(arr, mid + 1, right);
		merge(arr, left, mid, right);
	}
}

int main()
{
	int arr[] = { 19, 4, 5, 6, 3, 2, 4, 1, 2, 5, 6, 7, 3 };

	MergeSort(arr, 0, sizeof(arr) / sizeof(arr[0]) - 1);
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << " ";
	}
	cin.get();
	return 0;
}