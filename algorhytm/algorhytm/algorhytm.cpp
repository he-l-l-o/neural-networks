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
void forward(neuron *prev, int prev_size, neuron *next, int next_size, double **weight)
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
void backward(neuron *next, int next_size, neuron *prev, int prev_size, double **weight)
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

//функция обновления весов
void weights_update(neuron *next, int next_size, neuron *prev, int prev_size, double **weight, double learning_coefficient)
{
	for (int i = 0; i < next_size - 1; i++)
	{
		for (int j = 0; j < prev_size; j++)
		{
			weight[j][i] += learning_coefficient * next[i].error * prev[j].out;
		}
	}
}

//структура для чтения базы данных
struct entry
{
	short img[4][4][3];
	int line_type;
};


//очистка массива
void clean(double *arr, int size) {
	for (int i = 0; i < size; i++) {
		arr[i] = 0;
	}
}


int neural_learning(char *path)
{
	entry zap; //запись в базе данных
	zap.line_type = 0;

	//Инициализация слоев нейронной сети

	long int size0 = 17, size1 = 17, size2 = 6; //размеры массивов нейронов
	neuron *neuro0 = new neuron[size0];	//Нейроны входного слоя. 4 * 4 под пиксели + нейрон смещения
	if(neuro0 == NULL){
		return 1;
	}
	for (int i = 0; i < size0; i++)
	{ //ошибка входных нейронов равна 0
		neuro0[i].error = 0;
		neuro0[i].out = 0;
	}
	neuro0[size0 - 1].out = 1;
	neuron *neuro1 = new neuron[size1]; //Нейроны первого слоя (скрытый)
	if (neuro1 == NULL) {
		return 1;
	}
	neuro1[size1 - 1].out = 1;
	neuro1[size1 - 1].error = 0;
	neuron *neuro2 = new neuron[size2]; //Нейроны выходного слоя
	if (neuro2 == NULL) {
		return 1;
	}
	neuro2[size2 - 1].out = 1;
	neuro2[size2 - 1].error = 0;

	double* res = new double[size2 - 1];
	if (res == NULL) {
		return 1;
	}
	clean(res, size2 - 1);


	//Инициализация матриц связи между слоями

	double **weight01 = new double *[size0]; //Веса связей между нулевым и первым слоями
	if (weight01 == NULL) {
		return 1;
	}
	for (int i = 0; i < size0; i++)
	{
		weight01[i] = new double[size1 - 1]; //Количество столбцов на 1 меньше размера след. массива из-за нейрона смещения
		if (weight01[i] == NULL) {
			return 1;
		}
		for (int j = 0; j < size1 - 1; j++)
		{
			weight01[i][j] = (rand() % 100) / 100.0; //Изначально все веса заполняются рандомно
		}
	}
	double **weight12 = new double *[size1]; //Веса связей между первым и вторым слоями
	if (weight12 == NULL) {
		return 1;
	}
	for (int i = 0; i < size1; i++)
	{
		weight12[i] = new double[size2 - 1];
		if (weight12[i] == NULL) {
			return 1;
		}
		for (int j = 0; j < size2 - 1; j++)
		{
			weight12[i][j] = (rand() % 100) / 100.0;
		}
	}

	srand(time(0));
	FILE *data;
	if (fopen_s(&data, path, "rb") != 0) {
		return 3;
	}

	double error = 100;
	while (error > 0.004)
	{
		error = 0;
		for (int n = 0; n < 1000; n++)
		{
			int r = rand() % 100 + 1;
			for (int i = 0; i < r; i++)
			{
				if (fread(&zap, sizeof(zap), 1, data) == 0)
				{ //считывание данных из базы
					rewind(data);
					fread(&zap, sizeof(zap), 1, data);
				}
			}

			
			for (int i = 0, k = rand() % 3, l = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					neuro0[l].out = (double)zap.img[i][j][k] / 255; //заполнение входного слоя
					l++;
				}
			}
			forward(neuro0, size0, neuro1, size1, weight01); //вычисление выходных значений нейронов
			forward(neuro1, size1, neuro2, size2, weight12);

			for (int i = 0; i < size2; i++)
			{
				neuro2[i].error = 0;
			}

			clean(res, size2 - 1);
			if (zap.line_type > 5 || zap.line_type < 0) {
				return 2;
			}
			res[zap.line_type] = 1;
			for (int i = 0; i < size2 - 1; i++) { //вычисление ошибки выходного слоя
				neuro2[i].error = res[i] - neuro2[i].out;
				if (neuro2[i].out > 1 || neuro2[i].out < 1) {
					neuro2[i].error *= 0.1;
				}
				error += neuro2[i].error * neuro2[i].error;
			}


			backward(neuro2, size2, neuro1, size1, weight12); //вычисление ошибки нейронов

			weights_update(neuro1, size1, neuro0, size0, weight01, 0.01);
			weights_update(neuro2, size2, neuro1, size1, weight12, 0.01); //вычисление новых весов связей (0.1 - коэффицент обучения)
		}
		error /= 1000;
		cout << error << endl;
		//getchar();
	}
	FILE *weights;
	if (fopen_s(&weights, "..\\weights.data", "wb") != 0) {
		return 3;
	}
	for (int i = 0; i < size0; i++)
	{
		fwrite(weight01[i], sizeof(double), size1 - 1, weights);
	}
	for (int i = 0; i < size1; i++)
	{
		fwrite(weight12[i], sizeof(double), size2 - 1, weights);
	}
	fclose(weights);
	fclose(data);
	delete neuro0;
	neuro0 = NULL;
	delete neuro1;
	neuro1 = NULL;
	delete neuro2;
	neuro2 = NULL;
	delete res;
	res = NULL;
	for (int i = 0; i < size0; i++) {
		delete weight01[i];
		weight01[i] = NULL;
	}
	delete weight01;
	weight01 = NULL;
	for (int i = 0; i < size0; i++) {
		delete weight12[i];
		weight12[i] = NULL;
	}
	delete weight12;
	weight12 = NULL;
	return 0;
}

