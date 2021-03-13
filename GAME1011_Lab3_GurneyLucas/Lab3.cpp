#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

template <class T>
class SimpleVector
{
private:
	T* aptr;
	int arraySize;
	void subError() const;
public:
	SimpleVector(int);
	SimpleVector(const SimpleVector&);
	~SimpleVector();
	int size() const
	{
		return arraySize;
	}
	T& operator[](int);
	void print() const;
};

template <class T>
SimpleVector<T>::SimpleVector(int s)
{
	arraySize = s;
	aptr = new T[s];
	for (int i = 0; i < arraySize; i++)
	{
		aptr[i] = T();
	}
}

template <class T>
SimpleVector<T>::SimpleVector(const SimpleVector& obj)
{
	arraySize = obj.arraySize;
	aptr = new T[arraySize];
	for (int i = 0; i < arraySize; i++)
	{
		aptr[i] = obj.aptr[i];
	}
}

template <class T>
SimpleVector<T>::~SimpleVector()
{
	if (arraySize > 0)
	{
		delete[] aptr;
	}
}

template <class T>
void SimpleVector<T>::subError() const
{
	cout << "ERROR: Subscript out of range.\n";
	exit(0);
}

template <class T>
T& SimpleVector<T>::operator[](int sub)
{
	if (sub < 0 || sub >= arraySize)
	{
		subError();
	}
	return aptr[sub];
}

template <class T>
void SimpleVector<T>::print() const
{
	for (int i = 0; i < arraySize; i++)
	{
		cout << aptr[i] << " ";
	}
	cout << endl;
}

// This is where the number is found in the array
template <class T>
class SearchableVector : public SimpleVector <T>
{
public:
	SearchableVector(int s) :SimpleVector<T>(s) {}
	SearchableVector(SearchableVector& obj) : SimpleVector<T>(obj) {}
	SearchableVector(SimpleVector<T>& obj) : SimpleVector<T>(obj) {}
	int find(T);
};

template <class T>
int SearchableVector<T>::find(T item)
{
	int maxSize = this->size();
	int lowestSize = 0;
	int middle;

	while (lowestSize <= maxSize)
	{
		middle = lowestSize + (maxSize - 1) / 2;

		if (this->operator[](middle) == item)
		{
			return middle;
		}

		if (this->operator[](middle) < item)
		{
			lowestSize = middle + 1;
		}
		else
		{
			maxSize = middle - 1;
		}	
	}
	return -1;
}

int main()
{
	unsigned seed = time(0);
	srand(seed);
	const int SIZE = 10;
	SearchableVector<int> iTable(SIZE);
	SearchableVector<double> dTable(SIZE);

	for (int i = 0; i < SIZE; i++)
	{
		iTable[i] = (i + 1);
		dTable[i] = (i + 1.0 + (rand() % 99 * 0.01));
	}
	cout << "The values in iTable are:\n";
	iTable.print();
	cout << "The values in dTable are:\n";
	dTable.print();

	int result;
	cout << "Searching for the number 4 in iTable.\n";
	result = iTable.find(4);
	if (result == -1)
	{
		cout << "4 was not found.\n";
	}
	else
	{
		cout << "4 was found at subscript " << result << endl;
	}
	return 0;
}