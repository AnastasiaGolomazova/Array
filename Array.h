#include <iostream>
using namespace std;


enum ORDER { descending = -1, ascending = 1 }; //перечисление для направления сортировки

class Array
{
private:
	int* array;
	int size;
public:


	Array(int N = 256, int minrange = 0, int maxrange = 0, int oder = 0);

	Array(int* _array, int SIZE);

	Array(const Array& arr);

	~Array();

	void addKey(int i, int val);
	void Update(int minRange, int maxRange, int oder);
	void Sort(int oder);
	int findKey(int val);
	int& operator[] (int i);
	bool operator== (const Array& obj);
	bool operator!= (const Array& obj);

	Array& operator= (const Array& obj);

	Array operator+ (Array& obj);
	Array operator- (int val);
	Array operator+(int val);

	Array& operator-=(int val);
	Array& operator+=(int val);

	friend istream& operator >> (istream& in, Array& obj);
	friend ostream& operator << (ostream& out, Array& obj);
};
