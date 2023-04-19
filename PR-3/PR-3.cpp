#include <iostream>
#include <random>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct table
{
	stringstream zero;
	stringstream exchanges;
	stringstream comparisons;
	stringstream clock;
	table() : zero(";"), exchanges(""), comparisons(""), clock("") {}
};

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
void InsertSort(int*& arr, long long& countComp, long long& countEx  ,int right, int left = 0)
{
	countComp = 0;
	countEx = 0;
	for (int i = left + 1; i < right; i++)
	{
		int key = arr[i];
		int j = i - 1;
		while (j >= left && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j--;
			countComp++;
			countEx++;
		}
		arr[j + 1] = key;
	}
}
void Merge(int*& arr, long long& countComp, long long& countEx, int left, int mid, int right)
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
		countComp++;
		countEx++;
	}

	while (leftIndex <= mid)
	{
		temp[tempIndex] = arr[leftIndex];
		leftIndex++;
		tempIndex++;
		countEx++;
	}

	while (rightIndex <= right)
	{
		temp[tempIndex] = arr[rightIndex];
		rightIndex++;
		tempIndex++;
		countEx++;
	}
	for (int i = left, j = 0; i <= right; i++, j++)
	{
		arr[i] = temp[j];
	}

	delete[] temp;
}
void TimSort(int*& arr, int size, int& countComp, int& countEx)
{
	int minRunSize{ GetMinRun(size) };
	for (int i = 0; i < size; i += minRunSize)
	{
		long long tCC{ 0 };
		long long tCE{ 0 };
		InsertSort(arr, tCC, tCE, Min((i + minRunSize - 1), (size - 1)), i);
		countComp += tCC;
		countEx += tCE;
	}

	for (int runSize = minRunSize; runSize < size; runSize = 2 * runSize)
	{
		for (int left = 0; left < size; left += 2 * runSize)
		{
			long long tCC{ 0 };
			long long tCE{ 0 };
			int mid{ left + runSize - 1 };
			int right{ Min((left + 2 * runSize - 1),(size - 1)) };
			if (mid > size)
			{
				mid = left + (right - left - 1) / 2;
			}
			Merge(arr, tCC, tCE, left, mid, right);
			countComp += tCC;
			countEx += tCE;
		}
	}
}

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
void ArrOutFile(int*& arr, int size, string name)
{
	ofstream out_file(name);
	if (out_file.is_open())
	{
		for (int i = 0; i < size; i++)
			out_file << arr[i] << ';';
		out_file.close();
		cout << "Массив записан в " << name << endl;
	}
	else cerr << "Неудалось открыть файл!!!";
}

void fillStructInsert(int size, string binFileName, table& table)
{
	long long countComp{ 0 }, countEx{ 0 };
	int* arr{ new int[size] };
	
	ReadBin(arr, size, binFileName);
	
	auto startTime{ steady_clock::now() };
	InsertSort(arr, countComp, countEx, size);
	auto endTime{ steady_clock::now() };
	
	auto time{ duration_cast<microseconds>(endTime - startTime) };
	int elapsedTime = static_cast<int>(time.count());
	
	table.zero << size << ";";
	table.comparisons << countComp << ";";
	table.exchanges << countEx << ";";
	table.clock << elapsedTime << ";";

	//delete[] arr;
}
void fillStructTim(int size, string binFileName, table& table)
{
	int countComp{ 0 }, countEx{ 0 };
	int* arr{ new int[size] };
	
	ReadBin(arr, size, binFileName);
	
	auto startTime{ steady_clock::now() };
	TimSort(arr, size,countComp, countEx);
	auto endTime{ steady_clock::now() };
	
	auto time{ duration_cast<microseconds>(endTime - startTime) };
	int elapsedTime = static_cast<int>(time.count());
	
	table.zero << size << ";";
	table.comparisons << countComp << ";";
	table.exchanges << countEx << ";";
	table.clock << elapsedTime << ";";
	
	delete[] arr;
}

void fillFile(string filename, table& table)
{
	ofstream file("./results/"+filename);
	file << table.zero.str() << "\n";
	file << table.comparisons.str() << "\n";
	file << table.exchanges.str() << "\n";
	file << table.clock.str() << "\n";
	file.close();
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
			int x{ 0 }, y{ 0 };
			cout << "Сколько элементов в массиве?\n"; cin >> size;
			int* arr{ new int[size] };
			RandValues(arr, size);
			ArrOut(arr, size);
			TimSort(arr, size, x, y);
			cout << endl << endl;
			ArrOut(arr, size);
		}
		break;
		
		//Paste
		case 2:
		{
			long long x{ 0 }, y{ 0 };
			int size;
			int countComps{ 0 };
			cout << "Сколько элементов в массиве?\n"; cin >> size;
			int* arr{ new int[size] };
			RandValues(arr, size);
			ArrOut(arr, size);
			InsertSort(arr, x, y, size);
			cout << endl << endl;
			ArrOut(arr, size);
		}
		break;

		//подготовка исходных данных и занесение их в бинарный файл.
		case 3:
		{
			int size;
			string name;
			int countComps{ 0 };
			cout << "Сколько элементов в массиве?\n"; cin >> size;
			int* arr{ new int[size] };
			int j{ 49999 };
			for (int i = 0; i < 100000; i++,j--)
			{
				arr[i] = j;
			}
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

		//вывод в тескстовый для проверки
		case 4:
		{
			int size;
			cout << "Сколько элементов в массиве?\n"; cin >> size;
			int* arr{ new int[size] };
			ReadBin(arr, size, "averageCase.bin");
			ArrOutFile(arr, size, "averageCase.txt");
			ReadBin(arr, size, "bestCase.bin");
			ArrOutFile(arr, size, "bestCase.txt");
			ReadBin(arr, size, "worstCase.bin");
			ArrOutFile(arr, size, "worstCase.txt");
		}
		break;

		//составление файлов
		case 5:
		{
			table insertSort_best;
			table insertSort_worst;
			table insertSort_average;
			table timSort_best;
			table timSort_worst;
			table timSort_average;

			for (int size = 1000; size <= 100000; size += 500)
			{
			
				fillStructInsert(size, "bestCase.bin", insertSort_best);
				fillStructInsert(size, "worstCase.bin", insertSort_worst);
				fillStructInsert(size, "averageCase.bin", insertSort_average);
				fillStructTim(size, "bestCase.bin", timSort_best);
				fillStructTim(size, "worstCase.bin", timSort_worst);
				fillStructTim(size, "averageCase.bin", timSort_average);
			}
			
			fillFile("insertSort(best).txt", insertSort_best);
			fillFile("insertSort(worst).txt", insertSort_worst);
			fillFile("insertSort(average).txt", insertSort_average);
			fillFile("TimSort(best).txt", timSort_best);
			fillFile("TimSort(worst).txt", timSort_worst);
			fillFile("TimSort(average).txt", timSort_average);
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
