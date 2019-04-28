#include "pch.h"
#include <iostream>
#include <cmath>

struct neuron{
	double out, error;
};

//������� ���������� �������� ���������� ���� ����
void forward(neuron *prev, int prev_size, neuron *next, int next_size, double **weight) {
	int temp;
	for (int i = 0; i < next_size - 1; i++) {
		temp = 0;
		for (int j = 0; j < prev_size; j++) {
			temp += prev[j].out * weight[j][i];
		}
		next[i].out = 1 / (1 + exp(-temp));
	}
}

int main()
{
	//������������� ����� ��������� ����
	neuron *neuro0 = new neuron[17]; //������� �������� ����. 16 ��� ������� + ������ �������� //�������� �����-�����
	neuro0[16].out = 1;
	neuro0[16].error = 0;
	neuron *neuro1 = new neuron[10];
	neuro1[9].out = 1;
	neuro1[9].error = 0;
	neuron *neuro2 = new neuron[7];
	neuro2[6].out = 1;
	neuro2[6].error = 0;
	neuron *neuro3 = new neuron[4]; //������� ��������� ���� �� ������ ��� ������ ����������� �����

	//������������� ������ ����� ����� ������
	double **weight01 = new double*[17];
	for (int i = 0; i < 17; i++) {
		weight01[i] = new double[9]; //���������� �������� �� 1 ������ ������� ����. ������� ��-�� ������� ��������
		for (int j = 0; j < 9; j++) {
			weight01[i][j] = 1; //���������� ��� ���� ����������� ���������
		}
	}
	double **weight12 = new double*[10];
	for (int i = 0; i < 10; i++) {
		weight12[i] = new double[6];
		for (int j = 0; j < 6; j++) {
			weight12[i][j] = 1;
		}
	}
	double **weight23 = new double*[7];
	for (int i = 0; i < 7; i++) {
		weight23[i] = new double[4];
		for (int j = 0; j < 4; j++) {
			weight23[i][j] = 1;
		}
	}
}