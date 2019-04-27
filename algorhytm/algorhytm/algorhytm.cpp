#include "pch.h"
#include <iostream>

struct neuron{
	double out, error;
};

int main()
{
	//Инициализация слоев нейронной сети
	neuron *n0 = new neuron[17]; //Нейроны входного слоя. 16 под пиксели + нейрон смещения //временно черно-белые
	n0[16].out = 1;
	n0[16].error = 0;
	neuron *n1 = new neuron[10];
	n1[9].out = 1;
	n1[9].error = 0;
	neuron *n2 = new neuron[7];
	n2[6].out = 1;
	n2[6].error = 0;
	neuron *n3 = new neuron[4]; //Нейроны выходного слоя по одному под каждое направление линии

	//Инициализация матриц связи между слоями
	double **w01 = new double*[17];
	for (int i = 0; i < 17; i++) {
		w01[i] = new double[9]; //Количество столбцов на 1 меньше размера след. массива из-за нейрона смещения
		for (int j = 0; j < 9; j++) {
			w01[i][j] = 1; //Изначально все веса заполняются еденицами
		}
	}
	double **w12 = new double*[10];
	for (int i = 0; i < 10; i++) {
		w12[i] = new double[6];
		for (int j = 0; j < 6; j++) {
			w12[i][j] = 1;
		}
	}
	double **w23 = new double*[7];
	for (int i = 0; i < 7; i++) {
		w23[i] = new double[4];
		for (int j = 0; j < 4; j++) {
			w23[i][j] = 1;
		}
	}
}