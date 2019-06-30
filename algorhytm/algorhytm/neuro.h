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

//������� ���������� �������� ���������� ���� ����
void forward(neuron* prev, int prev_size, neuron* next, int next_size, double** weight);

//������� ���������� ������
//������ ��������� ���� ��������� ��������
void backward(neuron* next, int next_size, neuron* prev, int prev_size, double** weight);

//������� ���������� �����
void weights_update(neuron* next, int next_size, neuron* prev, int prev_size, double** weight, double learning_coefficient);

//��������� ��� ������ ���� ������
struct entry
{
	short img[4][4];
	int line_type;
};

//������� �������
void clean(double* arr, int size);

//�������� ����
int neural_learning(char* path);

//��������� ��������� �����������
int neural_processing(short arr[4][4][3], int k);

//��������� �����������
void image_processing(int*** arr, int*** res, int size_x, int size_y);