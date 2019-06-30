#include "neuro.h"
#include "pch.h"
#include <iostream>
#include <cmath>
//#include <string>
#include <random>
#include <ctime>
using namespace std;
struct neuron
{
	double out, error;
};

//функция вычисления значений следующего слоя сети
void forward(neuron* prev, int prev_size, neuron* next, int next_size, double** weight)
{
	double temp;
	for (int i = 0; i < next_size - 1; i++)
	{
		temp = 0;
		for (int j = 0; j < prev_size; j++)
		{
			temp += prev[j].out * weight[j][i];
		}
		if (temp > 1) {
			temp = 1 + 0.1 * (temp - 1);
		}
		if (temp < 0) {
			temp = 0.1 * temp;
		}
		next[i].out = temp;
	}
}

//функция вычисления ошибки
//ошибка выходного слоя считается отдельно
void backward(neuron* next, int next_size, neuron* prev, int prev_size, double** weight)
{
	for (int i = 0; i < prev_size - 1; i++)
	{
		prev[i].error = 0;
		for (int j = 0; j < next_size - 1; j++)
		{
			prev[i].error += next[j].error * weight[i][j];
		}
		if (prev[i].out > 1 || prev[i].out < 1) {
			prev[i].error *= 0.1;
		}
	}
}

//обработка фрагмента изображения
int neural_processing(short arr[4][4][3], int k)
{
	//Инициализация слоев нейронной сети

	long long int size0 = 17, size1 = 17, size2 = 6; //размеры массивов нейронов
	neuron* neuro0 = new neuron[size0];	//Нейроны входного слоя. 4 * 4 под пиксели + нейрон смещения
	if (neuro0 == NULL) {
		return -1;
	}
	for (int i = 0; i < size0; i++)
	{ //ошибка входных нейронов равна 0
		neuro0[i].error = 0;
		neuro0[i].out = 0;
	}
	neuro0[size0 - 1].out = 1;
	neuron* neuro1 = new neuron[size1]; //Нейроны первого слоя (скрытый)
	if (neuro1 == NULL) {
		return -1;
	}
	neuro1[size1 - 1].out = 1;
	neuro1[size1 - 1].error = 0;
	neuron* neuro2 = new neuron[size2]; //Нейроны выходного слоя
	if (neuro2 == NULL) {
		return -1;
	}
	neuro2[size2 - 1].out = 1;
	neuro2[size2 - 1].error = 0;

	//Инициализация матриц связи между слоями

	double** weight01 = new double* [size0]; //Веса связей между нулевым и первым слоями
	if (weight01 == NULL) {
		return -1;
	}
	for (int i = 0; i < size0; i++)
	{
		weight01[i] = new double[size1 - 1]; //Количество столбцов на 1 меньше размера след. массива из-за нейрона смещения
		if (weight01[i] == NULL) {
			return -1;
		}
	}
	double** weight12 = new double* [size1]; //Веса связей между первым и вторым слоями
	if (weight12 == NULL) {
		return -1;
	}
	for (int i = 0; i < size1; i++)
	{
		weight12[i] = new double[size2 - 1];
		if (weight12[i] == NULL) {
			return -1;
		}
	}

	FILE* weights;
	if (fopen_s(&weights, "..\\weights.data", "rb") != 0) {
		return -2;
	}
	for (int i = 0; i < size0; i++)
	{
		if (fread(weight01[i], sizeof(double), size1 - 1, weights) == 0) {
			return -3;
		}
	}
	for (int i = 0; i < size1; i++)
	{
		if (fread(weight12[i], sizeof(double), size2 - 1, weights) == 0) {
			return -3;
		}
	}

	srand(time(0));

	int l = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			neuro0[l].out = arr[i][j][k] / 255; //заполнение входного слоя
			l++;
		}
	}
	forward(neuro0, size0, neuro1, size1, weight01); //вычисление выходных значений нейронов
	forward(neuro1, size1, neuro2, size2, weight12);

	int ans = 0;
	for (int i = 0; i < size2 - 1; i++) {
		if (neuro2[i].out > neuro2[ans].out) {
			ans = i;
		}
	}
	fclose(weights);
	delete[] neuro0;
	neuro0 = NULL;
	delete[] neuro1;
	neuro1 = NULL;
	delete[] neuro2;
	neuro2 = NULL;
	for (int i = 0; i < size0; i++) {
		delete[] weight01[i];
		weight01[i] = NULL;
	}
	delete[] weight01;
	weight01 = NULL;
	for (int i = 0; i < size0; i++) {
		delete[] weight12[i];
		weight12[i] = NULL;
	}
	delete[] weight12;
	weight12 = NULL;
	return ans;
}

