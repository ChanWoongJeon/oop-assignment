#define _CRT_SECURE_NO_WARNINGS
#include "inf_int.h"
#include <iostream>
#include <math.h>
using namespace std;
/*
Originally written by
��ǻ�Ͱ��к�
������
*/

inf_int::inf_int()
{
	this->digits = new char[2];	// �����Ҵ�

	this->digits[0] = '0';		// default �� 0 ����
	this->digits[1] = '\0';
	this->length = 1;
	this->thesign = true;
}

inf_int::inf_int(int n) {
	char buf[100];

	if (n < 0) {		// ���� ó��
		this->thesign = false;
		n = -n;
	}
	else {
		this->thesign = true;
	}

	int i = 0;
	while (n > 0) {			// ���ڸ� ���ڿ��� ��ȯ�ϴ� ����
		buf[i] = n % 10 + '0';

		n /= 10;
		i++;
	}

	if (i == 0) {	// ������ ������ 0�� ���
		new (this) inf_int();	// ������ ��ȣ��...gcc���� �����Ͽ����� �ִٰ� ��. inf_int()�� ��� ������ �ν��Ͻ��� ������. 
	}
	else {
		buf[i] = '\0';

		this->digits = new char[i + 1];
		this->length = i;
		strcpy(this->digits, buf);
	}
}

inf_int::inf_int(const char* str)
{
	if (str[0] == '-') {
		this->digits = new char[strlen(str)];//14
		this->thesign = false;
		this->length = strlen(str) - 1;//13
		for (int i = 0; i < strlen(str) - 1; i++) {
			this->digits[i] = str[strlen(str) - i - 1];
		}
		this->digits[strlen(str) - 1] = '\0';
	}
	else {
		this->digits = new char[strlen(str) + 1];
		this->thesign = true;
		this->length = strlen(str);
		for (int i = 0; i < strlen(str); i++) {
			this->digits[i] = str[strlen(str) - i - 1];
		}
		this->digits[strlen(str)] = '\0';
	}

	
	
	// to be filled 
	// ��ȣ ó�� 
	// "100"�� ���Դٸ� ���� ǥ���� �°� "001"�� ��ȯ
	// ex) "-1053" -> thesign=false, digits="3501", len=4
}



inf_int::inf_int(const inf_int& a) {
	this->digits = new char[a.length + 1];

	strcpy(this->digits, a.digits);
	this->length = a.length;
	this->thesign = a.thesign;
}

inf_int::~inf_int() {
	delete digits;		// �޸� �Ҵ� ����
}

inf_int& inf_int::operator=(const inf_int& a)
{
	if (this->digits) {
		delete this->digits;		// �̹� ���ڿ��� ���� ��� ����.
	}
	this->digits = new char[a.length + 1];

	strcpy(this->digits, a.digits);
	this->length = a.length;
	this->thesign = a.thesign;

	return *this;
}

bool operator==(const inf_int& a, const inf_int& b)
{
	// we assume 0 is always positive.
	if ((strcmp(a.digits, b.digits) == 0) && a.thesign == b.thesign)	// ��ȣ�� ����, ������ ��ġ�ؾ���.
		return true;
	return false;
}

bool operator!=(const inf_int& a, const inf_int& b)
{
	return !operator==(a, b);
}

bool operator>(const inf_int& a, const inf_int& b)
{
	// to be filled
	// ���밪 ��
	// �� �� ����� ��� ���� ���� ���� �״�� return
	// �� �� ������ ��� ���� ���� ���� �����Ͽ� return
	// ��ȣ�� �ٸ� ���, a�� ����� ��� b�� ����, a�� ������ ��� b�� ����̱⿡ a�� ��ȣ�������� ��ȯ�ϸ� ��
	bool ins = true;
	if (a.thesign == false && b.thesign == true) { // -a , +b
		ins = false;
	}
	else if (a.thesign == true && b.thesign == false) { // +a , -b
		ins = true;
	}
	else if (a.thesign == true && b.thesign == true) {//+a, +b
		if (a.length > b.length) { // same sign, length is a > b
			ins = true;
		}
		else if (a.length < b.length) { // same sign, length is a < b
			ins = false;
		}
		else {
			if (!strcmp(a.digits, b.digits)) {// a, b are same
				ins = false;
			}
			else {
				for (int i = 0; i < a.length; i++) {
					if (a.digits[a.length - i - 1] - '0' < b.digits[a.length - i - 1] - '0') {
						ins = false;
						break;
					}
				}
			}
		}
	}
	else if (a.thesign == false && b.thesign == false) {// -a, -b
		if (a.length > b.length) { // same sign, length is a > b
			ins = false;
		}
		else if (a.length < b.length) { // same sign, length is a < b
			ins = true;
		}
		else {
			if (!strcmp(a.digits, b.digits)) {// a, b are same
				ins = false;
			}
			else {
				for (int i = 0; i < a.length; i++) {
					if (a.digits[a.length - i - 1] - '0' > b.digits[a.length - i - 1] - '0') {
						ins = false;
						break;
					}
				}
			}
		}
	}
	return ins;
}
//>filled
bool operator<(const inf_int& a, const inf_int& b)
{
	if (operator>(a, b) || operator==(a, b)) {
		return false;
	}
	else {
		return true;
	}
}

