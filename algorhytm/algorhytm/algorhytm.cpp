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

//������� ���������� �������� ���������� ���� ����
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

//������� ���������� ������
//������ ��������� ���� ��������� ��������
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

//������� ���������� �����
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

//��������� ��� ������ ���� ������
struct entry
{
	short img[4][4][3];
	int line_type;
};

void neural_learning(char *path)
{
	entry zap; //������ � ���� ������

	//������������� ����� ��������� ����

	int size0 = 17, size1 = 17, size2 = 5; //������� �������� ��������
	neuron *neuro0 = new neuron[size0];										//������� �������� ����. 4 * 4 ��� ������� + ������ ��������
	for (int i = 0; i < size0; i++)
	{ //������ ������� �������� ����� 0
		neuro0[i].error = 0;
		neuro0[i].out = 0;
	}
	neuro0[size0 - 1].out = 1;
	neuron *neuro1 = new neuron[size1]; //������� ������� ���� (�������)
	neuro1[size1 - 1].out = 1;
	neuro1[size1 - 1].error = 0;
	neuron *neuro2 = new neuron[size2]; //������� ������� ���� (�������)
	neuro2[size2 - 1].out = 1;
	neuro2[size2 - 1].error = 0;

	//������������� ������ ����� ����� ������

	new double[size1 - 1];

	double **weight01 = new double *[size0]; //���� ������ ����� ������� � ������ ������
	for (int i = 0; i < size0; i++)
	{
		weight01[i] = new double[size1 - 1]; //���������� �������� �� 1 ������ ������� ����. ������� ��-�� ������� ��������
		for (int j = 0; j < size1 - 1; j++)
		{
			weight01[i][j] = (rand() % 100) / 100.0; //���������� ��� ���� ����������� ��������
		}
	}
	double **weight12 = new double *[size1]; //���� ������ ����� ������ � ������ ������
	for (int i = 0; i < size1; i++)
	{
		weight12[i] = new double[size2 - 1];
		for (int j = 0; j < size2 - 1; j++)
		{
			weight12[i][j] = (rand() % 100) / 100.0;
		}
	}

	srand(time(0));
	FILE *data;
	fopen_s(&data, path, "rb");

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
				{ //���������� ������ �� ����
					rewind(data);
					fread(&zap, sizeof(zap), 1, data);
				}
			}

			
			for (int i = 0, k = rand() % 3, l = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					neuro0[l].out = zap.img[i][j][k] / 255; //���������� �������� ����
					l++;
				}
			}
			forward(neuro0, size0, neuro1, size1, weight01); //���������� �������� �������� ��������
			forward(neuro1, size1, neuro2, size2, weight12);
			if (n % 500 == 0)
				cout << zap.line_type << " | " << neuro2[0].out << " " << neuro2[1].out << " " << neuro2[2].out << " " << neuro2[3].out << endl;

			for (int i = 0; i < 4; i++)
			{
				neuro2[i].error = 0;
			}

			if (zap.line_type == 0)
			{ //���������� ������ ��������� ����
				if (neuro2[0].out > 0.2)
				{
					neuro2[0].error = 0.05 - neuro2[0].out;
					error++;
				}
				if (neuro2[1].out > 0.2)
				{
					neuro2[1].error = 0.05 - neuro2[1].out;
					error++;
				}
				if (neuro2[2].out > 0.2)
				{
					neuro2[2].error = 0.05 - neuro2[2].out;
					error++;
				}
				if (neuro2[3].out > 0.2)
				{
					neuro2[3].error = 0.05 - neuro2[3].out;
					error++;
				}
			}
			if (zap.line_type == 1)
			{
				if (neuro2[0].out < 0.8)
				{
					neuro2[0].error = 0.95 - neuro2[0].out;
					error++;
				}
				if (neuro2[1].out > 0.2)
				{
					neuro2[1].error = 0.05 - neuro2[1].out;
					error++;
				}
				if (neuro2[2].out > 0.2)
				{
					neuro2[2].error = 0.05 - neuro2[2].out;
					error++;
				}
				if (neuro2[3].out > 0.2)
				{
					neuro2[3].error = 0.05 - neuro2[3].out;
					error++;
				}
			}
			if (zap.line_type == 2)
			{
				if (neuro2[0].out > 0.2)
				{
					neuro2[0].error = 0.05 - neuro2[0].out;
					error++;
				}
				if (neuro2[1].out < 0.8)
				{
					neuro2[1].error = 0.95 - neuro2[1].out;
					error++;
				}
				if (neuro2[2].out > 0.2)
				{
					neuro2[2].error = 0.05 - neuro2[2].out;
					error++;
				}
				if (neuro2[3].out > 0.2)
				{
					neuro2[3].error = 0.05 - neuro2[3].out;
					error++;
				}
			}
			if (zap.line_type == 3)
			{
				if (neuro2[0].out > 0.2)
				{
					neuro2[0].error = 0.05 - neuro2[0].out;
					error++;
				}
				if (neuro2[1].out > 0.2)
				{
					neuro2[1].error = 0.05 - neuro2[1].out;
					error++;
				}
				if (neuro2[2].out < 0.8)
				{
					neuro2[2].error = 0.95 - neuro2[2].out;
					error++;
				}
				if (neuro2[3].out > 0.2)
				{
					neuro2[3].error = 0.05 - neuro2[3].out;
					error++;
				}
			}
			if (zap.line_type == 4)
			{
				if (neuro2[0].out > 0.2)
				{
					neuro2[0].error = 0.05 - neuro2[0].out;
					error++;
				}
				if (neuro2[1].out > 0.2)
				{
					neuro2[1].error = 0.05 - neuro2[1].out;
					error++;
				}
				if (neuro2[2].out > 0.2)
				{
					neuro2[2].error = 0.05 - neuro2[2].out;
					error++;
				}
				if (neuro2[3].out < 0.8)
				{
					neuro2[3].error = 0.95 - neuro2[3].out;
					error++;
				}
			}

			backward(neuro2, size2, neuro1, size1, weight12); //���������� ������ ��������
			backward(neuro1, size1, neuro0, size0, weight01);

			weights_update(neuro2, size2, neuro1, size1, weight12, 0.1); //���������� ����� ����� ������ (0.1 - ���������� ��������)
			weights_update(neuro1, size1, neuro0, size0, weight01, 0.1);
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
	fclose(weights);
}

