#include <iostream>
#include <random>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>


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
	uniform_int_distribution<int> distribution(-50000, 49999);

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
void InsertSort(int*& arr, int& countComp, int countSwap  ,int right, int left = 0)
{
	countComp = 0;
	countSwap = 0;
	for (int i = left + 1; i < right; i++)
	{
		int key = arr[i];
		int j = i - 1;
		while (j >= left && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j--;
			countComp++;
			countSwap++;
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
//void TimSort(int*& arr, int size)
//{
//	int minRunSize{ GetMinRun(size) };
//	for (int i = 0; i < size; i += minRunSize)
//	{
//		InsertSort(arr, min((i + minRunSize - 1), (size - 1)), i);
//	}
//
//	for (int runSize = minRunSize; runSize < size; runSize = 2 * runSize)
//	{
//		for (int left = 0; left < size; left += 2 * runSize)
//		{
//			int mid{ left + runSize - 1 };
//			int right{ Min((left + 2 * runSize - 1),(size - 1)) };
//			Merge(arr, left, mid, right);
//		}
//	}
//}

bool Write2Bin(int* arr, int size, string name)
{
    ofstream file(name, ios::out | ios::binary);
    if (file.is_open())
    {
        file.write((const char*) arr, size * sizeof(int));
        file.close();
		return true;
    }
    else
    {
		return false;
    }
}
bool ReadBin(int* arr, int size, string name)
{
	ifstream file(name, ios::in | ios::binary);
	if (file)
	{
		file.read((char*) arr, size * sizeof(int));
		file.close();
		return true;
	}
	else
	{
		return false;
	}
}

void InputFileARR(int* ARR, int size) {

	string line;
	int i{ 0 };
	ifstream file("input.txt");
	if (!file) cerr << "Не удалось открыть файл\n\n";

	while (getline(file, line, ';') && i < size) {
		if (i >= size)
			break;

		istringstream iss(line);
		int num;
		if (iss >> num) {
			num = stoi(line);
			ARR[i] = num;
			i++;
		}
	}
	file.close();
}

void ArrOutFile(int*& arr, int size)
{
	ofstream out_file("ching-chong.txt");
	if (out_file.is_open())
	{
		for (int i = 0; i < size; i++)
			out_file << setw(10) << arr[i];
		out_file.close();
		cout << "Массив записан в ching-chong.txt" << endl;
	}
	else cerr << "Неудалось открыть файл!!!";
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
			cout << "Сколько элементов в массиве?\n"; cin >> size;
			int* arr{ new int[size] };
			RandValues(arr, size);
			ArrOut(arr, size);
			//TimSort(arr, size);
			cout << endl << endl;
			ArrOut(arr, size);
		}
		break;
		
		//Paste
		case 2:
		{
			int size;
			int countComps{ 0 };
			cout << "Сколько элементов в массиве?\n"; cin >> size;
			int* arr{ new int[size] };
			RandValues(arr, size);
			ArrOut(arr, size);
//			InsertSort(arr, size);
			cout << endl << endl;
			ArrOut(arr, size);
		}
		break;

		case 3:
		{
			int size;
			string name;
			int countComps{ 0 };
			cout << "Сколько элементов в массиве?\n"; cin >> size;
			int* arr{ new int[size] };
			RandValues(arr, size);
			cout << "Название: "; cin >> name;
			if (Write2Bin(arr, size, name))
			{
				cout << "Всё норм";
			}
			else
			{
				cout << "Ошибка!!!";
			}
			;
		}
		break;


		case 4:
		{
			string name;
			int size;
			cout << "Сколько элементов в массиве?\n"; cin >> size;
			int* arr{ new int[size] };
			cout << "Название: "; cin >> name;
			if(ReadBin(arr, size, name))
			{
				cout << "Всё норм";
			}
			else
			{
			cout << "Ошибка!!!";
			}
			ArrOutFile(arr, size);
			
		}
		break;
		default:
		{
			system("cls");
			cout << "Нет такокго!!!";
			system("pause");
			system("cls");
		}	
		break;
		}
		cout << "\nЧто бы продолжить нажмите 0\n";
		cin >> enter;
	}
	return 0;
}
