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
			next[i].out = 1 + 0.1 * (temp - 1);
		}
		if (temp < 0) {
			next[i].out = 0.1 * temp;
		}
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
			weight[i][j] += learning_coefficient * next[i].error * prev[j].out;
		}
	}
}

//структура для чтения базы данных
struct entry
{
	short img[4][4];
	int line_type;
};

void neural_learning(char *path)
{
	entry zap; //запись в базе данных

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
		for (int j = 0; j < size1 - 1; j++)
		{
			weight01[i][j] = (rand() % 100) / 100.0; //Изначально все веса заполняются рандомно
		}
	}
	double **weight12 = new double *[size1]; //Веса связей между первым и вторым слоями
	for (int i = 0; i < size1; i++)
	{
		weight12[i] = new double[size2 - 1];
		for (int j = 0; j < size2 - 1; j++)
		{
			weight12[i][j] = (rand() % 100) / 100.0;
		}
	}
	double **weight23 = new double *[size2]; //Веса связей между вторым и третьим слоями
	for (int i = 0; i < size2; i++)
	{
		weight23[i] = new double[size3 - 1];
		for (int j = 0; j < size3 - 1; j++)
		{
			weight23[i][j] = (rand() % 100) / 100.0;
		}
	}
	double **weight34 = new double *[size3]; //Веса связей между третьим и четвертым слоями
	for (int i = 0; i < size3; i++)
	{
		weight34[i] = new double[size4 - 1];
		for (int j = 0; j < size4 - 1; j++)
		{
			weight34[i][j] = (rand() % 100) / 100.0;
		}
	}
	double **weight45 = new double *[size4]; //Веса связей между четвертым и пятым слоями
	for (int i = 0; i < size4; i++)
	{
		weight45[i] = new double[size5 - 1];
		for (int j = 0; j < size5 - 1; j++)
		{
			weight45[i][j] = (rand() % 100) / 100.0;
		}
	}

	srand(time(0));
	FILE *data;
	fopen_s(&data, path, "rb");
	for (int i = 0; i < 120; i++)
	{
		if (fread(&zap, sizeof(zap), 1, data) == 0)
		{ //считывание данных из базы
			rewind(data);
			fread(&zap, sizeof(zap), 1, data);
		}
		cout << zap.line_type << endl;
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << zap.img[i][j];
		}
		cout << endl;
	}

	double error = 1;
	while (error > 0.01)
	{
		error = 0;
		for (int n = 0; n < 1000; n++)
		{
			int r = rand() % 500 + 1;
			for (int i = 0; i < r; i++)
			{
				if (fread(&zap, sizeof(zap), 1, data) == 0)
				{ //считывание данных из базы
					rewind(data);
					fread(&zap, sizeof(zap), 1, data);
				}
			}

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					for (int k = 0; k < 1; k++)
					{
						neuro0[i].out = 1 / (1 + exp(-zap.img[i][j])); //заполнение входного слоя
					}
				}
			}
			forward(neuro0, size0, neuro1, size1, weight01); //вычисление выходных значений нейронов
			forward(neuro1, size1, neuro2, size2, weight12);
			forward(neuro2, size2, neuro3, size3, weight23);
			forward(neuro3, size3, neuro4, size4, weight34);
			forward(neuro4, size4, neuro5, size5, weight45);
			if (n % 500 == 0)
				cout << zap.line_type << " | " << neuro5[0].out << " " << neuro5[1].out << " " << neuro5[2].out << " " << neuro5[3].out << endl;

			for (int i = 0; i < 4; i++)
			{
				neuro5[i].error = 0;
			}

			if (zap.line_type == 0)
			{ //вычисление ошибки выходного слоя
				if (neuro5[0].out > 0.2)
				{
					neuro5[0].error = 0.05 - neuro5[0].out;
					error++;
				}
				if (neuro5[1].out > 0.2)
				{
					neuro5[1].error = 0.05 - neuro5[1].out;
					error++;
				}
				if (neuro5[2].out > 0.2)
				{
					neuro5[2].error = 0.05 - neuro5[2].out;
					error++;
				}
				if (neuro5[3].out > 0.2)
				{
					neuro5[3].error = 0.05 - neuro5[3].out;
					error++;
				}
			}
			if (zap.line_type == 1)
			{
				if (neuro5[0].out < 0.8)
				{
					neuro5[0].error = 0.95 - neuro5[0].out;
					error++;
				}
				if (neuro5[1].out > 0.2)
				{
					neuro5[1].error = 0.05 - neuro5[1].out;
					error++;
				}
				if (neuro5[2].out > 0.2)
				{
					neuro5[2].error = 0.05 - neuro5[2].out;
					error++;
				}
				if (neuro5[3].out > 0.2)
				{
					neuro5[3].error = 0.05 - neuro5[3].out;
					error++;
				}
			}
			if (zap.line_type == 2)
			{
				if (neuro5[0].out > 0.2)
				{
					neuro5[0].error = 0.05 - neuro5[0].out;
					error++;
				}
				if (neuro5[1].out < 0.8)
				{
					neuro5[1].error = 0.95 - neuro5[1].out;
					error++;
				}
				if (neuro5[2].out > 0.2)
				{
					neuro5[2].error = 0.05 - neuro5[2].out;
					error++;
				}
				if (neuro5[3].out > 0.2)
				{
					neuro5[3].error = 0.05 - neuro5[3].out;
					error++;
				}
			}
			if (zap.line_type == 3)
			{
				if (neuro5[0].out > 0.2)
				{
					neuro5[0].error = 0.05 - neuro5[0].out;
					error++;
				}
				if (neuro5[1].out > 0.2)
				{
					neuro5[1].error = 0.05 - neuro5[1].out;
					error++;
				}
				if (neuro5[2].out < 0.8)
				{
					neuro5[2].error = 0.95 - neuro5[2].out;
					error++;
				}
				if (neuro5[3].out > 0.2)
				{
					neuro5[3].error = 0.05 - neuro5[3].out;
					error++;
				}
			}
			if (zap.line_type == 4)
			{
				if (neuro5[0].out > 0.2)
				{
					neuro5[0].error = 0.05 - neuro5[0].out;
					error++;
				}
				if (neuro5[1].out > 0.2)
				{
					neuro5[1].error = 0.05 - neuro5[1].out;
					error++;
				}
				if (neuro5[2].out > 0.2)
				{
					neuro5[2].error = 0.05 - neuro5[2].out;
					error++;
				}
				if (neuro5[3].out < 0.8)
				{
					neuro5[3].error = 0.95 - neuro5[3].out;
					error++;
				}
			}

			backward(neuro5, size5, neuro4, size4, weight45); //вычисление ошибки нейронов
			backward(neuro4, size4, neuro3, size3, weight34);
			backward(neuro3, size3, neuro2, size2, weight23);
			backward(neuro2, size2, neuro1, size1, weight12);
			backward(neuro1, size1, neuro0, size0, weight01);

			weights_update(neuro0, size0, neuro1, size1, weight01, 0.1); //вычисление новых весов связей (0.1 - коэффицент обучения)
			weights_update(neuro1, size1, neuro2, size2, weight12, 0.1);
			weights_update(neuro2, size2, neuro3, size3, weight23, 0.1);
			weights_update(neuro3, size3, neuro4, size4, weight34, 0.1);
			weights_update(neuro4, size4, neuro5, size5, weight45, 0.1);
		}
		error /= 1000;
		cout << error << endl;
		//getchar();
	}
	FILE *weights;
	fopen_s(&weights, "..\\weights.data", "wb");
	for (int i = 0; i < size0; i++)
	{
		fwrite(weight01[i], sizeof(double), size1 - 1, weights);
	}
	for (int i = 0; i < size1; i++)
	{
		fwrite(weight12[i], sizeof(double), size2 - 1, weights);
	}
	for (int i = 0; i < size2; i++)
	{
		fwrite(weight23[i], sizeof(double), size3 - 1, weights);
	}
	for (int i = 0; i < size3; i++)
	{
		fwrite(weight34[i], sizeof(double), size4 - 1, weights);
	}
	for (int i = 0; i < size4; i++)
	{
		fwrite(weight45[i], sizeof(double), size5 - 1, weights);
	}
	fclose(weights);
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