int *neural_processing(short arr[4][4])
{
	//������������� ����� ��������� ����

	int size0 = 16, size1 = 16, size2 = 5, size3 = 5, size4 = 5, size5 = 5; //������� �������� ��������
	neuron *neuro0 = new neuron[size0];										//������� �������� ����. 8 * 8 * 3 ��� ������� + ������ ��������
	for (int i = 0; i < size0; i++)
	{ //������ ������� �������� ����� 0
		neuro0[i].error = 0;
		neuro0[i].out = 0;
	}
	neuro0[size0 - 1].out = 1;
	neuron *neuro1 = new neuron[size1]; //������� ������� ���� (�������)
	neuro1[size1 - 1].out = 1;
	neuro1[size1 - 1].error = 0;
	neuron *neuro2 = new neuron[size2]; //������� ������� ���� (�������)
	neuro2[size2 - 1].out = 1;
	neuro2[size2 - 1].error = 0;
	neuron *neuro3 = new neuron[size3]; //������� �������� ���� (�������)
	neuro3[size3 - 1].out = 1;
	neuro3[size3 - 1].error = 0;
	neuron *neuro4 = new neuron[size4]; //������� ���������� ���� (�������)
	neuro4[size4 - 1].out = 1;
	neuro4[size4 - 1].error = 0;
	neuron *neuro5 = new neuron[size5]; //������� ��������� ���� �� ������ ��� ������ ����������� �����(���� ������ ������, ����� ��� ��������� �������)
	neuro5[size5 - 1].out = 1;
	neuro5[size5 - 1].error = 0;

	//������������� ������ ����� ����� ������

	double **weight01 = new double *[size0]; //���� ������ ����� ������� � ������ ������
	for (int i = 0; i < size0; i++)
	{
		weight01[i] = new double[size1 - 1]; //���������� �������� �� 1 ������ ������� ����. ������� ��-�� ������� ��������
	}
	double **weight12 = new double *[size1]; //���� ������ ����� ������ � ������ ������
	for (int i = 0; i < size1; i++)
	{
		weight12[i] = new double[size2 - 1];
	}
	double **weight23 = new double *[size2]; //���� ������ ����� ������ � ������� ������
	for (int i = 0; i < size2; i++)
	{
		weight23[i] = new double[size3 - 1];
	}
	double **weight34 = new double *[size3]; //���� ������ ����� ������� � ��������� ������
	for (int i = 0; i < size3; i++)
	{
		weight34[i] = new double[size4 - 1];
	}
	double **weight45 = new double *[size4]; //���� ������ ����� ��������� � ����� ������
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
				neuro0[i].out = 1 / (1 + exp(-arr[i][j])); //���������� �������� ����
			}
		}
	}
	forward(neuro0, size0, neuro1, size1, weight01); //���������� �������� �������� ��������
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