#include "pch.h"
#include <iostream>
#include <cmath>
//#include <string>
#include <random>
#include <ctime>
using namespace std;

struct neuron{
	double out, error;
};

//функция вычисления значений следующего слоя сети
void forward(neuron *prev, int prev_size, neuron *next, int next_size, double **weight) {
	double temp;
	for (int i = 0; i < next_size - 1; i++) {
		temp = 0;
		for (int j = 0; j < prev_size; j++) {
			temp += prev[j].out * weight[j][i];
		}
		next[i].out = 1 / (1 + exp(-temp));
	}
}

//функция вычисления ошибки
//ошибка выходного слоя считается отдельно
void backward(neuron *next, int next_size, neuron *prev, int prev_size, double **weight) {
	for (int i = 0; i < prev_size - 1; i++) {
		prev[i].error = 0;
		for (int j = 0; j < next_size - 1; j++) {
			prev[i].error += next[j].error * weight[i][j];
		}
	}
}

//функция обновления весов
void weights_update(neuron *prev, int prev_size, neuron *next, int next_size, double **weight, double learning_coefficient) {
	for (int i = 0; i < prev_size; i++) {
		for (int j = 0; j < next_size; j++) {
			weight[i][j] += learning_coefficient * next[j].error * next[j].out * (1 - next[j].out) * prev[i].out;
		}
	}
}

int main()
{
	//Инициализация слоев нейронной сети

 	int size0 = 17, size1 = 10, size2 = 7, size3 = 5; //размеры массивов нейронов
	neuron *neuro0 = new neuron[size0]; //Нейроны входного слоя. 16 под пиксели + нейрон смещения //временно черно-белые
	for (int i = 0; i < size0; i++) { //ошибка входных нейронов равна 0
		neuro0[i].error = 0;
		neuro0[i].out = 0;
	}
	neuro0[16].out = 1;
	neuron *neuro1 = new neuron[size1]; //Нейроны первого слоя (скрытый)
	neuro1[9].out = 1;
	neuro1[9].error = 0;
	neuron *neuro2 = new neuron[size2]; //Нейроны второго слоя (скрытый)
	neuro2[6].out = 1;
	neuro2[6].error = 0;
	neuron *neuro3 = new neuron[size3]; //Нейроны выходного слоя по одному под каждое направление линии(один нейрон лишний, нужен для упрощения функций)

	//Инициализация матриц связи между слоями

	double **weight01 = new double*[size0]; //Веса связей между нулевым и первым слоями
	for (int i = 0; i < size0; i++) {
		weight01[i] = new double[size1 - 1]; //Количество столбцов на 1 меньше размера след. массива из-за нейрона смещения
		for (int j = 0; j < size1 - 1; j++) {
			weight01[i][j] = (rand() % 100) / 100.0; //Изначально все веса заполняются еденицами
		}
	}
	double **weight12 = new double*[size1]; //Веса связей между первым и вторым слоями
	for (int i = 0; i < size1; i++) {
		weight12[i] = new double[size2 - 1];
		for (int j = 0; j < size2 - 1; j++) {
			weight12[i][j] = (rand() % 100) / 100.0;
		}
	}
	double **weight23 = new double*[size2]; //Веса связей между вторым и третьим слоями
	for (int i = 0; i < size2; i++) {
		weight23[i] = new double[size3 - 1];
		for (int j = 0; j < size3 - 1; j++) {
			weight23[i][j] = (rand() % 100) / 100.0;
		}
	}

	srand(time(0));
	FILE *data;
	fopen_s(&data, "..\\data.txt", "rt");
	char *input = new char[100];
	int string_number;
	double error = 1;
	while (error > 0.01) {
		error = 0;
		for (int n = 0; n < 200; n++) {
			string_number = rand() % 16;
			for (int i = 0; i < string_number; i++) {
				if (fgets(input, 100, data) == NULL) {
					rewind(data);
					fgets(input, 100, data);
				}
			}

			for (int i = 0; i < 16; i += 2) {
				neuro0[i / 2].out = input[i] - '0';
			}
			forward(neuro0, size0, neuro1, size1, weight01);
			forward(neuro1, size1, neuro2, size2, weight12);
			forward(neuro2, size2, neuro3, size3, weight23);
			if(n % 50 == 0)
			cout << input[18] << " " << input[20] << " | " << neuro3[0].out << " " << neuro3[1].out << endl;
			

			if (abs(input[18] - '0' - neuro3[0].out) < 0.2) {
				neuro3[0].error = 0;
			}
			else {
				neuro3[0].error = input[18] - '0' - neuro3[0].out;
				error++;
			}

			if (abs(input[20] - '0' - neuro3[1].out) < 0.2) {
				neuro3[1].error = 0;
			}
			else {
				neuro3[1].error = input[20] - '0' - neuro3[1].out;
				error++;
			}
			neuro3[2].error = 0 - neuro3[2].out;
			neuro3[3].error = 0 - neuro3[3].out;

			backward(neuro3, size3, neuro2, size2, weight23);
			backward(neuro2, size2, neuro1, size1, weight12);
			backward(neuro1, size1, neuro0, size0, weight01);

			weights_update(neuro0, size0, neuro1, size1, weight01, 0.1);
			weights_update(neuro1, size1, neuro2, size2, weight12, 0.1);
			weights_update(neuro2, size2, neuro3, size3, weight23, 0.1);

		}
		error  /= 200;
		cout << error << endl;
		//getchar();
	}


}