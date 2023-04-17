#include <iostream>
#include <random>
#include <iomanip>

using namespace std;

void ArrOut(int* arr, int size)
{
	for (int i = 0; i < size; i++) cout << setw(12) << arr[i];
	cout << endl;
}
void RandValues(int* ARR, int size)
{
	random_device seed;
	mt19937 generator(seed());
	uniform_int_distribution<int> distribution(-100, 100);

	for (int i = 0; i < size; i++)
		ARR[i] = distribution(generator);
}
int Min(int a, int b)
{
	if (a > b)
	{
		return b;
	}
	else
	{
		return a;
	}
}
int GetMinRun(int size)
{
	int r{ 0 };
	while (size >= 64)
	{
		r |= size & 1;
		size >>= 1;
	}
	return size + r;
}
void InsertSort(int*& arr, int right, int left = 0)
{
	for (int i = left + 1; i <= right; i++)
	{
		int key = arr[i];
		int j = i - 1;
		while (j >= left && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}
void Merge(int*& arr, int left, int mid, int right)
{
	int sizeT = right - left + 1;
	int* temp{ new int[sizeT] };

	int leftIndex = { left };
	int rightIndex{ mid + 1 };
	int tempIndex{ 0 };
	while (leftIndex <= mid && rightIndex <= right)
	{
		if (arr[leftIndex] > arr[rightIndex])
		{
			temp[tempIndex] = arr[rightIndex];
			rightIndex++;
		}
		else
		{
			temp[tempIndex] = arr[leftIndex];
			leftIndex++;
		}
		tempIndex++;
	}

	while (leftIndex <= mid)
	{
		temp[tempIndex] = arr[leftIndex];
		leftIndex++;
		tempIndex++;
	}

	while (rightIndex <= right)
	{
		temp[tempIndex] = arr[rightIndex];
		rightIndex++;
		tempIndex++;
	}
	for (int i = left, j = 0; i <= right; i++, j++)
	{
		arr[i] = temp[j];
	}
	delete[] temp;
}
void TimSort(int*& arr, int size)
{
	int minRunSize{ GetMinRun(size) };
	for (int i = 0; i < size; i += minRunSize)
	{
		InsertSort(arr, min((i + minRunSize - 1), (size - 1)), i);
	}

	for (int runSize = minRunSize; runSize < size; runSize = 2 * runSize)
	{
		for (int left = 0; left < size; left += 2 * runSize)
		{
			int mid{ left + runSize - 1 };
			int right{ Min((left + 2 * runSize - 1),(size - 1)) };
			Merge(arr, left, mid, right);
		}
	}
}

int main()
{
	bool enter(false);
	while (!enter)
	{
		int task;
		cout << "Выберете задание\n";  cin >> task;

		switch (task)
		{

			//Tim
		case 1:
		{
			int size;
			cout << "Сколько элементов в массиве?"; cin >> size;
			int* arr{ new int[size] };
			RandValues(arr, size);
			ArrOut(arr, size);
			TimSort(arr, size);
			cout << endl << endl;
			ArrOut(arr, size);
		}
		break;


		//Paste
		case 2:
		{
			int size;
			cout << "Сколько элементов в массиве?"; cin >> size;
			int* arr{ new int[size] };
			RandValues(arr, size);
			ArrOut(arr, size);
			InsertSort(arr, size);
			cout << endl << endl;
			ArrOut(arr, size);
		}
		break;

		default:
		{

		}
		break;
		}
		cout << "Что бы продолжить нажмите 0\n";
		cin >> enter;
	}
	return 0;
}
