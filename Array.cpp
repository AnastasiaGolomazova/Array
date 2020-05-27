#include "Array.h"
#include <iostream>

using namespace std;

Array::Array(int N, int minrange, int maxrange, int order)//Конструктор который принимает размер, диапазон случ зн. и направление сортировки
{
	if (N < 1) { // проверка на размер массива
		throw 1;
	}

	array = new int[N]; // создаем N элементов 

	for (int i = 0; i < N; i++)
		array[i] = (double)rand() / RAND_MAX * (maxrange - minrange) + minrange; // заполняем массив случ.зн.
	if (order) // если сортировка true
		Sort(order); // сортируем
	size = N; // присваиваем размер N
}

Array::Array(int* _array, int SIZE)//конструктор который принимает другой массив
{
	if (!_array) { //проверка на исключение пустого указателя
		throw 2;
	}
	if (SIZE < 1) { //проверка на размер массива
		throw 1;
	}

	array = new int[SIZE]; //создаем SIZE элементов 

	for (int i = 0; i < SIZE; i++) //переприсваиваем элементы массива, увеличивая индекс на 1
	{
		array[i] = _array[i++];//копируем значения в наш массив
	}

	size = SIZE; // присваиваем размер SIZE
}

Array::Array(const Array& arr)//конструктор копирования одного экземпляра нашего класса в другой
{
	array = new int[arr.size]; //
	size = arr.size;

	for (int i = 0; i < size; array[i] = arr.array[i++]); // копируем значения в наш массив
}

Array::~Array()//деструктор
{
	delete[] array;
}

void Array::addKey(int i, int val)//вставляет в массив элемент в определенное место
{
	int* buf = new int[size + 1]; // создаем массив с типом int*, увеличивая размер массива на 1
	if (buf)
	{
		for (int j = 0; j < i; buf[j] = array[j++]); // копируем все, что левее нашего индекса
		buf[i] = val; // проходимся по всему массиву (паралельно присваивая элементы array массиву buf) и ищем i индекс, присваивая i-ому элементу значение val
		for (int j = i + 1; i < size; buf[j++] = array[i++]); // копируем все, что правее нашего индекса

		delete[] array;// освобождаю память
		array = buf; // переприсваиваю массив
		size++; // увеличиваю размер
	}
	else
		throw 4;
}

void Array::Update(int minrange = 0, int maxrange = 0, int oder = 0)//переприсваивает массиву новые случайные значения
{
	for (int i = 0; i < size; array[i++] = (double)rand() / RAND_MAX * (maxrange - minrange) + minrange); // перезаполняем значения
	if (oder) // сортируем по убыванию 
		Sort(oder);
}

void Array::Sort(int oder = 1) // >0 возрастание <0 убывание  сортировка (сортировка пузырьком) 
{
	if (oder > 0) {
		for (int i = size - 1; i >= 0; i--) {
			for (int j = 0; j < i; j++) {
				if (array[j] > array[j + 1]) {
					int temp = array[j];
					array[j] = array[j + 1];
					array[j + 1] = temp;
				}
			}
		}
	}
	else {
		for (int i = size - 1; i >= 0; i--) {
			for (int j = 0; j < i; j++) {
				if (array[j] < array[j + 1]) {
					int temp = array[j];
					array[j] = array[j + 1];
					array[j + 1] = temp;
				}
			}
		}
	}


}

int Array::findKey(int val)//найти значение в массиве, дать индекс этого элемента
{
	for (int i = 0; i < size; i++)
		if (val == array[i])
			return i;
	return 4;
}

int& Array::operator[] (int i)//получить элемент массива по индексу
{
	if (i > -1 && i < size)
		return array[i];
	throw 3;
}

bool Array::operator== (const Array& obj)//равны ли два массива
{
	if (size == obj.size)
	{
		for (int i = 0; i < size; i++) {
			if (array[i] != obj.array[i]) {

				return false;
			}
			return true;
		}
	}
	return false;
}

bool Array::operator!= (const Array& obj)//не равны ли два массива
{
	return !(*this == obj); // разименовываем указатель на текущий ID и сравниваем с объектом
}

Array& Array::operator= (const Array& obj)//оператор присваивания
{
	if (this != &obj)
	{
		delete[] array;
		array = new int[obj.size];
		if (!array) {
			throw 4;
		}
		else {
			size = obj.size;
			for (int i = 0; i < size; i++) {
				array[i] = obj.array[i];
			};
		}
	}

	return *this; // возвращает объект, который сгенерировал вызов
}

Array Array::operator+ (Array& obj)//сложить два массива
{
	Array x(size + obj.size);

	for (int i = 0; i < size; x[i] = array[i], i++);
	for (int i = 0, k = size; i < obj.size; x[k] = obj[i], i++, k++);

	return x;
}

Array Array::operator- (int val)//отнять от массива число
{
	int i = findKey(val);
	if (i > -1)
	{
		Array rez(size - 1);

		for (int j = 0; j < i; rez[j] = array[j], j++);
		for (int k = i + 1; i < size; rez[i] = array[k], k++, i++);

		return rez;
	}

	return *this; // возвращает объект, который сгенерировал вызов
}

Array& Array::operator-=(int val)//отнять у массива число и присвоить
{
	int i = findKey(val);
	if (i > -1)
	{
		int* buf = new int[size - 1];
		for (int j = 0; j < i; buf[j] = array[j], j++);
		for (int k = i + 1; i < size; buf[i] = array[k], k++, i++);
		delete[] array;
		array = buf;
		size--;
	}

	return *this; // возвращает объект, который сгенерировал вызов
}

Array Array::operator+ (int val)//прибавить к массиву число
{
	Array rez(size + 1);
	for (int i = 0; i < size; rez[i] = array[i], i++);
	rez[size] = val;

	return rez;
}

Array& Array::operator+=(int val)//прибавить и присвоить
{
	int* buf = new int[size + 1];
	if (buf)
	{
		for (int i = 0; i < size; buf[i] = array[i], i++);
		buf[size] = val;

		delete[] array;
		array = buf;
		size++;

		return *this; // возвращает объект, который сгенерировал вызов
	}
	throw 5;
}

istream& operator>> (istream& in, Array& obj)
{
	if (obj.array) // если массив уже определен, то удаляем
		delete[] obj.array;

	int n;
	in >> n; // считываем размер
	obj.size = n;
	obj.array = new int[n]; // присваиваем размер

	for (int i = 0; i < n; in >> obj[i], i++); // читаем из потока

	return in;
}

ostream& operator<< (ostream& out, Array& obj)
{
	for (int i = 0; i < obj.size; out << obj[i] << " ", i++); // выводим массив

	return out;
}