inf_int operator+(const inf_int& a, const inf_int& b)
{
	
	inf_int c;
	unsigned int i;

	if (a.thesign == b.thesign) {	// ������ ��ȣ�� ���� ��� + �����ڷ� ����
		for (i = 0; i < a.length; i++) {
			c.Add(a.digits[i], i + 1);
		}
		for (i = 0; i < b.length; i++) {
			c.Add(b.digits[i], i + 1);
		}

		c.thesign = a.thesign;

		return c;
	}
	else {	// ������ ��ȣ�� �ٸ� ��� - �����ڷ� ����
		c = b;
		c.thesign = a.thesign;

		return a - c;
	}
}

inf_int operator-(const inf_int& a, const inf_int& b)
{
	inf_int initial;
	inf_int c;
	if (a.thesign == b.thesign) {
		if (a > b) {
			if (a.thesign == true) {
				c = a;
				for (int i = 0; i < b.length;i++) {
					c.Sub(b.digits[i], i + 1);
				}
				return c;
			}
			else {
				c = b;
				for (int i = 0; i < a.length;i++) {
					c.Sub(a.digits[i], i + 1);
				}
				c.thesign = true;
				return c;
			}

		}
		else if (a < b) {
			if (a.thesign == true) {
				c = b;
				for (int i = 0; i < a.length;i++) {
					c.Sub(a.digits[i], i + 1);
				}
				c.thesign = false;
				return c;
			}
			else {
				c = a;
				for (int i = 0; i < b.length;i++) {
					c.Sub(b.digits[i], i + 1);
				}
				return c;
			}
		}
		else {
			return initial;
		}
	}
	else {
		c = b;
		c.thesign = a.thesign;
		return a + c;
	}
}

inf_int operator*(const inf_int& a, const inf_int& b)
{
	inf_int c;
	for (int i = 0; i < b.length; i++) {
		for (int j = 0; j < b.digits[i] - '0'; j++) {
			for (int k = 0; k < pow(10, i); k++) {
				c = c + a;
			}
		}
	}
	if (a.thesign != a.thesign) {
		c.thesign = false;
	}
	else {
		c.thesign = true;
	}
	return c;
}


ostream& operator<<(ostream& out, const inf_int& a)
{
	int i;

	if (a.thesign == false) {
		out << '-';
	}
	for (i = a.length - 1; i >= 0; i--) {
		out << a.digits[i];
	}
	return out;
}

void inf_int::Add(const char num, const unsigned int index)	// a�� index �ڸ����� n�� ���Ѵ�. 0<=n<=9, ex) a�� 391�϶�, Add(a, 2, 2)�� ����� 411
{
	if (this->length < index) {
		this->digits = (char*)realloc(this->digits, index + 1);

		if (this->digits == NULL) {		// �Ҵ� ���� ����ó��
			cout << "Memory reallocation failed, the program will terminate." << endl;

			exit(0);
		}

		this->length = index;					// ���� ����
		this->digits[this->length] = '\0';	// �ι��� ����
	}

	if (this->digits[index - 1] < '0') {	// ���� ���� '0'���� ���� �ƽ�Ű���� ��� 0���� ä��. �������� �ʾҴ� ���ο� �ڸ����� ��� �߻�
		this->digits[index - 1] = '0';
	}

	this->digits[index - 1] += num - '0';	// �� ����


	if (this->digits[index - 1] > '9') {	// �ڸ��ø��� �߻��� ���
		this->digits[index - 1] -= 10;	// ���� �ڸ������� (�ƽ�Ű��) 10�� ����
		Add('1', index + 1);			// ���ڸ��� 1�� ���Ѵ�
	}
}

void inf_int::Sub(const char num, const unsigned int index) {
	if (this->digits[index - 1] < num) {
		Sub('1', index + 1);
		this->digits[index - 1] += 10;
		this->digits[index - 1] -= num - '0';
	}
	else {
		this->digits[index - 1] -= num - '0';
	}
}
void inf_int::numb(const unsigned int index) {
	int a = this->length;
	this->digits = (char*)realloc(this->digits, this->length+index);
	this->length = a+index;
}