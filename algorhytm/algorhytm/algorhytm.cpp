#include "pch.h"
#include <iostream>
#include <cmath>
//#include <string>
#include <random>
#include <ctime>
#include "neuro.h"
using namespace std;


int main()
{
	char path[100];
	setlocale(0, "");
	cout << "������� ���� � ���� ������: ";
	cin >> path;
	neural_learning(path);
}