int *neural_processing(short arr[4][4])
{
	//Инициализация слоев нейронной сети

	int size0 = 16, size1 = 16, size2 = 5, size3 = 5, size4 = 5, size5 = 5; //размеры массивов нейронов
	neuron *neuro0 = new neuron[size0];										//Нейроны входного слоя. 8 * 8 * 3 под пиксели + нейрон смещения
	for (int i = 0; i < size0; i++)
	{ //ошибка входных нейронов равна 0
		neuro0[i].error = 0;
		neuro0[i].out = 0;
	}
	neuro0[size0 - 1].out = 1;
	neuron *neuro1 = new neuron[size1]; //Нейроны первого слоя (скрытый)
	neuro1[size1 - 1].out = 1;
	neuro1[size1 - 1].error = 0;
	neuron *neuro2 = new neuron[size2]; //Нейроны второго слоя (скрытый)
	neuro2[size2 - 1].out = 1;
	neuro2[size2 - 1].error = 0;
	neuron *neuro3 = new neuron[size3]; //Нейроны третьего слоя (скрытый)
	neuro3[size3 - 1].out = 1;
	neuro3[size3 - 1].error = 0;
	neuron *neuro4 = new neuron[size4]; //Нейроны четвертого слоя (скрытый)
	neuro4[size4 - 1].out = 1;
	neuro4[size4 - 1].error = 0;
	neuron *neuro5 = new neuron[size5]; //Нейроны выходного слоя по одному под каждое направление линии(один нейрон лишний, нужен для упрощения функций)
	neuro5[size5 - 1].out = 1;
	neuro5[size5 - 1].error = 0;

	//Инициализация матриц связи между слоями

	double **weight01 = new double *[size0]; //Веса связей между нулевым и первым слоями
	for (int i = 0; i < size0; i++)
	{
		weight01[i] = new double[size1 - 1]; //Количество столбцов на 1 меньше размера след. массива из-за нейрона смещения
	}
	double **weight12 = new double *[size1]; //Веса связей между первым и вторым слоями
	for (int i = 0; i < size1; i++)
	{
		weight12[i] = new double[size2 - 1];
	}
	double **weight23 = new double *[size2]; //Веса связей между вторым и третьим слоями
	for (int i = 0; i < size2; i++)
	{
		weight23[i] = new double[size3 - 1];
	}
	double **weight34 = new double *[size3]; //Веса связей между третьим и четвертым слоями
	for (int i = 0; i < size3; i++)
	{
		weight34[i] = new double[size4 - 1];
	}
	double **weight45 = new double *[size4]; //Веса связей между четвертым и пятым слоями
	for (int i = 0; i < size4; i++)
	{
		weight45[i] = new double[size5 - 1];
	}

	FILE *weights;
	fopen_s(&weights, "..\\weights.data", "rb");
	for (int i = 0; i < size0; i++)
	{
		fread(weight01[i], sizeof(double), size1 - 1, weights);
	}
	for (int i = 0; i < size1; i++)
	{
		fread(weight12[i], sizeof(double), size2 - 1, weights);
	}
	for (int i = 0; i < size2; i++)
	{
		fread(weight23[i], sizeof(double), size3 - 1, weights);
	}
	for (int i = 0; i < size3; i++)
	{
		fread(weight34[i], sizeof(double), size4 - 1, weights);
	}
	for (int i = 0; i < size4; i++)
	{
		fread(weight45[i], sizeof(double), size5 - 1, weights);
	}

	srand(time(0));

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 1; k++)
			{
				neuro0[i].out = 1 / (1 + exp(-arr[i][j])); //заполнение входного слоя
			}
		}
	}
	forward(neuro0, size0, neuro1, size1, weight01); //вычисление выходных значений нейронов
	forward(neuro1, size1, neuro2, size2, weight12);
	forward(neuro2, size2, neuro3, size3, weight23);
	forward(neuro3, size3, neuro4, size4, weight34);
	forward(neuro4, size4, neuro5, size5, weight45);

	int *out = new int[4];
	for (int i = 0; i < 4; i++)
	{
		if (neuro5[i].out > 0.8)
		{
			out[i] = 1;
		}
	}
	return out;
}

