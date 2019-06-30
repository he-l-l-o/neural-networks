#include "pch.h"
#include <iostream>
#include <cmath>
#include <string>
#include <random>
#include <ctime>
#include "neuro.h"
using namespace std;

int main()
{
	string str;
	setlocale(0, "");
	cout << "¬ведите путь к базе данных: ";
	cin >> str;
	char* path = new char[str.size() + 1];
	strcpy_s(path, str.size() + 1, str.c_str());
	neural_learning(path);
}