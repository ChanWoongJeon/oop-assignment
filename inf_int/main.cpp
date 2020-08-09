#include "inf_int.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>

using namespace std;

int main()
{
	inf_int a, e;
	inf_int b(1000);
	inf_int c("321111111111122222222222233333333333444444444445555555555");
	inf_int d("123451987651234572749499923455022211");
	//inf_int c("123345");
	//inf_int d("3333");
	inf_int f = d;
	inf_int g(f);


	a = c * b;

	b = c - d;


	if (f == d) {
		cout << "a : " << a << endl;
		cout << "b : " << b << endl;
		cout << "c : " << c << endl;
		cout << "d : " << d << endl;
		cout << "f : " << f << endl;
		cout << "a<b : " << (a < b) << endl;
		cout << "a>b : " << (a > b) << endl;
	}
	system("pause");
	return 0;
}