void image_processing(int ***&arr, int ***&res, int size_x, int size_y)
{
	short arr2[4][4];
	int *out;
	for (int i = 0; i < size_x - 7; i++)
	{
		for (int j = 0; j < size_y - 7; j++)
		{
			for (int a = 0; a < 8; a++)
			{
				for (int b = 0; b < 8; b++)
				{
					arr2[a][b] = arr[i + a][j + b][0];
				}
			}
			out = neural_processing(arr2);
			if (out[0] == 1)
			{
				for (int k = -5; k < 5; k++)
				{
					res[i][j + k][0] = 255;
					res[i][j + k][1] = 255;
					res[i][j + k][2] = 255;
				}
			}
			if (out[1] == 1)
			{
				for (int k = -5; k < 5; k++)
				{
					res[i + k][j][0] = 255;
					res[i + k][j][1] = 255;
					res[i + k][j][2] = 255;
				}
			}
			if (out[2] == 1)
			{
				for (int k = -5; k < 5; k++)
				{
					res[i + k][j + k][0] = 255;
					res[i + k][j + k][1] = 255;
					res[i + k][j + k][2] = 255;
				}
			}
			if (out[3] == 1)
			{
				for (int k = -5; k < 5; k++)
				{
					res[i - k][j + k][0] = 255;
					res[i - k][j + k][1] = 255;
					res[i - k][j + k][2] = 255;
				}
			}
		}
	}
}

int main()
{
	char path[100] = "..\\database.data\0";
	neural_learning(path);
}