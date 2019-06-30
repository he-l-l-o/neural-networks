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
	short img[4][4][3];
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

//������� ���������� �����
void weights_update(neuron* next, int next_size, neuron* prev, int prev_size, double** weight, double learning_coefficient)
{
	for (int i = 0; i < next_size - 1; i++)
	{
		for (int j = 0; j < prev_size; j++)
		{
			weight[j][i] += learning_coefficient * next[i].error * prev[j].out;
		}
	}
}

//������� �������
void clean(double* arr, int size) {
	for (int i = 0; i < size; i++) {
		arr[i] = 0;
	}
}

//�������� ����
int neural_learning(char* path)
{
	entry zap; //������ � ���� ������
	zap.line_type = 0;

	//������������� ����� ��������� ����

	long long int size0 = 17, size1 = 17, size2 = 6; //������� �������� ��������
	neuron* neuro0 = new neuron[size0];	//������� �������� ����. 4 * 4 ��� ������� + ������ ��������
	if (neuro0 == NULL) {
		return 1;
	}
	for (int i = 0; i < size0; i++)
	{ //������ ������� �������� ����� 0
		neuro0[i].error = 0;
		neuro0[i].out = 0;
	}
	neuro0[size0 - 1].out = 1;
	neuron* neuro1 = new neuron[size1]; //������� ������� ���� (�������)
	if (neuro1 == NULL) {
		return 1;
	}
	neuro1[size1 - 1].out = 1;
	neuro1[size1 - 1].error = 0;
	neuron* neuro2 = new neuron[size2]; //������� ��������� ����
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


	//������������� ������ ����� ����� ������

	double** weight01 = new double* [size0]; //���� ������ ����� ������� � ������ ������
	if (weight01 == NULL) {
		return 1;
	}
	for (int i = 0; i < size0; i++)
	{
		weight01[i] = new double[size1 - 1]; //���������� �������� �� 1 ������ ������� ����. ������� ��-�� ������� ��������
		if (weight01[i] == NULL) {
			return 1;
		}
		for (int j = 0; j < size1 - 1; j++)
		{
			weight01[i][j] = (rand() % 100) / 100.0; //���������� ��� ���� ����������� ��������
		}
	}
	double** weight12 = new double* [size1]; //���� ������ ����� ������ � ������ ������
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
	FILE* data;
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
				{ //���������� ������ �� ����
					rewind(data);
					fread(&zap, sizeof(zap), 1, data);
				}
			}


			for (int i = 0, k = rand() % 3, l = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					neuro0[l].out = (double)zap.img[i][j][k] / 255; //���������� �������� ����
					l++;
				}
			}
			forward(neuro0, size0, neuro1, size1, weight01); //���������� �������� �������� ��������
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
			for (int i = 0; i < size2 - 1; i++) { //���������� ������ ��������� ����
				neuro2[i].error = res[i] - neuro2[i].out;
				if (neuro2[i].out > 1 || neuro2[i].out < 1) {
					neuro2[i].error *= 0.1;
				}
				error += neuro2[i].error * neuro2[i].error;
			}


			backward(neuro2, size2, neuro1, size1, weight12); //���������� ������ ��������

			weights_update(neuro1, size1, neuro0, size0, weight01, 0.01);
			weights_update(neuro2, size2, neuro1, size1, weight12, 0.01); //���������� ����� ����� ������ (0.1 - ���������� ��������)
		}
		error /= 1000;
		cout << error << endl;
		//getchar();
	}
	FILE* weights;
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
	delete[] neuro0;
	neuro0 = NULL;
	delete[] neuro1;
	neuro1 = NULL;
	delete[] neuro2;
	neuro2 = NULL;
	delete[] res;
	res = NULL;
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
	return 0;
}

//��������� �����������
void image_processing(int*** arr, int*** res, int size_x, int size_y)
{
	short arr2[4][4][3];
	int out;
	for (int i = 0; i < size_x - 3; i++)
	{
		for (int j = 0; j < size_y - 3; j++)
		{
			for (int k = 0; k < 3; k++) {
				for (int a = 0; a < 4; a++)
				{
					for (int b = 0; b < 4; b++)
					{
						arr2[a][b][k] = arr[i + a][j + b][k];
					}
				}
			}
			if (out = neural_processing(arr2, 0) == 0) {
				if (out = neural_processing(arr2, 1) == 0) {
					out = neural_processing(arr2, 2);
				}
			}
			if (i % 3 == 0 && j % 3 == 0) {
				if (out == 1) {
					for (int a = -2; a < 3; a++) {
						if (j + a > 0 && j + a < size_y - 3) {
							arr[i][j + a][0] = 130;
							arr[i][j + a][1] = 130;
							arr[i][j + a][2] = 130;
						}
					}
				}
				if (out == 2) {
					for (int a = -2; a < 3; a++) {
						if (i + a > 0 && i + a < size_x - 3) {
							arr[i + a][j][0] = 130;
							arr[i + a][j][1] = 130;
							arr[i + a][j][2] = 130;
						}
					}
				}
				if (out == 3) {
					for (int a = -2; a < 3; a++) {
						if (i - a > 0 && i - a < size_x - 3 && j + a > 0 && j + a < size_y - 3) {
							arr[i - a][j + a][0] = 130;
							arr[i - a][j + a][1] = 130;
							arr[i - a][j + a][2] = 130;
						}
					}
				}
				if (out == 4) {
					for (int a = -2; a < 3; a++) {
						if (i + a > 0 && i + a < size_x - 3 && j + a > 0 && j + a < size_y - 3) {
							arr[i + a][j + a][0] = 130;
							arr[i + a][j + a][1] = 130;
							arr[i + a][j + a][2] = 130;
						}
					}
				}
			}
			if (out > 0) {
				arr[i][j][0] = 255;
				arr[i][j][1] = 255;
				arr[i][j][2] = 255;
			}
		}
	}
}