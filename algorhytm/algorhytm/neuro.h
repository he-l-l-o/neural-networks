#pragma once

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
void forward(neuron* prev, int prev_size, neuron* next, int next_size, double** weight);

//функция вычисления ошибки
//ошибка выходного слоя считается отдельно
void backward(neuron* next, int next_size, neuron* prev, int prev_size, double** weight);

//функция обновления весов
void weights_update(neuron* next, int next_size, neuron* prev, int prev_size, double** weight, double learning_coefficient);

//структура для чтения базы данных
struct entry
{
	short img[4][4][3];
	int line_type;
};

//очистка массива
void clean(double* arr, int size);

//обучение сети
int neural_learning(char* path);

//обработка фрагмента изображения
int neural_processing(short arr[4][4][3], int k);

//обработка изображения
void image_processing(int*** arr, int*** res, int size_x, int size_y);