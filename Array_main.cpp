#include <iostream>
#include "Array.h"

using namespace std;

int main()
{
	try
	{
		Array a(366, 22, 210, ascending);
		Array b(3, 1, 1, descending);
		Array c(20);
		Array d(20);

		cout << "obj a = "<< a << endl;
		cout << "obj b = " << b << endl;
		cout << "obj c = " << c << endl;
		cout << "obj d = " << c << endl;

		// проверка на оператор сравнения  !=
		if (c != d) {
			cout << "c != d " << endl;
		}
		else {
			cout << "c == d " << endl;
		}

		a += 5;
		cout << "obj a (+=) " << a << endl;
		c -= 100;
		cout << "obj c (-=) " << c << endl;

		// проверка на оператор сравнения  ==
		if (a == b) {
			cout << "a == b " << endl;
		}
		else {
			cout << "a != b " << endl;
		}

		// переприсваиваем объекты
		b = a;
		cout << "new obj b = " << b << endl;
		c = a + 4;
		cout << "new obj c = " << c << endl;

		//создаем новый объект
		Array f;
		f = a + b;
		cout << "obj f =" << f << endl;
		f = a - 3;
		cout << "obj f =" << f << endl;
		f = a + 3;
		cout << "obj f =" << f << endl;
		//переприсваиваем элементы
		c[0] = a[0] + b[0];
		cout << "obj c[0] = a[0] + b[0] = " << c << endl;
	}
	catch (int i) // ловушка для исключений
	{
		switch (i)
		{
		case 1:
			cout << "wrong size";
			break;
		case 2:
			cout << "empty pointer";
			break;
		case 3:
			cout << "wrong index";
			break;
		case 4:
			cout << "error";
			break;
		}
	}
	system("pause");
	return 0;
}
